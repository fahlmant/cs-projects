#include <sys/time.h>
#include <cstdlib>
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::cin;

float C(int n, int r);
float Creq(int n, int r);
float fact(int n);
float rec(int n);

int main(int argc, char *argv[])
{
	typedef struct timeval time;
	time stop, start;
	int n,r;
	if (argv[1][1] == 'n' && argv[3][1] == 'r')
	{
		n = atoi(argv[2]);
		r = atoi(argv[4]);
	}

	else if(argv[1][1] == 'r' && argv[3][1] == 'n')
	{
		r = atoi(argv[2]);
		n = atoi(argv[4]);
	}
	else
	{
		cout << "Usage: ./recurse [-n <number>] [-r <number>] " << endl;
		return 0;
	}


	gettimeofday(&start,NULL);

	C(n,r);	


	gettimeofday(&stop,NULL);

	if(stop.tv_sec > start.tv_sec)
	     cout << "Seconds: " << stop.tv_sec-start.tv_sec << endl;
	else
	     cout << "Micro: " << stop.tv_usec-start.tv_usec << endl;

	gettimeofday(&start,NULL);

	Creq(n,r);

	gettimeofday(&stop,NULL);

	if(stop.tv_sec > start.tv_sec)
	     cout <<"Seconds: " << stop.tv_sec-start.tv_sec << endl;
	else
	     cout <<"Micro: " << stop.tv_usec-start.tv_usec << endl;
	return 0;
}

float C(int n, int r)
{
	float sum_fact = (fact(n) / (fact(r) * fact(n-r)));
	return sum_fact;
}

float Creq(int n, int r)
{
	float sum_req = (rec(n) / (rec(r) * rec(n-r)));
	return sum_req;
	
}

float fact(int n)
{
	float i = 0, fact = 1;

	if(n<=1)
	{
		return 1;
	}
	else
	{
		for(i=1; i <= n; i++)
		{
			fact = fact*i;
		}
		return fact;
	}
}

float rec(int n)
{
	int fact;

	if(n<= 1)
	{
		return 1;
	}
	fact = n * rec(n - 1);
	return fact;
}


