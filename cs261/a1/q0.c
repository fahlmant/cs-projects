/* CS261- Assignment 1 - Q. 0*/
/* Name: Taylor Fahlman - Michael Papendieck
 * Date Due: 10/11/13
 * Solution description: Properly dereferenced the pointer and used the & symbol when appropriate. 
 */

#include <stdio.h>
#include <stdlib.h>

void fooA(int *iptr)
{
     /*Print the value pointed to by iptr*/
    printf("Value of X %u \n", *iptr);

     /*Print the address pointed to by iptr*/
    printf("Address of X %u \n", iptr);  

     /*Print the address of iptr itself*/ 
    printf("Address of iptr %i \n", &iptr);

}

int main()
{
    /*declare an integer x*/
    int x = 5;

    /*print the address of x*/
    printf("Adress %u \n", &x);

    /*Call fooA() with the address of x*/
    fooA(&x);

	/*print the value of x*/
    printf("Value of X %i \n", x);

    return 0;
}


