#include <iostream>

#define PROMPT "Please enter a whole number:"
#define NOT_PRIME "The number is not a prime number. \n"
#define PRIME "The number is a prime number. \n"        
#define DONE 0          /* ends successful program */                                                  

using namespace std;

int main(){
    int i;       /* loop counter */
    int number; /* number provided by user */
    int divisors = 0;

    cout << PROMPT;  /* promt user */
    cin >> number;  /* wait for user input */

    /* Prime numbers are defined as any number 
     * greater than one that is only divisible
     * by one and itself. Dividing the number
     * by two shortens the time it takes to
     * complete. */

    for(i = 3; i < number; i++)
    {
       if( number % i == 0 )
       {    /* if divisible */
          cout << NOT_PRIME << number; /* not prime */
          return DONE;        /* exit program */
       }
       else if ((number % i) != 0)
       {	 
	  divisors++; 
       }
    }  
    
    if(divisors == (number - 3))
    {
       cout << PRIME << number;
       
    }
    else 
    {
       cout << NOT_PRIME << number;
       return DONE;
    } 
    return 0;     /* exit program */
}
