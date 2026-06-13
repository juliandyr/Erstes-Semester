#include "player.h"

Player::Player(const std::string& name)
    : m_gamesWon(0), m_gamesLost(0), m_playerName(name) {}

int Player::getGamesWon() const {
    return m_gamesWon;
}

int Player::getGamesLost() const {
    return m_gamesLost;
}

void Player::addGameWon() {
    m_gamesWon++;
}

void Player::addGameLost() {
    m_gamesLost++;
}

int Player::getGamesPlayed() const {
    return m_gamesWon + m_gamesLost;
}

std::string Player::getName() {
    return m_playerName;
}
