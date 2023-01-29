#include <iostream>
#include <linux/nbd.h>
#include <netinet/in.h>
#include <argp.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <sys/types.h>

#include "nbd_comm.hpp"
#include "reactor.hpp"
#include "FileDesc.hpp"
#include "event.hpp"
#include "factory.hpp"
#include "thread_pool.hpp"
#include "handleton.hpp"

#ifndef BUSE_DEBUG
#define BUSE_DEBUG (0)
#endif

#ifdef WORDS_BIGENDIAN
u_int64_t ntohll(u_int64_t a)
{
    return a;
}
#else
u_int64_t ntohll(u_int64_t a)
{
    u_int32_t lo = a & 0xffffffff;
    u_int32_t hi = a >> 32U;
    lo = ntohl(lo);
    hi = ntohl(hi);
    return ((u_int64_t)lo) << 32U | hi;
}
#endif
#define htonll ntohll

static void *data;

using namespace ilrd;

class EventTask : public Task
{
public:
    EventTask(Event *event) : m_event(event)
    {
        // empty
    }
    void virtual operator()()
    {
        (*m_event)();
    }
    void LogTaskEvent();
    ~EventTask()
    {
        delete m_event;
    }

private:
    Event *m_event;
};

Event *CreateReadEvent(args_t &arg)
{
    return new ReadEvent(arg);
}

Event *CreateWriteEvent(args_t &arg)
{
    return new WriteEvent(arg);
}

static int read_imp(void *buf, u_int32_t len, u_int64_t offset, void *userdata)
{
    Factory<Event, std::string, args_t &> *factory = Handleton<Factory<Event, std::string, args_t &>>::GetInstance();
    Event *event = factory->Create("RE", (args_t &)buf);
    std::shared_ptr<Task> task(new EventTask(event));
    ThreadPool *tp = Handleton<ThreadPool>::GetInstance();
    tp->Add(task, PRIORITY::HIGH);

    if (*(int *)userdata)
    {
        fprintf(stderr, "R - %lu, %u\n", offset, len);
    }
    memcpy(buf, (char *)data + offset, len);

    return 0;
}

static int write_imp(const void *buf, u_int32_t len, u_int64_t offset, void *userdata)
{
    Factory<Event, std::string, args_t &> *factory = Handleton<Factory<Event, std::string, args_t &>>::GetInstance();
    Event *event = factory->Create("WE", (args_t &)buf);
    std::shared_ptr<Task> task(new EventTask(event));
    ThreadPool *tp = Handleton<ThreadPool>::GetInstance();
    tp->Add(task, PRIORITY::HIGH);

    if (*(int *)userdata)
        fprintf(stderr, "W - %lu, %u\n", offset, len);
    memcpy((char *)data + offset, buf, len);

    return 0;
}

static void disc_imp(void *userdata)
{
    if (*(int *)userdata)
        fprintf(stderr, "Received a disconnect request.\n");
}

static int flush_imp(void *userdata)
{
    if (*(int *)userdata)
        fprintf(stderr, "Received a flush request.\n");
    return 0;
}

static int trim_imp(u_int64_t from, u_int32_t len, void *userdata)
{
    if (*(int *)userdata)
        fprintf(stderr, "T - %lu, %u\n", from, len);
    return 0;
}

static int read_all(int fd, char *buf, size_t count)
{
    int bytes_read;

    while (count > 0)
    {
        bytes_read = read(fd, buf, count);
        assert(bytes_read > 0);
        buf += bytes_read;
        count -= bytes_read;
    }
    assert(count == 0);

    return 0;
}

static int write_all(int fd, char *buf, size_t count)
{
    int bytes_written;

    while (count > 0)
    {
        bytes_written = write(fd, buf, count);
        assert(bytes_written > 0);
        buf += bytes_written;
        count -= bytes_written;
    }
    assert(count == 0);

    return 0;
}

/* argument parsing using argp */
static struct argp_option options[] = {
    {"verbose", 'v', 0, 0, "Produce verbose output", 0},
    {0},
};

struct arguments
{
    unsigned long long size;
    char *device;
    int verbose;
};

static unsigned long long strtoull_with_prefix(const char *str, char **end)
{
    unsigned long long v = strtoull(str, end, 0);
    switch (**end)
    {
    case 'K':
        v *= 1024;
        *end += 1;
        break;
    case 'M':
        v *= 1024 * 1024;
        *end += 1;
        break;
    case 'G':
        v *= 1024 * 1024 * 1024;
        *end += 1;
        break;
    }
    return v;
}

/* Parse a single option. */
static error_t parse_opt(int key, char *arg, struct argp_state *state)
{
    struct arguments *arguments = (struct arguments *)state->input;
    char *endptr;

    switch (key)
    {

    case 'v':
        arguments->verbose = 1;
        break;

    case ARGP_KEY_ARG:
        switch (state->arg_num)
        {

        case 0:
            arguments->size = strtoull_with_prefix(arg, &endptr);
            if (*endptr != '\0')
            {
                /* failed to parse integer */
                errx(EXIT_FAILURE, "SIZE must be an integer");
            }
            break;

        case 1:
            arguments->device = arg;
            break;

        default:
            /* Too many arguments. */
            return ARGP_ERR_UNKNOWN;
        }
        break;

    case ARGP_KEY_END:
        if (state->arg_num < 2)
        {
            warnx("not enough arguments");
            argp_usage(state);
        }
        break;

    default:
        return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

static struct argp argp = {
    options,
    parse_opt,
    "SIZE DEVICE",
    "BUSE virtual block device that stores its content in memory.\n"
    "`SIZE` accepts suffixes K, M, G. `DEVICE` is path to block device, for example \"/dev/nbd0\".",
};

static void ReadCallback(int sk, const struct buse_operations *aop, void *userdata)
{
    u_int64_t from;
    u_int32_t len;
    ssize_t bytes_read;
    struct nbd_request request;
    struct nbd_reply reply;
    void *chunk;

    reply.magic = htonl(NBD_REPLY_MAGIC);
    reply.error = htonl(0);
    bytes_read = read(sk, &request, sizeof(request));
    assert(bytes_read == sizeof(request));
    memcpy(reply.handle, request.handle, sizeof(reply.handle));
    reply.error = htonl(0);

    len = ntohl(request.len);
    from = ntohll(request.from);
    assert(request.magic == htonl(NBD_REQUEST_MAGIC));

    switch (ntohl(request.type))
    {
    case NBD_CMD_READ:
        std::cout << "inside NBD_CMD_READ\n";
        if (BUSE_DEBUG)
            fprintf(stderr, "Request for read of size %d\n", len);
        /* Fill with zero in case actual read is not implemented */
        chunk = malloc(len);
        if (aop->read)
        {
            reply.error = aop->read(chunk, len, from, userdata);
        }
        else
        {
            /* If user not specified read operation, return EPERM error */
            reply.error = htonl(EPERM);
        }
        write_all(sk, (char *)&reply, sizeof(struct nbd_reply));
        write_all(sk, (char *)chunk, len);

        free(chunk);
        break;
    case NBD_CMD_WRITE:
        std::cout << "inside NBD_CMD_WRITE\n";
        if (BUSE_DEBUG)
            fprintf(stderr, "Request for write of size %d\n", len);
        chunk = malloc(len);
        read_all(sk, (char *)chunk, len);
        if (aop->write)
        {
            reply.error = aop->write(chunk, len, from, userdata);
        }
        else
        {
            /* If user not specified write operation, return EPERM error */
            reply.error = htonl(EPERM);
        }
        free(chunk);
        write_all(sk, (char *)&reply, sizeof(struct nbd_reply));
        break;
    case NBD_CMD_DISC:
        std::cout << "inside NBD_CMD_DISC\n";

        if (BUSE_DEBUG)
            fprintf(stderr, "Got NBD_CMD_DISC\n");
        /* Handle a disconnect request. */
        if (aop->disc)
        {
            aop->disc(userdata);
        }
#ifdef NBD_FLAG_SEND_FLUSH
    case NBD_CMD_FLUSH:
        std::cout << "inside NBD_CMD_FLUSH\n";

        if (BUSE_DEBUG)
            fprintf(stderr, "Got NBD_CMD_FLUSH\n");
        if (aop->flush)
        {
            reply.error = aop->flush(userdata);
        }
        write_all(sk, (char *)&reply, sizeof(struct nbd_reply));
        break;
#endif
#ifdef NBD_FLAG_SEND_TRIM
    case NBD_CMD_TRIM:
        std::cout << "inside NBD_CMD_TRIM\n";

        if (BUSE_DEBUG)
            fprintf(stderr, "Got NBD_CMD_TRIM\n");
        if (aop->trim)
        {
            reply.error = aop->trim(from, len, userdata);
        }
        write_all(sk, (char *)&reply, sizeof(struct nbd_reply));
        break;
#endif
    default:
        assert(0);
    }

    if (bytes_read == -1)
    {
        throw std::runtime_error("error reading userside of nbd socket");
    }
}

int main(int argc, char *argv[])
{
    struct arguments arguments;
    arguments.verbose = 0;
    argp_parse(&argp, argc, argv, 0, 0, &arguments);

    struct buse_operations aop = {NULL, NULL, NULL, NULL, NULL, 0, 0, 0};
    aop.read = read_imp;
    aop.write = write_imp;
    aop.disc = disc_imp;
    aop.flush = flush_imp;
    aop.trim = trim_imp;
    aop.size = arguments.size;

    Factory<Event, std::string, args_t &> *factory = Handleton<Factory<Event, std::string, args_t &>>::GetInstance();
    factory->Add("RE", CreateReadEvent);
    factory->Add("WE", CreateWriteEvent);
    Reactor *reactor = new Reactor();
    NbdComm nbdcomm;

    ThreadPool *tp = Handleton<ThreadPool>::GetInstance();

    data = malloc(aop.size);
    if (data == NULL)
    {
        err(EXIT_FAILURE, "failed to alloc space for data");
    }

    int fd_socket = nbdcomm.GetNbdSocket().GetFd();
    reactor->Add(fd_socket, std::bind(ReadCallback, fd_socket, &aop, (void *)&arguments.verbose), Operation::READ);
    tp->Run();
    reactor->Run();

    return 0;
}
