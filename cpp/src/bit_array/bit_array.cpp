#ifndef __RD12123_BIT_ARRAY_HPP__
#define __RD12123_BIT_ARRAY_HPP__

#include <cstddef> //size_t
#include <string>  //string
#include <vector>  //vector

#include "bit_array_helper.hpp"

#if __cplusplus <= (199711L)
#define noexcept throw()
#define nullptr 0
#endif

// Macros to generate the lookup table (at compile-time)
#define B2(n) n, n + 1, n + 1, n + 2
#define B4(n) B2(n), B2(n + 1), B2(n + 1), B2(n + 2)
#define B6(n) B4(n), B4(n + 1), B4(n + 1), B4(n + 2)
#define COUNT_BITS B6(0), B6(1), B6(1), B6(2)
#define WORD_SIZE (sizeof(size_t))
#define ALING_WORD_SIZE (WORD_SIZE - 1)
#define ALIGNED_BITS ((N + ALING_WORD_SIZE) & ~ALING_WORD_SIZE)
#define ALIGNED_BYTES (ALIGNED_BITS / WORD_SIZE)

unsigned int setbits_lookup[256] = {COUNT_BITS};
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

int countSetBits(int n)
{
    int count = setbits_lookup[n & 0xff] +         // consider the first 8 bits
                setbits_lookup[(n >> 8) & 0xff] +  // consider the next 8 bits
                setbits_lookup[(n >> 16) & 0xff] + // consider the next 8 bits
                setbits_lookup[(n >> 24) & 0xff];  // consider last 8 bits

    return count;
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

#endif //__RD12123__BitArray_HPP__AND