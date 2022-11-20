/*******************************************************************************
Name: Ran Aharon Cohen
Reviewer: Revital
Pass Vlg: Yes
Date: 07.05.22
File: calc.c
Description: Finite State Machine
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>/* malloc ,free and strtod */
#include <assert.h>/* assert */
#include <string.h>/* strlen */

#include "stack.h"	/* חסרות הערות */
#include "calc.h"
#define SIZE_OF_INPUTS 256	/* חסר רווח בין האינקלוד */
#define OPEN_BRAK_CHAR 40	/* קונבנציה לשים סוגריים מסביב לערכים של דיפיין */
#define CLOSE_BRAK_CHAR 41	/* יותר ברור לשים פשוט את התווים עצמם '(' ')' */
#define NUM_OF_OPERATORS 4

enum States
{
	START,
	WAIT_FOR_OPERAND,
	WAIT_FOR_OPERATOR,
	NUM_OF_STATES
};

enum Inputs
{
	INVALID = 0,
	OPERAND,
	ZERO,
	OPERATOR1,	/* אולי כדאי שם שיותר ברור מה הסוג שלו */
	OPERATOR2,
	OPERATOR3,
	OPERATOR4,
	OPEN_BRAK,
	CLOSE_BRAK,
	END,
	NUM_OF_INPUTS
};
	/* הערות כלליות: לא צריך comments להצהרות, יש קונבנציה של עד 80 תווים בשורה, בנוסף יש מלא warrnings בקומפילציה, ודבר אחרון - ההדפסות מקשות גם לעבור על הקוד עצמו (מעמיסות ולא מרווחות) וגם לראות את תוצאות הטסטים השונים, נראלי נכון לשלוח לבדיקה נקי ;) אחלה קוד בסך הכל, הערות לא משמעותיות, בעיקר אסרטים שחסרים, חלוקה טובה לפונקציות ולוטים מושקעים :) */
	/* פספסתי את ההצהרה של זה, אולי כדאי עם שאר המשתנים הגלובליים וגם להוסיף תחילית */
/* typedef functions: */
typedef void(*init_func)(unsigned char *c);
typedef double(*compute_func_t)(stack_t *st_operand, stack_t *st_operator, double *result);
typedef void(*retro_func_t)(char curr_operator, stack_t *st_operand, stack_t *st_operator, double *result);
typedef int(*zero_handle_func_t)(char **expression, stack_t *st_operand, int *state);
typedef int(*func_t)(char **expression, stack_t *st_operand, stack_t *st_operator, double *result, int *state);

/* initialization functions: */
static int CalcInitStacks(stack_t **s1, stack_t **s2, size_t stack_size);
static void DestroyStacks(stack_t **s1, stack_t **s2);
static void CalcInitInputLut(unsigned char input_lut[]);
/* calculator help functions: */
static char CalcParse(unsigned char c);
static int GetSintaxError(char **expression, stack_t *st_operand, stack_t *st_operator, double *result, int *state);
static int PushOperand(char **expression, stack_t *st_operand, stack_t *st_operator, double *result, int *state);
static int PushOperator(char **expression, stack_t *st_operand, stack_t *st_operator, double *result, int *state);
static int EmptyExpression(char **expression, stack_t *st_operand, stack_t *st_operator, double *result, int *state);
static int PushParenthesis(char **expression, stack_t *st_operand, stack_t *st_operator, double *result, int *state);
static int PushStartParenthesis(char **expression, stack_t *st_operand, stack_t *st_operator, double *result, int *state);
static int CalcUpToCloseParenthesis(char **expression, stack_t *st_operand, stack_t *st_operator, double *result, int *state);
static int FinishCalculation(char **expression, stack_t *st_operand, stack_t *st_operator, double *result, int *state);
static int PushZeroOrInvalid(char **expression, stack_t *st_operand, stack_t *st_operator, double *result, int *state);
static int InvalidOperation(char **expression, stack_t *st_operand, int *state);
static int PushZero(char **expression, stack_t *st_operand, int *state);

/* computation functions: */
static double ComputeDummy(stack_t *st_operand, stack_t *st_operator, double *result);
static double ComputePlus(stack_t *st_operand, stack_t *st_operator, double *result);
static double ComputeMinus(stack_t *st_operand, stack_t *st_operator, double *result);
static double ComputeMultiplication(stack_t *st_operand, stack_t *st_operator, double *result);
static double ComputeDivision(stack_t *st_operand, stack_t *st_operator, double *result);
static void RetroDummy(char curr_operator, stack_t *st_operand, stack_t *st_operator, double *result);
static void RetroCompute(char curr_operator, stack_t *st_operand, stack_t *st_operator, double *result);
  
/* LOOKUP TABLES: */	/* אולי לרווח את זה קצת שיהיה אפשר לעבור על זה, בעיקר את הרלוונטים */
static const func_t g_function_lut[NUM_OF_STATES][NUM_OF_INPUTS] = {
/* Start State: */
 		{&GetSintaxError ,&PushOperand,&PushOperand,&PushOperand,&PushOperand,&GetSintaxError, 						  		
 					 						&GetSintaxError,&PushStartParenthesis,&GetSintaxError,&EmptyExpression},			
/* WAIT_FOR_OPERAND: */	
		{&GetSintaxError, &PushOperand,&PushZeroOrInvalid,&GetSintaxError, &GetSintaxError, &GetSintaxError, 
											&GetSintaxError,&PushParenthesis,&GetSintaxError,&GetSintaxError},
/* WAIT_FOR_OPERATOR: */
		{&GetSintaxError, &GetSintaxError,&GetSintaxError,&PushOperator, &PushOperator,&PushOperator, &PushOperator, &GetSintaxError,
											&CalcUpToCloseParenthesis, &FinishCalculation}							 																	};
static const compute_func_t g_computation_lut[NUM_OF_OPERATORS + 4][NUM_OF_OPERATORS + 4] = {	/* נראלי מבלבל ולא מתאים לשינויים הפלוס 4, אפשר להשתמש בדיפיין מיוחד או באחד האינמים */
/* Dummy rows */{&ComputeDummy,&ComputeDummy,&ComputeDummy,&ComputeDummy,&ComputeDummy,&ComputeDummy,&ComputeDummy,&ComputeDummy},
/* Dummy rows */{&ComputeDummy,&ComputeDummy,&ComputeDummy,&ComputeDummy,&ComputeDummy,&ComputeDummy,&ComputeDummy,&ComputeDummy},
/* Dummy rows */{&ComputeDummy,&ComputeDummy,&ComputeDummy,&ComputeDummy,&ComputeDummy,&ComputeDummy,&ComputeDummy,&ComputeDummy},
/* Plus */		{&ComputeDummy,&ComputeDummy,&ComputeDummy,&ComputePlus,&ComputePlus,&ComputeDummy,&ComputeDummy,&ComputeDummy},
/* Minus */		{&ComputeDummy,&ComputeDummy,&ComputeDummy,&ComputeMinus,&ComputeMinus,&ComputeDummy,&ComputeDummy,&ComputeDummy},
/* Multiply */	{&ComputeDummy,&ComputeDummy,&ComputeDummy,&ComputeMultiplication,&ComputeMultiplication,&ComputeMultiplication, 		&ComputeMultiplication,&ComputeDummy},																																			
/* divide*/{&ComputeDummy,&ComputeDummy,&ComputeDummy,&ComputeDivision,&ComputeDivision,&ComputeDivision,&ComputeDivision,&ComputeDummy},
/* Dummy rows */{&ComputeDummy,&ComputeDummy,&ComputeDummy,&ComputeDummy,&ComputeDummy,&ComputeDummy,&ComputeDummy,&ComputeDummy}};	
			 		
static const retro_func_t g_retro_compute_lut[2]= {&RetroCompute, &RetroDummy};
static const zero_handle_func_t g_zero_or_invalid[2]= {&PushZero, &InvalidOperation};
static size_t count_open_parenthesis = 0;

/* Functions definitions: */

int Calculate(const char *expression, double *result)
{
	int input = 1;
	int state = 0;
	int status = 0;
	size_t str_size = 0;
	stack_t *s_operands = NULL;
	stack_t *s_operators = NULL;
	
	char *runner = (char *)expression;	/* חסר אסרט */
	str_size = strlen(expression);
	status = CalcInitStacks(&s_operands, &s_operators, str_size);
	
	while(END != input && SUCCESS == status)
	{
		input = CalcParse(*runner);		
		status = g_function_lut[state][input](&runner, s_operands, s_operators, result, &state);
	}
	count_open_parenthesis = 0;	/* נראלי יותר נכון לאתחל אותו בתחילת התוכנית ולא בסוף לקראת הקריאה הבאה */
	DestroyStacks(&s_operands, &s_operators);	/* רווחים */
	
	return status;
}

static int CalcInitStacks(stack_t **s1, stack_t **s2, size_t stack_size)
{
	*s1 = StackCreate(stack_size ,sizeof(double));	/* חסר אסרט */
	if(NULL == *s1)
	{
		StackDestroy(*s1);	/* חסר השמה לנאל בשניהם */
		
		return ALLOC_ERROR;
	}
	
	*s2 = StackCreate(stack_size ,sizeof(char));
	if(NULL == *s2)
	{
		StackDestroy(*s2);	/* נראלי התכוונת לשחרר את 1 */
		
		return ALLOC_ERROR;
	}
	
	return SUCCESS;
}

static void CalcInitInputLut(unsigned char input_lut[])	/* חסר אסרט */
{
	/* intitialize lut of inputs  */
    input_lut['0'] = ZERO;	/* עוד לא גיליתי למה הוא מקבל התייחסות שונה */
    input_lut['1'] = OPERAND;	/* את המספרים אפשר בלולאה */
    input_lut['2'] = OPERAND;
    input_lut['3'] = OPERAND;
    input_lut['4'] = OPERAND;
    input_lut['5'] = OPERAND;
    input_lut['6'] = OPERAND;
    input_lut['7'] = OPERAND;
    input_lut['8'] = OPERAND;
    input_lut['9'] = OPERAND;
    input_lut['+'] = OPERATOR1;
    input_lut['-'] = OPERATOR2;
    input_lut['*'] = OPERATOR3;
    input_lut['/'] = OPERATOR4;
    input_lut[OPEN_BRAK_CHAR] = OPEN_BRAK;
    input_lut[CLOSE_BRAK_CHAR] = CLOSE_BRAK;
    input_lut['\0'] = END;
}

static void DummyInit(unsigned char input_lut[])
{
	(void)input_lut;
}
	/* למה הוא מחזיר char אם זה enum? גם מה שקצת ראיתי לפעמים אתה שם אותו לתוך int ולפעמים ל char, קצת מבלבל מה המשמעות של מה שמחזיר */
static char CalcParse(unsigned char c)
{
	static unsigned char input_lut[256] = {0};
	int booly = 0;
	static init_func bool_func[2] = {&CalcInitInputLut, &DummyInit};
	
	bool_func[booly](input_lut);
	booly = 1;	/* הוא לא סטטי אז לא שומר על ערכו ויאתחל כל כניסה */
	
	return input_lut[c];
}


static void DestroyStacks(stack_t **s1, stack_t **s2)
{
	assert(NULL != *s1);
	assert(NULL != *s2);
	
	StackDestroy(*s1);
	StackDestroy(*s2);
}

static int GetSintaxError(char **expression, stack_t *st_operand, stack_t *st_operator, double *result, int *state)
{
	assert(NULL != expression);
	assert(NULL != st_operand);
	assert(NULL != st_operator);
	
	*result = 0;	/* חסר אסרט */
	printf("GetSintaxError\n\n");
	
	
	return SYNTAX_ERROR;
}

static int PushOperand(char **expression, stack_t *st_operand, stack_t *st_operator, double *result, int *state)
{
	double number = 0;
	char **runner = expression;
	
	assert(NULL != expression);
	assert(NULL != st_operand);
	assert(NULL != st_operator);
	
	number = strtod(*expression, runner);
	StackPush(st_operand, &number); 
	printf("PushOperand\n\n");
	/*printf("peek after push: %f \n",*(double *)StackPeek(st_operand));*/
	*state = WAIT_FOR_OPERATOR;	/* חסר אסרט */
	
	return SUCCESS;
}

static int PushZeroOrInvalid(char **expression, stack_t *st_operand, stack_t *st_operator, double *result, int *state)
{
	double number = 0;
	int is_division = ('/' == *(char *)StackPeek(st_operator));	/* מגניב שזה תמיד לא ריק */
	int status = 0;
	
	assert(NULL != expression);
	assert(NULL != st_operand);
	assert(NULL != st_operator);
	
	/*printf("PushZeroOrInvalid: is_division=%d\n\n",is_division);*/
	status = g_zero_or_invalid[is_division](expression, st_operand, state);
	
	return status;
}

static int PushZero(char **expression, stack_t *st_operand, int *state)
{
	double number = 0;
	char **runner = expression;
	
	assert(NULL != expression);
	assert(NULL != st_operand);
	
	number = strtod(*expression, runner);
	StackPush(st_operand, &number); 
	*state = WAIT_FOR_OPERATOR;
	
	return SUCCESS;
}

static int InvalidOperation(char **expression, stack_t *st_operand, int *state)
{
	assert(NULL != expression);
	assert(NULL != st_operand);
	
	printf("InvalidOperation\n\n");
	
	return MATH_ERROR;
}

static int PushOperator(char **expression, stack_t *st_operand, stack_t *st_operator, double *result, int *state)
{
	char curr_operator = 0;
	char curr_operator_enum = 0;
	double var1 = 0;
	double var2 = 0;
	size_t num_of_loops = 0;
	int is_empty_operator = StackIsEmpty(st_operator) || ('(' == *(char *)StackPeek(st_operator));	/* יותר מתאים לפונקציה והשם לא מתאר מדוייק, וזה לפני האסרט */
	
	assert(NULL != expression);
	assert(NULL != st_operand);
	assert(NULL != st_operator);
	printf("PushOperator\n");
	
	num_of_loops = StackSize(st_operator);	/* אפשר לעשות לולאה כל עוד לא ריק במקום לספור */
	while(num_of_loops--)
	{
		curr_operator = **expression;
		curr_operator_enum = CalcParse(curr_operator);
		g_retro_compute_lut[is_empty_operator](curr_operator_enum, st_operand, st_operator, result);
		is_empty_operator = StackIsEmpty(st_operator);	/* מעניין שהכנסת את זה ככה ולא בלופ, רעיון מגניב */
	}
	StackPush(st_operator, *expression); 
	*state = WAIT_FOR_OPERAND;
	*expression = *expression + 1;
	
	return SUCCESS;
}

static void RetroCompute(char curr_operator, stack_t *st_operand, stack_t *st_operator, double *result)
{
	char prev_operator = 0;
	
	assert(NULL != st_operand);
	assert(NULL != st_operator);
	
	prev_operator = *(char *)StackPeek(st_operator);
	prev_operator = CalcParse(prev_operator);
	printf("RetroCompute\n\n");		/* לקח לי קצת זמן להבין למה רטרו חחח */
	/*printf("prev_operator: %d\n",prev_operator);
	printf("curr_operator: %d\n",curr_operator);*/
	g_computation_lut[prev_operator][curr_operator](st_operand, st_operator, result);
}

static void RetroDummy(char curr_operator, stack_t *st_operand, stack_t *st_operator, double *result)
{
	printf("RetroDummy\n");
	(void)curr_operator;
	(void)st_operand;
	(void)st_operator;
	(void)result;
}
	/* נפל כשמכניסים מחרוזת ריקה */
static int EmptyExpression(char **expression, stack_t *st_operand, stack_t *st_operator, double *result, int *state)
{
	assert(NULL != expression);
	assert(NULL != st_operand);
	assert(NULL != st_operator);
	
	printf("EmptyExpression\n\n");
	if(0 == count_open_parenthesis)	/* אם להיות קטנונית אפשר היה להכניס בלוט חחחח */
	{
		return SUCCESS;
	}
	
	return SYNTAX_ERROR;
}

static int PushStartParenthesis(char **expression, stack_t *st_operand, stack_t *st_operator, double *result, int *state)
{
	char operator = **expression;	/* לפני האסרטטט */
	
	assert(NULL != expression);
	assert(NULL != st_operand);
	assert(NULL != st_operator);
	
	printf("PushParenthesis\n\n");
	StackPush(st_operator, &operator); 
	/*printf("peek operator after push: %c \n",*(char *)StackPeek(st_operator));*/
	*state = START;	/* אסרט חחח */
	*expression = *expression + 1;
	++count_open_parenthesis;
	
	return SUCCESS;
}
	/* שתי הפונקציות נראות בדיוק אותו הדבר!!! */
static int PushParenthesis(char **expression, stack_t *st_operand, stack_t *st_operator, double *result, int *state)
{
	char operator = **expression;
	
	assert(NULL != expression);
	assert(NULL != st_operand);
	assert(NULL != st_operator);
	
	printf("PushParenthesis\n\n");
	StackPush(st_operator, &operator); 
	/*printf("peek operator after push: %c \n",*(char *)StackPeek(st_operator));*/
	*state = START;
	*expression = *expression + 1;
	++count_open_parenthesis;
	
	return SUCCESS;
}

static int CalcUpToCloseParenthesis(char **expression, stack_t *st_operand, stack_t *st_operator, double *result, int *state)
{
	char operator = 0;
	
	assert(NULL != expression);
	assert(NULL != st_operand);
	assert(NULL != st_operator);
	if(0 == count_open_parenthesis)	/* אם זה חוזר אז אולי באמת עדיף לוט, ולהכניס את זה בתנאי */
	{
		*result = 0;
		return SYNTAX_ERROR;
	}
	printf("count_open_parenthesis: %d\n\n", count_open_parenthesis);
	printf("CalcUpToCloseParenthesis\n\n");
	while('(' != *(char *)StackPeek(st_operator))
	{
		operator = *(char *)StackPeek(st_operator);
		operator = CalcParse(operator);
		*result = g_computation_lut[operator][operator](st_operand, st_operator,result);
	}
	
	StackPop(st_operator);
	*state = WAIT_FOR_OPERATOR;
	*expression = *expression + 1;
	--count_open_parenthesis;
	
	return SUCCESS;
}

static int FinishCalculation(char **expression, stack_t *st_operand, stack_t *st_operator, double *result, int *state)
{
	char operator = 0;
	double  operand = 0;
	
	assert(NULL != expression);
	assert(NULL != st_operand);
	assert(NULL != st_operator);
	
	printf("FinishCalculation\n\n");
	
	if((0 < count_open_parenthesis))
	{
		*result = 0;
		return SYNTAX_ERROR;	/* אולי כדאי להוציא לפונקציה כשחוזר כל פעם ההשמה ל0 וערך החזרה דומה */
	}
	
	*result = *(double *)StackPeek(st_operand);
	while(1 != StackIsEmpty(st_operator))
	{
		operator = *(char *)StackPeek(st_operator);
		operand = *(double *)StackPeek(st_operand);
		operator = CalcParse(operator);
		
		if(0 == operand && OPERATOR4 == operator)	/* בדיקה מאוד ספציפית שהבנתי שלא רוצים שנבצע ככה */
		{
			return MATH_ERROR;	/* מעניין שדווקא כאן לא איפסת ל 0 את התוצאה חח */
		}
		
		*result = g_computation_lut[operator][operator](st_operand, st_operator,result);
	}
	
	printf("result: %f\n",*result);
	
	return SUCCESS;
}

static double ComputePlus(stack_t *st_operand, stack_t *st_operator, double *result)
{
	double var1 = 0;
	double var2 = 0;
	
	assert(NULL != st_operand);
	assert(NULL != st_operator);
	
	StackPop(st_operator);
	var2 = *(double *)StackPeek(st_operand);
	StackPop(st_operand);
	var1 = *(double *)StackPeek(st_operand);
	StackPop(st_operand);	/* עד כאן חוזר בכל הפונקציות אותו קוד, אולי כדאי לאחד ואז לשלוח רק לפי סוג החישוב */
	*result = var1 + var2;
	printf("ComputePlus result: %f\n",*result);
	StackPush(st_operand,result); 	/* ואז זה גם יכול להיות בחוץ כי חור בכולם */
	
	return *result;	/* מעניין אם צריך להחזיר אם מעדכנים בפנים, אולי זה סתם יותר נוח */
}

static double ComputeMinus(stack_t *st_operand, stack_t *st_operator, double *result)
{
	double var1 = 0;
	double var2 = 0;
	
	assert(NULL != st_operand);
	assert(NULL != st_operator);
	
	StackPop(st_operator);
	var2 = *(double *)StackPeek(st_operand);
	StackPop(st_operand);
	var1 = *(double *)StackPeek(st_operand);
	StackPop(st_operand);
	*result = var1 - var2;
	StackPush(st_operand,result); 
	printf("ComputeMinus result: %f\n",*result);
	
	return *result;
}

static double ComputeMultiplication(stack_t *st_operand, stack_t *st_operator, double *result)
{
	double var1 = 0;
	double var2 = 0;
	
	assert(NULL != st_operand);
	assert(NULL != st_operator);
	
	StackPop(st_operator);
	var2 = *(double *)StackPeek(st_operand);
	StackPop(st_operand);
	var1 = *(double *)StackPeek(st_operand);
	StackPop(st_operand);
	
	*result = var1 * var2;
	StackPush(st_operand,result); 
	printf("ComputeMultiplication result: %f*%f=%f\n",var1, var2, *result);
	return *result;
}

static double ComputeDivision(stack_t *st_operand, stack_t *st_operator, double *result)
{
	double var1 = 0;
	double var2 = 0;
	
	assert(NULL != st_operand);
	assert(NULL != st_operator);
	
	StackPop(st_operator);
	var2 = *(double *)StackPeek(st_operand);
	StackPop(st_operand);
	var1 = *(double *)StackPeek(st_operand);
	StackPop(st_operand);
	
	*result = var1 / var2;
	StackPush(st_operand,result); 
	printf("ComputeDivision result: %f\n",*result);
	return *result;
}

static double ComputeDummy(stack_t *st_operand, stack_t *st_operator, double *result)
{
	printf("ComputeDummy\n");
	(void)st_operand;
	(void)st_operator;
	(void)result;
	
	return *result;
}

