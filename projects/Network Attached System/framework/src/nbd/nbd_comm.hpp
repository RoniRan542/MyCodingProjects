/* -------------------------------------------------------------------------- *
 * FILENAME      -    nbd_comm.hpp
 * -------------------------------------------------------------------------- *
 * AUTHOR        -
 * STATUS        -    not tested
 * REVIEWER      -
 * DATE          -    02/11/22
 * -------------------------------------------------------------------------- */

#ifndef __RD12123_NBD_COMM_HPP__
#define __RD12123_NBD_COMM_HPP__

#if __cplusplus <= (199711L)
#define noexcept throw()
#define nullptr 0
#endif

/* ------------------------------------------------------------------- *
 *                             Include
 * ------------------------------------------------------------------ */
#include <string> //std::string

#include "reactor.hpp"
#include "FileDesc.hpp"

/* ------------------------------------------------------------------- *
 *                             Consts
 * ------------------------------------------------------------------ */

namespace ilrd
{
    struct buse_operations
    {
        int (*read)(void *buf, u_int32_t len, u_int64_t offset, void *userdata);
        int (*write)(const void *buf, u_int32_t len, u_int64_t offset, void *userdata);
        void (*disc)(void *userdata);
        int (*flush)(void *userdata);
        int (*trim)(u_int64_t from, u_int32_t len, void *userdata);

        // either set size, OR set both blksize and size_blocks
        u_int64_t size;
        u_int32_t blksize;
        u_int64_t size_blocks;
    };

    class NbdComm
    {

    public:
        explicit NbdComm(std::string dev_file = "/dev/nbd1", const size_t dev_size = 128);
        ~NbdComm() noexcept;

        NbdComm(const NbdComm &) = delete;
        NbdComm(NbdComm &&) = delete;
        const NbdComm &operator=(const NbdComm &) = delete;
        const NbdComm &operator=(NbdComm &&) = delete;
        FileDesc GetNbdSocket();

    private:
        FileDesc m_socket;
        int m_nbd;
        pid_t m_pid;
    };
}

#endif // __RD12123_NBD_COMM_HPP__
