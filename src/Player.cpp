#include "Player.hpp"
#include "Hand.hpp"
#include <string>

Player::Player(std::string name) : name { name } {}
Player::~Player() {}

void Player::clearHands() { hands.clear(); }

Hand& Player::startNewHand(double bet) {
	hands.push_back(Hand(bet));
	return hands.back();
}

std::string Player::getName() const { return name; }
double Player::getBankroll() const { return bankroll; }

void Player::win(double bet) { bankroll += bet; }
void Player::lose(double bet) { bankroll -= bet; }
