#ifndef __RD12123_SYSTEM_HPP__
#define __RD12123_SYSTEM_HPP__

#if __cplusplus <= (199711L)
#define noexcept throw()
#define nullptr 0
#endif

#include <iostream>

#include "../reactor/reactor.hpp"
#include "../distributer/distributer.hpp"

namespace ilrd
{
    class System
    {
    public:
        System(/* args */);
        ~System();

    private:
        Reactor m_reactor;
        Distributer m_distributer;
        Logger *m_logger;
    };
}

#endif // __RD12123_SYSTEM_HPP__