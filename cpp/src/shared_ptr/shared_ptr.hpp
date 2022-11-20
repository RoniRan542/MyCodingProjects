/*
date: 04.09.22
author: Ran
Reviwer: Adaya
file: shared_ptr
*/
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
    class SharedPtr
    {
    public:
        /*undefined behaviour if pointee does not point to dynamically allocated object*/
        explicit SharedPtr(T *pointee = 0);
        SharedPtr(const SharedPtr<T> &other) noexcept; // non-explicit
        template <class Y>
        SharedPtr(const SharedPtr<Y> &other) noexcept; // non-explicit
        SharedPtr<T> &operator=(const SharedPtr<T> &other) noexcept;
        template <class Y>
        SharedPtr<T> &operator=(const SharedPtr<Y> &other) noexcept;
        ~SharedPtr() noexcept;
        T &operator*() const noexcept;
        T *operator->() const noexcept;
        T *GetPtr() const noexcept;

    private:
        template <class Y>
        friend size_t *GetRefCount(const SharedPtr<Y> &shptr) noexcept;
        void ClearPtr();
        T *m_ptr;
        size_t *m_reference_count;
    };

    template <class T>
    SharedPtr<T>::SharedPtr(T *ptr)
        : m_ptr(ptr), m_reference_count(new std::size_t(1))
    {
        // empty
    }

    template <class T>
    SharedPtr<T>::~SharedPtr() noexcept
    {
        ClearPtr();
    }

    template <class T>
    SharedPtr<T>::SharedPtr(const SharedPtr<T> &other) noexcept
        : m_ptr(other.GetPtr()), m_reference_count(GetRefCount(other))
    {
        ++(*m_reference_count);
    }

    template <class T>
    template <class Y>
    SharedPtr<T>::SharedPtr(const SharedPtr<Y> &other) noexcept
        : m_ptr(other.GetPtr()), m_reference_count(GetRefCount(other))
    {
        ++(*m_reference_count);
    }

    template <class T>
    SharedPtr<T> &SharedPtr<T>::operator=(const SharedPtr<T> &other) noexcept
    {
        if (*this != other)
        {
            ClearPtr();
            m_ptr = other.GetPtr();
            m_reference_count = GetRefCount(other);
            ++(*m_reference_count);
        }

        return *this;
    }

    template <class T>
    template <class Y>
    SharedPtr<T> &SharedPtr<T>::operator=(const SharedPtr<Y> &other) noexcept
    {
        if (*this != other)
        {
            ClearPtr();
            m_ptr = other.GetPtr();
            m_reference_count = GetRefCount(other);
            ++(*m_reference_count);
        }

        return *this;
    }

    template <class T>
    T &SharedPtr<T>::operator*() const noexcept
    {
        return *m_ptr;
    }

    template <class T>
    T *SharedPtr<T>::operator->() const noexcept
    {
        return m_ptr;
    }

    template <class T>
    T *SharedPtr<T>::GetPtr() const noexcept
    {
        return m_ptr;
    }

    template <class T>
    size_t *GetRefCount(const SharedPtr<T> &shptr) noexcept
    {
        return shptr.m_reference_count;
    }

    template <class T, class Y>
    bool operator==(const SharedPtr<T> &lhs, const SharedPtr<Y> &rhs)
    {
        return lhs.GetPtr() == rhs.GetPtr();
    }

    template <class T, class Y>
    bool operator!=(const SharedPtr<T> &lhs, const SharedPtr<Y> &rhs)
    {
        return !(lhs == rhs);
    }

    template <class T>
    void SharedPtr<T>::ClearPtr()
    {

        if (1 == *m_reference_count)
        {
            delete m_reference_count;
            m_reference_count = nullptr;
            delete m_ptr;
            m_ptr = nullptr;
        }
        else
        {
            --(*m_reference_count);
        }
    }
}
#endif //__ILRD_RD12123_SHARED_PTR_HPP__
