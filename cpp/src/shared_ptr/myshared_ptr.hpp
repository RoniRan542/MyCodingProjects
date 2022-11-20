#ifndef __SHARED_PTR__
#define __SHARED_PTR__

#include <cstddef> /*c size_t*/
#include <iosfwd>  /*std*/

namespace ilrd
{
    template <class T>
    class SharedPtr
    {
    public:
        explicit SharedPtr(T *pointee);
        explicit SharedPtr(const SharedPtr<T> &other) noexcept;
        SharedPtr<T> &operator=(const SharedPtr<T> &other) noexcept;
        template <class Y>
        SharedPtr<T> &operator=(const SharedPtr<Y> &other) : shared_resource(other.shared_resource) noexcept;
        ~SharedPtr();
        T &operator*() noexcept;
        T *operator->() noexcept;
        T *GetPtr() noexcept;

    private:
        size_t *rc;
        T *shared_resource;
    };
    template <class T>
    bool operator==(const SharedPtr<T> &sp1, const SharedPtr<T> &sp2) noexcept;
    template <class T>
    bool operator!=(const SharedPtr<T> &sp1, const SharedPtr<T> &sp2) noexcept;
}

#endif //__SHARED_PTR__