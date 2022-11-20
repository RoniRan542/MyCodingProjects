#ifndef __RD12123_WAITABLE_QUEUE_HPP__
#define __RD12123_WAITABLE_QUEUE_HPP__

#include <queue>              // queue
#include <mutex>              //mutex
#include <atomic>             //atomic<std::uint64_t>
#include <condition_variable> //condition_variable
#include <chrono>             //chrono::seconds /milli
#include <iostream>           // std::cout
#include <thread>             // std::thread

namespace ilrd
{
    // T -copyable and assignable
    // Q - must support front(), pop(), push()
    template <class T, class Q = std::queue<T>>
    class Waitable_Queue
    {
    public:
        explicit Waitable_Queue();
        Waitable_Queue(const Waitable_Queue &other) = delete;
        void operator=(const Waitable_Queue &other) = delete;
        bool IsEmpty() const noexcept;
        void Push(const T &data);
        void Pop();
        void Pop(T &outparam);
        bool Pop(T &outparam, const std::chrono::seconds &timeout);
        bool Pop(T &outparam, const std::chrono::milliseconds &timeout);
        size_t GetSize() const noexcept;

    private:
        std::atomic<std::uint64_t> m_size;
        Q m_queue;
        std::mutex m_lock;
        std::condition_variable m_cond;
    };

    template <class T, class Q>
    Waitable_Queue<T, Q>::Waitable_Queue() : m_size(0)
    {
        // empty
    }

    template <class T, class Q>
    bool Waitable_Queue<T, Q>::IsEmpty() const noexcept
    {
        return m_size == 0;
    }

    template <class T, class Q>
    void Waitable_Queue<T, Q>::Push(const T &data)
    {
        std::unique_lock<std::mutex> writelock(m_lock);
        m_queue.push(data);
        ++m_size;
        m_cond.notify_one();
    }

    template <class T, class Q>
    void Waitable_Queue<T, Q>::Pop()
    {
        std::unique_lock<std::mutex> readlock(m_lock);

        while (0 == m_size)
        {
            m_cond.wait(readlock);
        }

        m_queue.pop();
        --m_size;
    }

    template <class T, class Q>
    void Waitable_Queue<T, Q>::Pop(T &outparam)
    {
        std::unique_lock<std::mutex> readlock(m_lock);

        while (0 == m_size)
        {
            m_cond.wait(readlock);
        }

        outparam = m_queue.front();
        m_queue.pop();
        --m_size;
    }

    template <class T, class Q>
    bool Waitable_Queue<T, Q>::Pop(T &outparam, const std::chrono::seconds &timeout)
    {
        return Pop(outparam, std::chrono::duration_cast<std::chrono::milliseconds>(timeout));
    }
    template <class T, class Q>
    bool Waitable_Queue<T, Q>::Pop(T &outparam, const std::chrono::milliseconds &timeout)
    {
        std::unique_lock<std::mutex> readlock(m_lock);
        while (0 == m_size)
        {
            if (m_cond.wait_for(readlock, timeout) == std::cv_status::timeout)
            {
                std::cout << "failed \n";
                return false;
            }
        }

        outparam = m_queue.front();
        m_queue.pop();
        --m_size;

        return true;
    }

    template <class T, class Q>
    size_t Waitable_Queue<T, Q>::GetSize() const noexcept
    {
        return m_size;
    }
}

#endif //__RD12123_WAITABLE_QUEUE_HPP__
