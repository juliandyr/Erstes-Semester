#ifndef DINOSAURIER_H
#define DINOSAURIER_H
#include <string>
#include "random.h"
#include <vector>
class Dinosaur
{
public:


    Dinosaur(int weight, int maxWeigt, std::string race, int age, double grothRate, int breedChance, int dieChance);

    virtual void age();

    virtual bool breed();

    virtual bool isDead();

    virtual int getWeight() const;

    void setWeight(int weight);

    int getMaxweight() const;

    double getGrowthRate() const;

    int getBreedChance() const;

    static void removeHerbi();
    static void removeCarni();


    virtual std::string getRace() const;


    int m_randDieChance=getRandom(1,100);
    int getDieChance() const;

    virtual bool getDead() const;
    void setDead(bool dead);

    virtual int getAge() const;

private:
    int m_weight;
    int m_maxweight;
    std::string m_race;
    int m_age {0};
    bool m_dead{false};
    double m_growthRate;
    int m_breedChance;
    int m_dieChance;
};

#endif // DINOSAURIER_H

