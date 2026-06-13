#include "park.h"
#include "dinosaur.h"
#include "herbivore.h"
#include "carnivore.h"
#include <vector>
#include <iostream>

Park::Park(){}

std::vector<Herbivore> herbiVector;
std::vector<Carnivore> carniVector;

void Park::fillingPark()
{



    //befüllen mit 4 Brachiosauriern und 4 Raptoren
    for (int i=1; i <5; i++){
        Herbivore newHerbi(1500, 30000, "Brachiosaurus",0,0.2,20,20,50);
        herbiVector.push_back(newHerbi);
        Carnivore newCarni(100, 1500, "Raptor",0,0.3,12,30);
        carniVector.push_back(newCarni);
    }
    //5 Parasaurolophusse
    for (int i=1; i <6; i++){
        Herbivore newHerbi(75, 15000, "Parasaurolophus",0,0.4,85,40,75);
        herbiVector.push_back(newHerbi);
    }
    //2 T-Rexe
    for (int i=1; i <3; i++){
        Carnivore newCarni(1600, 8000, "T-Rex",0,0.2,8,20);
        carniVector.push_back(newCarni);
    }
}

void Park::printPark()
{
    std::cout<<"Willkommen bei JURASSIC PARK!\n"
                 "Herbivoren: "<<std::endl;
    for (size_t i=0; i< herbiVector.size();i++){
        std::cout << "Rasse: "<< herbiVector.at(i).getRace()<<"\t"
                  << " Alter: "<< herbiVector.at(i).getAge()<<"\t"
                  << " Gewicht: "<< herbiVector.at(i).getWeight()
                  << std::endl;
    }
    std::cout<<
        "Carnivoren: "<<std::endl;
    for (size_t i=0; i< carniVector.size();i++){
        std::cout << "Rasse: "<< carniVector.at(i).getRace()<<"\t"
                  << " Alter: "<< carniVector.at(i).getAge()<<"\t"
                  << "Gewicht: "<< carniVector.at(i).getWeight()
                  << std::endl;
    }
    std::cout<<"Population Herbivoren: "<<herbiVector.size()<<" Population Carnivoren: "<<carniVector.size()<<std::endl;
}



void Park::passingTime(int time){


    for (int i =0; i < time; i++){
        for(size_t i=0; i < herbiVector.size(); i++){
            herbiVector.at(i).age();
            herbiVector.at(i).hide();
            //verändert größe des vektors
        }
        for (Herbivore herbivore: herbiVector){
            herbivore.breed();
        }
        for(size_t i=0; i < carniVector.size(); i++){
            carniVector.at(i).age();
            carniVector.at(i).hunt(i);
            if(carniVector.at(i).getDead()){
                Dinosaur::removeCarni();
            }
        }
        for (Carnivore carnivore: carniVector){
            carnivore.breed();
        }
        Dinosaur::removeHerbi();
        Dinosaur::removeCarni();
    }
}

/*
        for (auto& herbi : herbiVector) {
            herbi.age();
            herbi.hide();
            herbi.breed();
        }*/
