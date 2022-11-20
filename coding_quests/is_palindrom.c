/************************************************************
 *Name : Ran Aharon Cohen	 	    			            *
 *Date: 14.07.22		            		                *
 *Description : check if the string includes a palindrom    *
 ************************************************************/
#include <assert.h> /* assert */
#include <string.h> /* strchr */
#include <stdio.h>

#define TARGET (10)
#define GET_DIG(c) (c - '0')
#define GET_CHR(i) (i + '0')

enum status
{
    SUCCESS = 0,
    FALSE = 0,
    FAILURE = 1,
    TRUE = 1
};

int IsPalindrom(const char *str)
{
    size_t i = 0;
    char x1 = 0;
    char x2 = 0;

    assert(str);

    x1 = str[0];
    x2 = str[1];

    for (i = 2; i < strlen(str); i++)
    {
        if (x1 == x2 || x1 == str[i])
        {
            return TRUE;
        }
        x1 = x2;
        x2 = str[i];
    }

    return FALSE;
}

int main()
{
    const char *str = "gsabz";

    printf("is palindrom: %d\n", IsPalindrom(str));

    return SUCCESS;
}
