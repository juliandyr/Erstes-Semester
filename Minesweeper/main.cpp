#include <iostream>
#include "functions.h"
#include <array>




int main()
{
    initialize();
    display();
    while (inputfunction(true)){
        display();
        int counttiles{0};
        for (size_t r=0; r < rows; r++ ){
            for (size_t c=0; c<cols; c++){
                if (spielfeld2DA.at(r).at(c).state == hidden &&
                    spielfeld2DA.at(r).at(c).state !=mine){
                    counttiles++;
                }
            }
        }
        std::cout<<"Verbleibende Felder: "<<counttiles<<std::endl;
        if (counttiles == 0){
            std::cout<<"DU HAST GEWONNEN!"<<std::endl;
            return 0;
        }
    }
    std::cout<<"***BOOOOOM***\nDas Spiel ist vorbei :("<<std::endl;
    display();
    return 0;
}

