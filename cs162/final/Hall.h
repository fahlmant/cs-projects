#include <Room.h>

class Hall : public Room {


    public:
        Hall()
        {
            name = "Hall";
            check = 0;
            object = "brasskey";
            stat = 1;
		    pocketCheck = 0;
		    useCheck = 0;
		    doorCheck = 0;
    		keyGet = 0;
			objCheck = 1;
        }
        void lookObj();
		int objCheck;
	    int checker;
    	int buff;
		int pocketCheck;
	    int useCheck;
	    int doorCheck;
   		int keyGet;

};

void Hall::lookObj()
{
    if (stat == 1)
    {
        cout << "There is a small brasskey. It is in a small metal cage. There is a small slot on the wall, and it looks as if something fits inside it." << endl;
    }
    else
    {
        cout << "There is a small brasskey. " << endl;
    }
}
