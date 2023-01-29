
/* -------------------------------------------------------------------------- *
 * FILENAME      -    framework.hpp
 * -------------------------------------------------------------------------- *
 * AUTHOR        -
 * STATUS        -    not tested
 * REVIEWER      -
 * DATE          -    22/11/22
 * -------------------------------------------------------------------------- */

#ifndef __RD12123_FRAMEWORK_HPP__
#define __RD12123_FRAMEWORK_HPP__

#if __cplusplus <= (199711L)
#define noexcept throw()
#define nullptr 0
#endif

#include <iostream>
#include <vector>
#include <functional>
#include <memory>

#include "event.hpp"
#include "factory.hpp"
#include "thread_pool.hpp"
#include "nbd_comm.hpp"
#include "FileDesc.hpp"
#include "fw_io.hpp"
#include "task.hpp"

namespace ilrd
{
    template <class InputType, class OutputType>
    class Framework;

    Event *CreateReadEvent(args_t &arg)
    {
        return new ReadEvent(arg);
    }

    Event *CreateWriteEvent(args_t &arg)
    {
        return new WriteEvent(arg);
    }

    template <class InputType, class OutputType>
    class Framework
    {
    public:
        explicit Framework();
        ~Framework();
        void Run(); // Activate reactor
    private:
        void InvokeSending(FileDesc fd_in);    // call inpute callback, create event, wrap as task, put in threadpool for executing
        void InvokeReceiving(FileDesc fd_out); // call output callback, get data from minion/master and write it to user/filesystem
        InputType m_in;
        OutputType m_out;
        ThreadPool *m_tp;
        Reactor m_nbd_reactor;
        Factory<Event, std::string, args_t &> m_factory;
    };

    template <class InputType, class OutputType>
    Framework<InputType, OutputType>::Framework()
    {
        int connected_devices = 1;       // take from config file
        uint32_t port = 8888;            // take from config file
        std::string ip = "192.10.22.12"; // take from config file
        std::vector<std::pair<u_int32_t, std::string>> port_ip_vec(connected_devices);
        port_ip_vec.push_back(std::pair<u_int32_t, std::string>(port, ip));

        m_tp = Handleton<ThreadPool>::GetInstance();
        m_nbd_reactor.Add(m_in.GetFd().GetFd(), std::bind(&Framework<InputType, OutputType>::InvokeSending, this, m_in.GetFd()), READ);
        m_factory.Add("RD", CreateReadEvent);
        m_factory.Add("WR", CreateWriteEvent);
        m_factory.Add("DSC", CreateReadEvent);
        m_factory.Add("TRM", CreateReadEvent);
        m_factory.Add("FLS", CreateReadEvent);
    }

    template <class InputType, class OutputType>
    void Framework<InputType, OutputType>::Run()
    {
        m_tp->Run();
        m_nbd_reactor.Run();
    }

    template <class InputType, class OutputType>
    void Framework<InputType, OutputType>::InvokeSending(FileDesc fd_in)
    {
        static int counter = 0;
        std::shared_ptr<out_param_t> output_param(new out_param_t);
        m_in.Callback(fd_in, output_param);
        std::cout << "output_param: " << output_param.get()->event_name << std::endl;

        Event *event = m_factory.Create(output_param.get()->event_name, output_param.get()->args);
        //   m_out->dist.Distribute();
        std::shared_ptr<Task> task(new EventTask(event, m_out.GetMinionFs().get(), &m_in));
        m_tp->Add(task, PRIORITY::HIGH);
        std::cout << "InvokeSending: " << fd_in.GetFd() << std::endl;
        std::cout << "counter: " << counter++ << std::endl;
    }

    template <class InputType, class OutputType>
    void Framework<InputType, OutputType>::InvokeReceiving(FileDesc fd_out)
    {
        std::cout << "InvokeReceiving: " << fd_out.GetFd() << std::endl;
    }

    template <class InputType, class OutputType>
    Framework<InputType, OutputType>::~Framework()
    {
    }

    /* template <class InputType, class OutputType>
    static InputType *InitInput()
    {
        const std::string &dev_file = "/dev/nbd0"; // take from config file
        size_t dev_size = 128;                     // take from config file
        return InputType(dev_file, dev_size);
    }

    template <class InputType, class OutputType>
    static OutputType *InitOutput<OutputType>()
    {
        int connected_devices = 1;    // take from config file
        uint32_t port = 8888;         // take from config file
        uint32_t ip = "192.10.22.12"; // take from config file
        std::vector<std::pair<u_int32_t, std::string>> port_ip_vec(connected_devices);
        port_ip_vec.push_back(std::pair<u_int32_t, std::string>(port, ip));

        return OutputType(port_ip_vec);
    } */
}

#endif //__RD12123_FRAMEWORK_HPP__