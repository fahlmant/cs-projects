#include <Creature.cpp>
#include <stdlib.h>

using std::string;

class Elf : public Creature {

    public:
       Elf()
       {
            strength = 40;
            hp = 100;
            Creature e = Creature(strength, hp);
       }

       Elf(int newHp)
       {
            strength = 40;
            hp = newHp;
            Creature e = Creature(strength, hp);
       }

       int getDamage();
       string getSpecies();
    protected:

};
