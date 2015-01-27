#include <Loaded.h>
#include <cstdlib>
#include <stdlib.h>
#include <iostream>

using std::cout;
using std::endl;

int main()
{
    int num;

    LoadedDice ld1 = LoadedDice(6);
    LoadedDice ld2 = LoadedDice(6);
    num = rollTwoDice(ld1, ld2);
    cout << num << endl;
    return 0;
}
