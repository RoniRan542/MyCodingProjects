/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
- Author: Chen Rudy
- Date: 12/9/22
- tests for Thread Pool
- compile with makefile
- make sure you have my test.hpp in your include directory
- DONT PANIC! the test threads sleeps, give it time.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <chrono> //time for thread sleep
#include <thread> //this_thread::sleep_for

#include "thread_pool.hpp"
#include "test.hpp"
#include "../shared_ptr/shared_ptr.hpp"

static std::atomic<int> g_task_count(0);

// thread funcs
void intruding()
{
    static std::atomic<int> a(0);
    ++g_task_count;
    ++a;
    PRINT << GREEN "medium do you mind? " << a << YELLOW " global count: " << g_task_count << DEFAULT END;
}
void foo1()
{
    static std::atomic<int> a(0);
    ++g_task_count;
    ++a;
    PRINT << BLUE "high priority task: " << a << YELLOW " global count: " << g_task_count << DEFAULT END;
}
void foo2()
{
    static std::atomic<int> a(0);
    ++g_task_count;
    ++a;
    PRINT << GREEN "medium priority task: " << a << YELLOW " global count: " << g_task_count << DEFAULT END;
}
void foo3()
{
    static std::atomic<int> a(0);
    ++g_task_count;
    ++a;
    PRINT << PURPLE "low priority task: " << a << YELLOW " global count: " << g_task_count << DEFAULT END;
}

// tests
void PauseLocked();
void PopLocked();
void Intrude();
void Stop();
void SetThreadsRemoveWhilePause();
void SetThreadsRemoveWhileRun();
void SetNum();

using namespace ilrd;

int main()
try
{
    PauseLocked();
    PopLocked();
    Intrude();
    SetThreadsRemoveWhilePause();
    SetThreadsRemoveWhileRun();
    Stop();
    SetNum();
    return 0;
}
catch (const std::exception &e)
{
    PRINT << "failed to add tasks" << END;
    return 1;
}

void SetThreadsRemoveWhileRun()
{
    ThreadPool A(6);
    A.Add(std::shared_ptr<Task>(new Default_Task(foo3)), LOW);
    A.Add(std::shared_ptr<Task>(new Default_Task(foo1)), HIGH);
    A.Add(std::shared_ptr<Task>(new Default_Task(foo2)), MEDIUM);

    A.Run();
    A.SetNumberOfThreads(3);
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

void SetThreadsRemoveWhilePause()
{
    ThreadPool A(6);
    A.SetNumberOfThreads(3);
    A.Add(std::shared_ptr<Task>(new Default_Task(foo3)), LOW);
    A.Add(std::shared_ptr<Task>(new Default_Task(foo1)), HIGH);
    A.Add(std::shared_ptr<Task>(new Default_Task(foo2)), MEDIUM);
    std::this_thread::sleep_for(std::chrono::seconds(1));

    A.Run();
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

void PauseLocked() // also no call for stop
{
    ThreadPool A(3);
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

void PopLocked() // also no call for stop
{
    ThreadPool A(3);
    A.Run();
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

void Intrude()
{
    ThreadPool A(6);
    for (int i = 0; i < 10000; ++i)
    {
        A.Add(std::shared_ptr<Task>(new Default_Task(foo3)), LOW);
        A.Add(std::shared_ptr<Task>(new Default_Task(foo1)), HIGH);
        A.Add(std::shared_ptr<Task>(new Default_Task(foo2)), MEDIUM);
    }

    std::this_thread::sleep_for(std::chrono::seconds(2));
    A.Run();

    for (int i = 0; i < 100000; ++i)
    {
        A.Add(std::shared_ptr<Task>(new Default_Task(intruding)), MEDIUM);
    }

    std::this_thread::sleep_for(std::chrono::seconds(6));

    A.Pause();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    A.Run();

    std::this_thread::sleep_for(std::chrono::seconds(6));
    A.Add(std::shared_ptr<Task>(new Default_Task([]()
                                                 { PRINT << "WHO IS SHE?????" << END; })),
          LOW);
    std::this_thread::sleep_for(std::chrono::seconds(2));

    A.Stop();
}

void Stop()
{
    ThreadPool A(6);
    for (int i = 0; i < 10000; ++i)
    {
        A.Add(std::shared_ptr<Task>(new Default_Task(foo3)), LOW);
        A.Add(std::shared_ptr<Task>(new Default_Task(foo1)), HIGH);
        A.Add(std::shared_ptr<Task>(new Default_Task(foo2)), MEDIUM);
    }

    std::this_thread::sleep_for(std::chrono::seconds(2));
    A.Run();
    A.Stop();

    A.Add(std::shared_ptr<Task>(new Default_Task([]()
                                                 { PRINT << "Add task after stop" << END; })),
          LOW);
    A.Run();
}

void SetNum()
{
    ThreadPool A(6);
    for (int i = 0; i < 1000; ++i)
    {
        A.Add(std::shared_ptr<Task>(new Default_Task(foo3)), LOW);
        A.Add(std::shared_ptr<Task>(new Default_Task(foo1)), HIGH);
        A.Add(std::shared_ptr<Task>(new Default_Task(foo2)), MEDIUM);
    }

    std::this_thread::sleep_for(std::chrono::seconds(2));
    A.Run();

    A.SetNumberOfThreads(8);
    A.SetNumberOfThreads(3);

    for (int i = 0; i < 1000; ++i)
    {
        A.Add(std::shared_ptr<Task>(new Default_Task(foo3)), LOW);
        A.Add(std::shared_ptr<Task>(new Default_Task(foo1)), HIGH);
        A.Add(std::shared_ptr<Task>(new Default_Task(foo2)), MEDIUM);
    }

    A.SetNumberOfThreads(7);
    A.SetNumberOfThreads(2);

    std::this_thread::sleep_for(std::chrono::seconds(10));
    A.Add(std::shared_ptr<Task>(
              new Default_Task([]()
                               { PRINT << "Thanks for all the fish" << END; })),
          LOW);

    std::this_thread::sleep_for(std::chrono::seconds(1));
}
