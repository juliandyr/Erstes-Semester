#include "battleship2.h"
#include <random.h>
#include <iostream>


//Constructor for Playernames ->

Battleship::Battleship(const std::string& name1, const std::string& name2)
    : m_players {Player(name1), Player(name2)}{

}

//m_boards array has two boards; will be replaced by new ones;
//inside GameBoard Constructor is the enemyBoard and also the method of one own ships (randomShip method)

void Battleship::play(){

    m_boards[0] = GameBoard();      //player 1 board; 10 ships ->
    m_boards[1] = GameBoard();    //player 2 board;

    //bool activePlayer = true;
    int row = 0;
    int col = 0;
    bool firstPlayersTurn = false;
    int playerChoice = getRandom(1,2);
    if(playerChoice == 1){
        firstPlayersTurn = true;
    }
    else{
        firstPlayersTurn = false;
    }
    do{
    if(firstPlayersTurn){
        std::cout <<  m_players.at(0).getName() << " ist an der Reihe!" << std::endl;
        m_boards[0].printBoard();
        m_boards[0].printEnemyBoard();
        row = -1;                       //clears value from before
        col = -1;
        while(row < 0 || row > 9 || col >9 || col < 0){
            std::cout << "Welches Feld möchtest du beschießen?" << std::endl;
            std::cin >> row >> col;
        }
        if (m_boards[1].hit(row,col)){
            std::cout << "Hurra, du hast getroffen!" << std::endl;
            m_boards[0].mark(row,col,true);
        }
        else{
            std::cout << "Leider daneben!" << std::endl;
            m_boards[0].mark(row,col,false);
        }
        firstPlayersTurn = !firstPlayersTurn;
    }
    else{
        std::cout <<  m_players.at(1).getName() << " ist an der Reihe!" << std::endl;
        m_boards[1].printBoard();
        m_boards[1].printEnemyBoard();
        row = -1;                       //clears value from before
        col = -1;
        while(row < 0 || row > 9 || col > 9 || col < 0){
            std::cout << "Welches Feld möchtest du beschießen?" << std::endl;
            std::cin >> row >> col;
        }
        if (m_boards[0].hit(row,col)){
            std::cout << "Hurra, du hast getroffen!" << std::endl;
            m_boards[1].mark(row,col,true);
        }
        else{
            std::cout << "Leider daneben!" << std::endl;
            m_boards[1].mark(row,col,false);
        }
        firstPlayersTurn = !firstPlayersTurn;
    }
    }while(m_boards[0].allShipsSunk() == false && m_boards[1].allShipsSunk() == false);

    if(m_boards[0].allShipsSunk()){
        m_players[0].addGameLost();
        m_players[1].addGameWon();
        std::cout << "Hurra " <<  m_players.at(1).getName() << " hat gewonnen!" << std::endl;
    }
    else{
        m_players[0].addGameWon();
        m_players[1].addGameLost();
        std::cout << "Hurra " << m_players.at(0).getName() <<  " hat gewonnen!" << std::endl;
    }
    std::cout << "\nSTATISTIK:\n";
    std::cout << m_players[0].getName() << ": "
              << m_players[0].getGamesWon() << " Siege, "
              << m_players[0].getGamesLost() << " Niederlagen\n";

    std::cout << m_players[1].getName() << ": "
              << m_players[1].getGamesWon() << " Siege, "
              << m_players[1].getGamesLost() << " Niederlagen\n";


}
