/****************************************************
 *Name : Ran Aharon Cohen	 	    			    *
 *Date: 	14.07.22		            		    *
 *Description :	Implement a Barrier.                *
 *You have 3  threads in your process , each one of *
 *the threads call a lock function ,                *
 *First and second thread will be blocked, the third*
 *thread will release all of them.                  *
 ****************************************************/
#include <iostream>
#include <string.h>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <atomic>

using namespace std;

class Barrier
{
public:
    Barrier();
    void InitBarrier(size_t total_threads_in_system);
    void BarrierLock();

private:
    std::condition_variable m_cv;
    std::mutex m_mtx;
    std::atomic_int m_counter;
};

Barrier::Barrier()
{
}

void Barrier::InitBarrier(size_t total_threads_in_system)
{
    m_counter = total_threads_in_system;
    std::cout << m_counter << std::endl;
}

void Barrier::BarrierLock()
{
    std::unique_lock<std::mutex> lck(m_mtx);
    --m_counter;
    while (m_counter > 0)
    {
        m_cv.wait(lck);
    }

    m_cv.notify_all();
}

void Foo(Barrier *brr)
{
    brr->BarrierLock();
    std::cout << "hhhhhhhhh\n";
}

int main()
{
    Barrier brr;

    std::thread th[3];
    brr.InitBarrier(3);
    th[0] = std::thread(Foo, &brr);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    th[1] = std::thread(Foo, &brr);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    th[2] = std::thread(Foo, &brr);

    th[0].join();
    th[1].join();
    th[2].join();

    return 0;
}
