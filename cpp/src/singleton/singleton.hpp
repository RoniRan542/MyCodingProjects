#ifndef __RD12123_SINGLTON_HPP__
#define __RD12123_SINGLTON_HPP__

#include <boost/thread/mutex.hpp>
#include <cstdlib>
#include <boost/thread.hpp>
#include <boost/core/noncopyable.hpp>

#if __cplusplus <= (199711L)
#define noexcept throw()
#define nullptr 0
#endif

namespace ilrd
{
    template <class Base>
    class Singleton : private boost::noncopyable
    {

    public:
        static Base *GetInstance();
        static void DestroySingleton();

    private:
        Singleton();
        static bool m_singleton_destroyed;
        static Base *m_instance;
        static boost::mutex m_mutex;
    };

    template <class Base>
    bool Singleton<Base>::m_singleton_destroyed = false;
    template <class Base>
    boost::mutex Singleton<Base>::m_mutex;
    template <class Base>
    Base *Singleton<Base>::m_instance = nullptr;

    template <class Base>
    Base *Singleton<Base>::GetInstance()
    {
        boost::lock_guard<boost::mutex> lck_gd(m_mutex);
        if (true == m_singleton_destroyed)
        {
            std::abort();
        }

        if (nullptr == m_instance)
        {
            m_instance = new Base;
            std::atexit(DestroySingleton);
        }

        return m_instance;
    }

    template <class Base>
    void Singleton<Base>::DestroySingleton()
    {
        boost::lock_guard<boost::mutex> lck_gd(m_mutex);
        delete m_instance;
        m_instance = nullptr;
        m_singleton_destroyed = true;
    }

}

#endif //"__RD12123_SINGLTON_HPP__"