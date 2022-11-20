#ifndef __ILRD_RD12123_SIMPLE_STRING_HPP__
#define __ILRD_RD12123_SIMPLE_STRING_HPP__
#include <cstddef> //c size_t
#include <iostream>

namespace ilrd
{
    class String
    {
    public:
        String(const char *str_ = "");           // constructor (includes default)
        String(const String &other_);            // copy constructor
        ~String();                               // destructor
        String &operator=(const String &other_); // assignment operator
        const char *Cstr() const;                // get const char*
        size_t Length() const;                   // get length

    private:
        char *m_str;
    };

    std::ostream &operator<<(std::ostream &os, const String &x);
    bool operator==(const String &lhs, const String &rhs);
    bool operator>(const String &lhs, const String &rhs);
    bool operator<(const String &lhs, const String &rhs);

}

#endif