
#ifndef __SEMAPHORE_CPP__
#define __SEMAPHORE_CPP__

#include <mutex>
#include <cstring>
#include <condition_variable>

class Semaphore
{

public:
    Semaphore(unsigned long sem_limit) : m_sem_count(sem_limit)
    {
        // empty
    }

    void wait()
    {
        std::unique_lock<std::mutex> u_lock(m_sem_lock);
        while (!m_sem_count)
        {
            m_sem_cond_var.wait(u_lock);
        }
        m_sem_count--;
    }

    void post()
    {
        std::unique_lock<std::mutex> u_lock(m_sem_lock);
        m_sem_count++;
        u_lock.unlock();
        m_sem_cond_var.notify_one();
    }

private:
    std::mutex m_sem_lock;
    std::condition_variable m_sem_cond_var;
    unsigned long m_sem_count;
};

#endif /* __SEMAPHORE_CPP__ */