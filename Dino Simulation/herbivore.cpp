#include "herbivore.h"
#include "random.h"
#include "park.h"
Herbivore::Herbivore(int weight, int maxWeigt, std::string race, int age, double grothRate, int breedChance, int dieChance, int hideChance)
    : Dinosaur(weight,maxWeigt,race,age,grothRate,breedChance,dieChance), m_hideChance(hideChance)
{

}

bool Herbivore::hide()
{
    if (m_randHideChance <= getHideChance()){
        isHidden=true;
        return true;
    }
    else return false;
}

void Herbivore::age()
{
    Dinosaur::age();
}


bool Herbivore::breed()
{

    if(herbiVector.size()+carniVector.size() <100){
        int m_randbreedChance=getRandom(1,100);
        if(m_randbreedChance<=getBreedChance()){
            if (getRace()=="Brachiosaurus"){
                Herbivore newHerbi(1500, 30000, "Brachiosaurus",0,0.2,20,20,50);
                herbiVector.push_back(newHerbi);
                std::cout<<"Brachiosaurus hat ein Kind bekommen :) "<<std::endl;
            }
            if(herbiVector.size()+carniVector.size() <97){
                if (getRace()=="Parasaurolophus"){
                    for (int i=0;i<3;i++){
                        Herbivore newHerbi(75, 15000, "Parasaurolophus",0,0.4,85,40,75);
                        herbiVector.push_back(newHerbi);
                    }
                    std::cout<<"Parasaurolophus hat 3 Kinder bekommen :) "<<std::endl;
                }
                return true;
            }
        }
        return false;
    }
    std::cout<<"park ist voll"<<std::endl;
    return false;
}

int Herbivore::getHideChance() const
{
    return m_hideChance;
}

bool Herbivore::getIsHidden() const
{
    return isHidden;
}



