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

    /*
    - common Input:
    1. Reactor
    2. Factory
    3. Event

    - Diff Input:
    1. Listener(Master - NBD, Minion - Udp socket)

    - Common Output:
    1. Event
    2. Threadpool

    - Diff Output:
    1. StorageManager
    2. Retransmitor
    3. Server (StorageManager)

     */
    template <class Object>
    class Input
    {
    public:
        Input();
        Input(const std::string &dev_file, struct buse_operations aop);
        ~Input();

    private:
        Reactor m_reactor;
        Object m_nbd;
        Factory<Event, std::string, struct args &> *m_factory;
    };

    template <class type>
    class Output
    {
    public:
        Output();
        ~Output();

    private:
        Retransmitor m_trans;
        StorageManager m_sm;
        ThreadPool m_tp;
        // std::list<std::string> m_minions;
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

    template <class Inpute_type, class Output_type>
    class Device
    {
    public:
        Device(const std::string &dev_file = "/dev/nbd0", size_t dev_size = 128);
        ~Device();
        void Run();

    private:
        Inpute_type m_in;
        Output_type m_out;
    };
}
#endif //__RD12123_DEVICE_HPP__