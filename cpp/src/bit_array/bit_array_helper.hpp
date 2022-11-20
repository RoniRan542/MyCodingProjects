#ifndef __BIT_ARRAY_HELP__
#define __BIT_ARRAY_HELP__

#include <iostream>
#include "bit_array.hpp"

// Macros to generate the lookup table (at compile-time)
#define B2(n) n, n + 1, n + 1, n + 2
#define B4(n) B2(n), B2(n + 1), B2(n + 1), B2(n + 2)
#define B6(n) B4(n), B4(n + 1), B4(n + 1), B4(n + 2)
#define COUNT_BITS B6(0), B6(1), B6(1), B6(2)

u_char setbits_lookup[256] = {COUNT_BITS};
const size_t g_word_size = sizeof(size_t);
const std::string str_bits_lookup[16] = {
    "0000",
    "0001",
    "0010",
    "0011",
    "0100",
    "0101",
    "0110",
    "0111",
    "1000",
    "1001",
    "1010",
    "1011",
    "1100",
    "1101",
    "1110",
    "1111"};

class FunctorSet;
class FunctorFlip;
class FunctorConcatBits;
class FunctorOr;
class FunctorAnd;
class FunctorXor;
class FunctorAddSetBits;

void GetByteStr(u_char c, std::string &result);
u_char countSetBits(u_char c);
void ResetRemainderBits(std::vector<u_char> &m_bits_container, size_t bit_size, size_t byte_size);
inline void Assert(size_t pos, size_t n);

inline void Assert(size_t pos, size_t n)
{
    if (pos >= n)
    {
        throw std::out_of_range("position out of range");
    }
}

void GetByteStr(u_char c, std::string &result)
{
    result.insert(0, str_bits_lookup[c & 0x0f]);
    result.insert(0, str_bits_lookup[(c & 0xf0) >> 4]);
}

u_char countSetBits(u_char c)
{
    u_char count = setbits_lookup[c & 0xff];

    return count;
}

void ResetRemainderBits(std::vector<u_char> &m_bits_container, size_t bit_size, size_t byte_size)
{
    unsigned char on_bits[] = {255, 1, 3, 7, 15, 31, 63, 127};
    size_t on_bits_index = bit_size % g_word_size;
    m_bits_container.at(byte_size - 1) &= on_bits[on_bits_index];
}

class FunctorSet
{
public:
    FunctorSet(u_char val) : m_val(val) {}
    void operator()(u_char &byte)
    {
        byte = m_val;
    }

private:
    u_char m_val;
};

class FunctorFlip
{
public:
    void operator()(u_char &byte) const
    {
        byte = ~byte;
    }
};

class FunctorOr
{
public:
    FunctorOr(std::vector<u_char> other) : other_container(other), index(0) {}

    void operator()(u_char &byte)
    {
        byte |= other_container.at(index++);
    }

private:
    std::vector<u_char> other_container;
    size_t index;
};

class FunctorAnd
{
public:
    FunctorAnd(std::vector<u_char> other) : other_container(other), index(0) {}

    void operator()(u_char &byte)
    {
        byte &= other_container.at(index++);
    }

private:
    std::vector<u_char> other_container;
    size_t index;
};

class FunctorXor
{
public:
    FunctorXor(std::vector<u_char> other) : other_container(other), index(0) {}

    void operator()(u_char &byte)
    {
        byte ^= other_container.at(index++);
    }

private:
    std::vector<u_char> other_container;
    size_t index;
};

class FunctorAddSetBits
{
public:
    size_t operator()(int &count, const u_char &byte)
    {
        count += countSetBits(byte);

        return count;
    }
};

class FunctorConcatBits
{
public:
    FunctorConcatBits(std::string &str) : m_str(str) {}
    void operator()(const u_char &byte)
    {
        GetByteStr(byte, m_str);
    }

private:
    std::string &m_str;
};

#endif