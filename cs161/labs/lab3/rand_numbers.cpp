#include <iostream>
#include <ctime>
#include <cstdlib>


using namespace std;

int answer;

int guess(){

	cout << "Guess my number: " << endl;
	cin >> answer;
}


int main() {

	int x;
	int y;
	srand(time(NULL));
	
	x = rand();
	y = x % 50;
	
	guess();
	for(int i = 0; i <5; i++)
	{
		if (answer == y)
		{ 
			cout << "You got it!" << endl;
			break;
		}
		else
		{	
			if(answer < y)
			{
				cout << "You are too low, Guess again " << endl;	
				guess();
			}
			else if (answer > y)
			{
			cout << "You are too high, Guess again " << endl; 
				guess();
			}	
		}
	}
	
}	
