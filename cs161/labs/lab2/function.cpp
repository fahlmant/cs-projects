#include<iostream>
#include<cmath>

using std::cout;


int main()
{
	cout<<"2^23 - 1 is equal to " <<((pow(2.0,23.0)) - 1) << "\n";
	cout<<"5.0 ^ 3 is equal to " <<((pow(5.0,3.0))) << "\n";
	cout<<"The square root of 25 is "<<sqrt(25)<<"\n";
	cout<<"The square root of 96 is "<<sqrt(96)<<"\n";
	cout<<"The remainer of 34.0 / 5 is "<<(fmod(34.0,5))<<"\n";
	cout<<"Sin 90 - Cos 30 equals "<<(sin(90) - cos(30))<<"\n";
	cout<<"Ln(5) equals "<<(log(5))<<"\n";
	cout<<"log(100) equals "<<(log10(100))<<"\n";
	cout<<"e ^ 5.0 equals "<<(exp(5.0))<<"\n";
	cout<<"The sqaure root of 2 ^ 64 is "<<(sqrt((pow(2.0,64.0))))<<"\n";
	cout<<"The absolute value of -2.5 is "<<(ceil(fabs(-2.5)))<<"\n";
	return 0; 
}
