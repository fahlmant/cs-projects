#ifndef VEHICLE_H
#define VEHICLE_H

#include <iostream>
#include <stdlib.h>
#include <Creature.h>

class Creature_car{
     
    public:
        Creature *driver;
        Creature_car()
        {
            driver = NULL;
        }
        Creature_car(Creature *newDriver)
        {
            driver = newDriver;
        }
        string getVehicle();
        int getDistance();
};

string Creature_car :: getVehicle()
{
    string vehicle = "Vehicle";
    return vehicle;
}

int Creature_car :: getDistance()
{
    int dist = 100;
    return dist;

}

#endif /* VEHICLE_H */
