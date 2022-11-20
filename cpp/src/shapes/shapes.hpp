#ifndef __ILRD_RD12123_SHAPES_HPP__
#define __ILRD_RD12123_SHAPES_HPP__

#include <cstddef> // size_t

#if (__cplusplus >= 201103)
#define NOEXCEPT noexcept
#else
#define NOEXCEPT throw()
#endif

namespace ilrd
{
    class Shape
    {
    public:
        explicit Shape();
        virtual void Draw() const = 0;
        void Move(size_t offset);

        virtual ~Shape();

    private:
        size_t m_offset;
    };

    class Line : public Shape
    {
    public:
        virtual void Draw() const;
    };

    class Circle : public Shape
    {
    public:
        virtual void Draw() const;
    };

    class Rectangle : public Shape
    {
    public:
        virtual void Draw() const;
    };

    class Square : public Shape
    {
    public:
        virtual void Draw() const;
    };
}

#endif // __ILRD_RD12123_SHAPES_HPP__