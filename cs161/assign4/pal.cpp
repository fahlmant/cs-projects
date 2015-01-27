/*****
 *Program Name: Palindrome checker
 *Author: Taylor Fahlman
 *Date Due: 2/19/2013
 *Decription:Takes user input, and can determine if a string is a palindrome, or can reverse the string for the user
 *Input:What they want to do, and a string to check or reverse
 *Output: If a string is a palindrome or the reversed string
*****/
#include <iostream>
#include <string> 


using namespace std;

int determine_palindrome(int start, int end, string inp);
void revString(string inp, int num);

/*****
 *Function: Main
 *Description: Executes the code and runs the program
 *Parameters: None
 *Input: number to tell the program what type of test they want done, and a string
 *Output: If the string is a palindrome or not
*****/
int main()
{
	
   string inp;
   int check, run = 0;
   
   //Starts a loop that runs as long as the run int is unchanged
   do{
 	//checks what the user wants to do
   	cout << "Do you want to reverse a string, check a palindrome, or quit? (1,2,0)" << endl;
	cin >> check;
	//clears anything remaining from input
   	cin.ignore();
        
	//if the user entered one, runs the reverse string function
   	if(check == 1)
  	{
      		cout << "Please enter a string: " << endl;
		getline(cin, inp);
		//assigns size of string - 1 because size starts at 0
		int si = inp.size() - 1;
		//calls the reverse string function for the string
		revString(inp, si);
		//prints out a space and makes the line end here
		cout << " " << endl;
   	}
        
	//if the user entered 2, runs the check palindrome function
   	else if(check == 2)
   	{
		cout << "Please enter a string: " << endl;
		getline(cin, inp);
		// assigns size - 1 because dize starts at 0
		int si = inp.size() - 1;
		//calls determine palindrome function for the string inputed
        	int test = determine_palindrome(0,si,inp);
		// if the function returns a 1, print out that the string is a palindrome
   		if(test == 1)
   		{
   			cout << "This is a palindrome!" << endl;	
   		}
 		// if the functions returns a 2, print out that the string is a not a palindrome	
   		else if (test == 2)
   		{	
   			cout << "This is not a palindrome!" << endl;
   		}
   	}
	//if the user enters 0, change the run int so that the do loop exits
   	else if(check == 0)
   	{
   		run = 1;
   	}

   
   }while(run == 0); // check condition for the while loop

   return 0;

}

/*****
 *Function: Determine Palindrome
 *Description: Checks a string if it"s a palindrome
 *Parameters: 2 ints, to access each char in the string, and the string it evaluates
 *Input: None
 *Output: Returns a number to tell main if the string is a palindrome
*****/
int determine_palindrome(int start, int end,  string  inp)
{
   	// Checks opposite characters if they are equal, if not, not a palindrome
	if(inp[start] != inp[end])
	{
		return 2;
	}
	//If the two ints are equal, ends check
	else if (start == end)
	{
		return 1;
	}
	//calls the function again, adds one to the start and takes away one from the end.
	else
	   return determine_palindrome(start + 1, end - 1, inp);

}
/*****
 *Function: Reverse String
 *Description: Takes a string and prints out the reverse
 *Parameters: String to reverse, and an int to acces that char in the string
 *Input: none
 *Output: Reversed string
*****/
void revString(string inp, int start)
{
   	// checks if number is greater or equal to 0, becuase string chars are from 0 to the size
	if(start >= 0)
	{
	   //prints out char of index start, starts at end, goes to 0
	   cout << inp[start];
	   //calls function again, decrememnting from start
	   revString(inp, start - 1);
	}   
}
