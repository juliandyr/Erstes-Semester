#include "part.h"

Part::Part(int row, int col) : m_row(row), m_col(col), m_status(0){}

int Part::getRow() const{
    return m_row;
}

int Part::getCol() const{
    return m_col;
}

bool Part::isDamaged() const{
    if(m_status ==1){
        return true;
    }
    else{
        return false;
    }
}

void Part::setDamaged(){
    m_status = 1;
}
