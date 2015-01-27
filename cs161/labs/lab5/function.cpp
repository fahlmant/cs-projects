#include <iostream>
#include <stdlib.h>
#include <string>
#include <cstdlib>
using namespace std;

int is_pos_int(int a);


int get_positive_int(string a, string b)
{
   	int check;
	int i = atoi(a.c_str());
	int j = atoi(b.c_str());
	
	int first = is_pos_int(i);
	int second = is_pos_int(j);
	if( first == 1 && second == 1)
	{
		check = 1;
	}
	else
	{
		check = 0;
	}
	
	return check;
}


int is_pos_int(int a)
{
   int check;
   if(a > 0)
   {
   	check = 1;
   }
   else
   {
   	check = 0;
   }

   return check;

}

void increment(int a)
{
    for(int i = 0; i <= a; i++)
    {
        cout << i << " ";
    }
    cout << endl;

}

void backwards(int a)
{
    for(int i = 0; a >=i; a--)
    {
        cout << a << " ";
    }
    cout << endl;

}

void param(int a, int b)
{
    for(a;a <= b; a++)
    {
        cout << a << " ";
    }
    cout << endl;
}

int main()
{
   int ans = 1, checker, a, b;
   string num1, num2;
   while(ans == 1)
   { 
    cout << "Would you like to run? (0 for no, 1 for yes) " << endl;
    cin >> ans;
    if(ans == 1)
    {	  
        cout << "Please enter the first number: " << endl;
        cin >> num1;
        cout << "Please enter the second number: " << endl;
        cin >> num2;
	checker = get_positive_int(num1,num2);
	if(checker == 1)
	{	
	   	a = atoi(num1.c_str());
		b = atoi(num2.c_str());
        	increment(a);
	        backwards(a);
        	param(a,b);
	}
	else
	{
		while(checker != 1)
		{
			cout << "please enter the first number: " << endl;
			cin >> num1; 
			cout << "Please enter the second number: " << endl;
			cin >> num2;
			checker = get_positive_int(num1,num2);
			if(checker == 1)
		   	{
			        a = atoi(num1.c_str());
				b = atoi(num2.c_str());
				increment(a);
				backwards(a);
				param(a,b);
			}
	         }		
	}
    }
    else if(ans == 0)
    {
        return 0;
    }
    else
    {
        cout << "That is not valid. Please run the program again" << endl;
        return 0;    
    }
   }
   
  return 0;
}
