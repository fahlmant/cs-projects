#ifndef CREATURE_CPP
#define CREATURE_CPP

#include <Creature.h>


using std::cout;
using std::endl;
using std::string;

int Creature::getDamage()
{
    int damage;
    damage = (rand() % strength) + 1;
    cout << "The " << getSpecies() << " does " << damage << " damage!" << endl;
    return damage;
}

int Creature::getHitpoints()
{
    return hp;
}

void Creature::setHitpoints(int newHp)
{
    hp = newHp;
}

#endif /* CREATURE_CPP */
