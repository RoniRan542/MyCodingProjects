/* -------------------------------------------------------------------------- *
 * FILENAME      -    device.hpp
 * -------------------------------------------------------------------------- *
 * AUTHOR        -
 * STATUS        -    not tested
 * REVIEWER      -
 * DATE          -    17/11/22
 * -------------------------------------------------------------------------- */

#ifndef __RD12123_DEVICE_HPP__
#define __RD12123_DEVICE_HPP__

#if __cplusplus <= (199711L)
#define noexcept throw()
#define nullptr 0
#endif

#include <iostream>
#include <list>

#include "../reactor/reactor.hpp"
#include "../nbd/nbd_comm.hpp"
#include "../thread_pool/thread_pool.hpp"
#include "../event/event.hpp"
#include "../factory/factory.hpp"

namespace ilrd
{
    class Input
    {
    public:
        Input();
        Input(const std::string &dev_file, struct buse_operations aop);
        ~Input();

    private:
        Reactor m_reactor;
        NbdComm m_nbd;
        Factory<Event, std::string, struct args &> *m_factory;
    };

    class Output
    {
    public:
        Output();
        ~Output();

    private:
        Retransmitor m_trans;
        StorageManager m_sm;
        ThreadPool m_tp;
    };

    class Retransmitor
    {
    public:
        Retransmitor();
        void Send();
        ~Retransmitor();

    private:
    };

    class StorageManager
    {
    public:
        StorageManager();
        void insert(Task ts);
        Task Get();
        ~StorageManager();

    private:
        std::list<Task> m_task_history;
    };

    class Device
    {
    public:
        Device(const std::string &dev_file = "/dev/nbd0", size_t dev_size = 128);
        ~Device();
        void Run();

    private:
        Input m_in;
        Output m_out;
        std::list<std::string> m_minions;
    };
}
#endif //__RD12123_DEVICE_HPP__