#include <iostream>

#include "shared_ptr.hpp"

using namespace std;

namespace ilrd
{
    template <class T>
    SharedPtr<T>::SharedPtr(T *ptr) : m_ptr(ptr), m_reference_count
    {
    }
    /*undefined behaviour if pointee does not point to dynamically allocated object*/
    explicit SharedPtr(T *pointee = 0);
    SharedPtr(const SharedPtr<T> &other) noexcept; // non-explicit
    template <class Y>
    SharedPtr<T> &operator=(const SharedPtr<Y> &other) noexcept;
    ~SharedPtr() noexcept;
    T &operator*() const;
    T *operator->() const noexcept;
    T *GetPtr() const noexcept;

    template <class T, class Y>
    bool operator==(const SharedPtr<T> &lhs, const SharedPtr<Y> &rhs)
    {
    }

    template <class T, class Y>
    bool operator!=(const SharedPtr<T> &lhs, const SharedPtr<Y> &rhs)
    {
    }
}