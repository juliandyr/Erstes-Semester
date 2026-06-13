#ifndef PARK_H
#define PARK_H
#include <iostream>
#include <vector>
#include "dinosaur.h"
#include "herbivore.h"
#include "carnivore.h"

//Vectoren für Herbis und Carnis
extern std::vector<Herbivore>herbiVector;
extern std::vector<Carnivore>carniVector;

class Park{
public:
    Park();
    void passingTime(int time);
    void fillingPark();
    void printPark();
private:

};



#endif // PARK_H
