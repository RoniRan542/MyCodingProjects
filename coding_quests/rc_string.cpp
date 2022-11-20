/************************************************************
 *Name : Ran Aharon Cohen	 	    			            *
 *Date: 14.07.22		            		                *
 *Description : implement reference string class            *
 ************************************************************/
#include <iostream>
#include <cstring>

namespace ilrd
{
    class String
    {
    public:
        explicit String(const char *str_ = "");
        ~String();
        String &operator=(const String &other);
        String &operator=(const char *str_);
        char *GetStr() const;

    private:
        struct RC
        {
            char *m_str;
            std::size_t m_count;
        };

        RC *m_rc;
    };

    String::String(const char *str_) : m_rc(new (RC))
    {
        std::size_t len = strlen(str_) + 1;
        m_rc->m_str = new char[len];

        memcpy(m_rc->m_str, str_, len);
        m_rc->m_count = 1;
    }

    String::~String()
    {
        std::cout << "ctor\n";

        if (1 == m_rc->m_count)
        {
            delete[] m_rc->m_str;
            m_rc->m_str = 0;

            delete m_rc;
        }
        else
        {
            --(m_rc->m_count);
        }

        m_rc = 0;
    }

    String &String ::operator=(const String &other)
    {
        if (this != &other)
        {
            if (1 == m_rc->m_count)
            {
                delete[] m_rc->m_str;
                m_rc->m_str = 0;

                delete m_rc;
                m_rc = 0;
            }
            else
            {
                --m_rc->m_count;
            }

            m_rc = other.m_rc;
            ++m_rc->m_count;
        }

        return *this;
    }

    String &String ::operator=(const char *str_)
    {
        *this = String(str_);

        return *this;
    }

    char *String::GetStr() const
    {
        return m_rc->m_str;
    }
}

int main()
{
    using namespace ilrd;

    String s1("neta");
    String s2("hagar");

    std::cout << "before:\n";
    std::cout << "s1 = " << s1.GetStr() << std::endl;
    std::cout << "s2 = " << s2.GetStr() << std::endl;

    s1 = s2;

    std::cout << "\nafter:\n";
    std::cout << "s1 = " << s1.GetStr() << std::endl;
    std::cout << "s2 = " << s2.GetStr() << std::endl;

    s1 = "jeorje";

    std::cout << "\nstring literal:\n";
    std::cout << "s1 = " << s1.GetStr() << std::endl;

    return 0;
}
