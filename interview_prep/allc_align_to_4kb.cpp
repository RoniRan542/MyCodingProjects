// how would u impl an aligned malloc and an aligned free  (aligned to 4kb*)

#include <iostream>

static const int k_bytes = 1024;
static const int four_k_bytes = 4 * 1024;
static const int word_size = 8;

char *AllocAlignedMemory(size_t num_of_bytes)
{
    if (num_of_bytes % four_k_bytes == 0)
    {
        return (char *)malloc(num_of_bytes);
    }

    size_t new_amount = num_of_bytes + four_k_bytes;
    new_amount = new_amount & ~(four_k_bytes - 1);
    new_amount = new_amount + word_size;

    char *mem = (char *)malloc(new_amount);

    size_t gap = new_amount - num_of_bytes;

    char *new_ptr = mem + gap;
    *((size_t *)new_ptr - 1) = gap;

    return new_ptr;
}

void FreeAlignedMemory(char *ptr)
{
    size_t gap = *((size_t *)ptr - 1);

    free(ptr - gap);
}

int main()
{
    char *ptr = AllocAlignedMemory(4150);

    FreeAlignedMemory(ptr);

    return 0;
}