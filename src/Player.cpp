#include "Player.hpp"
#include "Hand.hpp"
#include <string>

// Constructor
Player::Player(std::string name) : name { name } {}

void Player::clearHands() { hands.clear(); }

void Player::startNewHand(double bet) {
	hands.push_back(Hand(bet));
}

std::string Player::getName() const { return name; }
double Player::getBankroll() const { return bankroll; }

