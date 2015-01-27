#include <iostream>

using namespace std;

class Temper
{
private:
	double kelv, far, cel;
	
public:
	void set_kelv()
	{
		cout << "Enter temperature in Kelvins: " << endl;
		cin >> kelv;
		cel = kelv - 273.15;
		far = ((9/5.0)*(cel)) + 32;
		cout << "Your temperature in Kelvin is " << kelv << endl;
		cout << "Your temperature in Celcius is " << cel << endl;	
		cout << "Your temperature in Fahrenheit is " << far << endl;
	}
	
	void set_cel()
	{
		cout << "Enter temoerature in Celsius: " << endl;
		cin >> cel;
		kelv = cel + 273.15;
		far = ((9/5.0)*(cel)) + 32;
		cout << "Your temperature in Kelvin is " << kelv << endl;
		cout << "Your temperautre in Celcius is " << cel << endl;
		cout << "Your temperature in Fahrenheit is " << far << endl;
	}
	
	void set_far()
	{
		cout << "Enter temperature in Fahrenheit: " << endl; 
		cin >> far;
		cel = ((5.0/9) * (far - 32));
		kelv = cel + 273.15;
		cout << "Your temperature in Kelvin is " << kelv << endl;
		cout << "Your temperature in Celcius is " << cel << endl;
		cout << "Your temperature in Fahrenheit is " << far << endl;
	}


};

int main()
{

	int check;
	Temper temp;
	cout << "Enter 1 for Kelvin, 2 for Calsius, or 3 for Fahrenheit. " << endl;
	cin >> check;
	
	if(check == 1)
	{
		temp.set_kelv();
	}
	if(check == 2)
	{
		temp.set_cel();
	}
	if(check == 3)
	{
		temp.set_far();
	}
	return 0;
	
}
