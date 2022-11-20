#ifndef __ILRD_RD12123_RCSTRING_HPP__
#define __ILRD_RD12123_RCSTRING_HPP__

#include <iosfwd>  /*std*/
#include <cstddef> /*c size_t*/

namespace ilrd_RCString
{
    class RCString
    {
    public:
        RCString(const char *str = ""); // non explicit by intention
        RCString(const RCString &other) noexcept;
        RCString &operator=(const RCString &other) noexcept;
        ~RCString();
        size_t Length() const noexcept;
        const char *RCstr() const noexcept;
        char &operator[](size_t pos);
        char operator[](size_t pos) const; // char c = S1[3];

    private:
        typedef struct rc_data rc_data_t;
        rc_data_t *m_x;
    };
    bool operator==(const RCString &s1, const RCString &s2) noexcept;
    bool operator!=(const RCString &s1, const RCString &s2) noexcept;
    bool operator>(const RCString &s1, const RCString &s2) noexcept;
    bool operator<(const RCString &s1, const RCString &s2) noexcept;
    std::ostream &operator<<(std::ostream &os, const RCString &x);
    std::istream &operator>>(std::istream &is, RCString &x);
}

#endif