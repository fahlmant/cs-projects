/**********************************************************
 **Program Name: Buoyancy
 **Author: Taylor Fahlman
 **Date: Jan 28, 2013
 **Description: Tells the user if a sphere will sink or float
 **Input: Sphere weight in lbs and radius in ft
 **Output: Caluclutates if the sphere will float, tells user, asks if they want to compute another spehere
**********************************************************/



#include <iostream>
#include <cmath>
#include <string>

using namespace std;
int i;

const double PI = 4.0 * atan(1.0);


/*******
 ** Function: Buoyant
 ** Description: Takes user input and calucates if a spehere will float or sink
 ** Paramaters: None
 ** Pre-conditions: None
 ** Post-conditions: None
*******/
int buoyant()
{
	double lbs;
	double rad;
	double s_weight = 62.4;
	double frac = 1.333333;
	cout << "Enter weight in lbs: " << endl;
	cin >> lbs;
	cout << "Enter radius in feet: " << endl;
	cin >> rad;
	double rad3 =(rad * rad * rad);
	double vol = (frac * rad3 * PI);
	
	double force_buoyant = s_weight * vol;
	


	if (force_buoyant >= lbs)
	{
		cout << "This spehere will float" << endl;
	}
	else if (force_buoyant < lbs)
	{
		cout << "This spehere will sink" << endl;
	}
	else
	{
		cout << "Something is wrong" << endl;
	}
	

}

/*****
 ** Function: question
 ** Decription: Asks the user if they want to compute again.
 ** Paramaters: None
 ** Pre-conditions: None
 ** Post-conditions: If the user says no, int = 0, if yes, the function will be called again.
*****/ 
int question()
{
	string ans;
	string yes ("y");
	string no ("n");
	cout << "Do you want to compute again? (y,n)" << endl;
	cin >> ans;
	
	if(ans.compare(yes) == 0)
	{
		i = 1;
	}
	else if (ans.compare(no) == 0)
	{
		cout << "Goodbye" << endl;
		i = 0;
	}
	else
	{
		cout << "There has been an error" << endl;
	}
	
}	
/*****
 ** Function: main
 ** Description: The main thread. Runs the functions called
 ** Parameters: None
 ** Pre-conditions: i must equal run to execute the functions
 ** Post-conditions: None 	
*****/ 
int main()
{	
	i = 1;
	while(i == 1)
	{
		buoyant();
		question();
	}
}

