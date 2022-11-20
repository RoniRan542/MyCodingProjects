#include <iostream>
#include <algorithm>

class OrFunctor
{
public:
    OrFunctor(const std::vector<char> *vector)
            :m_index(0),m_vector(vector)
    {
        //Empty
    }

    void operator() (char &byte)
    {
        byte |= m_vector->at(m_index);
        ++m_index;
    }
private:
    int m_index;
    const std::vector<char> *m_vector;
};

class AndFunctor
{
public:
    AndFunctor(const std::vector<char> *vector)
            :m_index(0),m_vector(vector)
    {
        //Empty
    }

    void operator() (char &byte)
    {
        byte &= m_vector->at(m_index);
        ++m_index;
    }
private:
    int m_index;
    const std::vector<char> *m_vector;
};

class XorFunctor
{
public:
    XorFunctor(const std::vector<char> *vector)
            :m_index(0),m_vector(vector)
    {
        //Empty
    }

    void operator() (char &byte)
    {
        byte ^= m_vector->at(m_index);
        ++m_index;
    }
private:
    int m_index;
    const std::vector<char> *m_vector;
};

class FlipFunctor
{
public:
    FlipFunctor(){}

    void operator() (char &byte)
    {
        byte = ~byte;
    }
};

class SetAllFunc
{
public:
    SetAllFunc(char set_to):m_set_to(set_to)
    {
        //Empty
    }

    void operator() (char &byte)
    {
        byte = m_set_to;
    }

private:
    char m_set_to;
};

class CountFunc
{
public:
    CountFunc(){}

    size_t operator() (int &value,char byte)
    {
        const u_int64_t m1  = 0x5555555555555555;
        const u_int64_t m2  = 0x3333333333333333;
        const u_int64_t m4  = 0x0f0f0f0f0f0f0f0f; 
        const u_int64_t h01 = 0x0101010101010101;

        byte -= ((byte >>  1) & m1 );
        byte = (byte & m2 ) + ((byte >>  2) & m2 ); 
        byte = ((byte + (byte >>  4)) & m4 );

        return (value += ((byte * h01) >> 56)); 
    }
};


class StringTransformFunc
{
public:
    StringTransformFunc(char byte):m_byte(byte)
    {
        //Empty
    }

    std::string operator() (std::string &str,char bit)
    {
        (void)bit;
        if((m_byte & 1))
        {
            str += "1";
        }
        else
        {
            str += "0";
        }
        m_byte>>=1;
        return str;
    }
private:
    char m_byte;
};

class ToStringFunc
{
public:
    ToStringFunc()
    {
        //Empty
    }

    std::string operator() (std::string &str ,char byte)
    {
        std::string fake_loop = "00000000";

        str = std::accumulate(fake_loop.begin(),fake_loop.end(),str,StringTransformFunc(byte));

        return str;
    }
};