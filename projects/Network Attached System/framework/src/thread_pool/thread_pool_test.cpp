/*********************************************************
 * author: Ran Aharon Cohen                              *
 * reviewer: Amir                                        *
 * date: 13.09.22                                        *
 * file: thread_pool test                              *
 *********************************************************/
#include <iostream> //cout
using namespace std;

#include "thread_pool.hpp"
using namespace ilrd;

#define RUNTEST(test)                     \
    {                                     \
        if (0 == test)                    \
        {                                 \
            cout << "\x1b[0;32m\n";       \
            cout << "OK!\n\n";            \
            cout << "\x1b[0m";            \
        }                                 \
        else                              \
        {                                 \
            cout << "\x1b[1;31m";         \
            cout << "\nTest Failed!\n\n"; \
            cout << "\x1b[0m";            \
        }                                 \
    }
#define TEST(x, y) ValCheck(x, y, __LINE__)
static int ValCheck(double expected_val, double recieved_val, int line);

size_t count_t1 = 0;
size_t count_t2 = 0;
size_t count_t3 = 0;
size_t count_t4 = 0;
size_t count_t5 = 0;
size_t count_t6 = 0;

void Task1()
{
    ++count_t1;
    cout << "test task1 HIGH\x1b[0;32m\n";
}

void Task2()
{
    ++count_t2;
    cout << "test task2 LOW\x1b[0;32m\n";
}
void Task3()
{
    ++count_t3;
    cout << "test task3 MEDIUM\x1b[0;32m\n";
}

void Task4()
{
    ++count_t4;
    cout << "test task4 LOW\x1b[0;32m\n";
}
void Task5()
{
    ++count_t5;
    cout << "test task5 HIGH\x1b[0;32m\n";
}
void Task6()
{
    ++count_t6;
    cout << "test task6 HIGH\x1b[0;32m\n";
}

int Phase1Test();

int main()
{
    cout << "---- Thread Pool ----\n";

    Phase1Test();

    return 0;
}

int Phase1Test()
{
    cout << "\n-- Phase 1 --\n";
    int result = 0;
    ThreadPool tp;

    for (size_t i = 0; i < 100; i++)
    {
        std::shared_ptr<Default_Task> shp1(new Default_Task(Task1));
        tp.Add(shp1, HIGH);
    }
    tp.Stop();
    for (size_t i = 0; i < 100; i++)
    {
        std::shared_ptr<Default_Task> shp1(new Default_Task(Task2));
        tp.Add(shp1, LOW);
    }

    for (size_t i = 0; i < 100; i++)
    {
        std::shared_ptr<Default_Task> shp1(new Default_Task(Task3));
        tp.Add(shp1, MEDIUM);
    }

    tp.Run();

    for (size_t i = 0; i < 100; i++)
    {
        std::shared_ptr<Default_Task> shp1(new Default_Task(Task4));
        tp.Add(shp1, LOW);
    }

    std::this_thread::sleep_for(std::chrono::seconds(2));
    tp.Pause();
    tp.SetNumberOfThreads(4);

    tp.Run();
    for (size_t i = 0; i < 100; i++)
    {
        std::shared_ptr<Default_Task> shp1(new Default_Task(Task5));
        tp.Add(shp1, HIGH);
    }

    tp.SetNumberOfThreads(16);

    for (size_t i = 0; i < 100; i++)
    {
        std::shared_ptr<Default_Task> shp1(new Default_Task(Task6));
        tp.Add(shp1, HIGH);
    }

    std::this_thread::sleep_for(std::chrono::seconds(2));
    tp.Pause();
    tp.Run();

    TEST(0, count_t1);
    TEST(100, count_t2);
    TEST(100, count_t3);
    TEST(100, count_t4);
    TEST(100, count_t5);
    TEST(100, count_t6);

    RUNTEST(result);

    return 0;
}

/******************************************************************************/

static int ValCheck(double expected_val, double recieved_val, int line)
{
    if (recieved_val != expected_val)
    {
        cout << "----------------FAIL line " << line << "----------------\n";
        cout << "got " << recieved_val << " when wanted " << expected_val << endl;
        return 1;
    }

    return 0;
}
