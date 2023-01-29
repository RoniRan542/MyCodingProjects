/*********************************************************
 * author: Ran Aharon Cohen                              *
 * reviewer: Mariana                                     *
 * date: 09.10.22                                        *
 * file: reactor API implementation                      *
 *********************************************************/
#include <iostream>   // for std::
#include "logger.hpp" /* loggeer API */

#include "reactor.hpp"
#include "reactor_imp.hpp"

#define handle_error(msg)   \
    do                      \
    {                       \
        perror(msg);        \
        exit(EXIT_FAILURE); \
    } while (0)

namespace ilrd
{
    typedef enum Operation operation_t;
    void CheckStdin(Reactor *reactor);

    Reactor::Reactor() : m_rcimpl(m_invoke), m_stop(false), m_inside_loop(false)
    {
        m_logger = Handleton<Logger>::GetInstance();
        m_logger->SetPath("reactor_logger.txt");
        m_logger->Log("Reactor: created\n");
        auto func = std::bind<void>(CheckStdin, this);
        Add(STDIN_FILENO, func, operation_t::READ);
    }

    void Reactor::Add(int fd, std::function<void()> func, operation_t op)
    {
        m_logger->Log("Reactor: adding fd\n");
        m_rcimpl.AddImp(fd, op);
        std::pair<int, Operation> callback(fd, op);
        m_invoke[callback] = func;
    }

    void Reactor::Remove(int fd, operation_t op) noexcept
    {
        std::pair<int, Operation> to_remove(fd, op);
        if (m_inside_loop)
        {
            m_to_remove.push_back(to_remove);
        }
        else
        {
            m_invoke.erase(to_remove);
            m_rcimpl.RemoveImp(fd, op);
            m_logger->Log("Reactor: fd was removed\n");
        }
    }

    void Reactor::Run()
    {
        m_logger->Log("Reactor: started running\n");
        while (!m_stop)
        {
            m_inside_loop = true;
            m_rcimpl.RunImp();
            m_inside_loop = false;

            while (!m_to_remove.empty())
            {
                std::pair<int, Operation> to_remove = m_to_remove.front();
                Remove(to_remove.first, to_remove.second);
                m_to_remove.pop_front();
            }
        }
    }

    void Reactor::Stop()
    {
        m_stop = true;
        m_rcimpl.StopImp();
        m_logger->Log("Reactor: stopped\n");
    }

    void CheckStdin(Reactor *reactor)
    {
        std::string input;
        std::cin >> input;
        if (input == "stop")
        {
            reactor->Stop();
        }
    }
}