
#include <stddef.h> /*size_t*/
#include <stdio.h> /*printf*/

#include "stack.h" /*typedef stack_t*/


void TestStackChar(void);
void TestStackInt(void);
void TestStackFloat(void);
void TestStr(void);

int main(void)
{
	TestStackChar();
	TestStackInt();
	TestStackFloat();
	TestStr();
	
	return 0;
}


void TestStackChar(void)
{
	stack_t *stack_char = StackCreate(5 ,sizeof(char));
	char ch1 = 'R';
	char ch2 = 'a';
	char ch3 = 'n';
	char ch4 = 'C';
	char ch5 = 'o';
	
	printf("***********************CHAR STACK***********************\n\n");

	printf("The size of stack is: %lu\n", StackSize(stack_char));
	printf("The Stack Capacity of stack is: %lu\n", StackCapacity(stack_char));
	
	StackPush(stack_char , &ch1);
	StackPush(stack_char , &ch2);
	StackPush(stack_char , &ch3);
	printf("After Three push :The last item in the stack is: %c\n" , 
												*(char *)StackPeek(stack_char));
	printf("Is the stack empty?  %d\n", StackIsEmpty(stack_char));
	printf("The size of stack is: %lu\n", StackSize(stack_char));
	
	StackPush(stack_char , &ch4);
	
	
	printf("After two more push :The last item in the stack is: %c\n" , 
												*(char *)StackPeek(stack_char));
												
	printf("The size of stack is: %lu\n", StackSize(stack_char));
	
	StackPop(stack_char);
	
	printf("After two pop :The last item in the stack is: %c\n" , 
												*(char *)StackPeek(stack_char));
	printf("The size of stack is: %lu\n", StackSize(stack_char));
	StackPush(stack_char , &ch4);
	printf("After one push :The last item in the stack is: %c\n" , 
												*(char *)StackPeek(stack_char));
	printf("The size of stack is: %lu\n", StackSize(stack_char));
	StackPop(stack_char);
	printf("After another pop :The last item in the stack is: %c\n" , 
												*(char *)StackPeek(stack_char));
	printf("Is the stack empty?  %d\n", StackIsEmpty(stack_char));
	StackPop(stack_char);
	printf("After another pop :The last item in the stack is: %c\n\n" , 
												*(char *)StackPeek(stack_char));
	StackPop(stack_char);
	printf("After another pop :The last item in the stack is: %c\n\n" , 
												*(char *)StackPeek(stack_char));
	
	StackDestroy(stack_char);
}

void TestStackInt(void)
{
	stack_t *stack_int = StackCreate(3 , sizeof(int)); 
	int num1_int = 3;
	int num2_int = 7;
	int num3_int = 85;
	int num4_int = 16654333;
	
	printf("***********************INT STACK***********************\n\n");
	
	printf("The size of stack is: %lu\n", StackSize(stack_int));
	printf("The Stack Capacity of stack is: %lu\n", StackCapacity(stack_int));
	
	StackPush(stack_int , &num1_int);
	
	printf("After First push :The last item in the stack is: %d\n" , 
												  *(int *)StackPeek(stack_int));
	printf("Is the stack empty?  %d\n", StackIsEmpty(stack_int));
	printf("The size of stack is: %lu\n", StackSize(stack_int));
	
	StackPush(stack_int , &num2_int);
	
	printf("After push :The last item in the stack is: %d\n" , 
												  *(int *)StackPeek(stack_int));
	StackPush(stack_int , &num3_int);
	
	printf("After push :The last item in the stack is: %d\n" , 
												  *(int *)StackPeek(stack_int));
	
	printf("After push :The last item in the stack is: %d\n" , 
												  *(int *)StackPeek(stack_int));
	printf("The size of stack is: %lu\n", StackSize(stack_int));
	
	StackPop(stack_int);
	
	printf("After First pop :The last item in the stack is: %d\n" , 
											      *(int *)StackPeek(stack_int));
	printf("The size of stack is: %lu\n", StackSize(stack_int));
	
	StackPop(stack_int);
	
	printf("Is the stack empty?  %d\n\n\n", StackIsEmpty(stack_int));
	
	StackDestroy(stack_int);

}

void TestStackFloat(void)
{
	stack_t *stack_float = StackCreate(5 ,sizeof(float));
	float num1_d = 1.0;
	float num2_d = 2.0;
	float num3_d = 3.0;
	
	printf("***********************FLOAT STACK***********************\n\n");

	printf("The size of stack is: %lu\n", StackSize(stack_float));
	printf("The Stack Capacity of stack is: %lu\n", StackCapacity(stack_float));
	printf("Is the stack empty?  %d\n", StackIsEmpty(stack_float));
	
	StackPush(stack_float , &num1_d);
	
	printf("After First push :The last item in the stack is: %.2f\n" , 
											  *(float *)StackPeek(stack_float));
	printf("Is the stack empty?  %d\n", StackIsEmpty(stack_float));
	printf("The size of stack is: %lu\n", StackSize(stack_float));
	
	StackPush(stack_float , &num2_d);
	
	printf("After Second push :The last item in the stack is: %.2f\n" , 
											  *(float *)StackPeek(stack_float));
	printf("The size of stack is: %lu\n", StackSize(stack_float));
	
	StackPush(stack_float , &num3_d);
	
	printf("After Third push :The last item in the stack is: %.2f\n" , 
											  *(float *)StackPeek(stack_float));
	printf("The size of stack is: %lu\n", StackSize(stack_float));
	
	StackPop(stack_float);
	
	printf("After First pop :The last item in the stack is: %.2f\n" , 
											  *(float *)StackPeek(stack_float));
	printf("The size of stack is: %lu\n", StackSize(stack_float));
	
	StackPush(stack_float , &num3_d);
	
	printf("After Third push :The last item in the stack is: %.2f\n" , 
											  *(float *)StackPeek(stack_float));
	printf("The size of stack is: %lu\n", StackSize(stack_float));
	
	StackPop(stack_float);
	
	printf("After Second pop :The last item in the stack is: %.2f\n" , 
											  *(float *)StackPeek(stack_float));
	printf("Is the stack empty?  %d\n", StackIsEmpty(stack_float));
	
	StackPop(stack_float);
	
	printf("After Second pop :The last item in the stack is: %.2f\n" , 
											  *(float *)StackPeek(stack_float));
	StackPop(stack_float);
	
	printf("After Third pop :is the stack empty? : %d\n\n" ,
													 StackIsEmpty(stack_float));
	
	StackDestroy(stack_float);	
}


void TestStr()
{
	char *str1 = "Boom!";
	char *str2 = "Big reveal!";
	char *str3 = "I turned myself";
	char *str4 = "into a ";
	char *str5 = "pickle!";
	 
	stack_t *p = StackCreate(5, 16);
	
	printf("-----------------string test-----------------\n");
	printf("Capacity is: %ld\n", StackCapacity(p));
	StackPush(p, str1);
	StackPush(p, str2);
	StackPush(p, str3);
	printf("Stack Size After 3 Pushes: %ld\n", StackSize(p));
	StackPush(p, str4);
	StackPush(p, str5);
	printf("Stack Size After 5 Pushes: %ld\n", StackSize(p));
	printf("peek: %s\n", (char *)StackPeek(p));
	StackPop(p);
	StackPop(p);
	printf("peek: %s\n", (char *)StackPeek(p));
	printf("Is Stack Empty? After 3 Pops %d\n", StackIsEmpty(p));
	StackPop(p);
	StackPop(p); 
	printf("Is Stack Empty? After 5 Pops  %d\n", StackIsEmpty(p));
	StackDestroy(p);
	printf("-------------thank you for waching-------------\n");
}

