#include <Creature.cpp>
#include <stdlib.h>

using std::string;

class Demon : public Creature {

    public:
        Demon()
        {
            strength = 40;
            hp = 100;
        }
        Demon(int newHp)
        {
            strength = 40;
            hp = newHp;
        }

        virtual int getDamage();
        string getSpecies();

};
