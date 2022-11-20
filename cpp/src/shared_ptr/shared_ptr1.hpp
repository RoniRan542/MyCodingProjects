#ifndef __ILRD_RD12123_SHARED_PTR_HPP__
#define __ILRD_RD12123_SHARED_PTR_HPP__

#include <cstddef>

#if __cplusplus <= (199711L)
#define noexcept throw()
#define nullptr 0
#endif

namespace ilrd
{
    template <class T>
    class Shared_Pointer
    {
    public:
        /*undefined behaviour if pointee does not point to dynamically allocated object*/
        explicit Shared_Pointer(T *pointee = 0);
        Shared_Pointer(const Shared_Pointer<T> &other) noexcept;
        template <class Y>
        Shared_Pointer(const Shared_Pointer<Y> &other) noexcept; // non-explicit
        Shared_Pointer<T> &operator=(const Shared_Pointer<T> &other) noexcept;
        template <class Y>
        Shared_Pointer<T> &operator=(const Shared_Pointer<Y> &other) noexcept;
        ~Shared_Pointer() noexcept;
        T &operator*() const; // why no noexcept?
        T *operator->() const noexcept;
        T *GetPtr() const noexcept;

    private:
        template <class R>
        friend size_t *GetRC(const Shared_Pointer<R> &ptr) noexcept; // why in private?
        void DeleteRef() noexcept;                                   // why is this a member function? just define it outside with a param
        size_t *m_reference_count;
        T *m_ptr;
    };

    template <class T, class Y>
    bool operator==(const Shared_Pointer<T> &lhs, const Shared_Pointer<Y> &rhs);

    template <class T, class Y>
    bool operator!=(const Shared_Pointer<T> &lhs, const Shared_Pointer<Y> &rhs);

    template <class T>
    Shared_Pointer<T>::Shared_Pointer(T *pointee)
        : m_reference_count(new size_t(1)), m_ptr(pointee)
    {
        // empty
    }

    template <class T>
    Shared_Pointer<T>::Shared_Pointer(const Shared_Pointer<T> &other) noexcept
        : m_reference_count(GetRC(other)), m_ptr(other.m_ptr) // use func GetPtr
    {
        ++(*GetRC(other));
    }

    template <class T>
    template <class Y>
    Shared_Pointer<T>::Shared_Pointer(const Shared_Pointer<Y> &other) noexcept
        : m_reference_count(GetRC(other)), m_ptr(other.GetPtr())
    {
        ++(*GetRC(other));
    }

    template <class T>
    Shared_Pointer<T> &Shared_Pointer<T>::
    operator=(const Shared_Pointer<T> &other) noexcept
    {
        ++*GetRC(other); // put it at the bottum
        DeleteRef();
        m_reference_count = GetRC(other);
        m_ptr = other.GetPtr(); // for logical order: put this above
        return *this;           // line space
    }

    template <class T>
    template <class Y>
    Shared_Pointer<T> &Shared_Pointer<T>::
    operator=(const Shared_Pointer<Y> &other) noexcept
    {
        ++*GetRC(other);
        DeleteRef();
        m_reference_count = GetRC(other);
        m_ptr = other.GetPtr();
        return *this;
    }

    template <class T>
    Shared_Pointer<T>::~Shared_Pointer() noexcept
    {
        DeleteRef();
    }

    template <class T>
    T &Shared_Pointer<T>::operator*() const
    {
        return *m_ptr;
    }

    template <class T>
    T *Shared_Pointer<T>::operator->() const noexcept
    {
        return m_ptr;
    }

    template <class T>
    T *Shared_Pointer<T>::GetPtr() const noexcept
    {
        return m_ptr;
    }

    template <class R>
    size_t *GetRC(const Shared_Pointer<R> &ptr) noexcept
    {
        return ptr.m_reference_count;
    }

    template <class T, class Y>
    bool operator==(const Shared_Pointer<T> &lhs, const Shared_Pointer<Y> &rhs)
    {
        return lhs.GetPtr() == rhs.GetPtr();
    }

    template <class T, class Y>
    bool operator!=(const Shared_Pointer<T> &lhs, const Shared_Pointer<Y> &rhs)
    {
        return false == (lhs == rhs); // use ! for clearness?
    }

    template <class T>
    void Shared_Pointer<T>::DeleteRef() noexcept
    {
        if (1 == *m_reference_count)
        {
            delete (m_reference_count);
            m_reference_count = nullptr;
            delete (m_ptr);
            m_ptr = nullptr;
        }
        else
        {
            --*m_reference_count;
        }
    }
}
#endif //__ILRD_RD12123_SHARED_PTR_HPP__