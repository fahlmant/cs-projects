/********
 *Author: Taylor Fahlman
 *Date: 5/27/13
 *Decription: Let's the user choose two creatures, then makes them battle
 * Input: Two choices of creatures
 * Output: The battle between the two creatures and the winner
********/


#include "Human.cpp"
#include "Elf.cpp"
#include "Balrog.cpp"
#include "Cyber.cpp"

using std::cout;
using std::endl;
using std::string;
using namespace std;

Creature *battle(Creature *c1, Creature *c2);
Creature *type(int creature_num);
/**********
 *Function: main
 *Desc: takes in two inputs, creates two creatures based on input, and passes them to the battle function, outputs the winner and deletes the pointers
 *Parameters: n/a
 ********/ 
int main()
{
    int chose_one;
    int chose_two;

    cout << "Chose the first Creature! Press 1 for Human, 2 for Elf, 3 for Cyberdemon, or 4 for Balrog " << endl;
    cin >> chose_one;
    cout << "Chose the next Creature! Press 1 for Human, 2 for Elf, 3 for Cyberdemon, or 4 for Balrog " << endl;
    cin >> chose_two;
    cout << endl;

    Creature *c1 = type(chose_one);
    Creature *c2 = type(chose_two);
    
    Creature *winner = battle(c1, c2);
    string win = winner->getSpecies();

    cout << "The winner is the " << win << endl;
    delete c2;
    delete c1;
    return 0;
}

/******
 *Function: type
 *Desc: takes in an int, then creates a Creature pointer basefd of input. Returns it and deletes it.
 *Parameters: creature_num, determines what creature to make and put in creature pointer.
******/

Creature *type(int creature_num)
{
    Creature *chosen;

    if(creature_num == 1)
    {
        Human *h = new Human(300);
        chosen = h;
    }
    else if (creature_num == 2)
    {
        Elf *e = new Elf(300);
        chosen = e;
    }
    else if(creature_num == 3)
    {
        Cyberdemon *c = new Cyberdemon(300);
        Demon *d = c;
        chosen = d;
    }
    else if(creature_num == 4)
    {
        Balrog *b = new Balrog(300);
        Demon *d = b;
        chosen = d;
    }

    return chosen;
    delete chosen;

}

/*******
 *Function: battle
 *Desc: Takes in two creature pointers, and battles the two until one has 0 or less hp. Returns the winner
 *Parameters: Two creature pointers that battle against each other.
*******/

Creature *battle(Creature *c1, Creature *c2)
{

    int c1Hp;
    int c2Hp;
    int dam1;
    int dam2;
    string cre1;
    string cre2;
    Creature *winner;

    c1Hp = c1->getHitpoints();
    c2Hp = c2->getHitpoints();
    cre1 = c1->getSpecies();
    cre2 = c2->getSpecies();
    

    while(c1Hp > 0 && c2Hp > 0)
    {
        srand(time(NULL));

        cout << "The " << cre1 << " attacks the " << cre2 << endl;
        dam1 = c1->getDamage();
        c2Hp -= dam1;
        if(c2Hp > 0)
        {
            cout << "The " <<  cre2 << " has " << c2Hp << " HP left!" << endl;
        }
        cout << endl;
        cout << endl;

        sleep(3);

        cout << "The " << cre2 << " attacks the " << cre1 << endl;
        dam2 = c2 ->getDamage();
        c1Hp -= dam2;
        if(c1Hp > 0)
        {
            cout << "The " <<  cre1 << " has " << c1Hp << " HP left! " << endl;
        }
        cout << endl;
        cout << endl;
 
        sleep(3);
    }

    if(c1Hp <= 0)
    {
        winner = c2;
    }
    else if (c2Hp <= 0)
    {
        winner = c1;
    }



    return winner;
    delete winner;
}

