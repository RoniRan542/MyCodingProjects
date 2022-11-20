/****************************************************
 *Name : Ran Aharon Cohen	 	    			    *
 *Date: 	14.07.22		            		    *
 *Description :	check whether the string of numbers *
 *includes 2 numbers that sum up to 10 			    *
 ***************************************************/
#include <assert.h> /* assert */
#include <string.h> /* strchr */
#include <stdio.h>

#define TARGET_SUM (10)
#define LUT_SIZE (11)
#define GET_DIG(c) (c - '0')
#define GET_CHR(i) (i + '0')

enum status
{
    SUCCESS = 0,
    FALSE = 0,
    FAILURE = 1,
    TRUE = 1
};

/* a simple solution O(n)*/
int IsSumTenStr(const char *str)
{
    char complement = 0;

    assert(str);

    while ('\0' != *str)
    {
        complement = TARGET_SUM - GET_DIG(*str);
        if (NULL != strchr(str, GET_CHR(complement)))
        {
            return TRUE;
        }
        ++str;
    }

    return FALSE;
}

/* a better solution O(n) - Hagar*/

int IsTenSumFound(const char *str)
{
    size_t digits_lut[LUT_SIZE] = {0};

    assert(NULL != str);

    while ('\0' != *str)
    {
        if (0 != digits_lut[TARGET_SUM - (*str - '0')])
        {
            return TRUE;
        }

        ++digits_lut[*str - '0'];
        ++str;
    }

    return FALSE;
}

int main()
{
    const char *str = "62222022222242";

    printf("is sum of ten: %d\n", IsSumTenStr(str));
    printf("is ten sum: %d\n", IsTenSumFound(str));

    return SUCCESS;
}
