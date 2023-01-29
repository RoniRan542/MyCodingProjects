/* -------------------------------------------------------------------------- *
 * FILENAME      -    retransmitor.hpp
 * -------------------------------------------------------------------------- *
 * AUTHOR        -
 * STATUS        -    not tested
 * REVIEWER      -
 * DATE          -    27/11/22
 * -------------------------------------------------------------------------- */

#ifndef __RETRANSMITOR_HPP__
#define __RETRANSMITOR_HPP__

#if __cplusplus <= (199711L)
#define noexcept throw()
#define nullptr 0
#endif

#include <iostream>

#include "FileDesc.hpp"

namespace ilrd
{
    class Retransmitor
    {
    public:
        Retransmitor(std::size_t wait_time);
        ~Retransmitor();

    private:
        std::size_t m_wait_time;
    };

}

#endif // __RETRANSMITOR_HPP__