// bits mirroring  - brute force to efficient
#include <iostream>

size_t MirrorBits(size_t num)
{
    num = ((num & 0x5555555555555555UL) << 1) | ((num & 0xAAAAAAAAAAAAAAAAUL) >> 1);
    num = ((num & 0x3333333333333333UL) << 2) | ((num & 0xCCCCCCCCCCCCCCCCUL) >> 2);
    num = ((num & 0x0f0f0f0f0f0f0f0fUL) << 4) | ((num & 0xf0f0f0f0f0f0f0f0UL) >> 4);
    num = ((num & 0x00ff00ff00ff00ffUL) << 8) | ((num & 0xff00ff00ff00ff00UL) >> 8);
    num = ((num & 0x0000ffff0000ffffUL) << 16) | ((num & 0xffff0000ffff0000UL) >> 16);
    num = ((num & 0x00000000ffffffffUL) << 32) | ((num & 0xffffffff00000000UL) >> 32);

    return num;
}

int main()
{
    std::cout << MirrorBits(15) << std::endl;

    return 0;
}
