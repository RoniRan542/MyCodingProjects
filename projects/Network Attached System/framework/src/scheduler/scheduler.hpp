#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include <chrono>
#include <queue>
#include <thread>
#include "handleton.hpp"
#include "waitable_queue.hpp"
#include "timer.hpp"

class ITask
{
public:
    ITask();
    virtual ~ITask(){};
    virtual void Run() = 0;

private:
    std::chrono::system_clock::time_point m_wanted_time;
    friend class Scheduler;
};

class Scheduler
{
public:
    void AddTask(std::shared_ptr<ITask> task, const std::chrono::milliseconds &delay);
    void Run();
    void Stop();
    friend class Handleton<Scheduler>;
    Scheduler(const Scheduler &other_) = delete;
    Scheduler &operator=(const Scheduler &other_) = delete;

private:
    class FunctorCompare
    {
    public:
        bool operator()(std::shared_ptr<ITask> task1, std::shared_ptr<ITask> task2);
    };
    class EmptyTask : public ITask
    {
    public:
        void Run();
    };
    Scheduler();
    ~Scheduler() = default;
    WaitableQueue<std::shared_ptr<ITask>, PriorityQueue<std::shared_ptr<ITask>, FunctorCompare>> m_priority_queue;
    void StartRunning();
    std::thread m_run_thread;
    bool m_is_running;
    Timer m_timer;
};

#endif