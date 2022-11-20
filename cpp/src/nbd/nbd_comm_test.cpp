#include <iostream>
#include <linux/nbd.h>
#include <netinet/in.h>
#include <argp.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "nbd_comm.hpp"
#include "../reactor/reactor.hpp"
#include "FileDesc.hpp"
#include "../Event/event.hpp"
#include "../factory/factory.hpp"
#include "../singleton/singleton.hpp"
#include "../thread_pool/thread_pool.hpp"

using namespace ilrd;
/* BUSE callbacks */
static void *data;

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

Event *CreateReadEvent(struct args &arg)
{
    return new ReadEvent(arg);
}

Event *CreateWriteEvent(struct args &arg)
{
    return new WriteEvent(arg);
}

static int read_imp(void *buf, u_int32_t len, u_int64_t offset, void *userdata)
{
    Factory<Event, std::string, struct args &> *factory = Singleton<Factory<Event, std::string, struct args &>>::GetInstance();
    Event *event = factory->Create("RE", (struct args &)buf);
    std::shared_ptr<Task> task(new EventTask(event));
    ThreadPool *tp = Singleton<ThreadPool>::GetInstance();
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
    Factory<Event, std::string, struct args &> *factory = Singleton<Factory<Event, std::string, struct args &>>::GetInstance();
    Event *event = factory->Create("WE", (struct args &)buf);
    std::shared_ptr<Task> task(new EventTask(event));
    ThreadPool *tp = Singleton<ThreadPool>::GetInstance();
    tp->Add(task, PRIORITY::HIGH);

    if (*(int *)userdata)
        fprintf(stderr, "W - %lu, %u\n", offset, len);
    memcpy((char *)data + offset, buf, len);

    return 0;
}

static void disk_imp(void *userdata)
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
    .options = options,
    .parser = parse_opt,
    .args_doc = "SIZE DEVICE",
    .doc = "BUSE virtual block device that stores its content in memory.\n"
           "`SIZE` accepts suffixes K, M, G. `DEVICE` is path to block device, for example \"/dev/nbd0\".",
};

int main(int argc, char *argv[])
{
    struct arguments arguments = {
        .verbose = 0,
    };
    argp_parse(&argp, argc, argv, 0, 0, &arguments);

    struct buse_operations aop = {
        .read = read_imp,
        .write = write_imp,
        .disc = disk_imp,
        .flush = flush_imp,
        .trim = trim_imp,
        .size = arguments.size,
    };

    Factory<Event, std::string, struct args &> *factory = Singleton<Factory<Event, std::string, struct args &>>::GetInstance();
    factory->Add("RE", CreateReadEvent);
    factory->Add("WE", CreateWriteEvent);
    Reactor *reactor = new Reactor();
    NbdComm nbdcomm(reactor, argv[2], &aop, (void *)&arguments.verbose);
    ThreadPool *tp = Singleton<ThreadPool>::GetInstance();

    data = malloc(aop.size);
    if (data == NULL)
    {
        err(EXIT_FAILURE, "failed to alloc space for data");
    }

    tp->Run();
    reactor->Run();

    return 0;
}
