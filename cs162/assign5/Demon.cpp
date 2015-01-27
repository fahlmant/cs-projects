#ifndef DEMON_CPP
#define DEMON_CPP
#include <Demon.h>

using std::string;
using std::cout;

int Demon::getDamage()
{
    int damage, chance;
    chance = (rand() % 100);
    damage = Creature::getDamage();
    if(chance <= 5)
    {
        damage += 50;
        cout << " super hit ";
    }
}

string Demon::getSpecies()
{
    string spe = "Demon";
    return spe;
}

#endif /* DEMON_CPP */
