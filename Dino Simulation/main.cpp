#include <iostream>
#include <random>
#include <vector>
#include "park.h"
#include <random.h>

using namespace std;

int getRandom(int lower, int upper);
std::random_device rd;

int getRandom(int lower, int upper)
{
    std::uniform_int_distribution<int> dist(lower, upper);
    return dist(rd);
}



int main()
{
    Park newPark;
    newPark.fillingPark();
    newPark.printPark();
    bool var{true};
    while(var){
        std::cout<<"wie viel zeit soll vergehen? "<<std::endl;
        int time;
        std::cin>> time;
        newPark.passingTime(time);
        newPark.printPark();
        std::cout<<"soll weiter? 0 Nein, 1 Ja"<<std::endl;
        std::cin>>var;
    }
    return 0;
}
