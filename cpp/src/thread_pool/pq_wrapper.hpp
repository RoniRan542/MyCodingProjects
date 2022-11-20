#ifndef __RD12123_PRIORITY_QUEUE_WRAPPER_HPP__
#define __RD12123_PRIORITY_QUEUE_WRAPPER_HPP__

#include <queue>
#include <functional>

namespace ilrd
{
    template <class T,
              class Container = std::vector<T>,
              class Compare = std::less<typename Container::value_type>>

    class PQwrapper
    {
    public:
        const T &front() const;
        void pop();
        void push(const T &value);
        bool empty() const;

    private:
        std::priority_queue<T, Container, Compare> m_queue;
    };
    template <class T, class Container, class Compare>
    const T &PQwrapper<T, Container, Compare>::front() const
    {
        return m_queue.top();
    }

    template <class T, class Container, class Compare>
    void PQwrapper<T, Container, Compare>::pop()
    {
        m_queue.pop();
    }

    template <class T, class Container, class Compare>
    void PQwrapper<T, Container, Compare>::push(const T &value)
    {
        m_queue.push(value);
    }

    template <class T, class Container, class Compare>
    bool PQwrapper<T, Container, Compare>::empty() const
    {
        return m_queue.empty();
    }
}
#endif //__RD12123_PRIORITY_QUEUE_WRAPPER_HPP__