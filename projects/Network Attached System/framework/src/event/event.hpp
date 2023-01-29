#ifndef __RD12123_EVENT_HPP__
#define __RD12123_EVENT_HPP__

#if __cplusplus <= (199711L)
#define noexcept throw()
#define nullptr 0
#endif

#include <iostream>
#include <linux/nbd.h>
#include <memory>
#include <functional>

namespace ilrd
{
    typedef struct Args
    {
        char event_data[4096];
        struct nbd_reply reply;
        u_int64_t from;
        u_int32_t len;
        int fd_sock;
        int action;
    } args_t;

    class Event
    {
    public:
        explicit Event(){};
        virtual void operator()() = 0;
        virtual args_t &GetData() = 0;
        virtual ~Event() noexcept {};
    };

    class ReadEvent : public Event
    {
    public:
        explicit ReadEvent(args_t &target_stream);
        virtual void operator()();
        virtual args_t &GetData();
        virtual ~ReadEvent() noexcept;

    private:
        args_t m_args;
    };

    class WriteEvent : public Event
    {
    public:
        explicit WriteEvent(args_t &data_stream);
        virtual void operator()();
        virtual args_t &GetData();
        virtual ~WriteEvent() noexcept;

    private:
        args_t m_args;
    };
}

#endif // __RD12123_EVENT_HPP__