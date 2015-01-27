#include<iostream>

using namespace std;
using namespace string;

int main
{

	string answer;
	cout<<"Do you like vi?";
	cin>>answer;
	if(answer == "yes")
	{ 
		int ans = 1;
	}
	else if(answer == "no")
	{
		int ans = 0;
	}
	else
	{
		cout<<"Not Valid";
	}
	
	if(ans == 1)
	{
		cout<<"YOU LOVE VI!";
	}
	else if(ans == 0)
	{
		cout<<"YOU HATE VI!";
	}
	else
	{
		cout<<"";
	}	






















