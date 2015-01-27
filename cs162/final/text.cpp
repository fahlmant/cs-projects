/*****
*Author: Taylor Fahlman
*Program: Final CS 162 Project - Castle Quest
*Date Due: 6/11/13
*Description: A text based game that has the player go through rooms and collect items, eventually exiting the last room and ending the game
*****/
#include <Dungeon.h>
#include <Hall.h>
#include <Closet.h>
#include <Tower.h>
#include <Throne.h>
#include <Court.h>
#include <Gate.h>
#include <iostream>
#include <string>
#include <Drivers.h>


using std::string;
using std::cout;
using std::endl;
using std::cin;

/***
*Function: Main
*Desciption: Creates pointers to object of each type of room needed in the game. Handles what room the player is in. Starts game, prints out welcome messages and end messages, then deletes ptrs; 
***/

int main()
{
    string inventory[9];
    int gameCheck = 0;

    cout << endl;
    cout << endl;
    welcome();

    Dungeon *d = new Dungeon();
    Hall *h = new Hall();
    Tower *t = new Tower();
    Closet *c = new Closet();
    Gate *g = new Gate();
    Court *co = new Court();
    Throne *th = new Throne();
    


    dungeonDriver(d, inventory);
    gameCheck = 1;
    while(gameCheck != 8)
    {
		if(gameCheck == 1)
		{
                	gameCheck = hallDriver(h, inventory);
		}
		else if(gameCheck == 2)
		{
			gameCheck = closetDriver(c, inventory);
        	}
		else if(gameCheck == 3)
		{
			gameCheck = towerDriver(t, inventory);
		}
		else if(gameCheck == 4)
		{
			gameCheck = gateDriver(g, inventory);
		}
		else if(gameCheck == 5)
		{
			gameCheck = throneDriver(th, inventory);	
		}
		else if(gameCheck == 6)
		{
			gameCheck = courtDriver(co, inventory);
		}
		else if(gameCheck == 7)
		{	
			cout << "You won the game! Congrats! " << endl;
			gameCheck = 8;
		}

    } 
    
    delete d;
    delete h;	
    delete t;
    delete c;
    delete g;
    delete th;
    delete co;
	
    return 0;

}

