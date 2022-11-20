
#include <iostream> // for std to test prints and offsetof
#include <cstring>  // for strlen and strcmp

#include "RCString.hpp"

using namespace std;

const size_t g_max_input_size = 100;
const size_t g_char_ptr = sizeof(char *);

namespace ilrd_RCString
{

    typedef struct rc_data
    {
        size_t rc;
        char *m_str;
    } rc_data_t;

    static rc_data_t *CreateObject(const char *str);

    RCString::RCString(const char *str_) : m_x(CreateObject(str_))
    {
        // empty;
    }

    RCString::~RCString()
    {
        if (m_x->rc == 1)
        {
            operator delete(m_x);
            m_x = 0;
        }
        else
        {
            --m_x->rc;
        }
    }

    RCString::RCString(const RCString &other_) throw() : m_x(other_.m_x)
    {
        ++m_x->rc;
    }

    RCString &RCString::operator=(const RCString &other_) throw()
    {
        if (m_x != other_.m_x)
        {
            this->~RCString();
            m_x = other_.m_x;
            ++m_x->rc;
        }

        return *this;
    }

    size_t RCString::Length() const throw()
    {
        return strlen(m_x->m_str);
    }

    const char *RCString::RCstr() const throw()
    {
        return m_x->m_str;
    }

    char &RCString::operator[](size_t pos)
    {

        const char *copy = m_x->m_str;
        if (1 < m_x->rc)
        {
            --m_x->rc;
            m_x = CreateObject(copy);
        }

        return m_x->m_str[pos];
    }

    char RCString::operator[](size_t pos) const
    {
        return m_x->m_str[pos];
    }

    ostream &operator<<(std::ostream &os, const RCString &x)
    {
        return os << x.RCstr();
    }

    istream &operator>>(std::istream &is, RCString &x)
    {
        char temp[g_max_input_size] = "";
        is >> temp;
        RCString copy(temp);
        x = copy;

        return is;
    }

    bool operator==(const RCString &lhs, const RCString &rhs) throw()
    {
        return 0 == strcmp(lhs.RCstr(), rhs.RCstr());
    }

    bool operator!=(const RCString &lhs, const RCString &rhs) throw()
    {
        return !(lhs == rhs);
    }

    bool operator>(const RCString &lhs, const RCString &rhs) throw()
    {
        return (0 < strcmp(lhs.RCstr(), rhs.RCstr()));
    }

    bool operator<(const RCString &lhs, const RCString &rhs) throw()
    {
        return rhs > lhs;
    }

    static rc_data_t *CreateObject(const char *str)
    {
        try
        {
            size_t len = strlen(str);
            rc_data_t *obj_data = static_cast<rc_data_t *>(operator new(sizeof(rc_data_t) + len + 1));
            size_t offset = offsetof(rc_data_t, m_str);
            obj_data->m_str = reinterpret_cast<char *>(obj_data) + offset + g_char_ptr;
            memcpy(obj_data->m_str, str, len + 1);
            obj_data->rc = 1;
            return obj_data;
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
            throw(e);
        }
    }

}
