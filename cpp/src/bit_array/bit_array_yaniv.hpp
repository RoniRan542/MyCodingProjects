#ifndef __RD12123_BIT_ARRAY_HPP__
#define __RD12123_BIT_ARRAY_HPP__

#include <cstddef>   //size_t
#include <string>    //string
#include <vector>    //vector
#include <algorithm> //foreach
#include <numeric>   //accumulate
#include "bit_array_functors_yaniv.hpp"

#if __cplusplus <= (199711L)
#define noexcept throw()
#define nullptr 0
#endif

static const size_t bits_in_byte = 8;

namespace ilrd
{
    template <size_t N>
    class BitArray
    {
    private:
        class BitHandler;

    public:
        explicit BitArray();

        BitHandler operator[](size_t pos);
        bool operator[](size_t pos) const;

        bool operator==(const BitArray &other) const noexcept;
        bool operator!=(const BitArray &other) const noexcept;

        bool Get(size_t pos) const;
        BitArray &Set(size_t pos, bool value);
        BitArray &SetAll(bool value) noexcept;
        BitArray &Flip(size_t pos);
        BitArray &FlipAll() noexcept;
        size_t Count() const noexcept;
        std::string ToString() const;

        BitArray &operator|=(const BitArray &other) noexcept;
        BitArray &operator&=(const BitArray &other) noexcept;
        BitArray &operator^=(const BitArray &other) noexcept;

    private:
        std::vector<char> m_array;
        class BitHandler
        {
        public:
            explicit BitHandler(BitArray *arr, size_t pos) noexcept;
            BitHandler &operator=(bool other) noexcept;

            operator bool() const noexcept;
            // add an operator overload to the ! operator
        private:
            BitArray *m_arr;
            size_t m_index;
            // you can put it up, not compiler problems
            BitHandler &operator=(BitHandler &other) noexcept; // to make the compiler shut up about it
        };
    };

    template <size_t N>
    BitArray<N>::BitArray()
    {
        // better to init vars in the init list
        size_t bytes = (N / bits_in_byte) + !!(N % bits_in_byte);
        m_array.resize(bytes);
    }

    template <size_t N>
    bool BitArray<N>::operator[](size_t pos) const
    {
        size_t bit_location = pos / bits_in_byte;
        size_t bit_location_in_byte = pos - (bit_location * bits_in_byte);
        char byte = m_array[bit_location];
        // you can drop the !!. equivalnt to (1 << bit_location_in_byte)
        return !!(byte & (1 << bit_location_in_byte));
    }

    template <size_t N>
    typename BitArray<N>::BitHandler BitArray<N>::operator[](size_t pos)
    {
        return BitHandler(this, pos);
    }

    // TODO: what is this implementation for?

    /*     template<size_t N>
        typename BitArray<N>::BitHandler &BitArray<N>::BitHandler::operator=(const BitHandler &other) noexcept
        {
            m_arr->Set(other.m_index,other.m_arr->Get(other.m_index));

            return *this;
        } */

    template <size_t N>
    bool BitArray<N>::operator==(const BitArray &other) const noexcept
    {
        return m_array == other.m_array;
    }

    template <size_t N>
    bool BitArray<N>::operator!=(const BitArray &other) const noexcept
    {
        return !(m_array == other.m_array);
    }

    template <size_t N>
    bool BitArray<N>::Get(size_t pos) const
    {
        size_t bit_location = pos / bits_in_byte;
        size_t bit_location_in_byte = pos - (bit_location * bits_in_byte);
        char byte = m_array.at(bit_location);

        // you can drop the !!. equivalnt to (1 << bit_location_in_byte)
        return !!(byte & (1 << bit_location_in_byte));
    }

    static void SetBitOn(size_t pos, char &byte)
    {
        char mask = 1 << pos;
        byte |= mask;
    }

    static void SetBitOff(size_t pos, char &byte)
    {
        char mask = 1 << pos;
        byte &= (~mask);
    }

    template <size_t N>
    BitArray<N> &BitArray<N>::Set(size_t pos, bool value)
    {
        size_t bit_location = pos / bits_in_byte;
        size_t bit_location_in_byte = pos - (bit_location * bits_in_byte);
        char &byte = m_array.at(bit_location);

        if (value)
        {
            SetBitOn(bit_location_in_byte, byte);
        }
        else
        {
            SetBitOff(bit_location_in_byte, byte);
        }

        return *this;
    }

    template <size_t N>
    BitArray<N> &BitArray<N>::SetAll(bool value) noexcept
    {
        char byte_to_set = '\0';
        unsigned char byte_tbl[8] = {255, 1, 3, 7, 15, 31, 63, 127};

        if (value)
        {
            byte_to_set = ~byte_to_set;
        }

        std::for_each(m_array.begin(), m_array.end(), SetAllFunc(byte_to_set));
        m_array[N / bits_in_byte] &= byte_tbl[N % bits_in_byte];

        return *this;
    }

    template <size_t N>
    BitArray<N> &BitArray<N>::Flip(size_t pos)
    {
        size_t bit_location = pos / bits_in_byte;
        size_t bit_location_in_byte = pos - (bit_location * bits_in_byte);
        char byte = m_array.at(bit_location);
        // you should combine 177 and 178 to one line
        char new_byte = ((true) << bit_location_in_byte);
        m_array.at(bit_location) = byte ^ new_byte;

        return *this;
    }

    template <size_t N>
    BitArray<N> &BitArray<N>::FlipAll() noexcept
    {
        unsigned char byte_tbl[8] = {255, 1, 3, 7, 15, 31, 63, 127};

        std::for_each(m_array.begin(), m_array.end(), FlipFunctor());
        // Yaffe!! maybe give it a separate func for clearness(reset_spare_bits() )
        m_array[N / bits_in_byte] &= byte_tbl[N % bits_in_byte];

        return *this;
    }

    template <size_t N>
    size_t BitArray<N>::Count() const noexcept
    {
        size_t count = 0;
        // just return the function
        count = accumulate(m_array.begin(), m_array.end(), 0, CountFunc());

        return count;
    }

    template <size_t N>
    std::string BitArray<N>::ToString() const
    {
        //  I think the right way to initialize is str("")
        std::string str = "";
        str = std::accumulate(m_array.begin(), m_array.end(), str, ToStringFunc());

        str.resize(N);
        return str;
    }

    template <size_t N>
    BitArray<N> &BitArray<N>::operator|=(const BitArray<N> &other) noexcept
    {
        std::for_each(m_array.begin(), m_array.end(), OrFunctor(&(other.m_array)));

        return *this;
    }

    template <size_t N>
    BitArray<N> &BitArray<N>::operator&=(const BitArray<N> &other) noexcept
    {
        std::for_each(m_array.begin(), m_array.end(), AndFunctor(&(other.m_array)));

        return *this;
    }

    template <size_t N>
    BitArray<N> &BitArray<N>::operator^=(const BitArray<N> &other) noexcept
    {
        std::for_each(m_array.begin(), m_array.end(), XorFunctor(&(other.m_array)));

        return *this;
    }

    template <size_t N>
    BitArray<N>::BitHandler::BitHandler(BitArray *arr, size_t pos) noexcept : m_arr(arr), m_index(pos)
    {
        // Empty
    }

    template <size_t N>
    typename BitArray<N>::BitHandler &BitArray<N>::BitHandler::operator=(bool other) noexcept
    {
        // I think BitHandler shouldn't depend on BitArray imlementation. Should be the oposit
        m_arr->Set(m_index, other);

        return *this;
    }

    template <size_t N>
    BitArray<N>::BitHandler::operator bool() const noexcept
    {
        /* return m_arr->Get(m_index); */
        return (*const_cast<const BitArray<N> *>(m_arr))[m_index];
    }

} // namespace ilrd
#endif //__RD12123_BIT_ARRAY_HPP__