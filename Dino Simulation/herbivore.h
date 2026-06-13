#ifndef HERBIVORE_H
#define HERBIVORE_H
#include "dinosaur.h"

#include "random.h"
class Herbivore: public Dinosaur
{
public:
    Herbivore(int weight, int maxWeigt, std::string race, int age, double grothRate, int breedChance, int dieChance, int hideChance);
    bool hide();
    void age() override;
    bool breed() override;
    int m_randHideChance=getRandom(1,100);


    int getHideChance() const;

    bool getIsHidden() const;

private:
    int m_hideChance;
    bool isHidden{false};


};

#endif // HERBIVORE_H
