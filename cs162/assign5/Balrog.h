
#include <Demon.cpp>
#include <stdlib.h>

using std::string;

class Balrog : public Demon {

    public:
        Balrog()
        {
            strength = 30;
            hp = 100;
        }
        Balrog(int newHp)
        {
            strength = 30;
            hp = newHp;
        }
        int getDamage();
        string getSpecies();
        

    protected:
    

};
