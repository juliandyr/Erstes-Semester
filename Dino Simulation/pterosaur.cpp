#include "pterosaur.h"


Pterosaur::Pterosaur(double maxW, const std::string &r, double growthR, double BreedSRate, double huntSuccesRate) : Dinosaur(maxW, r, growthR, BreedSRate)
{
    weight = maxWeight * 0.20;
    huntSuccesfulRate = huntSuccesRate;
    notEatenCounter = 0;
}

bool Pterosaur::huntSuccess(){
    int randomNumber = getRandom(1,100);
    int huntSuccesfulR = huntSuccesfulRate * 100;
    for(int i = huntSuccesfulR+1; i<=100;i++){
        if(randomNumber == i){
            return false;
        }
    }
    return true;
}



bool Pterosaur::hunt(std::vector<Dinosaur *> &herbivores, std::vector<Dinosaur *> &carnivores){
    unsigned long notHuntCounter = 0;
    bool huntHerbivoreSuccess = true;

    if(notEatenCounter == 3){
        setAlive(false);
        return false;
    }
    for (size_t i = 0; i < herbivores.size(); ++i){
        if(!huntSuccess()){
            //std::cout << "Pterosauro hat nichts gegessen" << std::endl;
            notHuntCounter++;
        }
        else{
            huntHerbivoreSuccess = true;
            return true;

        }
        if(notHuntCounter == herbivores.size()){
            huntHerbivoreSuccess = false;
        }
    }
    if(!huntHerbivoreSuccess){
        notHuntCounter = 0;
        for (size_t i = 0; i < carnivores.size(); ++i){
            if(!huntSuccess()){
                notHuntCounter++;
            }
            else{
                return true;
            }
            if(notHuntCounter == carnivores.size()){
                notEatenCounter++;
                return false;
            }

        }
    }
}

