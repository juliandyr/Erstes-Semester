#ifndef PTEROSAUR_H
#define PTEROSAUR_H
#include "dinosaur.h"



class Pterosaur : public Dinosaur{
public:
    Pterosaur(double maxW, const std::string &r, double growthR, double BreedSRate, double huntSuccesRate);

    bool hunt(std::vector<Dinosaur*>& herbivores, std::vector<Dinosaur*>& carnivores)override;
    bool huntSuccess();

private:
    double huntSuccesfulRate;
    int notEatenCounter;

};

#endif // PTEROSAUR_H
