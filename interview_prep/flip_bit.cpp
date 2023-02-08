#include <cstdio>
#include <climits>
#include <cstring>

int FlipBit(int val, unsigned int n)
{
    unsigned int tmp1 = INT_MAX;
    unsigned int tmp2 = 1;
    tmp1 ^= (1 << (n - 1));
    tmp2 <<= (n - 1);

    if (val & tmp2)
    {
        return (val & tmp1);
    }

    return (val | tmp2);
}

unsigned int numSetBits(unsigned int val)
{
    int count = 0;

    while (val)
    {
        ++count;
        val &= (val - 1);
    }

    return count;
}

long Nfibonacci(int n)
{
    long fib1 = 0;
    long fib2 = 1;
    long tmp = 0;

    if (n == 0)
    {
        return 0;
    }
    else if (n == 1)
    {
        return 1;
    }

    while (n > 0)
    {
        tmp = fib2;
        fib2 = fib1 + fib2;
        fib1 = tmp;
        --n;
    }

    return fib2;
}

int MultiplyByEight(int num)
{
    return (num << 3);
}

void foo()
{
    char *s1 = "hello";
    char s2[] = "hello";
    char *s3 = s1;
    printf("%lu %lu %lu %lu \n", sizeof(s1), sizeof(s2), strlen(s1), strlen(s2));

    // s3[0] = 'H';
    printf("%s \n", s3);
}

struct S
{
    int *i;
    char c;
    int *j;
    short s;
};

struct S2
{
    unsigned char c : 1;
    int *j;
    unsigned int i : 2;
    unsigned short s : 3;
    unsigned char x : 2;
};

union
{
    char array[3];
    char i;
    short s;
} jack;

void foo2()
{
    size_t array[] = {0, 1, 2, 3, 4, 5};
    size_t val = 3;
    printf("%lu \n", val[array]);
    printf("sizeof int is %lu \n", sizeof(int));
    printf("sizeof struct S is %lu \n", sizeof(struct S));
    printf("sizeof struct S2 is %lu \n", sizeof(struct S2));
    printf("sizeof jack is %lu \n", sizeof(jack));
}

int main()
{
    // printf("the result of %d with bit %d fliped is %d\n", 1, 3, FlipBit(1, 3));
    // printf("the result of %d with bit %d fliped is %d\n", 5, 3, FlipBit(5, 3));
    // printf("the result of %d with bit %d fliped is %d\n", 1, 4, FlipBit(1, 4));
    // printf("the number of set bits in %u is %u\n", 1, numSetBits(1));
    // printf("the number of set bits in %u is %u\n", 9, numSetBits(9));
    // printf("the number of set bits in %u is %u\n", 15, numSetBits(15));
    // printf("the number of set bits in %u is %u\n", 255, numSetBits(255));

    // printf("the %d fibonacci is %d\n", 1, Nfibonacci(1));
    // printf("the %d fibonacci is %d\n", 2, Nfibonacci(2));
    // printf("the %d fibonacci is %d\n", 3, Nfibonacci(3));
    // printf("the %d fibonacci is %d\n", 4, Nfibonacci(4));
    // printf("the %d fibonacci is %d\n", 5, Nfibonacci(5));
    // printf("the %d fibonacci is %d\n", 6, Nfibonacci(6));
    // printf("the %d fibonacci is %d\n", 6, Nfibonacci(7));
    // printf("the %d fibonacci is %d\n", 6, Nfibonacci(8));
    // printf("the %d fibonacci is %d\n", 6, Nfibonacci(9));
    // printf("the %d fibonacci is %ld\n", 10, Nfibonacci(50));
    // printf("the %d fibonacci is %ld\n", 10, Nfibonacci(80));

    // printf("%d * 8 = %d\n", 4, MultiplyByEight(4));
    // printf("%d * 8 = %d\n", 5, MultiplyByEight(5));
    // printf("%d * 8 = %d\n", 10, MultiplyByEight(10));

    foo();
    foo2();
    return 0;
}