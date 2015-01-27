#include<iostream>
#include<stdio.h>
#include<math.h>

using namespace std;


class Fraction
{
private:
	double num, denom, frac, big, gdc, num_low, denom_low;

public:
	void get_num()
	{
		cout << "Enter a numerator"  << endl;
		cin >> num;
	}
	
	void get_denom()
	{	
		cout << "Enter a denominator" << endl;
		cin >> denom;
	}

	void calc()
	{
		frac = num / denom;
		cout << "Decimal: " << frac << endl;	
	}

    void gcd()
    {
        if(denom > num){
            big = denom;
        }
        else if(num > denom){
            big = num;
        }
        
        for(int i = 0; i < big; i++)
        {
            if(fmod(num,i) == 0 && fmod(denom,i) == 0)
            {
                gdc = i;
            }
        }
        
        num_low = num/gdc;
        denom_low = denom/gdc;
    }

    void print_ans()
    {
        cout << "Your fraction in lowest terms is " << num_low << "/" << denom_low << endl;
    }
	

	
};


int main()
{
    Fraction frac;
    
    frac.get_num();
    frac.get_denom();
    frac.gcd();
    frac.calc();
    frac.print_ans();

    return 0;
}
