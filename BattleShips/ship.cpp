#include "ship.h"


Ship::Ship(){}


//Konstruktor für Parts of ship

Ship::Ship(int row, int col, int lengthOfShip, Direction direction){

    int newcol = 0;
    //aft Teil
    Part aft = Part(row, col);
    m_parts.push_back(aft);
    // if(Dirrection::north && length = 1){
    //2. Part object -> Part row = Part 1 row - (length -1)
    // -> Part col = Part 1 col - (length -1)

    if (direction == Direction::west){
        newcol = col;                               //erste Schleife überflüssig laut Chat
        for (int i = 0; i < 1; i++){
            for (int e = 1; e < lengthOfShip; e++){
                newcol--;
                Part part = Part(row,newcol);
                m_parts.push_back(part);
            }
        }

    }
    else if (direction == Direction::east){
        for (int i = 1; i < lengthOfShip; i++){
            int currentCol = col +i;
            Part part = Part(row,currentCol);
            m_parts.push_back(part);
        }

    }
    else if (direction == Direction::north){
        for (int i = 1; i < lengthOfShip; i++){
            int currentRow = row -i;
            Part part = Part(currentRow,col);
            m_parts.push_back(part);
        }

    }
    else if (direction == Direction::south){
        for (int i = 1; i < lengthOfShip; i++){
            int currentRow = row +i;
            Part part = Part(currentRow,col);
            m_parts.push_back(part);
        }

    }
}

//gibt zurück, ob sich an den jeweiligen Koordinaten ein Part des Schiffs befindet
//geht jedes Part in m_parts durch und prüft, ob sich davon eins an den Koordinaten befindet, wenn ja, dann true.

bool Ship::hasPartIn(int row, int col) const{

    //Part testpart = Part(row,col);                überflüssig laut Chat

    for (size_t i = 0; i< m_parts.size(); i++){
        if(/*testpart.getRow()*/ row == m_parts[i].getRow() && /*testpart.getCol()*/ col == m_parts[i].getCol()){
            return true;
        }
    }
    return false;

}

//ist die Koordinate wirklich ein Part des Schiffs, dann kann durch diese Funktion der jeweilige Part bearbeitet werden(durch Referenz)

Part& Ship::getPartIn(int row, int col) {
    if (hasPartIn(row,col)){                                //tipp gebraucht von chat, weil ich nicht wusste, wie ich eine referenz zurückgeben soll
        for (size_t i = 0; i < m_parts.size(); i++){
            if(/*testpart.getRow()*/ row == m_parts[i].getRow() && /*testpart.getCol()*/ col == m_parts[i].getCol()){
                return m_parts[i];                          //niemals drauf gekommen!
            }
        }
    }
    //Exception not necessary
}

//ship is sunk, when all parts are damaged (=1)
//we have the method isDamaged(), which returns true if m_status = 1.
//if we have a ship of the size 3, then all 3 parts should be damaged -> counter == number of damaged parts

bool Ship::isSunk(){
    size_t counter = 0;
    for (size_t i = 0; i < m_parts.size(); i++){
        if (m_parts[i].isDamaged()){
            counter++;
        }
    }
    if(counter == m_parts.size()){
        return true;

    }
    else{
        return false;
    }

}

//same procedure; if method isDamaged() returns true then damagedCounter++;
//if DamagedCounter greater than 0 -> one part at least is damaged.

bool Ship::isDamaged(){
    int damagedCounter = 0;
    for (size_t i = 0; i < m_parts.size(); i++){
        if (m_parts[i].isDamaged()){
            damagedCounter++;
        }
    }
    if (damagedCounter > 0){
        return true;                //laut Chat wäre hier return(DamagedCounter >0) gegangen
    }
    else{
        return false;
    }
}






