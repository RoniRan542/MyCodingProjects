/* -------------------------------------------------------------------------- *
 * FILENAME      -    task.hpp
 * -------------------------------------------------------------------------- *
 * AUTHOR        -
 * STATUS        -    not tested
 * REVIEWER      -
 * DATE          -    19/12/22
 * -------------------------------------------------------------------------- */

#ifndef __TASK_HPP__
#define __TASK_HPP__

#if __cplusplus <= (199711L)
#define noexcept throw()
#define nullptr 0
#endif

#include <iostream>
#include <vector>
#include <functional>
#include <memory>
#include <cstring>
#include <linux/nbd.h>

#include "event.hpp"
#include "thread_pool.hpp"
#include "fw_io.hpp"
#include "handleton.hpp"
#include "logger.hpp"

namespace ilrd
{

    static int read_all(int fd, char *buf, std::size_t count)
    {
        int bytes_read;

        while (count > 0)
        {
            bytes_read = read(fd, buf, count);
            assert(bytes_read > 0);
            buf += bytes_read;
            count -= bytes_read;
        }
        assert(count == 0);

        return 0;
    }

    static int write_all(int fd, char *buf, std::size_t count)
    {
        int bytes_written;

        while (count > 0)
        {
            bytes_written = write(fd, buf, count);
            assert(bytes_written > 0);
            buf += bytes_written;
            count -= bytes_written;
        }
        assert(count == 0);

        return 0;
    }

    class EventTask : public Task
    {
    public:
        EventTask(Event *event, char *minion_data, InputMaster *in) : m_event(event),
                                                                      m_minion_data(minion_data), m_in(in)
        {
            m_action = event->GetData().action;
            m_from = event->GetData().from;
            m_len = event->GetData().len;
            m_chunk = malloc(m_len);
            m_sk = event->GetData().fd_sock;
            m_reply = event->GetData().reply;
        }
        void virtual operator()()
        {
            if (m_action == 1)
            {
                memcpy(m_chunk, m_minion_data + m_from, m_len);
                m_in->mu.lock();
                write_all(m_sk, (char *)&m_reply, sizeof(struct nbd_reply));
                write_all(m_sk, (char *)m_chunk, m_len);
                m_in->mu.unlock();
            }
            else if (m_action == 2)
            {
                // read_all(m_sk, (char *)m_chunk, m_len);
                memcpy(m_minion_data + m_from,
                       m_event->GetData().event_data, m_len);
                m_in->mu.lock();
                write_all(m_sk, (char *)&m_reply, sizeof(struct nbd_reply));
                m_in->mu.unlock();
            }
            else if (m_action == 3)
            {
                std::cout << " action 3" << std::endl;
            }
            else if (m_action == 4)
            {
                std::cout << " action 4" << std::endl;
            }
            else if (m_action == 5)
            {
                std::cout << " action 5" << std::endl;
            }
            (*m_event)();
        }
        void LogTaskEvent()
        {
            /* Logger *logger = Handleton<Logger>::GetInstance();
            logger->Log() */
        }

        virtual ~EventTask()
        {
            free(m_chunk);
            delete m_event;
        }

    private:
        InputMaster *m_in;
        Event *m_event;
        void *m_chunk;
        u_int64_t m_from;
        u_int32_t m_len;
        int m_sk;
        int m_action;
        struct nbd_reply m_reply;
        char *m_minion_data;
    };

}
#endif //__TASK_HPP__