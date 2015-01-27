#ifndef ROOM
#define ROOM

#include <iostream>

using std::string;
using std::endl;
using std::cout;

class Room{

    public:
        Room() { 
        
            name = "Room";
            check = 0;
            object = "Object";
            stat = 0;
        }

        string getName();
        string name;
        string object;
        int checkRoom();
        int check;
        string getObject();
        int stat;
        int getObjectStat();
        void lookObj();

};

int Room::checkRoom()
{
    return check;
}


string Room::getName()
{
    return name;
}

string Room::getObject()
{
    return object;
}

int Room::getObjectStat()
{
    return stat;
}

void Room::lookObj()
{
    cout << "Look at this object! " << endl;
}

#endif /* ROOM */
