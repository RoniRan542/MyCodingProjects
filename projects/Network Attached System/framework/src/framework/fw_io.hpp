/* -------------------------------------------------------------------------- *
 * FILENAME      -    master_io.hpp
 * -------------------------------------------------------------------------- *
 * AUTHOR        -
 * STATUS        -    not tested
 * REVIEWER      -
 * DATE          -    27/11/22
 * -------------------------------------------------------------------------- */

#ifndef __RD12123_MASTER_IO_HPP__
#define __RD12123_MASTER_IO_HPP__

#if __cplusplus <= (199711L)
#define noexcept throw()
#define nullptr 0
#endif

#include <iostream>
#include <vector>
#include <memory>
#include <functional>
#include <mutex>

#include "FileDesc.hpp"
#include "nbd_comm.hpp"

namespace ilrd
{
    struct Params
    {
        void *op;
    };

    typedef struct OutputParam
    {
        std::string event_name;
        args_t args;
    } out_param_t;

    class InputMaster
    {
    public:
        explicit InputMaster(std::string dev_file = "/dev/nbd0", std::size_t dev_size = 128);
        FileDesc GetFd() const;
        void Callback(FileDesc fd_out, std::shared_ptr<out_param_t> &output_param); // event is output param
        std::mutex mu;

    private:
        FileDesc m_fdsock_nbd;
        NbdComm m_nbd_comm;
    };

    class OutputMaster
    {
    public:
        explicit OutputMaster(std::vector<std::pair<u_int32_t, std::string>> port_ips =
                                  {std::pair<u_int32_t, std::string>(0, "")},
                              size_t dev_size = 128);
        FileDesc GetFd() const;
        std::shared_ptr<char> GetMinionFs() const;
        void Callback(FileDesc fd_out);
        // SendMessage(void *data);

    private:
        // Distributer dist;
        // Retransmitor retrans;
        // UDPServer server; // not sure if we need it
        FileDesc m_fdsocket;
        std::shared_ptr<char> m_minion_fs;
    };
}
#endif // __RD12123_MASTER_IO_HPP__