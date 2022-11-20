
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <exception>
#include <linux/nbd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <assert.h>
#include <sys/wait.h>
#include <errno.h>
#include <err.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <thread>
#include <chrono>
#include <semaphore>

#include "nbd_comm.hpp"
#include "FileDesc.hpp"
#include "../reactor/reactor.hpp"

#ifndef BUSE_DEBUG
#define BUSE_DEBUG (0)
#endif

/*
 * These helper functions were taken from cliserv.h in the nbd distribution.
 */
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

namespace ilrd
{
    static int set_sigaction(int sig, const struct sigaction *act);
    static void ReadCallback(int sk, const struct buse_operations *aop, void *userdata);
    static void disconnect_nbd(int m_nbd);
    static const size_t mb_size = 1048576;
    static void BlockSignals();
    static void ConfigureNbd(int sk, int nbd);
    static void EnableSignals();
    static int PrepareNbd(std::string dev_file, const struct buse_operations *aop);

    NbdComm::NbdComm(Reactor *reactor, std::string dev_file, const struct buse_operations *aop, void *userdata)
        : m_aop(aop), m_userdata(userdata), m_socket(FileDesc(0)), m_nbd(-1)
    {
        int sp[2];
        int nbd, err, sk, flags;

        err = socketpair(AF_UNIX, SOCK_STREAM, 0, sp);
        if (err == -1)
        {
            std::cout << "socketpair failed.\n";
        }

        nbd = PrepareNbd(dev_file, aop);

        m_pid = fork();
        if (m_pid == 0)
        {
            BlockSignals();

            close(sp[0]);
            sk = sp[1];

            ConfigureNbd(sk, nbd);
        }

        /* Parent handles termination signals by terminating nbd device. */
        assert(m_nbd == -1);
        m_nbd = nbd;

        EnableSignals();

        close(sp[1]);
        reactor->Add(sp[0], std::bind(ReadCallback, sp[0], m_aop, m_userdata), Operation::READ);
    }

    static int PrepareNbd(std::string dev_file, const struct buse_operations *aop)
    {
        int err, nbd;
        nbd = open(dev_file.c_str(), O_RDWR);
        if (nbd == -1)
        {
            throw std::runtime_error("couldn't open nbd.\n");
        }

        if (aop->blksize)
        {
            if (ioctl(nbd, NBD_SET_BLKSIZE, aop->blksize) == -1)
            {
                throw std::runtime_error("couldn't NBD_SET_BLKSIZE nbd.\n");
            }
        }
        if (aop->size)
        {
            if (ioctl(nbd, NBD_SET_SIZE, aop->size) == -1)
            {
                throw std::runtime_error("couldn't NBD_SET_SIZE nbd.\n");
            }
        }
        if (aop->size_blocks)
        {
            if (ioctl(nbd, NBD_SET_SIZE_BLOCKS, aop->size_blocks) == -1)
            {
                throw std::runtime_error("couldn't NBD_SET_SIZE_BLOCKS nbd.\n");
            }
        }

        err = ioctl(nbd, NBD_CLEAR_SOCK);
        if (err == -1)
        {
            throw std::runtime_error("ioctl(nbd, NBD_CLEAR_SOCK) failed.\n");
        }

        return nbd;
    }

    static void BlockSignals()
    {
        sigset_t sigset;
        if (
            sigfillset(&sigset) != 0 ||
            sigprocmask(SIG_SETMASK, &sigset, NULL) != 0)
        {
            throw std::runtime_error("error: failed to block signals in child");
        }
    }

    static void EnableSignals()
    {
        struct sigaction act;
        act.sa_handler = disconnect_nbd;
        act.sa_flags = SA_RESTART;
        if (
            sigemptyset(&act.sa_mask) != 0 ||
            sigaddset(&act.sa_mask, SIGINT) != 0 ||
            sigaddset(&act.sa_mask, SIGTERM) != 0)
        {
            throw std::runtime_error("failed to prepare signal mask in parent");
        }
        if (
            set_sigaction(SIGINT, &act) != 0 ||
            set_sigaction(SIGTERM, &act) != 0)
        {
            throw std::runtime_error("failed to register signal handlers in parent");
        }
    }

    static void ConfigureNbd(int sk, int nbd)
    {
        int flags, err;

        if (ioctl(nbd, NBD_SET_SOCK, sk) == -1)
        {
            throw std::runtime_error("ioctl(nbd, NBD_SET_SOCK, sk) failed.");
        }
        else
        {
#if defined NBD_SET_FLAGS
            flags = 0;
#if defined NBD_FLAG_SEND_TRIM
            flags |= NBD_FLAG_SEND_TRIM;
#endif
#if defined NBD_FLAG_SEND_FLUSH
            flags |= NBD_FLAG_SEND_FLUSH;
#endif
            if (flags != 0 && ioctl(nbd, NBD_SET_FLAGS, flags) == -1)
            {
                throw std::runtime_error("ioctl(nbd, NBD_SET_FLAGS failed.\n");
            }
#endif
            err = ioctl(nbd, NBD_DO_IT);
            if (err == -1)
            {
                throw std::runtime_error("NBD_DO_IT terminated with error");
            }
        }
        if (
            ioctl(nbd, NBD_CLEAR_QUE) == -1 ||
            ioctl(nbd, NBD_CLEAR_SOCK) == -1)
        {
            throw std::runtime_error("failed to perform nbd cleanup actions");
        }

        exit(0);
    }

    NbdComm::~NbdComm() noexcept
    {
        disconnect_nbd(m_nbd);

        close(m_socket.GetFd());
        int status = 0;
        if (waitpid(m_pid, &status, 0) == -1)
        {
            std::cout << "failed to wait to child process\n";
        }
        if (WEXITSTATUS(status) != 0)
        {
            std::cout << "exit status returned\n";
        }
    }

    FileDesc NbdComm::GetNbdSocket()
    {
        return m_socket;
    }

    /* Signal handler to gracefully disconnect from nbd kernel driver. */
    static void disconnect_nbd(int m_nbd)
    {
        if (m_nbd != -1)
        {
            if (ioctl(m_nbd, NBD_DISCONNECT) == -1)
            {
                std::cerr << "failed to request disconect on nbd device";
            }
            else
            {
                m_nbd = -1;
                std::cout << "sucessfuly requested disconnect on nbd device\n";
            }
        }
    }

    /* Sets signal action like regular sigaction but is suspicious. */
    static int set_sigaction(int sig, const struct sigaction *act)
    {
        struct sigaction oact;
        int r = sigaction(sig, act, &oact);
        if (r == 0 && oact.sa_handler != SIG_DFL)
        {
            throw std::runtime_error("overriden non-default signal handler ");
        }
        return r;
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

}