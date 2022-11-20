
#ifndef __RD12123_DISPATCHER_HPP__
#define __RD12123_DISPATCHER_HPP__

#if __cplusplus <= (199711L)
#define noexcept throw()
#define nullptr 0
#endif

#include <list>     //list API
#include <iostream> // for std API

namespace ilrd
{
    template <class EVENT>
    class Dispatcher;
    template <class EVENT>
    class Listener
    {
    public:
        Listener();
        Listener(const Listener &other) = delete;
        Listener(Listener &&other) = delete;
        Listener &operator=(const Listener &other) = delete;
        Listener &operator=(Listener &&other) = delete;
        virtual ~Listener() noexcept;

    private:
        friend class Dispatcher<EVENT>;
        std::list<Dispatcher<EVENT> *> m_dispatchers;
        virtual void Invoke(const EVENT &) = 0;
        virtual void PublisherDied(void) = 0;
    };
    template <class EVENT>
    Listener<EVENT>::Listener()
    {
        // empty
    }

    template <class EVENT>
    Listener<EVENT>::~Listener() noexcept
    {
        while (!m_dispatchers.empty())
        {
            Dispatcher<EVENT> *curr_disp = m_dispatchers.front();

            curr_disp->RemoveListener(this);
        }
    }

    template <class EVENT>
    class Default_Listener : public Listener<EVENT>
    {
    private:
        using pub_died_func = void (*)(void);
        using invoke_func = void (*)(const EVENT &);

    public:
        Default_Listener(pub_died_func publisher_died, invoke_func invoke);

    private:
        pub_died_func m_pub_died;
        invoke_func m_invoke;
        virtual void Invoke(const EVENT &event);
        virtual void PublisherDied(void);
    };

    template <class EVENT>
    Default_Listener<EVENT>::Default_Listener(pub_died_func publisher_died, invoke_func invoke)
        : m_pub_died(publisher_died), m_invoke(invoke)
    {
        // empty
    }

    template <class EVENT>
    void Default_Listener<EVENT>::Invoke(const EVENT &event)
    {
        (*m_invoke)(event);
    }

    template <class EVENT>
    void Default_Listener<EVENT>::PublisherDied(void)
    {
        (*m_pub_died)();
    }

    template <class EVENT>
    class Dispatcher
    {
    public:
        Dispatcher();
        Dispatcher(const Dispatcher &other);
        Dispatcher(Dispatcher &&other) = delete;
        Dispatcher &operator=(Dispatcher &&other) = delete;
        Dispatcher &operator=(const Dispatcher &other);
        ~Dispatcher() noexcept;
        void AddListener(Listener<EVENT> *new_listener);
        void RemoveListener(Listener<EVENT> *new_listener) noexcept;
        void Invoke(const EVENT &e);

    private:
        std::list<Listener<EVENT> *> m_listeners;
    };

    template <class EVENT>
    Dispatcher<EVENT>::Dispatcher()
    {
        // empty
    }

    template <class EVENT>
    Dispatcher<EVENT>::Dispatcher(const Dispatcher &other)
    {
        for (auto const &listener : other.m_listeners)
        {
            AddListener(listener);
        }
    }

    template <class EVENT>
    Dispatcher<EVENT> &Dispatcher<EVENT>::operator=(const Dispatcher &other)
    {
        if (this != &other)
        {
            for (auto const &listener : m_listeners)
            {
                listener->PublisherDied();
                RemoveListener(listener);
            }

            for (auto const &listener : other.m_listeners)
            {
                AddListener(listener);
            }
        }

        return *this;
    }

    template <class EVENT>
    Dispatcher<EVENT>::~Dispatcher() noexcept
    {
        while (!m_listeners.empty())
        {
            Listener<EVENT> *curr_lis = m_listeners.front();
            curr_lis->PublisherDied();
            RemoveListener(curr_lis);
        }
    }

    template <class EVENT>
    void Dispatcher<EVENT>::AddListener(Listener<EVENT> *new_listener)
    {
        m_listeners.push_back(new_listener);
        new_listener->m_dispatchers.push_back(this);
    }

    template <class EVENT>
    void Dispatcher<EVENT>::RemoveListener(Listener<EVENT> *listener_to_remove) noexcept
    {
        m_listeners.remove(listener_to_remove);
        listener_to_remove->m_dispatchers.remove(this);
    }

    template <class EVENT>
    void Dispatcher<EVENT>::Invoke(const EVENT &e)
    {
        for (auto const &listener : m_listeners)
        {
            listener->Invoke(e);
        }
    }
}

#endif //__RD12123_DISPATCHER_HPP__