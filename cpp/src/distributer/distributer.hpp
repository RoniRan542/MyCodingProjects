#ifndef __RD12123_DISTRIBUTER_HPP__
#define __RD12123_DISTRIBUTER_HPP__

#if __cplusplus <= (199711L)
#define noexcept throw()
#define nullptr 0
#endif

#include <iostream>
#include <map>

#include "../system/system.hpp"
#include "../retransmitor/retarnsmitor.hpp"

namespace ilrd
{
    class Distributer
    {
    public:
        Distributer(/* args */);
        ~Distributer();

    private:
        std::map<int, System> storage;
        Retransmitor retransmit;
    };
}

#endif // __RD12123_DISTRIBUTER_HPP__