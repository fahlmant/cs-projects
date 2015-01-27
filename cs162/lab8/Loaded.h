#include <Dice.h>
#include <time.h>
#include <cstdlib>

class LoadedDice : public Dice {

    public:
        LoadedDice();
        LoadedDice(int newSides);
        int rollDice() const;
};

LoadedDice::LoadedDice()
{
    numSides = 6;
    srand(time(NULL));
}

LoadedDice::LoadedDice(int newSides)
{
    numSides = newSides;
    srand(time(NULL));
}

int LoadedDice::rollDice() const
{
    int chance = (rand() % 10) + 1;

    if(chance > 5)
    {
        return numSides;
    }
    else
    {
        return Dice::rollDice();
    }
}
