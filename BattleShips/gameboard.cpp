#include "gameboard.h"
#include <iostream>
#include <ostream>
#include "random.h"
#include <random>

//sets the "schmierzettel" with only 's' and then calls the randomPlaceships
GameBoard::GameBoard(){
    for (size_t i = 0; i< m_enemyBoard.size();i++){
        for (size_t e = 0; e< m_enemyBoard[i].size();e++){
            m_enemyBoard.at(i).at(e) = '.';
        }
    }
    randomPlaceShips();

}

void GameBoard::printBoard(){

    //bool makes it easier if there is a part of the ship at the coordinates;
    //if nothing is there, if nicht gefunden (gefunden = false), then that coordinate is water
    //example: 00 -> now the third for loop goes through every element of m_ships.
    //let's say singleship number 1 has a part of its ship in 00, then the method hasPartin will return true, if
    //thats the case, then depending on the status of the part, it will be displayed as for example a damagedPart
    //the if (gefunden = false) will not be read due to gefunden being set to true, if found.

        constexpr char water = '.';
        constexpr char damagedPart = 'X';
        constexpr char sunkenShipPart = 'S';

        std::cout << "    DEIN SPIELFELD\n";
        std::cout << "    ";
        for (int col = 0; col < 10; ++col)
            std::cout << col << " ";
        std::cout << "\n   " << std::string(20, '-') << "\n";

        for (int row = 0; row < 10; ++row) {
            std::cout << row << " | ";
            for (int col = 0; col < 10; ++col) {
                bool gefunden = false;
                for (size_t k = 0; k < m_ships.size(); k++) {
                    Ship& singleShip = m_ships[k];
                    if (singleShip.hasPartIn(row, col)) {
                        gefunden = true;
                        if (singleShip.getPartIn(row, col).isDamaged()) {
                            std::cout << damagedPart << " ";
                        } else if (singleShip.isSunk()) {
                            std::cout << sunkenShipPart << " ";
                        } else {
                            std::cout << k << " ";
                        }
                        break;
                    }
                }
                if (!gefunden) {
                    std::cout << water << " ";
                }
            }
            std::cout << std::endl;
        }
    }

//just prints the "Schmierzettel" -> 2D array

    void GameBoard::printEnemyBoard() {
        std::cout << "\n    SCHMIERZETTEL\n";
        std::cout << "    ";
        for (int col = 0; col < 10; ++col)
            std::cout << col << " ";
        std::cout << "\n   " << std::string(20, '-') << "\n";

        for (int row = 0; row < 10; ++row) {
            std::cout << row << " | ";
            for (int col = 0; col < 10; ++col) {
                std::cout << m_enemyBoard.at(row).at(col) << " ";
            }
            std::cout << std::endl;
        }
    }


//changes one of the ship's parts to damaged; only possible, because of getPartIn()

bool GameBoard::hit(int row, int col){
    for (size_t i = 0; i < m_ships.size(); i++){
        if(m_ships[i].hasPartIn(row,col)){                  //if true, then the ship at index i,
            Part& partRef = m_ships[i].getPartIn(row,col);  //its part will be now referenced with partRef
            partRef.setDamaged();                           //now part (=partRef) can be manipulated -> m_status set to one
            return true;
        }
    }
    return false;
}

//marks the coordinate with an 'X' if bool washit == true, if not then 'O'

void GameBoard::mark(int row, int col, bool wasHit){

    if(wasHit){
        m_enemyBoard.at(row).at(col) = 'X';
    }
    else{
        m_enemyBoard.at(row).at(col) = 'O';
    }


}

//places 10 random ships
//static cast of direction 
//make pair of coords

void GameBoard::randomPlaceShips() {
    std::array<int, 10> shipSizes = {5, 4, 4, 3, 3, 3, 2, 2, 2, 2};
    std::vector<Ship> ships;

    int maxAttempts = 1000;
    int attempts = 0;
    size_t s = 0;

    while (s < shipSizes.size() && attempts < maxAttempts) {
        int size = shipSizes[s];

        int row = getRandom(0, 9);
        int col = getRandom(0, 9);
        Direction dir = static_cast<Direction>(getRandom(0, 3));

        bool collision = false;
        std::vector<std::pair<int, int>> coords;
//gets all the coords
        for (int i = 0; i < size; ++i) {
            int r = row;
            int c = col;
            if (dir == Direction::north) r = row - i;
            if (dir == Direction::south) r = row + i;
            if (dir == Direction::east)  c = col + i;
            if (dir == Direction::west)  c = col - i;

            if (r < 0 || r >= 10 || c < 0 || c >= 10) {
                collision = true;
                break;
            }

            coords.push_back({r, c});
        }

        // checks if collided
        if (!collision) {
            for (const Ship& existing : ships) {
                for (const auto& [r, c] : coords) {
                    if (existing.hasPartIn(r, c)) {
                        collision = true;
                        break;
                    }
                }
                if (collision) break;
            }
        }

        if (!collision) {
            ships.push_back(Ship(row, col, size, dir));
            ++s;
        }

        ++attempts;
    }                                       // this was implemented because I had an out of range error
    if (ships.size() != 10) {
        std::cerr << "Fehler: Es konnten nicht 10 Schiffe platziert werden (nur "
                  << ships.size() << ")." << std::endl;
        std::exit(1);  // stops program before m_ships[i] executes
    }

    // copies safely now
    for (size_t i = 0; i < 10; ++i) {
        m_ships[i] = ships[i];
    }
}


//returns only true if all ships are sunk

bool GameBoard::allShipsSunk(){

    int counter = 0;
    for (auto ship : m_ships){
        if (ship.isSunk()){
            counter++;
        }
    }
    if (counter == 10){
        return true;
    }
    else{
        return false;
    }
}

//first attempt of randomPlaceShips

// void GameBoard::randomPlaceShips(){

//     //std::array<int, 4> directions{0,1,2,3};

//     // int directionNorth = static_cast<int>(Direction::north);        //=0
//     // int directionEast = static_cast<int>(Direction::east);          //=1
//     // int directionWest = static_cast<int>(Direction::south);
//     // int directionSouth = static_cast<int>(Direction::west);

//     //vektor einmal anlegen
//     std::vector<int> m_parts;
//     std::vector<Ship> ships;
//     //int m=0;


//     int rowR = getRandom(0,11);
//     int colR = getRandom(0,11);
//     int sizeR = 5;                          //from 5-2
//     int directionR = getRandom(0,3);
//     Direction dir = Direction::west;        //so initialisieren?


//     if(directionR == 0){
//         dir = static_cast<Direction>(directionR);
//     }
//     else if(directionR == 1){
//         dir = static_cast<Direction>(directionR);
//     }
//     else if(directionR == 2){
//         dir = static_cast<Direction>(directionR);
//     }
//     else if(directionR == 3){
//         dir = static_cast<Direction>(directionR);
//     }

//     Ship dreadnought = Ship(rowR,colR,sizeR,dir);

//     //4,3,5,north
//     std::vector<std::pair<int,int>>m_partsD;

//     auto pair0 = std::make_pair(rowR,colR);

//     m_partsD.push_back(pair0);

//     for (int i = 0; i < sizeR; ++i) {

//         int r = rowR;
//         int c = colR;

//         if (dir == Direction::north) {
//             r = rowR - i;
//         } else if (dir == Direction::south) {
//             r = rowR + i;
//         } else if (dir == Direction::east) {
//             c = colR + i;
//         } else if (dir == Direction::west) {
//             c = colR - i;
//         }
//         m_partsD.push_back({r, c});
//     }


//     ships.push_back(dreadnought);

//     int m=0;
//     while(m<2){
//     rowR = getRandom(0,11);
//     colR = getRandom(0,11);
//     sizeR = 4;                          //from 5-2
//     directionR = getRandom(0,3);


//     if(directionR == 0){
//         dir = static_cast<Direction>(directionR);
//     }
//     else if(directionR == 1){
//         dir = static_cast<Direction>(directionR);
//     }
//     else if(directionR == 2){
//         dir = static_cast<Direction>(directionR);
//     }
//     else if(directionR == 3){
//         dir = static_cast<Direction>(directionR);
//     }

//     int counterReps = 0;
//     //int newcol1 = 0;
//     std::vector<std::pair<int,int>>m_partsC;

//     auto pair1 = std::make_pair(rowR,colR);

//     m_partsC.push_back(pair1);

//     for (int i = 0; i < sizeR; ++i) {

//         int r = rowR;
//         int c = colR;

//         if (dir == Direction::north) {
//             r = rowR - i;
//         } else if (dir == Direction::south) {
//             r = rowR + i;
//         } else if (dir == Direction::east) {
//             c = colR + i;
//         } else if (dir == Direction::west) {
//             c = colR - i;
//         }
//         m_partsC.push_back({r, c});
//     }

//     for (auto e :m_partsC){
//         for (auto i:m_partsD){
//             if(i==e){
//                 counterReps++;
//             }
//         }
//     }
//     for (auto e :m_partsC){
//         for (auto i:m_partsC){
//             if(i==e){
//                 counterReps++;
//             }
//         }
//     }
//     if (counterReps > 0){
//         m--;
//     }
//     else{
//         Ship cruiser = Ship(rowR,colR,sizeR,dir);
//         ships.push_back(cruiser);
//         m++;
//     }
//  }



// }
