
#include <string.h>
#include <iosfwd>

#include "event.hpp"

namespace ilrd
{
    static void ConvetToChars(std::vector<char> &m_data, unsigned int data);
    size_t char_size = sizeof(char);
    ReadEvent::ReadEvent(struct args &target_stream)
    {
    }
    void ReadEvent::operator()()
    {
        std::cout << "EventRead operate\n";
    }
    ReadEvent::~ReadEvent() noexcept
    {
    }

    WriteEvent::WriteEvent(struct args &data_stream)
    {
    }

    void WriteEvent::operator()()
    {
        std::cout << "EventWrite operate\n";
    }

    WriteEvent::~WriteEvent() noexcept
    {
    }

    static void ConvetToChars(std::vector<char> &m_data, unsigned int data)
    {
        size_t data_size = sizeof(data);
        unsigned char mask = 0xff;

        for (unsigned int i = 0; i < data_size; ++i)
        {
            m_data[i] = (data >> (i * char_size)) & mask;
        }
    }
}
