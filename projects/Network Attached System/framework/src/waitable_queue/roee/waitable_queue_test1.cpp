/************************************************
*Name: Roee Kishon                              *
*Reviewer:                                      *
*Date: 07.09.22                                 *
*File: waitable_queue.hpp                       *
************************************************/

#include <iostream>
#include <thread>
#include <chrono>

#include "waitable_queue.hpp"

#define RUNTEST(test) {\
            if (!test)\
            {\
                std::cout << "OK\n";\
            }\
            else\
            {\
                std::cout << "FAILURE\n";\
            }\
        }

using namespace ilrd;

int Life();
void Pusher(int i, Waitable_Queue<int> *wq);
void Popper(int i, Waitable_Queue<int> *wq);

int main()
{
    RUNTEST(Life());

    return 0;
}

int Life()
{
    int result = 0;
    int i = 1;
    Waitable_Queue<int> wq;

    std::thread t1(Pusher, i++, &wq);
    t1.join();
    std::thread t2(Pusher, i++, &wq);
    t2.join();
    std::thread t3(Pusher, i++, &wq);
    t3.join();
    std::thread t4(Pusher, i++, &wq);
    t4.join();

    std::cout << "POPPERS\n";

    i = 1;
    std::thread t5(Popper, i++, &wq);
    std::thread t6(Popper, i++, &wq);
    std::thread t7(Popper, i++, &wq);
    std::thread t8(Popper, i++, &wq);

    t5.join();
    t6.join();
    t7.join();
    t8.join();

    return result;
}

void Pusher(int i, Waitable_Queue<int> *wq)
{
    std::cout << "Pusher " << i << " executing" << std::endl;
    wq->Push(i);
    std::cout << "Pusher " << i << " done" << std::endl;
}

void Popper(int i, Waitable_Queue<int> *wq)
{
    int popped_i = -1;
    std::cout << "Popper " << i << " executing" << std::endl;
    std::chrono::milliseconds ms(100);
    wq->Pop(popped_i, ms);

    std::cout << "Popper " << i << " popped " << popped_i << std::endl;
}

