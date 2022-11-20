/*********************************
Author: Ran
Reviewer: Nuri
Date: 29.08.22
**********************************/
#ifndef __SCOPELOCK__
#define __SCOPELOCK__

#include <boost/core/noncopyable.hpp> /*uncopyable*/
#include <exception>                  /*exception*/
#include <iostream>                   /*cerr*/

#if __cplusplus <= (199711L)
#define noexcept throw()
#define nullptr 0
#endif

namespace ilrd
{
    // T must implement Lock() and Unlock() functions
    template <typename T>
    class ScopeLock : private boost::noncopyable
    {
    public:
        explicit ScopeLock(T &lock);
        ~ScopeLock() noexcept;

    private:
        T &m_lock;
    };

    template <typename T>
    ScopeLock<T>::ScopeLock(T &lock) : m_lock(lock)
    {
        m_lock.lock();
    }

    template <typename T>
    ScopeLock<T>::~ScopeLock() noexcept
    {
        try
        {
            m_lock.unlock();
        }
        catch (std::exception &e)
        {
            std::cerr << "error in unlock " << e.what();
        }
    }
}

#endif //__SCOPELOCK_HPP__