#include <iostream>
#include <cmath>

//Defines the specific weight of water
#define WATER_WEIGHT 62.4
#define PI 3.13159

using namespace std;

int main() {
   //Variables needed to calculate buoyancy
   float radius, bforce, volume, weight; 

   //Prompt user for weight and radius of sphere
   cout << "Please enter the weight (lbs): ";
   cin >> weight;

   cout << "Please enter the radius: ";
   cin >> radius;

   //Calculate the volume and buoyancy force
   int radthree = (radius * radius) * radius;
   volume = (4/3) * PI * radthree;
   bforce = volume * WATER_WEIGHT;

   //Determine if the sphere will sink or float
   if(bforce >= weight) {
      cout << "The sphere will float!\n";
   }
   else{
      cout << "The sphere will sink!\n"; 
   }

   return 0;
}
