/*********************************************************
 * author: Ran Aharon Cohen                              *
 * reviewer: Amir                                        *
 * date: 13.09.22                                        *
 * file: thread_pool Header                              *
 *********************************************************/
#ifndef __RD12123_THREAD_POOL_HPP__
#define __RD12123_THREAD_POOL_HPP__

#include <iostream>
#include <functional>
#include <thread>
#include <queue>

#include "waitable_queue.hpp"
#include "pq_wrapper.hpp"

namespace ilrd
{

    enum PRIORITY
    {
        HIGHEST = 0,
        HIGH = 1,
        MEDIUM = 2,
        LOW = 3

    };

    enum STATUS
    {
        DONE = 0,
        RUN = 1,
        PAUSE = 2,
        STOP = 3
    };

    enum THREAD_STATE
    {
        WORK = 0,
        EXIT = 1
    };

    class Task;

    class FunctorCompareTasks
    {
    public:
        bool operator()(const std::pair<PRIORITY, std::shared_ptr<Task>> &task1,
                        const std::pair<PRIORITY, std::shared_ptr<Task>> &task2)
        {
            return task1.first > task2.first;
        }

    private:
    };

    class ThreadPool
    {
    private:
        class ThreadUnit; // forward declaration

    public:
        explicit ThreadPool(size_t n_threads =
                                std::thread::hardware_concurrency(),
                            size_t niceness = 0);
        ~ThreadPool() noexcept;
        ThreadPool(const ThreadPool &) = delete;
        ThreadPool &operator=(const ThreadPool &) = delete;
        void Add(std::shared_ptr<Task> function, PRIORITY pr);
        void Run() noexcept;
        void Pause() noexcept; // stops pulling tasks from queue
        void Stop() noexcept;  // Pause + flush for task queue
        void SetNumberOfThreads(size_t n_threads);
        enum STATUS GetStatus() const { return m_is_running; }
        // void Remove(std::shared_ptr<Task> function); <<----- (ADVANCED)

    private:
        Waitable_Queue<std::pair<PRIORITY, std::shared_ptr<Task>>,
                       PQwrapper<std::pair<PRIORITY, std::shared_ptr<Task>>,
                                 std::vector<std::pair<PRIORITY, std::shared_ptr<Task>>>,
                                 FunctorCompareTasks>>
            m_task_queue;
        std::queue<std::shared_ptr<ThreadUnit>> m_thread_queue;
        size_t m_niceness;
        STATUS m_is_running;
        std::condition_variable cv;
        class ThreadUnit
        {
        public:
            explicit ThreadUnit(ThreadPool *m_thread_pool);
            ~ThreadUnit();
            ThreadUnit(const ThreadUnit &) = delete;
            ThreadUnit operator=(const ThreadUnit &) = delete;
            THREAD_STATE GetState() const { return thread_state; }
            void SetState(THREAD_STATE ts) { thread_state = ts; }

        private:
            ThreadPool *m_thread_pool;
            THREAD_STATE thread_state;
            std::thread m_thread;
            void standard_func();
        };
    };

    class Task
    {
    public:
        void virtual operator()() = 0;
        virtual ~Task() {}

    private:
    };

    class Default_Task : public Task
    {
    public:
        Default_Task(std::function<void()> func);
        void virtual operator()()
        {
            m_func();
        }
        virtual ~Default_Task();

    private:
        std::function<void()> m_func;
    };

} // namespace ilrd

#endif //__RD12123_THREAD_POOL_HPP__