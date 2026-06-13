#ifndef CARNIVORE_H
#define CARNIVORE_H
#include "dinosaur.h"

class Carnivore : public Dinosaur
{
public:
    Carnivore(int weight, int maxWeigt, std::string race, int age, double grothRate, int breedChance, int dieChance);
    void hunt(int index);        //soll später Vektor bekommen wo Herbis drin sind und wenn einer nicht versteckt= gefressen
        //dafür mit for schleife durch und falls gefressen break; und saturated yes
        //dann zähler nach for schleife, der die (Tage) zählt. Wenn mehr als 2 stirbt der carni

    bool breed() override;
    void age() override;
    bool isDead() override;
    int getAge() const override;
    int getWeight() const override;
    std::string getRace() const override;
    //bool getDead() const;

    bool getSaturated() const;
    void setSaturated(bool value);

private:
    int counter{0}; //wenn hunt 2mal nicht erfolgreich stirbt der carni
    bool saturated;

};

#endif // CARNIVORE_H
