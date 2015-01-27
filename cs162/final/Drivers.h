/****
*File: Drivers
*Description: About, welcome and help print out basic information about the game.
*commandHandler handles all the commands the user inputs and returns the proper int for the drivers
*There are drivers for each class. For each int that commandHander returns, the drivers handle the correct
*inputs to make the game work. For example, if someone tries to get the sword in a room without the sword,
*it would return an "unsucceful" message, but if they were able to get the sword in that room, then it would
*tell the user they got the sword and add it to their inventory. Each room was different enough to have a different driver.
****/

using std::cout;
using std::endl;
using std::cin;

void about()
{
    cout << "Author: Taylor Fahlman (ONID: fahlmant)" << endl;
    cout << "Final Project for CS 162, Spring Term 2013" << endl;
    cout << "Castle Quest, a text based game, written in C++ demonstating the use of classes " << endl;
}

void help()
{
    cout << "The commands you may use are:" << endl;
    cout << "see: (let's you inspect the object and get more information about them.)" << endl;
    cout << "look: (lists all the objects in the room.)" << endl;
    cout << "get: (gets the object for you if possible.)" << endl;
    cout << "use: (Uses item if it's in your pocket.)" << endl;
    cout << "pocket: (Lists all the items that are in your pocket.)" << endl;
    cout << "go: (Let's you go to an adjacent room.) " << endl;
    cout << "about: (Shows information about the game.) " << endl;
	cout << "cheat: (prints out the minimum list of commands you need to win the game.) " << endl; 
    cout << endl;
    cout << "The syntax of this game is as follows. You will see a prompt >>" << endl;
    cout << "First you will enter a command and press enter. After, the console will promt you again, and you enter an object in the room to act on " << endl;
    cout << "Note: Use lowercase letters in all commands" << endl;
    cout << endl;
    cout << "To quit, press Ctrl-C" << endl;
    cout << endl;

}

void welcome()
{
    cout << "Welcome to Castle Quest! This is a text based game. To move around or to see, get and use objects, you must type commands into the console. If you need help, just type 'help'" << endl;
    cout << endl;
	cout << "If something dosen't work, try and go to another room, then come back and try again! " << endl;
    cout << "You awake and find yourself in a Dungeon. You have no idea how you got here. There is a key on the ground, and a stairwell leading out of the room. There is a barred door between you and the stairwell." << endl;
    cout << endl;
	


}

int commandHandler(string command)
{
    if (command == "get")
    {
        cout << "What object would you like to get?" << endl;
        return 1;
    }
    else if (command == "see")
    {
        cout << "What object would you like to see?" << endl;
        return 2;
    }
    else if (command == "use")
    {
        cout << "What object would you like to use?" << endl;
        return 3;
    }
    else if (command == "look")
    {
        return 4;
    }
    else if (command == "pocket")
    {
        return 6;
    }
    else if (command == "go")
    {
        return 5;
    }
    else if (command == "help")
    {
        help();
        return 7;
    }
    else if (command == "about")
    {
        about();
        return 8;
    }
	else if(command == "cheat")
	{
		cout << "get" << endl;
		cout << "key" << endl;
		cout << "use" << endl;
		cout << "key" << endl;
		cout << "go" << endl;
		cout << "right" << endl;
		cout << "get" << endl;
		cout << "crowbar" << endl;
		cout << "go" << endl;
		cout << "back" << endl;
		cout << "use" << endl;
		cout << "crowbar" << endl;
		cout << "go" << endl;
		cout << "left" << endl;
		cout << "use" << endl;
		cout << "crowbar" << endl;
		cout << "get" << endl;
		cout << "sword" << endl;
		cout << "go" << endl;
		cout << "forward" << endl;
		cout << "go" << endl;
		cout << "left" << endl;
		cout << "use" << endl;
		cout << "sword" << endl;
		cout << "get" << endl;
		cout << "crown" << endl;
		cout << "go" << endl;
		cout << "back" << endl;
		cout << "go" << endl;
		cout << "back" << endl;
		cout << "go" << endl;
		cout << "right" << endl;
		cout << "use" << endl;
		cout << "crown" << endl;
		cout << "get" << endl;
		cout << "glove" << endl;
		cout << "go" << endl;
		cout << "back" << endl;
		cout << "go" << endl;
		cout << "forward" << endl;
		cout << "go" << endl;
		cout << "right" << endl;
		cout << "use" << endl;
		cout << "glove" << endl;
		cout << "get" << endl;
		cout << "jewel" << endl;
		cout << "go" << endl;
		cout << "back" << endl;
		cout << "go" << endl;
		cout << "back" << endl;
		cout << "go" << endl;
		cout << "left" << endl;
		cout << "use" << endl;
		cout << "jewel" << endl;
		cout << "get" << endl;
		cout << "shield" << endl;
		cout << "go" << endl;
		cout << "back" << endl;
		cout << "use" << endl;
		cout << "shield" << endl;
		cout << "get" << endl;
		cout << "brasskey" << endl;
		cout << "go" << endl;
		cout << "forward" << endl;
		cout << "use" << endl;
		cout << "brasskey" << endl;
	}
    else
    {
        cout << "This is not a recognized command" << endl;
        return 19;
    }
}


void dungeonDriver(Dungeon *d, string inventory[])
{
    string current;
    string command;
    string object;
    int commandCheck;
    int objCheck;
    int checker;
    string pocket;

    current = d->getName();
    objCheck = d->getObjectStat();
    checker = d->check;

    cout << "You are in the " << current << endl;

    while(checker == 0)
    {
        cout << ">> ";
        cin >> command;
        commandCheck = commandHandler(command);
        if(commandCheck < 4)
        {
            cout << ">> ";
            cin >> object;
            if(commandCheck == 1)
            {
                if(object == "key")
                {
                    if(objCheck == 1)
                    {
                        cout << "You get the " << object << endl;
                        objCheck = 0;
                        inventory[0] = "key";
                        pocket = inventory[0];
                    }
                    else
                        cout << "You already got this object " << endl;
                }
                else
                    cout << "That is not a valid object" << endl;
            }
            else if(commandCheck == 2)
            {
                if(object == "key")
                {
                    d->lookObj();
                }
                if(object == "door")
                {
                    cout << "It's a door" << endl;
                }
            }
            else if(commandCheck == 3)
            {
                if(object == "key")
                {
                    if(pocket == "key")
                    {
                        cout << "You use the key on the door. It's a perfect fit! The door swings open and you go up the stairwell." << endl;
                        checker = 1;
                    }
                    else
                        cout << "You don't have that item! " << endl;
                }
                else
                        cout << "You don't have that object! " << endl;
            }
        }
        if (commandCheck == 4)
        {   
            cout << "All objects in the room" << endl;
            cout << "key" << endl;
            cout << "door" << endl;

        }
        if (commandCheck == 6)
        {
            cout << "Pocket: " << endl;
            if(objCheck == 0)
            {
                cout << pocket << endl;
            }
        }   
        else if (commandCheck == 5)
        {
            cout << "You can't go anywhere!" << endl;
        }
    }
}

int hallDriver(Hall *h, string inventory[])
{
    string current;
    string command;
    string object;
    string where;
    int commandCheck;
    int objCheck;
    int checker;
    int buff;
    string pocket;
    int pocketCheck = h->pocketCheck;
    int useCheck = h->useCheck;
    int doorCheck = h->doorCheck;
    int keyGet = h->keyGet;

    current = h->getName();
    checker = h->check;

    cout << "You are in the " << current << endl;

    while(checker == 0)
    {
        cout << ">> ";
        cin >> command;
        commandCheck = commandHandler(command);
        if(commandCheck < 4)
        {
            cout << ">> ";
            cin >> object;
            if(commandCheck == 1)
            {
                if(object == "brasskey")
                {

                    if(h->keyGet == 1 && h->objCheck == 1)
                    {
                        cout << "You got the brasskey! " << endl;
						inventory[7] = "brasskey";
                        h->objCheck = 2;
                    }
                    else
                        cout << "You can't get that right now " << endl;
                }
                else
                    cout << "That is not a valid object" << endl;    
            }
            else if(commandCheck == 2)
            {
                if(object == "brasskey")
                {
                    h->lookObj();
                }
                else if(object == "door")
                {
                    cout << "It's a door. It looks very weak, like something could break it easily." << endl;
                }
                else
                    cout << "You can't do that! " << endl;
            }
            else if(commandCheck == 3)
            {
                if(object == "crowbar")
                {
                    pocket = inventory[1];
                    if(pocket == "crowbar" && h->doorCheck == 0)
                    {
                        cout << "You hit the door with the crowbar. It easily crumbles apart. You can now go further down the hall" << endl;
						cout << "(You need to go to another room before you can continue down this hall.)" << endl;
                        h->doorCheck = 1;
                    }
                    else
                        cout << "You can't do that " << endl;
                }
             
                else if(object == "shield")
                {    
                    pocket = inventory[6];
                    if(pocket == "shield")
                    {
                        cout << "You slide the shield into the small slot. The cage around the brasskey disappears." << endl;
                        h->stat = 0;
                        h->keyGet = 1;
                    }
                    else
                        cout << "You don't have that item! " << endl;
                }
                else
                    cout << "You can't do that!" << endl;
            }
        }

        else if(commandCheck == 4)
        {
            cout << "All objects in the room: " << endl;
            cout << "A brasskey in a cage " << endl;
            cout << "A large door that looks very old " << endl;
        }
        else if(commandCheck == 5)
        {
            cout << "You can go left, right or forward " << endl;
            cout << ">> ";
            cin >> where;
            if(where == "left")
            {
                return 2;
                checker = 1;
            }
            else if(where == "right")
            {
                return 3;
                checker = 1;
            }
            else if (where == "forward")
            {
                if(doorCheck == 1)
                {
                    return 4;
                    checker = 1;
                }
                else
                    cout << "The door is in the way " << endl;
            }
            else 
                cout << "You can't do that " << endl;
        }
        else if(commandCheck == 6)
        {
            cout << "Pokcet: " << endl;
            for(int i = 0; i < 9; i++)
            {
                pocket = inventory[i];
                cout << pocket << endl;
            }
        }
    }    
}


int closetDriver(Closet *c, string inventory[])
{
    string current;
    string command;
    string object;
    string where;
    string classObj1 = c->object1;
    string classObj2 = c->object2;
    string pocket;

    int commandCheck;

    int checker;
    int buff;



    current = c->getName();
    int objCheck = c->getObjectStat();
    checker = c->check;

    cout << "You are in the " << current << endl;

    while(checker == 0)
    {
        cout << ">> ";
        cin >> command;
        commandCheck = commandHandler(command);
        if(commandCheck < 4)
        {
            cout << ">> ";
            cin >> object;
            if(commandCheck == 1)
            {
                if(object == classObj1)
                {
					if(c->swordCheck == 1)
					{
                    	cout << "You got the sword! " << endl;
	                    inventory[2] = "sword";
    	                c->swordCheck = 2;
					}
					else
						cout << "You can't do that!" << endl;
                }
                else if (object == classObj2 && c->shieldCheck == 1)
                {
                    cout << "You got the shield! " << endl;
                    inventory[6] = "shield";
                    c->shieldCheck = 0;
                }
                else
                    cout << "You can't do that " << endl;
            }
            else if(commandCheck == 2)
            {
				if(object == classObj1)
				{
					c->lookObj();
				}
				else if(object == classObj2)
				{
					c->lookObj2();
				}

            }
            else if(commandCheck == 3)
            {
	         if(object == "crowbar")
                {
	   		      pocket = inventory[1];
                    if(pocket == "crowbar" && c->swordCheck == 0)
                    {
                        cout << "You break the box and the sword falls out!" << endl;
                      
                        c->swordCheck = 1;
                    }
                    else 
                        cout << "You can't do that! " << endl;
                }
                else if (object == "jewel")
                {
                    pocket = inventory[5];
                    if(pocket == "jewel")
                    {
                        cout << "You put the jewel in the small slot. The shield stops glowing. You can touch it now. " << endl;
                        c->shieldCheck = 1;
                    }
                }
                else
                    cout << "You can't do that! " << endl;

            }
        }

        else if(commandCheck == 4)
        {
            cout << "All objects in the room: " << endl;
			if(c->objCheck == 1)
			{
				cout << "sword" << endl;
			}
			if(c->objCheck2 == 1)
			{
				cout << "shield" << endl;
			}
        }
        else if(commandCheck == 5)
        {
            cout << "You can go back "<< endl;
            cout << ">> ";
            cin >> where;
            if(where == "back")
            {
	        	return 1;
				checker = 1;
            }
            else
                cout << "You can't do that " << endl;
        }
        else if(commandCheck == 6)
        {
            cout << "Pokcet: " << endl;
            for(int i = 0; i < 9; i++)
            {
                pocket = inventory[i];
                cout << pocket << endl;
            }
        }
    }    
}



int towerDriver(Tower *t, string inventory[])
{
    string current;
    string command;
    string object;
    string where;
    string classObj1 = t->object1;
    string classObj2 = t->object2;
    string pocket;

    int commandCheck;

    int checker;
    int buff;

    current = t->getName();
    int objCheck = t->getObjectStat();
    checker = t->check;

    cout << "You are in the " << current << endl;

    while(checker == 0)
    {
        cout << ">> ";
        cin >> command;
        commandCheck = commandHandler(command);
        if(commandCheck < 4)
        {
            cout << ">> ";
            cin >> object;
            if(commandCheck == 1)
            {
				if(object == classObj1)
				{
					if(t->objCheck == 1)
					{
						cout << "You got the crowbar! " << endl;
						inventory[1] = "crowbar";
						t->objCheck = 0;
					}
					else
						cout << "You can't do that!" << endl;
				}
				else if(object == classObj2)
				{
					if(t->objCheck2 == 1 && t->gloveCheck == 1)
					{
						cout << "You got the glove! " << endl;
						inventory[4] = "glove";
						t->objCheck2 = 0;	
					}
					else
						cout << "You can't do that!" << endl;
				}
				else
					cout << "You can't do that!" << endl;
            
			}
            else if(commandCheck == 2)
            {
				if(object == classObj1)
				{
					t->lookObj();
				}
				else if(object == classObj2)
				{
					t->lookObj2();
				}

            }
            else if(commandCheck == 3)
            {
				if(object == "crown")
				{
					pocket = inventory[3];
					if(pocket == "crown")
					{
						cout << "You suddenly grow taller! The glove seems within your reach!" << endl;
						t->gloveCheck = 1;
					}
					else
						cout << "You don't have that! " << endl;
				}
				else
					cout << "You can't do that!" << endl;
            }
        }

        else if(commandCheck == 4)
        {
            cout << "All objects in the room: " << endl;
			if(t->objCheck == 1)
			{
				cout << "crowbar" << endl;
			}
			if(t->objCheck2 == 1)
			{
				cout << "glove" << endl;
			}
        }
        else if(commandCheck == 5)
        {
            cout << "You can go back "<< endl;
            cout << ">> ";
            cin >> where;
            if(where == "back")
            {
	        	return 1;
				checker = 1;
            }
            else
                cout << "You can't do that " << endl;
        }
        else if(commandCheck == 6)
        {
            cout << "Pokcet: " << endl;
            for(int i = 0; i < 9; i++)
            {
                pocket = inventory[i];
                cout << pocket << endl;
            }
        }
    }    
}


int gateDriver(Gate *g, string inventory[])
{
	string current;
    string command;
    string object;
    string where;
    string classObj1 = g->object1;
    string pocket;

    int commandCheck;

    int checker;
    int buff;

    current = g->getName();
    int objCheck = g->getObjectStat();
    checker = g->check;

    cout << "You are in the " << current << endl;

    while(checker == 0)
    {
        cout << ">> ";
        cin >> command;
        commandCheck = commandHandler(command);
        if(commandCheck < 4)
        {
            cout << ">> ";
            cin >> object;
            if(commandCheck == 1)
            {
				cout << "You can't do that! " << endl;			
			}
			else if(commandCheck == 2)
        	{
				if(object == classObj1)
				{
					g->lookObj();
				}
        	}
			else if(commandCheck == 3)
         	{
				if(object == "brasskey")
				{
					pocket = inventory[7];
					if(pocket == "brasskey")
					{
						cout << "You open the gate! You walk outside! You're free! " << endl;
						return 7;
						checker = 1;
					}
					else
						cout << "You can't do that! " << endl;
				}
				else
					cout << "You can't do that! " << endl;		

		 	}
		}
		else if(commandCheck == 4)
        {
            cout << "All objects in the room: " << endl;
			cout << "Gate " << endl;
        }
        else if(commandCheck == 5)
        {
            cout << "You can go left, right, or back. "<< endl;
            cout << ">> ";
            cin >> where;
    		if(where == "left")
			{
				return 5;
				checker = 1;
			}
			else if(where == "right")
			{
				return 6;
				checker = 1;
			}
			else if(where == "back")
			{
				return 1;
				checker = 1;
			}
            else
                cout << "You can't do that " << endl;
        }
        else if(commandCheck == 6)
        {
            cout << "Pokcet: " << endl;
            for(int i = 0; i < 9; i++)
            {
                pocket = inventory[i];
                cout << pocket << endl;
			}
		}
	}
}

int courtDriver(Court *co, string inventory[])
{
	string current;
    string command;
    string object;
    string where;
    string classObj1 = co->object1;
    string pocket;

    int commandCheck;

    int checker;
    int buff;

    current = co->getName();
    int objCheck = co->getObjectStat();
    checker = co->check;

    cout << "You are in the " << current << endl;

    while(checker == 0)
    {
        cout << ">> ";
        cin >> command;
        commandCheck = commandHandler(command);
        if(commandCheck < 4)
        {
            cout << ">> ";
            cin >> object;
            if(commandCheck == 1)
            {
				if(object == classObj1 && co->jewelGet == 1)
				{
					cout << "You got the jewel! " << endl;
					inventory[5] = "jewel";
					co->jewelGet = 2;
					co->objCheck = 0;
				}
				else 
					cout << "You can't do that! " << endl;				
			}
			else if(commandCheck == 2)
        	{
				if(object == classObj1)
				{
					co->lookObj();
				}

        	}
			else if(commandCheck == 3)
         	{
				pocket = inventory[4];
				if(pocket == "glove" && co->jewelGet == 0)
				{
					cout << "You put on the glove! It looks safe to touch the jewel now!" << endl;
					co->jewelGet = 1;
					co->stat = 1;
				}	
				else
					cout << "You can't do that!" << endl;
		 	}
		}
		  else if(commandCheck == 4)
          {
            cout << "All objects in the room: " << endl;
			if(co->objCheck == 1)
			{
				cout << "jewel" << endl;
			}
        }
        else if(commandCheck == 5)
        {
            cout << "You can go back "<< endl;
            cout << ">> ";
            cin >> where;
            if(where == "back")
            {
	        	return 4;
				checker = 1;
            }
            else
                cout << "You can't do that " << endl;
        }
        else if(commandCheck == 6)
        {
            cout << "Pokcet: " << endl;
            for(int i = 0; i < 9; i++)
            {
                pocket = inventory[i];
                cout << pocket << endl;
			}
		}
	}
}




		


int throneDriver(Throne *th, string inventory[])
{
	string current;
    string command;
    string object;
    string where;
    string classObj1 = th->object1;
    string pocket;

    int commandCheck;

    int checker;
    int buff;

    current = th->getName();
    int objCheck = th->getObjectStat();
    checker = th->check;

    cout << "You are in the " << current << endl;

    while(checker == 0)
    {
        cout << ">> ";
        cin >> command;
        commandCheck = commandHandler(command);
        if(commandCheck < 4)
        {
            cout << ">> ";
            cin >> object;
            if(commandCheck == 1)
            {
				if(object == classObj1 && th->crownGet == 1)
				{
					cout << "You got the crown! " << endl;
					inventory[3] = "crown";
					th->crownGet = 2;
					th->objCheck = 0;			
				}
				else
					cout << "You can't do that!" << endl;
			}
			else if(commandCheck == 2)
        	{
				if(object == classObj1)
				{
					th->lookObj();
				}

        	}
			else if(commandCheck == 3)
         	{
				if(object == "sword")
				{
					pocket = inventory[2];
					if(pocket == "sword" && th->stat == 0)
					{
						cout << "You use the sword to break open the casing! The crown is just sitting there! " << endl;
						th->stat = 1;
						th->crownGet = 1;
					}
				}
				else
					cout << "You can't do that! " << endl;
		 	}
		}
		else if(commandCheck == 4)
        {
            cout << "All objects in the room: " << endl;
			if(th->objCheck == 1)
			{
				cout << "crown" << endl;

			}
        }
        else if(commandCheck == 5)
        {
            cout << "You can go back "<< endl;
            cout << ">> ";
            cin >> where;
            if(where == "back")
            {
	        	return 4;
				checker = 1;
            }
            else
                cout << "You can't do that " << endl;
        }
        else if(commandCheck == 6)
        {
            cout << "Pokcet: " << endl;
            for(int i = 0; i < 9; i++)
            {
                pocket = inventory[i];
                cout << pocket << endl;
			}
		}
	}
}







