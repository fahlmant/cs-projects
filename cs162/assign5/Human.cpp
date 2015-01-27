#ifndef HUMAN_CPP
#define HUMAN_CPP
#include <Human.h>

using std::string;

int Human::getDamage()
{
    int damage;
    damage = Creature::getDamage();
    return damage;

}

string Human::getSpecies()
{   
    string spe = "Human";
    return spe;
}

int Human::getHitpoints()
{
    return hp;
}
#endif /* HUMAN_CPP */
