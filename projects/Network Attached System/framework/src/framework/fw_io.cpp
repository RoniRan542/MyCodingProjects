#include <iostream>
#include <list>
#include <linux/nbd.h>
#include <netinet/in.h>
#include <argp.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <sys/types.h>
#include <functional>
#include <memory>

#include "event.hpp"
#include "fw_io.hpp"

namespace ilrd
{
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

    static int read_all(int fd, char *buf, std::size_t count)
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

    static int write_all(int fd, char *buf, std::size_t count)
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

    InputMaster::InputMaster(std::string dev_file, std::size_t dev_size)
    {
        m_fdsock_nbd = m_nbd_comm.GetNbdSocket();
    }

    FileDesc InputMaster::GetFd() const
    {
        return m_fdsock_nbd;
    }

    void InputMaster::Callback(FileDesc fd_out, std::shared_ptr<out_param_t> &output_param)
    {
        int sk = fd_out.GetFd();
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
            if (BUSE_DEBUG)
                fprintf(stderr, "Request for read of size %d\n", len);
            /* chunk = malloc(len);
            memcpy(chunk, m_data.get() + from, len); */
            output_param.get()->event_name = "RD";
            // output_param.get()->args.event_data.reset((char *)chunk);
            output_param.get()->args.from = from;
            output_param.get()->args.len = len;
            output_param.get()->args.fd_sock = sk;
            output_param.get()->args.action = 1; // replace later with enum
            output_param.get()->args.reply = reply;
            /* write_all(sk, (char *)&reply, sizeof(struct nbd_reply));
            write_all(sk, (char *)chunk, len); */
            break;
        case NBD_CMD_WRITE:
            if (BUSE_DEBUG)
                fprintf(stderr, "Request for write of size %d\n", len);
            /* chunk = malloc(len);
            read_all(sk, (char *)chunk, len); */
            output_param.get()->event_name = "WR";
            // output_param.get()->args.event_data.reset((char *)chunk);
            output_param.get()->args.from = from;
            output_param.get()->args.len = len;
            read_all(sk, output_param.get()->args.event_data, len);
            output_param.get()->args.fd_sock = sk;
            output_param.get()->args.action = 2; // replace later with enum
            output_param.get()->args.reply = reply;
            /*  memcpy(m_data.get() + from, output_param.get()->args.event_data.get(), output_param.get()->args.len);
             write_all(sk, (char *)&reply, sizeof(struct nbd_reply)); */
            break;
        case NBD_CMD_DISC:
            if (BUSE_DEBUG)
            {
                fprintf(stderr, "Got NBD_CMD_DISC\n");
            }
            fprintf(stderr, "Received a disconnect request.\n");
            output_param.get()->event_name = "DSC";
            output_param.get()->args.action = 3;
#ifdef NBD_FLAG_SEND_FLUSH
        case NBD_CMD_FLUSH:
            if (BUSE_DEBUG)
            {
                fprintf(stderr, "Got NBD_CMD_FLUSH\n");
            }
            fprintf(stderr, "Received a flush request.\n");
            write_all(sk, (char *)&reply, sizeof(struct nbd_reply));
            output_param.get()->event_name = "FLS";
            output_param.get()->args.action = 4;
            break;
#endif
#ifdef NBD_FLAG_SEND_TRIM
        case NBD_CMD_TRIM:
            if (BUSE_DEBUG)
                fprintf(stderr, "Got NBD_CMD_TRIM\n");
            fprintf(stderr, "T - %lu, %u\n", from, len);
            write_all(sk, (char *)&reply, sizeof(struct nbd_reply));
            output_param.get()->event_name = "TRM";
            output_param.get()->args.action = 5;
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

    OutputMaster::OutputMaster(std::vector<std::pair<u_int32_t, std::string>> port_ips, size_t dev_size)
        : m_minion_fs(new char[dev_size * 1048576], std::default_delete<char[]>())
    {
        m_fdsocket = FileDesc(STDOUT_FILENO);
    }

    FileDesc OutputMaster::GetFd() const
    {
        return m_fdsocket;
    }

    void OutputMaster::Callback(FileDesc fd_out)
    {
        std::cout << "output callback\n";
    }

    std::shared_ptr<char> OutputMaster::GetMinionFs() const
    {
        return m_minion_fs;
    }
}