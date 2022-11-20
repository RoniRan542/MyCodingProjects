#include <stdio.h> /* printf */ 

#include "calc.h"
#define RUNTEST(test) {\
            if (0 == test)\
            {\
                printf("\x1b[0;32m");\
                printf("OK!\n\n");\
                printf("\x1b[0m");\
            }\
            else\
            {\
                printf("\x1b[1;31m");\
                printf("Test Failed!\n\n");\
                printf("\x1b[0m");\
            }\
        }

int TestInt(int expected, int result);
int TestCreate(void);
int TestCalcPlusMinus(void);
int TestCalcMultiplication(void);
int TestCalcParenthesis(void);

int main()
{
    int result = 0;
    printf("\n\n***************************************************************\n");
    printf("*              Test For TestCalcPlusMinus Function                       *\n");
    printf("***************************************************************\n\n");
    result = TestCalcPlusMinus();
   	printf("THE FINAL RESULT OF THE TEST: ");
   	RUNTEST(result);
    printf("\n\n***************************************************************\n");
    printf("*              Test For TestCalcMultiplication Function                       *\n");
    printf("***************************************************************\n\n");
    result = TestCalcMultiplication();
   	printf("THE FINAL RESULT OF THE TEST: ");
   	RUNTEST(result);
   	printf("\n\n***************************************************************\n");
    printf("*              Test For TestCalcParenthesis Function                       *\n");
    printf("***************************************************************\n\n");
    result = TestCalcParenthesis();
   	printf("THE FINAL RESULT OF THE TEST: ");
   	RUNTEST(result);
    return 0;
}

int TestCreate(void)
{
	int result = 0;
	
	
	return result;
}

int TestCalcPlusMinus(void)
{
	int result = 0;
	double d_num = 0.00;
	double *d_result = &d_num;
	const char *input1 = "54+15";
	const char *input2 = "54-15+9-40";
	const char *input3 = "5*4";
	const char *input4 = "8/4";
	const char *input5 = "+555+4";
	const char *input6 = "5-10";
	const char *input7 = "10*4-2";
	const char *input8 = " 10-4*2";
	
	printf("Check if d_result return 69.0:\n");
	Calculate(input1, d_result);
	result += TestInt((double)69, *d_result);
	RUNTEST(result);
	printf("Check if d_result return 8.0:\n");
	Calculate(input2, d_result);
	result += TestInt((double)8, *d_result);
	RUNTEST(result);
	printf("Check if 5*4 return 20.0:\n");
	Calculate(input3, d_result);
	result += TestInt((double)20, *d_result);
	RUNTEST(result);
	printf("Check if 8/4 return 2.0:\n");
	Calculate(input4, d_result);
	result += TestInt((double)2, *d_result);
	RUNTEST(result);
	printf("Check if +555+4 return 559:\n");
	Calculate(input5, d_result);
	result += TestInt((double)559, *d_result);
	RUNTEST(result);
	printf("Check if 5-10 return -5.0:\n");
	Calculate(input6, d_result);
	result += TestInt((double)-5, *d_result);
	RUNTEST(result);
	printf("Check if 10*4-2 return 38.0:\n");
	Calculate(input7, d_result);
	result += TestInt((double)38, *d_result);
	RUNTEST(result);
	printf("Check if ' '10-4-2 return 0.00:\n");
	result += TestInt(2, Calculate(input8, d_result));/* change for Hadar */
	result += TestInt((double)0, *d_result);
	RUNTEST(result);
	
	return result; 
}

int TestCalcMultiplication(void)
{
	int result = 0;
	double d_num = 0.00;
	double *d_result = &d_num;
	const char *input1 = "54*15*16+55";
	const char *input2 = "54+15+9*40";
	const char *input3 = "5*4+5*4";
	const char *input4 = "8+4*2";
	const char *input5 = "*555*2";
	const char *input6 = "5-10*10";
	const char *input7 = "10*4/2";
	const char *input8 = "10 -4*2";
	const char *input9 = "5-10/10";
	const char *input10 = "10-4*2/0";
	
	printf("Check if d_result return 13015.0:\n");
	Calculate(input1, d_result);
	result += TestInt((double)13015, *d_result);
	RUNTEST(result);
	printf("Check if 5*4+5*4 return 40.0:\n");
	Calculate(input3, d_result);
	result += TestInt((double)40, *d_result);
	RUNTEST(result);
	printf("Check if *555*2 return error:\n");
	result += TestInt(2, Calculate(input5, d_result));/* change for Hadar */
	RUNTEST(result);
	printf("Check if d_result return 429.0:\n");
	Calculate(input2, d_result);
	result += TestInt((double)429, *d_result);
	RUNTEST(result);
	
	printf("Check if 8+4*2 return 16.0:\n");
	Calculate(input4, d_result);
	result += TestInt((double)16, *d_result);
	RUNTEST(result);
	
	printf("Check if 5-10*10 return -95.0:\n");
	Calculate(input6, d_result);
	result += TestInt((double)-95, *d_result);
	RUNTEST(result);
	printf("Check if 5-10/10 return 4.0:\n");
	Calculate(input9, d_result);
	result += TestInt((double)4, *d_result);
	RUNTEST(result);
	printf("Check if 10*4/2 return 20.0:\n");
	Calculate(input7, d_result);
	result += TestInt((double)20, *d_result);
	RUNTEST(result);
	printf("Check if 10-4*2 return 2.00:\n");
	result += TestInt(2, Calculate(input8, d_result));
	RUNTEST(result);/* change for Hadar */
	printf("Check if 10-4*2/0 return MATH_ERROR:\n");
	result += TestInt(3, Calculate(input10, d_result));/* change for Hadar */
	RUNTEST(result);
	
	return result; 
}

int TestCalcParenthesis(void)
{
	int result = 0;
	double d_num = 0.00;
	double *d_result = &d_num;
	const char *input1 = "(54*5)";
	const char *input2 = "(54+15)+9*40";
	const char *input3 = "5*(4+5)*4";
	const char *input4 = "(8+4)*2";
	const char *input5 = "(555*2)+(100/4)";
	const char *input6 = "(555*2)*(100/4)";
	const char *input7 = "(10*4/2)+(42/8)-2*200";
	const char *input8 = "()+10-4*2";
	const char *input9 = "(5-10)100/10";
	const char *input10 = "10-4*2/10*0/2+500";
	
	
	printf("Check if 10-4*2/10*0/2+500 return 510.0:\n");
	Calculate(input10, d_result);
	result += TestInt((double)510, *d_result);
	RUNTEST(result);
	printf("Check if (5-10)100/10 return error:\n");
	result += TestInt(2, Calculate(input9, d_result));
	RUNTEST(result);/* change for Hadar */
	printf("Check if d_result return syntax error:\n");
	result += TestInt(2, Calculate(input8, d_result));/* change for Hadar */
	RUNTEST(result);
	
	printf("Check if (10*4/2)+(42/8)-2*200 return −374.75:\n");
	Calculate(input7, d_result);
	result += TestInt((double)-374.75, *d_result);
	RUNTEST(result);
	
	printf("Check if (555*2)*(100/4) return 27750.0:\n");
	Calculate(input6, d_result);
	result += TestInt((double)27750, *d_result);
	RUNTEST(result);
	printf("Check if (555*2)+(100/4) return 1135.0:\n");
	Calculate(input5, d_result);
	result += TestInt((double)1135, *d_result);
	RUNTEST(result);
	printf("Check if (8+4)*2 return 24.0:\n");
	Calculate(input4, d_result);
	result += TestInt((double)24, *d_result);
	RUNTEST(result);
	printf("Check if 5*(4+5)*4 return 180.00:\n");
	Calculate(input3, d_result);
	result += TestInt((double)180, *d_result);
	RUNTEST(result);
	printf("Check if (54+15)+9*40 return 429.00:\n");
	Calculate(input2, d_result);
	result += TestInt((double)429, *d_result);
	RUNTEST(result);
	printf("Check if (54*5) return 270:\n");
	Calculate(input1, d_result);
	result += TestInt((double)270, *d_result);
	RUNTEST(result);
	
	return result; 
}

int TestInt(int expected, int result)
{
	return ((expected == result) ? 0 : 1);
}
