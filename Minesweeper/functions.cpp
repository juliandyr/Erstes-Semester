#include <iostream>
#include <vector>
#include <array>
#include "functions.h"
#include <random>

//rdm nummer
std::random_device rd;
std::mt19937 gen(rd());
int getRandom(int lower, int upper)
{
    std::uniform_int_distribution<int> dist(lower, upper);
    return dist(gen);
}

array<array<Tile, cols>, rows> spielfeld2DA;

int debug = false;

//für initialize()
int countMines(int x, int y){
    int count {0};
    for (int dx =-1; dx <=1; dx++){
        for (int dy = -1; dy <=1; dy++){
            if (dx == 0 && dy == 0){
                continue;
            }
            int newx = x + dx;
            int newy = y + dy;
            //grenzen überprüfen && falls mine count erhöhen
            if (newx >= 0 && newx < rows && newy >= 0 && newy < cols){
                if (spielfeld2DA.at(newx).at(newy).state == mine){
                    count++;
                }
            }
        }
    }
    return count;
};


void initialize(){
    //alle tiles auf hidden
    for (size_t r =0; r < rows; r++){
        for(size_t c =0; c < cols; c++){
            spielfeld2DA.at(r).at(c).state =hidden;
            spielfeld2DA.at(r).at(c).sourroundingMines = 0;
        }
    }

    //minen plazieren
    for(int i =0; i < 15; ){
        int a=getRandom(0,11);
        int b=getRandom(0,11);
        //damit keine mine mit einer mine überschrieben wird:
        if (spielfeld2DA.at(a).at(b).state==mine){
            continue;
        }
        i++;
        spielfeld2DA.at(a).at(b).state=mine;
    }

    //sourroundingmines schauen für eine koordinate
    for (size_t r = 0; r < rows; r++){
        for (size_t c = 0; c < cols; c++){
            if (spielfeld2DA.at(r).at(c).state != mine){
                spielfeld2DA.at(r).at(c).sourroundingMines = countMines(r,c); //countmines ist die funktion
            }
        }
    }


};


void display(){
    for (size_t r = 0; r < rows; r++){
        //für Zeilennummer (zweistellig)
        if (r+1<10) std::cout<< "0"<<r+1<<"|";
        else std::cout<<r+1<<"|";

        //spieleransicht
        for (size_t c = 0; c < cols; c++){
            if (spielfeld2DA.at(r).at(c).state == hidden ||spielfeld2DA.at(r).at(c).state == mine){
                std::cout <<" *";
            }
            else if (spielfeld2DA.at(r).at(c).state == revealed && spielfeld2DA.at(r).at(c).sourroundingMines ==0){
                std::cout <<" .";
            }
            else if (spielfeld2DA.at(r).at(c).state == revealed && spielfeld2DA.at(r).at(c).sourroundingMines >0){
                std::cout <<" "<<spielfeld2DA.at(r).at(c).sourroundingMines;
            }
        }

        // Abstand zwischen Spieleransicht und Debug-Ansicht
        std::cout << "   ";
        // FÜR DEBUG ANSICHT AUSKOMMENTIEREN ENTFERNEN!!!!!
        // Zeilennummer rechts
        if (debug ==true){
            if (r + 1 < 10) std::cout << "0" << r + 1 << "|";
            else std::cout << r + 1 << "|";

            for (size_t c = 0; c < cols; c++) {
                if (spielfeld2DA.at(r).at(c).state == mine) {
                    std::cout << " X";
                }
                else {
                    std::cout << " *";
                }
            }
        }

        std::cout << std::endl;
    }
    //untere Trennlinie
    for (int i = 0; i < cols * 2 + 3; i++) std::cout << "-";
    std::cout << " ";
    // FÜR DEBUG ANSICHT DEBUG AUF TRUE! (OBEN)
    if (debug==true){
        for (int i = 0; i < cols * 2 + 3; i++) std::cout << "-";
    }
    std::cout << std::endl;

    //spaltennummern unten
    std::cout << "   ";
    for (size_t c = 1; c <= cols; c++) {
        if (c < 10) std::cout << " " << c;
        else std::cout << c;
    }
    // FÜR DEBUG ANSICHT DEBUG AUF TRUE! (OBEN)
    if (debug==true){
        std::cout << "      ";
        for (size_t c = 1; c <= cols; c++) {
            if (c < 10) std::cout << " " << c;
            else std::cout << c;
        }
    }
    std::cout << std::endl;
};

bool inputfunction(bool continuegame){

    std::cout<<"\nBitte geben sie ihren Zug ein.\nZeile (1-12) _Leerzeichen_ Spalte (1-12):"<<std::endl;
    int zeile,spalte;
    std::cin>>zeile >>spalte;
    zeile--; spalte--;

    // Eingabegrenzen prüfen
    if (zeile < 0 || zeile >= rows || spalte < 0 || spalte >= cols) {
        std::cout << "Ungültige Eingabe!" << std::endl;
        return continuegame==true;
    }

    if (spielfeld2DA.at(zeile).at(spalte).state==mine){
        debug=true;
        return continuegame==false;
    }

    if (spielfeld2DA.at(zeile).at(spalte).sourroundingMines == 0) {
        // Erst aufdecken, dann checkNeighbours aktivieren
        spielfeld2DA.at(zeile).at(spalte).state = revealed;
        checkNeighbours();
    } else {
        spielfeld2DA.at(zeile).at(spalte).state = revealed;
    }

    return true;

};

bool revealedEmptyNeighbour(int x, int y){
    for (int dx =-1; dx <=1; dx++){
        for (int dy = -1; dy <=1; dy++){
            int newx = x + dx;
            int newy = y + dy;
            if (newx >= 0 && newx < rows && newy >= 0 && newy < cols)
                if (spielfeld2DA.at(newx).at(newy).state==revealed &&
                    spielfeld2DA.at(newx).at(newy).sourroundingMines== 0){
                    return true;
                }
        }
    }
    return false;
};

bool checkNeighbours(){
    bool verändert;
    bool repeat=true;
    do {
        repeat = false;
        for (size_t r = 0; r < rows; r++) {
            for (size_t c = 0; c < cols; c++) {
                if (spielfeld2DA.at(r).at(c).state == hidden &&
                    revealedEmptyNeighbour(r, c)) {
                    spielfeld2DA.at(r).at(c).state = revealed;
                    repeat = true;
                    verändert = true;
                }
            }
        }
    } while (repeat);

    return verändert;
};

int counthiddentiles(int x, int y){
    int count{0};
    int newx = x;
    int newy = y;
    for (size_t r=0; r < rows; r++ ){
        for (size_t c=0; c<cols; c++){
            if (spielfeld2DA.at(newx).at(newy).state == hidden){
                count++;
            }
            else break;
        }
    }
    count -= 15;
    return count;
};





