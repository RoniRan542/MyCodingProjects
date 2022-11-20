
#include <stdio.h>
static unsigned int lut_assci[256] = {0};

void InitLut(int *lut)
{
    lut['I'] = 1;
    lut['V'] = 5;
    lut['X'] = 10;
    lut['L'] = 50;
    lut['C'] = 100;
    lut['D'] = 500;
    lut['M'] = 1000;
}

int romanToInt(char *s)
{

    int prev = 0;
    int sum = 0;

    while (*s != '\0')
    {
        if (prev * 10 == lut_assci[*s] || prev * 5 == lut_assci[*s])
        {
            sum += (lut_assci[*s] - prev) - prev;
            prev = 0;
        }
        else
        {
            sum += lut_assci[*s];
            prev = lut_assci[*s];
        }
        ++s;
    }

    return sum;
}

int main()
{
    InitLut(lut_assci);
    printf("III = %d \n", romanToInt("III"));
    printf("LVIII = %d \n", romanToInt("LVIII"));
    printf("MCMXCIV = %d \n", romanToInt("MCMXCIV"));

    return 0;
}