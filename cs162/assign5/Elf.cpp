#ifndef ELF_CPP
#define ELF_CPP
#include <Elf.h>

using std::string;
using std::cout;

int Elf::getDamage()
{
    
    int damage;
    int chance;
    damage = Creature::getDamage();
    if(chance <= 10)
    {
        damage *= 2;
	 cout << " magic bonus ";
    }

    return damage;
}

string Elf::getSpecies()
{
    string spe = "Elf";
    return spe;
}

#endif /* ELF_CPP */
