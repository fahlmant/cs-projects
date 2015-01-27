//#include <cstdlib>
#include <stdlib.h>
#include <time.h>
class Dice{

    public:
        Dice();
        Dice(int newSides);
        virtual int rollDice() const;
    protected:
        int numSides;
};

Dice::Dice() 
{
    numSides = 6;
    srand(time(NULL));
}

Dice::Dice(int newSides)
{
    numSides = newSides;
    srand(time(NULL));
}

int Dice::rollDice() const 
{
    return (rand() % numSides) + 1;

}

int rollTwoDice(const Dice& die1, const Dice& die2)
{
    return die1.rollDice() + die2.rollDice();
}

