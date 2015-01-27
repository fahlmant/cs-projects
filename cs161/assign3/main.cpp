/***
 *Program: Integrate
 *Author: Taylor Fahlman
 *Date Due: 2/8/2013
 *Description: Can integrate 5 functions by trapezoid or rectangle from user input
 *Input: Select which function, a, b, n and what type of integral
 *Output: The summation of the integral the user selected
 * 
 * 9/10/2014: NEEDS BUG FIXING
***/  


#include <iostream>
#include <stdlib.h>
#include <cmath>

using namespace std;

/***
 *Function: F1
 *Description: Calculates F1(x) at x = a
 *Paramaters: x = a, number where f1 is evaluated at 
 *Pre-Condition: n/a
 *Post-Condition: n/a
***/
float f1(float a)
{   
    float sum;
    sum = (((5 * pow(a,4)) + (3 * (pow(a,3))) - (10 * a) + 2));
    return sum;
}

/***
 *Function: F2
 *Description: Calculates F2(x) at x = a
 *Paramaters: x = a, number where f3 is evaluated at 
 *Pre-Condition: n/a
 *Post-Condition: n/a
***/
float f2(float a)
{
    float sum; 
    sum = ((pow(a,2)) - 10);
    return sum;
}

/***
 *Function: F3
 *Description: Calculates F3(x) at x = a
 *Paramaters: x = a, number where f3 is evaluated at 
 *Pre-Condition: n/a
 *Post-Condition: n/a
***/
float f3(float a)
{
    float sum; 
    sum = ((40 * a) + 5);
    return sum;
}

/***
 *Function: F4
 *Description: Calculates F4(x) at x = a
 *Paramaters: x = a, number where f4 is evaluated at 
 *Pre-Condition: n/a
 *Post-Condition: n/a
***/
float f4(float a)
{
    float sum; 
    sum = (pow(a,3));
    return sum;
}

/***
 *Function: F5
 *Description: Calculates F5(x) at x = a
 *Paramaters: x = a, number where f5 is evaluated at 
 *Pre-Condition: n/a
 *Post-Condition: n/a
***/
float f5(float a)
{
    float sum; 
    sum = ((20 * (pow(a,2))) + (10 * a) - 2);
    return sum;
}

/***
 *Function: Rect
 *Description: Calculates a rectangle summation of the function called
 *Paramaters: a, the starting point, b the ending point, n the number of intervals, dist the distance of each interval
 *Pre-Condition: n/a
 *Post-Condition: n/a
***/
float rect(float a, int b, int n, int dist)
{
    float sum = 0;
   	for(a; a < b; a += dist)
   	{
         sum += a * dist;
    }
    return sum;
}

/***
 *Function: Trap
 *Description: Calculates a trapezoid summation of the function called
 *Paramaters: a, the starting point, adist the next point after a, b the ending point, n the number of intervals, dist the distance of each interval
 *Pre-Condition: n/a
 *Post-Condition: n/a
***/
float trap(float a, float adist, int b, int n, int dist)
{
    float sum = 0;
    for(a; a < b; a += dist)
    {
        sum += (((a + adist) / 2) * dist);
    }
    return sum;
}


/***
 *Function: Calc 
 *Description: Calls the rect or trap function of a certain function depending on user input
 *Paramaters: x, the start point, b the end point, n the number of intervals, type the type of summation, func the function to sum
 *Pre-Condition: n/a
 *Post-Condition: n/a
***/
int calc(int x, int y, int n, int type, int func)
{
   	int t = type;
   	float a = x, b = y, inv = n, sum = 0, sum1 = 0;
	float dist = ((b-a) / inv);

    if(func == 1)
    {
             if(type == 0)
             {
                sum = rect(f1(a), b, n, dist);
                cout << sum << endl;
             }
             else if(type == 1)
             {
                sum = trap(f1(a), f1(a + dist), b, n, dist);
                cout << sum << endl;
             }
             else if(type == 2)
             {
                sum = rect(f1(a), b, n, dist);
                sum1 = trap(f1(a), f1(a + dist), b, n, dist);
                cout << sum << endl;
                cout << sum1 << endl;
             }
       }
    else if(func == 2)
    {
             if(type == 0)
             {
                sum = rect(f2(a), b, n, dist);
                cout << sum << endl;
             }
             else if(type == 1)
             {
                sum = trap(f2(a), f2(a+dist), b, n, dist);
                cout << sum << endl;
             }
             else if(type == 2)
             {
                sum = rect(f2(a), b, n, dist);
                sum1 = trap(f2(a), f2(a+dist), b, n, dist);
                cout << sum << endl;
                cout << sum1 << endl;
             }
    }

    else if(func == 3)
    {
             if(type == 0)
             {
                sum = rect(f3(a), b, n, dist);
                cout << sum << endl;
             }
             else if(type == 1)
             {
                sum = trap(f3(a), f3(a+dist), b, n, dist);
                cout << sum << endl;
             }
             else if(type == 2)
             {
                sum = rect(f3(a), b, n, dist);
                sum1 = trap(f3(a), f3(a+dist), b, n, dist);
                cout << sum << endl;
                cout << sum1 << endl;
             }
    }
    
    else if(func == 4)
    {
             if(type == 0)
             {
                sum = rect(f4(a), b, n, dist);
                cout << sum << endl;
             }
             else if(type == 1)
             {
                sum = trap(f4(a), f4(a+dist), b, n, dist);
                cout << sum << endl;
             }
             else if(type == 2)
             {
                sum = rect(f4(a), b, n, dist);
                sum1 = trap(f4(a), f4(a+dist), b, n, dist);
                cout << sum << endl;
                cout << sum1 << endl;
             }
    }
    
    else if(func == 5)
    {
             if(type == 0)
             {
                sum = rect(f5(a), b, n, dist);
                cout << sum << endl;
             }
             else if(type == 1)
             {
                sum = trap(f5(a), f5(a+dist), b, n, dist);
                cout << sum << endl;
             }
             else if(type == 2)
             {
                sum = rect(f5(a), b, n, dist);
                sum1 = trap(f5(a), f5(a+dist), b, n, dist);
                cout << sum << endl;
                cout << sum1 << endl;
             }
    }
}

/***
 *Function:  Main
 *Description: Asks the user if they want to run the program, then asks for a,b,function and type of summation
 *Paramaters: n/a 
 *Pre-Condition: n/a
 *Post-Condition: n/a
***/
int main()
{
  int parse = 1;
  int req;

    do
    {
        cout << "Do you want to run this program? (1 for yes, 0 for no)" << endl;
        cin >> req;
        
        if(req == 0)
        {
                return 0;
        }        
        else if(req == 1)
        { 
            int funct_num, a_num, b_num, n_num, type_num;
    
            cout << "What function do you want to run? (1,2,3,4,5)" << endl;
            cin >> funct_num;
            cout << "Please enter your a " << endl;
            cin >> a_num;
            cout << "Please enter your b " << endl;
            cin >> b_num;
            cout << "Please enter your n " << endl;
            cin >> n_num;
            cout << "Rectangle, Trapeziod, or Both? (0,1,2) " << endl;
            cin >> type_num;
    
            if(funct_num == 1)
            {
                calc(a_num, b_num, n_num, type_num, funct_num);
            }
            else if(funct_num == 2)
            {
                calc(a_num, b_num, n_num, type_num, funct_num);
            }
            else if(funct_num == 3)
            {
                calc(a_num, b_num, n_num, type_num, funct_num);
            }
            else if(funct_num == 4)
            {
                calc(a_num, b_num, n_num, type_num, funct_num);
            }
            else if(funct_num == 5)
            {
               calc(a_num, b_num, n_num, type_num, funct_num);
            }
            else
            { 
                cout << "That is not valid. Please run the program again. " << endl;
                parse = 0;
            }
        }
    }while(parse == 1);
    
    return 0;
}
