#include <iostream>
#include <stdlib.h>
#include <Creature.cpp>

using std::string;

class Human: public Creature {

    public:
        Human()
        {
            strength = 50;
            hp = 100;
            Creature h = Creature(strength, hp);
            //Creature * h = new Creature(strength, hp);
        }
        Human(int newHp)
        {
            strength = 50;
            hp = newHp;
            Creature h = Creature(strength, hp);
            //Creature * h = new Creature(strength, hp);
        }
        int getDamage();
        int getHitpoints();
        string getSpecies();
        
    private:

};

