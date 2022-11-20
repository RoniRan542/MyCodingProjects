#include <stdio.h>

#include "../include/bit_array.h"

#define R2(n) n, n + 2 * 64, n + 1 * 64, n + 3 * 64
#define R4(n) R2(n), R2(n + 2 * 16), R2(n + 1 * 16), R2(n + 3 * 16)
#define R6(n) R4(n), R4(n + 2 * 4), R4(n + 1 * 4), R4(n + 3 * 4)

bit_arr_t BitArrSetBitOn(bit_arr_t arr, uint64_t index)
{
    uint64_t mask = 1;
    mask <<= index;

    return (arr | mask);
}

bit_arr_t BitArrSetBitOff(bit_arr_t arr, uint64_t index)
{
    uint64_t mask = 1;
    mask <<= index;

    if (0 != (mask & arr))
    {
        arr ^= mask;
    }

    return arr;
}

bit_arr_t BitArrSetBit(bit_arr_t arr, uint64_t index, int bool_val)
{
    if (1 == bool_val)
    {
        return BitArrSetBitOn(arr, index);
    }

    return BitArrSetBitOff(arr, index);
}

int BitArrGetBitVal(bit_arr_t arr, uint64_t index)
{
    uint64_t mask = 1;
    mask <<= index;

    return (0 != (mask & arr));
}

bit_arr_t BitArrFlipBit(bit_arr_t arr, uint64_t index)
{
    return !BitArrGetBitVal(arr, index);
}

uint64_t BitArrCountOn(bit_arr_t arr)
{
    uint64_t counter = 0;

    while (0 != arr)
    {
        arr = arr & (arr - 1);
        ++counter;
    }

    return counter;
}

uint64_t BitArrCountOff(bit_arr_t arr)
{
    return (ARR_BIT_SIZE - BitArrCountOn(arr));
}

bit_arr_t BitArrSetAll(bit_arr_t arr)
{
    return ~(0 & arr);
}

bit_arr_t BitArrResetAll(bit_arr_t arr)
{
    (void)arr;
    return (~(uint64_t)0);
}

bit_arr_t BitArrRotateArrR(bit_arr_t arr, uint64_t shift)
{
    uint64_t rotate = shift % (ARR_BIT_SIZE);
    uint64_t lsb = 0;

    while (rotate--)
    {
        lsb = BitArrGetBitVal(arr, 0);
        arr >>= 1;

        if (1 == lsb)
        {
            arr = BitArrSetBitOn(arr, (ARR_BIT_SIZE)-1);
        }
    }

    return arr;
}

bit_arr_t AlternativeBitArrRotateArrR(bit_arr_t arr, uint64_t shift)
{
    shift %= ARR_BIT_SIZE;
    return arr << shift | arr >> (ARR_BIT_SIZE - shift);
}

bit_arr_t BitArrRotateArrL(bit_arr_t arr, uint64_t shift)
{
    uint64_t rotate = shift % (ARR_BIT_SIZE);
    uint64_t msb = 0;

    while (0 < rotate)
    {
        msb = BitArrGetBitVal(arr, (ARR_BIT_SIZE - 1));
        arr <<= 1;

        if (1 == msb)
        {
            arr = BitArrSetBitOn(arr, 0);
        }
        --rotate;
    }

    return arr;
}

bit_arr_t BitArrMirror(bit_arr_t arr)
{
    bit_arr_t mirror = 0;
    int i = 0;
    uint64_t mask = 1;

    while (arr)
    {
        mirror = mirror << 1;

        if (1 == (arr & mask))
        {
            mirror = mirror ^ mask;
        }
        arr = arr >> 1;
        ++i;
    }

    mirror <<= (ARR_BIT_SIZE - i);
    return mirror;
}

char *BitArrToString(bit_arr_t arr, char *dest)
{
    int i = (ARR_BIT_SIZE)-1;
    int bit = 0;
    char *runner = dest;
    if (NULL == dest)
    {
        return NULL;
    }

    while (0 <= i)
    {
        bit = BitArrGetBitVal(arr, i);
        *runner = bit + '0';
        ++runner;
        --i;
    }

    *runner += '\0';
    return dest;
}

bit_arr_t BitArrCountLut(bit_arr_t arr)
{
    int i = 0;
    char lookuptable[256] = {0};
    unsigned int count = 0;

    for (i = 0; i < 256; i++)
    {
        lookuptable[i] = (i & 1) + lookuptable[i / 2];
    }

    count = lookuptable[arr & 0xff] +
            lookuptable[(arr >> 8) & 0xff] +
            lookuptable[(arr >> 16) & 0xff] +
            lookuptable[(arr >> 24) & 0xff] +
            lookuptable[(arr >> 32) & 0xff] +
            lookuptable[(arr >> 40) & 0xff] +
            lookuptable[(arr >> 48) & 0xff] +
            lookuptable[(arr >> 56) & 0xff];

    return count;
}

bit_arr_t BitArrMirrorLut(bit_arr_t arr)
{
    int i = 0;
    int devider = 2;
    uint64_t lut[6] = {0xFFFFFFFF00000000, 0xFFFF0000FFFF0000, 0xFF00FF00FF00FF00,
                       0xF0F0F0F0F0F0F0F0, 0xCCCCCCCCCCCCCCCC, 0xAAAAAAAAAAAAAAAA};

    for (i = 0; 6 > i; ++i, devider *= 2)
    {
        arr = (arr & lut[i]) >> (ARR_BIT_SIZE / devider) |
              (arr & (~lut[i])) << (ARR_BIT_SIZE / devider);
    }

    return arr;
}
