/* -------------------------------------------------------------------------- *
 * FILENAME      -    reactor_imp.hpp
 * -------------------------------------------------------------------------- *
 * AUTHOR        -    Ran Aharon Cohen
 * STATUS        -    not tested
 * REVIEWER      -
 * DATE          -    02/10/22
 * -------------------------------------------------------------------------- */

#ifndef __RD_12123_REACTOR_IMPL_HPP__
#define __RD_12123_REACTOR_IMPL_HPP__

#include <iostream>
#include <map>
#include <functional>
#include <memory>

#if __cplusplus <= (199711L)
#define noexcept throw()
#define nullptr 0
#endif

namespace ilrd
{

    struct Params;
    enum Operation
    {
        READ,
        WRITE,
        EXCEPTION
    };

    class ReactorImp
    {

    public:
        explicit ReactorImp(std::map<std::pair<int, Operation>, std::function<void()>> &callbacks);
        void AddImp(int fd, Operation op);
        void RemoveImp(int fd, Operation op) noexcept;
        void RunImp();
        void StopImp();

    private:
        std::shared_ptr<Params> m_params;
        std::map<std::pair<int, Operation>, std::function<void()>> &m_callbacks;
        void UpdateMaxFD();
    };
}
#endif //__RD_12123_REACTOR_IMPL_HPP__