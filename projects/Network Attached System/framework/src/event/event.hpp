#ifndef __RD12123_EVENT_HPP__
#define __RD12123_EVENT_HPP__

#if __cplusplus <= (199711L)
#define noexcept throw()
#define nullptr 0
#endif

#include <iostream>
#include <vector>

namespace ilrd
{
    struct args
    {
        void *data;
    };

    class Event
    {
    public:
        explicit Event(){};
        virtual void operator()() = 0;
        virtual ~Event() noexcept {};
    };

    class ReadEvent : public Event
    {
    public:
        explicit ReadEvent(struct args &target_stream);
        virtual void operator()();
        virtual ~ReadEvent() noexcept;

    private:
        std::vector<char> m_target; // where to read from
    };

    class WriteEvent : public Event
    {
    public:
        explicit WriteEvent(struct args &data_stream);
        virtual void operator()();
        virtual ~WriteEvent() noexcept;

    private:
        std::vector<char> m_data;
    };
}

#endif // __RD12123_EVENT_HPP__