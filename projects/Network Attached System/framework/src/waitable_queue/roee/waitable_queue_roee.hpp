/************************************************
 *Name: Roee Kishon                              *
 *Reviewer:                                      *
 *Date: 07.09.22                                 *
 *File: waitable_queue.hpp                       *
 ************************************************/

#ifndef __RD12123_WAITABLE_QUEUE_HPP__
#define __RD12123_WAITABLE_QUEUE_HPP__

#include <queue>              // queue
#include <mutex>              //mutex
#include <atomic>             //atomic<std::uint64_t>
#include <chrono>             //chrono::seconds /milli
#include <condition_variable> //cond var

namespace ilrd
{
    // T -copyable and assignable
    // Q - must support T &front(), void pop(),
    //     void push(const T&)
    template <class T, class Q = std::queue<T>>
    class Waitable_Queue
    {
    public:
        explicit Waitable_Queue();
        Waitable_Queue(const Waitable_Queue &other) = delete;
        void operator=(const Waitable_Queue &other) = delete;
        bool IsEmpty() const noexcept;
        void Push(const T &data);
        void Pop(T &outparam);
        bool Pop(T &outparam, const std::chrono::seconds &timeout);
        bool Pop(T &outparam, const std::chrono::milliseconds &timeout);

    private:
        std::atomic<std::uint64_t> m_size;
        Q m_queue;
        std::mutex m_push_lock;
        std::mutex m_pop_lock;
        std::condition_variable m_cv;
    };

    template <class T, class Q>
    Waitable_Queue<T, Q>::Waitable_Queue() : m_size(0)
    {
        // empty
    }

    template <class T, class Q>
    bool Waitable_Queue<T, Q>::IsEmpty() const noexcept
    {
        return (0 == m_size);
    }

    template <class T, class Q>
    void Waitable_Queue<T, Q>::Push(const T &data)
    {
        std::unique_lock<std::mutex> ul(m_push_lock);

        m_queue.push(data);
        ++m_size;

        m_cv.notify_one();
    }

    template <class T, class Q>
    void Waitable_Queue<T, Q>::Pop(T &outparam)
    {
        std::unique_lock<std::mutex> ul(m_pop_lock);

        if (IsEmpty())
        {
            m_cv.wait(ul);
        }

        outparam = m_queue.front();
        m_queue.pop();
        --m_size;
    }

    template <class T, class Q>
    bool Waitable_Queue<T, Q>::Pop(T &outparam, const std::chrono::seconds &timeout)
    {
        return Pop(outparam,
                   std::chrono::duration_cast<std::chrono::milliseconds>(timeout));
    }

    template <class T, class Q>
    bool Waitable_Queue<T, Q>::Pop(T &outparam, const std::chrono::milliseconds &timeout)
    {
        std::unique_lock<std::mutex> ul(m_pop_lock);

        if (IsEmpty() && (std::cv_status::timeout == m_cv.wait_for(ul, timeout)))
        {
            return false;
        }

        outparam = m_queue.front();
        m_queue.pop();
        --m_size;

        return true;
    }
} // namespace ilrd

#endif //__RD12123_WAITABLE_QUEUE_HPP__
