
#include <iostream>
#include <cstring>

#include "simple_string.hpp"

using namespace std;

namespace ilrd
{
    static char *CreateObject(const char *str);

    String::String(const char *str_) : m_str(CreateObject(str_))
    {
        // empty;
    }

    String::~String()
    {
        delete[] m_str;
        m_str = 0;
    }

    String::String(const String &other_) : m_str(CreateObject(other_.Cstr()))
    {
        // empty
    }

    String &String::operator=(const String &other_)
    {
        try
        {
            if (this != &other_)
            {
                delete[] m_str;
                m_str = CreateObject(other_.Cstr());
            }
        }
        catch (exception &e)
        {
            delete[] m_str;
        }

        return *this;
    }

    size_t String::Length() const
    {
        return strlen(m_str);
    }

    const char *String::Cstr() const
    {
        return m_str;
    }

    ostream &operator<<(std::ostream &os, const String &x)
    {
        return os << x.Cstr();
    }
    bool operator==(const String &lhs, const String &rhs)
    {
        return 0 == strcmp(lhs.Cstr(), rhs.Cstr());
    }

    bool operator>(const String &lhs, const String &rhs)
    {
        return (0 < strcmp(lhs.Cstr(), rhs.Cstr()));
    }

    bool operator<(const String &lhs, const String &rhs)
    {
        return (0 > strcmp(lhs.Cstr(), rhs.Cstr()));
    }

    static char *CreateObject(const char *str)
    {
        size_t len = strlen(str);
        char *new_str = new char[len + 1];
        memcpy(new_str, str, len + 1);

        return new_str;
    }
}
