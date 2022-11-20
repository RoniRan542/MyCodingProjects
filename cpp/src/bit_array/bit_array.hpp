/*********************************
Author: Ran
Reviewer: Roee
Date: 07.09.22
**********************************/
#ifndef __RD12123_BIT_ARRAY_HPP__
#define __RD12123_BIT_ARRAY_HPP__

#include <cstddef>   //size_t
#include <string>    //string
#include <numeric>   //for accumulate
#include <vector>    //vector
#include <algorithm> // STL algorithms

#include "bit_array_helper.hpp"

#if __cplusplus <= (199711L)
#define noexcept throw()
#define nullptr 0
#endif

#define WORD_SIZE (sizeof(size_t))
#define ALIGN_WORD_SIZE (WORD_SIZE - 1)
#define ALIGNED_BITS ((N + ALIGN_WORD_SIZE) & ~ALIGN_WORD_SIZE)
#define ALIGNED_BYTES (ALIGNED_BITS / WORD_SIZE)

namespace ilrd
{
    template <size_t N>
    class BitArray
    {
    private:
        class BitHandler;

    public:
        explicit BitArray();
        BitHandler operator[](size_t index) noexcept;
        bool operator[](size_t index) const noexcept;
        BitArray &operator|=(const BitArray &other) noexcept;
        BitArray &operator&=(const BitArray &other) noexcept;
        BitArray &operator^=(const BitArray &other) noexcept;
        bool operator==(const BitArray &other) const noexcept;
        bool operator!=(const BitArray &other) const noexcept;
        bool Get(size_t index) const;
        BitArray &Set(size_t index, bool val);
        BitArray &SetAll(bool val) noexcept;
        BitArray &Flip(size_t index);
        BitArray &FlipAll() noexcept;
        size_t Count() const noexcept;
        std::string ToString() const;

    private:
        std::vector<u_char> m_bits_container;

        /* ****************************************************************************
         *                      inner class BitHandler                                *
         ******************************************************************************/
        class BitHandler
        {
        public:
            BitHandler(BitArray *ptr, size_t bit_index) noexcept;
            ~BitHandler() noexcept;
            BitHandler &operator=(const BitHandler &other) noexcept;
            BitHandler &operator=(bool val) noexcept;
            BitHandler &operator!() noexcept;
            operator bool() const noexcept;

        private:
            BitArray *m_arr_ptr;
            size_t m_bit_index;
        };
    };

    template <size_t N>
    BitArray<N>::BitArray() : m_bits_container(ALIGNED_BYTES, 0)
    {
        // empty
    }
    template <size_t N>
    typename BitArray<N>::BitHandler BitArray<N>::operator[](size_t index) noexcept
    {
        return BitHandler(this, index);
    }

    template <size_t N>
    bool BitArray<N>::operator[](size_t index) const noexcept
    {
        return Get(index);
    }

    template <size_t N>
    bool BitArray<N>::Get(size_t index) const
    {
        Assert(index, N);

        u_char mask = 1;
        size_t char_num = index / WORD_SIZE;
        mask <<= index % WORD_SIZE;

        return (m_bits_container.at(char_num) & mask);
    }

    template <size_t N>
    BitArray<N> &BitArray<N>::Set(size_t index, bool val)
    {
        Assert(index, N);

        size_t char_num = index / WORD_SIZE;
        u_char reset_bit = 1;
        reset_bit <<= index % WORD_SIZE;
        m_bits_container.at(char_num) &= ~reset_bit;

        u_char mask = val;
        mask <<= index % WORD_SIZE;
        m_bits_container.at(char_num) ^= mask;

        return *this;
    }

    template <size_t N>
    BitArray<N> &BitArray<N>::SetAll(bool val) noexcept
    {
        u_char mask = (val ? 0xff : 0);
        std::for_each(m_bits_container.begin(),
                      m_bits_container.end(), FunctorSet(mask));
        ResetRemainderBits(m_bits_container, N, ALIGNED_BYTES);

        return *this;
    }

    template <size_t N>
    BitArray<N> &BitArray<N>::Flip(size_t index)
    {
        Assert(index, N);

        Set(index, !(Get(index)));

        return *this;
    }

    template <size_t N>
    BitArray<N> &BitArray<N>::FlipAll() noexcept
    {
        std::for_each(m_bits_container.begin(),
                      m_bits_container.end(), FunctorFlip());
        ResetRemainderBits(m_bits_container, N, ALIGNED_BYTES);
        return *this;
    }

    template <size_t N>
    bool BitArray<N>::operator==(const BitArray &other) const noexcept
    {
        return m_bits_container == other.m_bits_container;
    }

    template <size_t N>
    bool BitArray<N>::operator!=(const BitArray &other) const noexcept
    {
        return !(*this == other);
    }

    template <size_t N>
    BitArray<N> &BitArray<N>::operator|=(const BitArray &other) noexcept
    {
        std::for_each(m_bits_container.begin(),
                      m_bits_container.end(), FunctorOr(other.m_bits_container));

        return *this;
    }

    template <size_t N>
    BitArray<N> &BitArray<N>::operator&=(const BitArray &other) noexcept
    {
        std::for_each(m_bits_container.begin(),
                      m_bits_container.end(), FunctorAnd(other.m_bits_container));

        return *this;
    }

    template <size_t N>
    BitArray<N> &BitArray<N>::operator^=(const BitArray &other) noexcept
    {
        std::for_each(m_bits_container.begin(),
                      m_bits_container.end(), FunctorXor(other.m_bits_container));

        return *this;
    }

    template <size_t N>
    size_t BitArray<N>::Count() const noexcept
    {

        return std::accumulate(m_bits_container.begin(),
                               m_bits_container.end(), 0, FunctorAddSetBits());
    }

    template <size_t N>
    std::string BitArray<N>::ToString() const
    {
        std::string str_output("");
        std::for_each(m_bits_container.begin(),
                      m_bits_container.end(), FunctorConcatBits(str_output));
        size_t on_bits_index = N % WORD_SIZE;

        return str_output.substr(WORD_SIZE - on_bits_index, ALIGNED_BITS);
    }

    template <size_t N>
    BitArray<N>::BitHandler::BitHandler(BitArray *ptr, size_t bit_index) noexcept
        : m_arr_ptr(ptr), m_bit_index(bit_index)
    {
        // empty
    }

    template <size_t N>
    BitArray<N>::BitHandler::~BitHandler() noexcept
    {
        // empty
    }

    template <size_t N>
    typename BitArray<N>::BitHandler &BitArray<N>::BitHandler::operator=(const BitHandler &other) noexcept
    {
        size_t char_num = m_bit_index / WORD_SIZE;
        u_char reset_bit = 1;
        reset_bit <<= m_bit_index % WORD_SIZE;
        m_arr_ptr->m_bits_container.at(char_num) &= ~reset_bit;

        u_char mask = bool(other);
        mask <<= m_bit_index % WORD_SIZE;
        m_arr_ptr->m_bits_container.at(char_num) ^= mask;

        return *this;
    }

    template <size_t N>
    typename BitArray<N>::BitHandler &BitArray<N>::BitHandler::operator=(bool val) noexcept
    {
        u_char mask = val;
        size_t char_num = m_bit_index / WORD_SIZE;
        mask <<= m_bit_index % WORD_SIZE;

        u_char reset_bit = 1;
        reset_bit <<= m_bit_index % WORD_SIZE;

        m_arr_ptr->m_bits_container.at(char_num) &= ~reset_bit;
        m_arr_ptr->m_bits_container.at(char_num) ^= mask;

        return *this;
    }

    template <size_t N>
    BitArray<N>::BitHandler::operator bool() const noexcept
    {
        u_char mask = 1;
        size_t char_num = m_bit_index / WORD_SIZE;
        mask <<= m_bit_index % WORD_SIZE;

        return (m_arr_ptr->m_bits_container.at(char_num) & mask);
    }

    template <size_t N>
    typename BitArray<N>::BitHandler &BitArray<N>::BitHandler::operator!() noexcept
    {
        *this = !(bool(*this));

        return *this;
    }

}

#endif //__RD12123__BitArray_HPP__AND