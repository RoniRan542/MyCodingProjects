/* -------------------------------------------------------------------------- *
 * FILENAME      -    handleton.hpp
 * -------------------------------------------------------------------------- *
 * AUTHOR        -    Ran Aharon Cohen
 * STATUS        -    not tested
 * REVIEWER      -
 * DATE          -    26/10/22
 * -------------------------------------------------------------------------- */

#ifndef __RD12123_HANDLETON_HPP__
#define __RD12123_HANDLETON_HPP__

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
    class Handleton : private boost::noncopyable
    {
    public:
        static Base *GetInstance();
        static void DestroyHandleton();

    private:
        Handleton();
        static bool m_handleton_destroyed;
        static Base *m_instance;
        static boost::mutex m_mutex;
    };
    template <class Base>
    bool Handleton<Base>::m_handleton_destroyed = false;
    template <class Base>
    boost::mutex Handleton<Base>::m_mutex;
    template <class Base>
    Base *Handleton<Base>::m_instance = nullptr;

#ifdef SHARED_LIBRARY
    template <class Base>
    Base *Handleton<Base>::GetInstance()
    {
        boost::lock_guard<boost::mutex> lck_gd(m_mutex);
        if (true == m_handleton_destroyed)
        {
            std::abort();
        }

        if (nullptr == m_instance)
        {
            m_instance = new Base;
            std::atexit(DestroyHandleton);
        }

        return m_instance;
    }

    template <class Base>
    void Handleton<Base>::DestroyHandleton()
    {
        boost::lock_guard<boost::mutex> lck_gd(m_mutex);
        delete m_instance;
        m_instance = nullptr;
        m_handleton_destroyed = true;
    }
#endif // SHARED_LIBRARY
}

#endif //__RD12123_HANDLETON_HPP__