#include <iostream>

using namespace std;
/****
 *Program: Letter cryptography
 *Author: Taylor Fahlman
 *Date Due:
 *Description: Find a solution where every letter has a different numerical reputation
 *Input: 
 *Output:
*****/ 
int main()
{
    int t = 0, g = 0, d = 0, o = 0, ans = 0, guess = 0;

    for(int i = 0; i < 10; i++)
    {
        t = i;
        for(int j = 0; j < 10; j++)
        {
            g = j;
            for(int k = 0; k < 10; k++)
            {
                d = k;
                for(int l = 0; l < 10; l++)
                {
                    o = l;
                    guess = (t*o*o) * 4;
                    //guess = ((t*100) + (10*o) + (1*o)) * 4;
                    ans = (g*o*o*d);
                    //ans = (g* 1000) + (o* 100) + (o*10) + d;
                    if((t != g && t != d) && (t != o))
                    {
                        if((g != d) && (g != o))
                        {
                            if(d != o)
                            {
                                if(guess == ans)
                                {
                                    cout << "T: " << t << endl;
                                    cout << "O: " << o << endl;
                                    cout << "D: " << d << endl;
                                    cout << "G: " << g << endl;
                                    cout << " " << endl;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return 0;
}

                   




