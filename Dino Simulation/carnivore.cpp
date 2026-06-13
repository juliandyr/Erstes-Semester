#include "carnivore.h"
#include "park.h"


Carnivore::Carnivore(int weight, int maxWeigt, std::string race, int age, double grothRate, int breedChance, int dieChance)
    : Dinosaur(weight,maxWeigt,race,age,grothRate,breedChance,dieChance)
{

}

void Carnivore::hunt(int index)
{
    bool hasEaten = false;

    for (size_t i = 0; i < herbiVector.size(); i++) {
        if (herbiVector.at(i).getWeight() < carniVector.at(index).getWeight()) {
            if (!herbiVector.at(i).getIsHidden()) {
                herbiVector.at(i).setDead(true); // Nur markieren
                carniVector.at(index).setSaturated(true);
                std::cout << herbiVector.at(i).getRace() << " ist gestorben weil gefressen\n";
                hasEaten = true;
                break;  // Nur ein Tier pro Zeit fressen
            }
        }
    }

    if (!hasEaten) {
        counter++;
    } else {
        counter = 0; // reset, weil er gefressen hat
    }

    if (counter >= 2 && !carniVector.at(index).getSaturated()) {
        carniVector.at(index).setDead(true);  // Nur markieren
        std::cout << "Carni ist gestorben weil verhungert\n";
    }
}



bool Carnivore::breed()
{
    if(herbiVector.size()+carniVector.size() <100){
        int m_randbreedChance=getRandom(1,100);
        if(m_randbreedChance<=getBreedChance()){
            if (getRace()=="Raptor"){
                Carnivore newCarni(100, 1500, "Raptor",0,0.3,12,30);
                carniVector.push_back(newCarni);
            }
            else if (getRace()=="T-Rex"){
                Carnivore newCarni(1600, 8000, "T-Rex",0,0.2,8,20);
                carniVector.push_back(newCarni);
            }
            return true;
        }
        return false;
    }
    return false;
}

void Carnivore::age()
{
    Dinosaur::age();
}

bool Carnivore::isDead()
{
    return Dinosaur::isDead();
}

int Carnivore::getAge() const
{
    return Dinosaur::getAge();
}

int Carnivore::getWeight() const
{
    return Dinosaur::getWeight();
}

std::string Carnivore::getRace() const
{
    return Dinosaur::getRace();
}


bool Carnivore::getSaturated() const
{
    return saturated;
}

void Carnivore::setSaturated(bool value)
{
    saturated = value;
}


