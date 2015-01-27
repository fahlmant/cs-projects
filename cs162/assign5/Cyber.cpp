#include <Cyber.h>
#include <stdlib.h>

int Cyberdemon::getDamage()
{
    int damage;
    damage = Demon::getDamage();
    return damage;
}

string Cyberdemon::getSpecies()
{
    string spe = "Cyberdemon";
    return spe;
}
