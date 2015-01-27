/************
 ** Program: Primes
 ** Author: Taylor Fahlman
 ** Date: Jan 28 2013
 ** Description: Takes number, prints all primes between 3 and that number. 
 ** Input: Number grater than 3
 ** Output: All the prime numbers between 3 and the input
***************/ 

#include <iostream>
#include <cmath>

using namespace std;

/*****
 **Function: Main 
 **Description: Executes the code, asks for input greater than 3, calculates all primes between 3 and that number,  ** prints it out
 **Paramaters: None
 **Pre-conditions: None
 **Post-conditions: None
*****/ 
int main()
{	
	int counter;
	int num;
	cout << "Enter a number greater than 3: " << endl;
	cin >> num;

	cout << "3" << endl;	
	for (int i = 3; i < num; i++)
	{
		for(int j = 2; j*j <= i; j++)
		{
	
			if( (i % j) == 0)
			{
				break;
			}
			else if( j+1 > sqrt(i))
			{
				cout << i << endl;
			}
		}
	}
}
