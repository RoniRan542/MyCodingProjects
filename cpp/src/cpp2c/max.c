#include <stdio.h>
#include "max.h"

TEMPLATE_MAX(int)
TEMPLATE_MAX(double)

int main()
{
    int a = Max_int(5, 6);
    float b = Max_double(5.5, 6.5);
    printf("a = %d, b = %f\n", a, b);
    return 0;
}