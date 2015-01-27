#include <Demon.cpp>
#include <stdlib.h>

using std::string;

class Cyberdemon : public Demon {

    public:
        
        Cyberdemon()
        {
            strength = 50;
            hp = 100;
        }
        Cyberdemon(int newHp)
        {
            strength = 50;
            hp = newHp;
        }
        int getDamage();
        string getSpecies();
    private:

};
