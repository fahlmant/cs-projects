#include <Room.h>

using std::string;
using std::cout;
using std::endl;

class Dungeon : public Room{


    public:
        Dungeon()
        {
            name = "Dungeon";
            check = 0;
            object = "Key";
            stat = 1;
        }
        int checkRoom();
        int getObjectStat();
        void lookObj();
};

int Dungeon::checkRoom()
{
    return check;
}

int Dungeon::getObjectStat()
{
    return stat;
}

void Dungeon::lookObj()
{
    cout << "The key is small and golden. It looks like it would fit inside the door. " << endl;
}
