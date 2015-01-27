/* CS261- Assignment 1 - Q.2*/
/* Name: Taylor Fahlman - Michael Papendeick
 * Date Due: 10/11/13
 * Solution description: Properly dereference pointers and pass addresses to modify values. 
 */
 
#include <stdio.h>
#include <stdlib.h>

int foo(int* a, int* b, int c){
    /*Set a to double its original value*/
	*a = 2 * (*a);
    
    /*Set b to half its original value*/
	*b = (.5) * (*b);
    
    /*Assign a+b to c*/
	c = (*a + *b);
    
    /*Return c*/
	return c;
}

int main(){
    int x = 7;/*Declare three integers x,y and z and initialize them to 7, 8, 9 respectively*/
    int y = 8;
	int z = 9;
	int foo_num;

    /*Print the values of x, y and z*/
	printf("X: %d \n", x);
	printf("Y: %d \n" , y);
	printf("Z: %d \n" ,z);
    
    /*Call foo() appropriately, passing x,y,z as parameters*/
	foo_num = foo(&x, &y, z);
    
    /*Print the value returned by foo*/
	printf("Value returned by foo: %d \n", foo_num);
	    
    /*Print the values of x, y and z again*/
	printf("X: %d \n", x);
	printf("Y: %d \n" , y);
	printf("Z: %d \n" ,z);

	
 
    /*Is the return value different than the value of z?  Why?*/
    return 0;
}
    
    