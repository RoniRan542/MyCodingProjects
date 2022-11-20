/*********************************************************
 * author: Ran Aharon Cohen                              *
 * reviewer: Amir                                        *
 * date: 13.09.22                                        *
 * file: thread_pool implementation                      *
 *********************************************************/
#include <unistd.h> // nice()
#include <iostream>
#include "thread_pool.hpp"

namespace ilrd
{
    void ThreadPool::ThreadUnit::standard_func()
    {
        std::mutex mutex;
        std::unique_lock<std::mutex> laki(mutex);

        while (m_thread_pool->m_is_running != DONE && thread_state == WORK)
        {
            m_thread_pool->cv.wait(laki);

            while (m_thread_pool->m_is_running == RUN)
            {
                std::pair<PRIORITY, std::shared_ptr<Task>> g_task;
                m_thread_pool->m_task_queue.Pop(g_task);
                (*g_task.second)();
            }
        }
    }

    ThreadPool::ThreadPool(size_t n_threads,
                           size_t niceness) : m_niceness(niceness), m_is_running(PAUSE)
    {
        if (-1 == nice(niceness))
        {
            throw std::runtime_error("failed to change proc niceness\n");
        }
        for (size_t i = 0; i < n_threads; ++i)
        {
            std::shared_ptr<ThreadUnit> sptr(new ThreadUnit(this));
            m_thread_queue.push(sptr);
        }
    }

    void InsertEmptyTasks(ThreadPool *tp, size_t q_size)
    {
        for (size_t i = 0; i < q_size; ++i)
        {
            tp->Add(std::shared_ptr<Task>(new Default_Task([]() {})), HIGHEST);
        }
    }

    ThreadPool::~ThreadPool() noexcept
    {
        Stop();
        m_is_running = DONE;
        try
        {
            InsertEmptyTasks(this, m_thread_queue.size());
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
        cv.notify_all();

        while (!m_thread_queue.empty())
        {
            m_thread_queue.pop();
        }
    }

    void ThreadPool::Add(std::shared_ptr<Task> function, PRIORITY pr)
    {
        m_task_queue.Push(std::pair<PRIORITY, std::shared_ptr<Task>>(pr, function));
        cv.notify_one();
    }

    void ThreadPool::SetNumberOfThreads(size_t n_threads)
    {
        size_t curr_size = m_thread_queue.size();

        if (curr_size < n_threads)
        {
            for (size_t i = 0; i < n_threads - curr_size; ++i)
            {
                std::shared_ptr<ThreadUnit> sptr(new ThreadUnit(this));
                m_thread_queue.push(sptr);
            }
        }
        else if (curr_size > n_threads)
        {
            bool was_running = (m_is_running == RUN) ? true : false;
            Pause();

            for (size_t i = 0; i < curr_size - n_threads; ++i)
            {
                ThreadUnit *tu = m_thread_queue.front().get();
                tu->SetState(EXIT);
                cv.notify_all();
                InsertEmptyTasks(this, curr_size);
                m_thread_queue.pop();
            }

            (true == was_running) ? Run() : (void)0;
        }
    }

    void ThreadPool::Run() noexcept
    {
        m_is_running = RUN;
        cv.notify_all();
    }

    void ThreadPool::Pause() noexcept
    {
        m_is_running = PAUSE;
        InsertEmptyTasks(this, m_thread_queue.size());
    }

    void ThreadPool::Stop() noexcept
    {
        m_is_running = STOP;

        InsertEmptyTasks(this, m_thread_queue.size());
        while (!m_task_queue.IsEmpty())
        {
            std::pair<PRIORITY, std::shared_ptr<Task>> task;
            m_task_queue.Pop(task);
        }
    }

    Default_Task::Default_Task(std::function<void()> func)
        : m_func(func)
    {
        // empty
    }

    Default_Task::~Default_Task()
    {
        // empty
    }

    ThreadPool::ThreadUnit::ThreadUnit(ThreadPool *m_thread_pool)
        : m_thread_pool(m_thread_pool),
          thread_state(WORK),
          m_thread(std::thread(&ThreadPool::ThreadUnit::standard_func, this))
    {
        // empty
    }

    ThreadPool::ThreadUnit::~ThreadUnit()
    {
        m_thread.join();
    }

}