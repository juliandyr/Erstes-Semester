#include "dinosaur.h"
#include "random.h"
#include "park.h"

Dinosaur::Dinosaur(int weight, int maxWeigt, std::string race, int age, double growthRate, int breedChance, int dieChance)
    : m_weight(weight), m_maxweight(maxWeigt), m_race(race), m_age(age), m_growthRate(growthRate), m_breedChance(breedChance), m_dieChance(dieChance)
{

}

bool Dinosaur::breed() {
    return false;  // default Verhalten
}

void Dinosaur::age()
{
    m_age++;
    //zunehmen
    if(getWeight()<getMaxweight()){
        m_weight+=(getGrowthRate()*m_weight);
    }
    //bei maxweight chance zu sterben
    else {
        m_weight=getMaxweight();
        if(getDieChance()<=m_randDieChance){
            m_dead=true;
        }
        else setDead(true);
    }
}


bool Dinosaur::isDead()
{
    if (m_dead==true)
        return true;
    else return false;
}


void Dinosaur::removeHerbi()
{
    for (size_t i =0; i < herbiVector.size(); i++){
        if(herbiVector.at(i).isDead()){
            herbiVector.erase(herbiVector.begin()+i);
            i--;        //weil sich nach dem löschen der index verschiebt
        }
    }
}

void Dinosaur::removeCarni()
{
    for (size_t i =0; i < carniVector.size(); i++){
        if(carniVector.at(i).isDead()){
            carniVector.erase(carniVector.begin()+i);
            i--;        //weil sich nach dem löschen der index verschiebt
        }
    }
}

int Dinosaur::getWeight() const
{
    return m_weight;
}

void Dinosaur::setWeight(int weight)
{
    m_weight = weight;
}

int Dinosaur::getMaxweight() const
{
    return m_maxweight;
}

double Dinosaur::getGrowthRate() const
{
    return m_growthRate;
}

int Dinosaur::getBreedChance() const
{
    return m_breedChance;
}

std::string Dinosaur::getRace() const
{
    return m_race;
}

int Dinosaur::getDieChance() const
{
    return m_dieChance;
}

bool Dinosaur::getDead() const
{
    return m_dead;
}

void Dinosaur::setDead(bool dead)
{
    m_dead = dead;
}

int Dinosaur::getAge() const
{
    return m_age;
}


