/*********************************************************
 * author: Ran Aharon Cohen                              *
 * reviewer: Mariana                                     *
 * date: 09.10.22                                        *
 * file: reactor specific implementation                 *
 *********************************************************/
#include <sys/select.h> //for select
#include <errno.h>
#include <iostream>

#include "reactor_imp.hpp"
#include "handleton.hpp"
#include "../logger/logger.hpp"

#define MAX(Y, X) ((Y) > (X) ? (Y) : (X))

namespace ilrd
{
    class SelectFailedException : public std::exception
    {
    public:
        virtual const char *what() const noexcept
        {
            return "SelectFailedException";
        }
    };

    struct Params
    {
        fd_set read_set;
        fd_set write_set;
        fd_set except_set;
        int max_fd;
    };

    static void ResetParams(std::shared_ptr<Params> params)
    {
        FD_ZERO(&params->read_set);
        FD_ZERO(&params->write_set);
        FD_ZERO(&params->except_set);
        params->max_fd = 0;
    }
    ReactorImp::ReactorImp(std::map<std::pair<int, Operation>, std::function<void()>> &callbacks)
        : m_params(new Params), m_callbacks(callbacks)
    {
        ResetParams(m_params);
    }

    void ReactorImp::AddImp(int fd, Operation op)
    {
        switch (op)
        {
        case Operation::READ:
            FD_SET(fd, &m_params->read_set);
            break;
        case Operation::WRITE:
            FD_SET(fd, &m_params->write_set);
            break;
        case Operation::EXCEPTION:
            FD_SET(fd, &m_params->except_set);
            break;
        default:
            std::cout << "an error occured: wrong input. \n";
            break;
        }

        m_params->max_fd = MAX(m_params->max_fd, fd);
    }

    void ReactorImp::RemoveImp(int fd, Operation op) noexcept
    {
        switch (op)
        {
        case Operation::READ:
            FD_CLR(fd, &m_params->read_set);
            break;
        case Operation::WRITE:
            FD_CLR(fd, &m_params->write_set);
            break;
        case Operation::EXCEPTION:
            FD_CLR(fd, &m_params->except_set);
            break;
        default:
            std::cout << "an error occured: wrong input. \n";
            break;
        }

        UpdateMaxFD();
    }

    void ReactorImp::RunImp()
    {
        fd_set read_cpy = m_params->read_set;
        fd_set write_cpy = m_params->write_set;
        fd_set except_cpy = m_params->except_set;

        int ret_val = select(m_params->max_fd + 1, &read_cpy,
                             &write_cpy, &except_cpy, nullptr);
        if (-1 == ret_val)
        {
            std::cout << strerror(errno) << std::endl;
            throw SelectFailedException();
        }

        for (auto const &handle : m_callbacks)
        {
            switch (handle.first.second)
            {
            case Operation::READ:
                if (FD_ISSET(handle.first.first, &read_cpy))
                {
                    handle.second();
                }
                break;
            case Operation::WRITE:
                if (FD_ISSET(handle.first.first, &write_cpy))
                {
                    handle.second();
                }
                break;
            case Operation::EXCEPTION:
                if (FD_ISSET(handle.first.first, &except_cpy))
                {
                    handle.second();
                }
                break;
            default:
                Handleton<Logger>::GetInstance()->Log("Timeout reached.\n");
                break;
            }
        }
    }

    void ReactorImp::StopImp()
    {
        ResetParams(m_params);
    }

    void ReactorImp::UpdateMaxFD()
    {
        for (int i = m_params->max_fd; i >= 0; --i)
        {
            if (FD_ISSET(i, &m_params->read_set))
            {
                m_params->max_fd = i;
                break;
            }

            if (FD_ISSET(i, &m_params->write_set))
            {
                m_params->max_fd = i;
                break;
            }

            if (FD_ISSET(i, &m_params->except_set))
            {
                m_params->max_fd = i;
                break;
            }
        }
    }
}
