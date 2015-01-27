#include <iostream>

using namespace std;

/****
 *Program: Matrix Multiplication
 *Author: Taylor Fahlman
 *Date Due:
 *Description: Multiplies 2 matrices and stores the answer in a third matrix.
 *Input: 2 matrices
 *Output: Resulting matrix of the product
*****/ 

int main()
{
    int a[10][10];
    int b[10][10];
    int c[10][10];

    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            cout << "Enter element " << i+1 << " " << j+1 << " for matrix A." << endl;
            cin >> a[i][j];
        }

    }

    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            cout << "Enter element " << i+1 << " " << j+1 << " for matrix B." << endl;
            cin >> b[i][j];
        }
    }

    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            c[i][j] = 0;
            for(int k = 0; k < 10; k++)
            {
                c[i][j] = c[i][j] + (a[i][k]*b[k][j]);
            }
        }
    }

    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            cout << c[i][j] << " ";
        }
        cout << " " << endl;
    }

    return 0;


}
