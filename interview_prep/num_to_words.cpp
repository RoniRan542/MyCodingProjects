/*

Convert a given number to string

 */
#include <stdio.h>
#include <iostream>
#include <chrono>

/* typedef struct data
{
    char str[10];
    int count;
} data_t; */

int CountDigits(int number)
{
    int counter = 0;

    while (number)
    {
        number /= 10;
        ++counter;
    }

    return counter;
}

int CreateDevider(int digits)
{
    int tens = 1;
    --digits;
    while (digits--)
    {
        tens *= 10;
    }

    return tens;
}

void ConvertIntToString(int number)
{
    char lut1[20][10] = {
        " ", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven", "twelve", "thirteen",
        "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
    char lut2[10][10] = {" ", " ", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};
    char lut3[4][10] = {"", "thousand", "million", "billion"};
    int temp1 = 0;
    int temp2 = 0;
    int temp3 = 0;
    int digits = CountDigits(number);
    int devider = CreateDevider(digits);
    int lut3_index = (digits / 3) - (!(digits % 3));

    while (digits > 0)
    {
        if ((digits % 3) == 0)
        {
            if ((number / devider) != 0)
            {
                printf("%s ", lut1[number / devider]);
                printf("hundrad ");
                number %= devider;
                devider /= 10;
                --digits;
            }
            else
            {
                --digits;
                devider /= 10;
                printf("and ");
            }
        }
        else if ((digits % 3) == 2)
        {
            if ((number / devider) == 0)
            {
                --digits;
            }
            else
            {
                temp1 = number / devider;
                number %= devider;
                devider /= 10;
                temp2 = number / devider;
                temp3 = (temp1 * 10) + temp2;

                if (temp3 < 20)
                {
                    printf("%s ", lut1[temp3]);
                }
                else
                {
                    printf("%s ", lut2[temp1]);
                    printf("%s ", lut1[temp2]);
                }
                digits -= 2;
            }

            number %= devider;
            devider /= 10;
        }
        else
        {
            printf("%s ", lut1[number / devider]);
            number %= devider;
            devider /= 10;
            --digits;
        }

        if (digits % 3 == 0)
        {
            printf("%s ", lut3[lut3_index--]);
        }
    }

    printf("\n");
}

int main()
{
    // Start the timer
    auto start = std::chrono::high_resolution_clock::now();

    ConvertIntToString(5);
    ConvertIntToString(50);
    ConvertIntToString(55);
    ConvertIntToString(555);
    ConvertIntToString(5555);
    ConvertIntToString(5555333);
    ConvertIntToString(199364412);
    ConvertIntToString(10001);
    ConvertIntToString(10011);
    ConvertIntToString(11011);
    ConvertIntToString(110111);

    // Stop the timer
    auto stop = std::chrono::high_resolution_clock::now();

    // Calculate the elapsed time
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "Elapsed time: " << elapsed.count() << " microseconds" << std::endl;

    return 0;
}
