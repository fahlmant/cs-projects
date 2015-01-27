#include <iostream>
#include <sys/time.h>
#include <cstdlib>

using namespace std;

class GasPump
{

private:

	double total_charge, cost;
	
public:
	void print_total_pumped(double amount_pumped)
	{	
		cout << "Total gas pumped: " << amount_pumped << endl;
	}
	
	void print_total_cost()
	{
		cout << "Total Cost: " << total_charge << endl;
	}
	
	void cost_per_gallon()
	{
		cout << "Cost per gallon: " << cost << endl;
	}
	
	void set_total()
	{	
		total_charge = 0;
	}

	void get_cost()
	{
		cout << "Cost per gallon? " << endl;
		cin >> cost;	
	}
	void final_cost(double amount_pumped)
	{
		total_charge = amount_pumped * cost;
	}

};


int main()
{
	GasPump pump;
	int checker;
	double timer, amount_pumped, rate = .1;
	typedef struct timeval time;
	time stop, start;

	pump.set_total();
	pump.get_cost();
	cout << "Enter 1 to start, 0 to stop " << endl;
	cin >> checker;
	if(checker == 1)
	{
		gettimeofday(&start, NULL);
	}
	cin >> checker;
	if (checker == 0)
	{
		gettimeofday(&stop, NULL);
	}
	timer = stop.tv_sec - start.tv_sec;
	amount_pumped = rate * timer; 	
	pump.final_cost(amount_pumped);
	pump.print_total_pumped(amount_pumped);
	pump.print_total_cost();
	pump.cost_per_gallon();
	return 0;
}
