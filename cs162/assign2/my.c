/***
*Program: My.c
*Author: Taylor Fahlman
*Date Due: 4/21/2013
*Description: Converts an int from input to a string
*Input: Integer and base
*Output: The string of the integer in the correct base
***/
#include <stdio.h>
#include <stdlib.h>

void myitoa(int x, char* out, int size, int base);
int size_of(int x, int base);

/**
 *Function: Main
 *Descrption: Executes the main code. 
 *Parapmeters: None.
 *Pre-Condition: n/a
 *Post-condition: n/a 
**/
int main()
{
    //takes input of number, and the base
    int x, base, i = 0, size = 0;
    printf("Enter number\n");
    scanf("%i", &x);
    printf("Enter base\n");
    scanf("%i", &base);
    //gets the number of digits in the int
    size = size_of(x, base);

    //creates a char* and allocates the number of bytes needed based off the number of digits in the int
    char* out = (char*) malloc(size);
    //calls myitoa
    myitoa(x, out, size, base);
    //if the number is negative, prints out the negative of the char* 
    if(x < 0)
        printf("-%s\n", out);
    //otherwise prints out straight char*
    else
        printf("%s\n", out);
}
/**
 *Function: size_of
 *Description: Determines the number of decimals in the int input.
 *Paramters: Number that was put in, and the base of the number.
 *Pre-condition: n/a
 *Post-condition: n/a
**/
int size_of(int x, int base)
{
    int size = 0;
    int num = abs(x);
    //find the number of digits in the int.
    while(num > 0)
    {
        size++;
        num /= base;
    }
    //returns the number
    return size;

}
/**
 *Function: myitoa
 *Description: Converts int that was put in to a string
 *Parameters: int x thats the inputed number, char* to store string, size thats number of digits, and base of the number
 *Pre-condition: n/a
 *Post-condition: n/a
**/ 

void myitoa(int x, char* out, int size, int base)
{
    int digits, num, x1, x2;

    //makes a copies of x
    x2 = abs(x);
    
    out[size-1] = '\0'; //assign the last element to the null terminator
       
    //convert from int to string
    int i = size-1;   

    while(x2 > 0)
    {
        //takes last int, converts to char and assigns it to the ith element, decrements i
        out[i] = "0123456789abcdef"[x2 % base];
        x2 /= base;
        i--;
    }
}
