#include <Balrog.h>

using std::cout;
using std::string;

int Balrog::getDamage()
{
    int damage;

    cout << "Double hit! " << endl;
    damage = Demon::getDamage();
    damage += Demon::getDamage();
    return damage;
}

string Balrog::getSpecies()
{
    string spe = "Balrog";
    return spe;
}
