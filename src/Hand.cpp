#include "Hand.hpp"
#include "Card.hpp"
#include <iostream>

const int BLACKJACK_VALUE { 21 };
const int ACE_DIFF_VALUE { 10 };

Hand::Hand(double initialBet) : bet { initialBet } {}

void Hand::addCard(Card c) {
	cards.push_back(c);
}

std::vector<Card>& Hand::getCards() { return cards; }

int Hand::getTotalValue() const {
	int total { 0 };
	for (const Card& c : cards) {
		total += c.getValue();
	}
	return total;
}

int Hand::getNumAces() const {
	int numAces { 0 };
	for (const Card& c : cards) {
		if (c.rank == Rank::ACE) ++numAces;
	}
	return numAces;
}

int Hand::getRealValue() const {
	int total { getTotalValue() };
	int numAces { getNumAces() };

	while (total > BLACKJACK_VALUE && numAces > 0) {
		--numAces;
		total -= ACE_DIFF_VALUE;
	}
	return total;
}

double Hand::getBet() const { return bet; }

bool Hand::isSoft() const {
	int total { getTotalValue() };
	int numAces { getNumAces() };

	while (total > BLACKJACK_VALUE && numAces > 0) {
		--numAces;
		total -= ACE_DIFF_VALUE;
	}
	return numAces > 0;
}

bool Hand::isTwoCards() const { return cards.size() == 2; }

bool Hand::isPair() const { return isTwoCards() && cards[0].getValue() == cards[1].getValue(); }

bool Hand::isBlackjack() const { return isTwoCards() && !isSplit && getTotalValue() == BLACKJACK_VALUE; }

bool Hand::isBusted() const { return getRealValue() > 21; }

bool Hand::is21() const { return getRealValue() == 21; }

bool Hand::isSurrendered() const { return surrendered; }

bool Hand::isDoubled() const { return doubled; }

bool Hand::isSplitHand() const { return isSplit; }

bool Hand::isFinished() const { return finished; }

void Hand::printHand() const {
	std::cout << cards.front().toString();
	for (int i = 1; i < static_cast<int>(cards.size()); ++i) {
		std::cout << ' ' << cards[i].toString();
	}
	std::cout << '\n';
}

void Hand::surrender() {
	surrendered = true;
	bet *= 0.5;
}

void Hand::doubleDown() {
	doubled = true;
	bet *= 2;
}

void Hand::split() { isSplit = true; }

void Hand::zeroBet() { bet = 0.0; }

Card Hand::pop_back() {
	Card card { cards.back() };
	cards.pop_back();
	return card;
}

void Hand::finish() { finished = true; }

