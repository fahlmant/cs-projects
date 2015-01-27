

#include <iostream>
#include <stdlib.h>

using std::cout;
using std::endl;
using std::string;

class Creature{


    protected:
        int strength;
        int hp;
    public:
        Creature()
        {

        }
        Creature(int newStrength, int newHp)
        {
            strength = newStrength;
            hp = newHp;
        }
        virtual string getSpecies()
        {
            string spe = "Creature";
            return spe;
        }
        int getDamage(); 
        int getHitpoints();
        void setHitpoints(int newHp);
};

