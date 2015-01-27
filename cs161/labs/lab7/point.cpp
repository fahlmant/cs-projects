#include <iostream>


using std::cout;
using std::endl;


int main(){

	double *d;
	double d1, d2, d3;
	
	d = &d1;
	*d = 7.8;
	cout << d1 << endl;
	d = &d2;
	*d = 10.0; 
	cout << d2 << endl;
	d = &d3;
	*d = .009;
	cout << d3 << endl;
	return 0;




}
