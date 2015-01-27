/* CS261- Assignment 1 - Q.3*/
/* Name:
 * Date:
 * Solution description:
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void sort(int* number, int n){
     /*Sort the given array number , of length n*/
	
	int swap;
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			if (number[j] > number [j+1])
			{
				swap = number[j];
				number[j] = number[j+1];
				number[j+1] = swap;				
			}
		}
	}
	     
}

int main(){

	srand(time(NULL));

    /*Declare an integer n and assign it a value of 20.*/
    int n = 20;

    /*Allocate memory for an array of n integers using malloc.*/
    int *arrayToBeSorted;
    arrayToBeSorted = malloc(n * sizeof(int));

    /*Fill this array with random numbers between 0 and n, using rand().*/
    for(int i = 0; i < n; i++)
	{
		arrayToBeSorted[i] = rand() % n;
	}

    /*Print the contents of the array.*/
	for(int j = 0; j < n; j++)
	{
		printf("%d \n", arrayToBeSorted[j]);
	}


    /*Pass this array along with n to the sort() function.*/
    sort(arrayToBeSorted, n);

	printf("\n");
	printf("Sorted \n");
    /*Print the contents of the array.*/  
		for(int k = 0; k < n; k++)
	{
		printf("%d \n", arrayToBeSorted[k]);
	}  
    
	free(arrayToBeSorted);
    return 0;
}