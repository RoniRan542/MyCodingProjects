
#include <iostream>
#include <string.h>
#include <vector>

#include "event.hpp"

namespace ilrd
{
    // static void ConvetToChars(std::vector<> &m_data, unsigned int data);
    size_t char_size = sizeof(char);
    ReadEvent::ReadEvent(args_t &target_stream) : m_args(target_stream)
    {
        // empty
    }
    void ReadEvent::operator()()
    {
        std::cout << "EventRead operate\n";
        std::cout << "from: " << m_args.from << "\n";
        std::cout << "len: " << m_args.len << "\n";
    }
    args_t &ReadEvent::GetData()
    {
        return m_args;
    }

    ReadEvent::~ReadEvent() noexcept
    {
    }

    WriteEvent::WriteEvent(args_t &data_stream) : m_args(data_stream)
    {
    }

    void WriteEvent::operator()()
    {
        std::cout << "EventWrite operate\n";
    }

    args_t &WriteEvent::GetData()
    {
        return m_args;
    }

    WriteEvent::~WriteEvent() noexcept
    {
    }
    /*
        static void ConvetToChars(std::vector<char> &m_data, unsigned int data)
        {
            size_t data_size = sizeof(data);
            unsigned char mask = 0xff;

            for (unsigned int i = 0; i < data_size; ++i)
            {
                m_data[i] = (data >> (i * char_size)) & mask;
            }
        } */
}
