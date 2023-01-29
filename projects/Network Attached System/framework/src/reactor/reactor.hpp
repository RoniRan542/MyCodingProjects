/*********************************************************
 * author: Ran Aharon Cohen                              *
 * reviewer: Mariana                                     *
 * date: 09.10.22                                        *
 * file: reactor API                                     *
 *********************************************************/
#ifndef __RD_12123_REACTOR_HPP__
#define __RD_12123_REACTOR_HPP__

#include <iostream>
#include <map>
#include <functional>

#include "logger.hpp"
#include "reactor_imp.hpp"

#if __cplusplus <= (199711L)
#define noexcept throw()
#define nullptr 0
#endif

namespace ilrd
{
    class SelectFailedException;
    typedef enum Operation operation_t;
    class Reactor
    {
    public:
        explicit Reactor();
        Reactor(const Reactor &) = delete;
        Reactor(Reactor &&) = delete;
        const Reactor &operator=(const Reactor &) = delete;
        const Reactor &operator=(Reactor &&) = delete;
        void Add(int fd, std::function<void()> func, operation_t op);
        void Remove(int fd, operation_t op) noexcept;
        void Run(); // blocking function
        void Stop();

    private:
        std::map<std::pair<int, operation_t>, std::function<void()>> m_invoke;
        std::list<std::pair<int, operation_t>> m_to_remove;
        ReactorImp m_rcimpl;
        Logger *m_logger;
        bool m_stop;
        bool m_inside_loop;
    };

} // namespace ilrd

#endif //__RD_12123_REACTOR_HPP__