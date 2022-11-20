#include <stdio.h>

#include "bit_array.h"

int main()
{
	size_t num = 7;/*000000111*/
	size_t num2 = 102; /*01100110*/
	size_t num3 = 8536; /*0010000101011000*/
	size_t num4 = 837; /*01101000101*/
	size_t num5 = 0;
	size_t num6 = 2;
	char arr[80] = {'O'};
	
	
	printf("------------------Test for SetBitOn------------------\n"); 
	printf("%lu ----------> ans 23\n" , BitArrSetBitOn(num , 4)); 
	printf("%lu ----------> ans 358\n" , BitArrSetBitOn(num2, 8));
	printf("%lu ----------> ans 74072\n" , BitArrSetBitOn(num3, 16));
	printf("%lu ----------> ans 8536\n" , BitArrSetBitOn(num3, 3));
	printf("%lu ----------> ans 9223372036854775808\n" , BitArrSetBitOn(num5, 63));/* your result is 18446744071562067968*/
	printf("%lu ----------> ans 8536 your problem\n" , BitArrSetBitOn(num3, 70));
	
	printf("\n------------------Test for SetBitOff------------------\n");
	printf("%ld ----------> ans 7\n" , BitArrSetBitOff(num , 4));
	printf("%ld ----------> ans 7\n" , BitArrSetBitOff(num , 3));
	printf("%ld ----------> ans 100\n" , BitArrSetBitOff(num2, 1));
	printf("%ld ----------> ans 8472\n" , BitArrSetBitOff(num3, 6));
	printf("%ld ----------> ans 5 your problem \n" , BitArrSetBitOff(num , 65));
	
	printf("\n------------------Test for SetBit------------------\n");
	printf("%ld ----------> ans 7\n" , BitArrSetBit(num , 4 , 0));
	printf("%ld ----------> ans 23\n" , BitArrSetBit(num , 4 , 1));
	printf("%ld ----------> ans 358\n" , BitArrSetBit(num2, 8 , 1));
	printf("%ld ----------> ans 8472\n" , BitArrSetBit(num3, 6 ,0 ));
	printf("%ld ----------> ans 5 your problem \n" , BitArrSetBit(num , 65, 0));
	
	
	printf("\n------------------Test for Get Bit Val------------------\n");
	printf("%d ----------> ans 0\n" , BitArrGetBitVal(num , 4));
	printf("%d ----------> ans 1\n" , BitArrGetBitVal(num , 0));
	printf("%d ----------> ans 0\n" , BitArrGetBitVal(num2 , 30));
	printf("%d ----------> ans 1\n" , BitArrGetBitVal(num3 , 8));
	printf("%d ----------> ans 0\n" , BitArrGetBitVal(num3 , 65));
	
	printf("\n------------------Test for Flip Bit------------------\n");
	printf("%ld ----------> ans 23\n" , BitArrFlipBit(num , 4)); 
	printf("%ld ----------> ans 358\n" , BitArrFlipBit(num2, 8));
	printf("%ld ----------> ans 74072\n" , BitArrFlipBit(num3, 16));
	printf("%ld ----------> ans 8528\n" , BitArrFlipBit(num3, 3));
	printf("%ld ----------> ans 8472 your problem\n" , BitArrFlipBit(num3, 70));
	
	printf("\n------------------Test for Bit Arr Count On------------------\n");
	printf("%ld ----------> ans 3\n" , BitArrCountOn(num));
	printf("%ld ----------> ans 4\n" , BitArrCountOn(num2));
	printf("%ld ----------> ans 5\n" , BitArrCountOn(num3));
	printf("%ld ----------> ans 5\n" , BitArrCountOn(num4));
	printf("%ld ----------> ans 0\n" , BitArrCountOn(num5));

	printf("\n------------------Test for Bit Arr Count Off------------------\n");
	printf("%lu ----------> ans 61\n" , BitArrCountOff(num ));
	printf("%lu ----------> ans 60\n" , BitArrCountOff(num2 ));
	printf("%lu ----------> ans 59\n" , BitArrCountOff(num3));
	printf("%lu ----------> ans 59\n" , BitArrCountOff(num4));
	printf("%lu ----------> ans 64\n" , BitArrCountOff(num5));
	
	printf("\n------------------Test for SetAll------------------\n");
	printf("%lu ----------> ans 18446744073709551615\n" , BitArrSetAll(num5 ));
	printf("%lu ----------> ans 18446744073709551615\n" , BitArrSetAll(num3 ));
	
	
	printf("\n------------------Test for Rotate Arr R------------------\n");
	printf("%lu ----------> ans 1\n" , BitArrRotateArrR(num6 , 1)); 
	printf("%lu ----------> ans 9223372036854775808\n" , BitArrRotateArrR(num6, 2));
	printf("%lu ----------> ans 8536\n" , BitArrRotateArrR(num3, 64));
	printf("%lu ----------> ans 1067\n" , BitArrRotateArrR(num3, 3));
	printf("%lu ----------> ans 9223372036854776341\n" , BitArrRotateArrR(num3, 4));
	printf("%lu ----------> ans 6917529027641081989\n" , BitArrRotateArrR(num3, 70));
	
	printf("\n------------------Test for Rotate Arr L------------------\n");
	printf("%lu -> ans 2\n" , BitArrRotateArrL( (BitArrRotateArrR(num6 , 1) ) , 1) ); 
	printf("%lu -> ans 2\n" , BitArrRotateArrL( (BitArrRotateArrR(num6, 2) ), 2) );
	printf("%lu -> ans 8536\n" , BitArrRotateArrL( (BitArrRotateArrR(num3, 64) ), 64) );
	printf("%lu -> ans 8536\n" , BitArrRotateArrL( (BitArrRotateArrR(num3, 3) ),3 ) );
	printf("%lu -> ans 8536\n" , BitArrRotateArrL( (BitArrRotateArrR(num3, 4) ) , 4) );
	printf("%lu -> ans 8536\n" , BitArrRotateArrL( (BitArrRotateArrR(num3, 70) ) , 70) );
	
	printf("\n------------------Test for Bit Arr Mirror------------------\n");
	printf("%lu ----------> ans 16140901064495857664\n" , BitArrMirror(num));
	printf("%lu ----------> ans 7349874591868649472\n" , BitArrMirror(num2));
	printf("%lu ----------> ans 1910652141911932928\n" , BitArrMirror(num3));
	printf("%lu ----------> ans 11727373429672771584\n" , BitArrMirror(num4));
	printf("%lu ----------> ans 0\n" , BitArrMirror(num5));
	/*
	printf("\n------------------Test for Bit Arr Mirror Lut------------------\n");
	printf("%lu ----------> ans 16140901064495857664\n" , BitArrMirrorLut(num));
	printf("%lu ----------> ans 7349874591868649472\n" , BitArrMirrorLut(num2));
	printf("%lu ----------> ans 1910652141911932928\n" , BitArrMirrorLut(num3));
	printf("%lu ----------> ans 11727373429672771584\n" , BitArrMirrorLut(num4));
	printf("%lu ----------> ans 0\n" , BitArrMirrorLut(num5));
	
	printf("\n------------------Test for Bit Arr Count Lookup table------------------\n");
	printf("%ld ----------> ans 3\n" , BitArrCountLut(num));
	printf("%ld ----------> ans 4\n" , BitArrCountLut(num2));
	printf("%ld ----------> ans 5\n" , BitArrCountLut(num3));
	printf("%ld ----------> ans 5\n" , BitArrCountLut(num4));
	printf("%ld ----------> ans 0\n" , BitArrCountLut(num5));
	printf("%lu ----------> ans 0\n" , BitArrCountLut(num5));*/
	
	printf("\n------------------Test for Bit Arr To String------------------\n");
	printf("%s ----------> ans 000111\n" , BitArrToString(num , arr));
	printf("%s ----------> ans 01100110\n" , BitArrToString(num2 , arr));
	printf("%s ----------> ans 0010000101011000\n" , BitArrToString(num3 , arr));
	printf("%s ----------> ans 01101000101\n" , BitArrToString(num4 , arr));
	printf("%s ----------> ans 0\n" , BitArrToString(num5 , arr));
	
	
	
	return 0;
}
