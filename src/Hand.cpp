#include "Hand.hpp"
#include "Card.hpp"
#include <iostream>

const int BLACKJACK_VALUE { 21 };
const int ACE_DIFF_VALUE { 10 };

// Constructor
Hand::Hand(double initialBet) : bet { initialBet } {}

/**
 *  Adds a given card to the Hand.
 */
void Hand::addCard(Card c) {
	cards.push_back(c);
}

/**
 *  Accessor for cards
 */
std::vector<Card>& Hand::getCards() { return cards; }

/**
 *  Returns the total value of the Hand, with all Aces at 11.
 */
int Hand::getTotalValue() const {
	int total { 0 };
	for (const Card& c : cards) {
		total += c.getValue();
	}
	return total;
}

/**
 *  Returns the number of Aces in the Hand.
 */
int Hand::getNumAces() const {
	int numAces { 0 };
	for (const Card& c : cards) {
		if (c.rank == Rank::ACE) ++numAces;
	}
	return numAces;
}


/**
 *  Returns the play value of the Hand.
 *  I.e. highest possible value under 21. Aces are counted as 11 until they need to be 1.
 */
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

/**
 *  Returns whether the Hand is soft, i.e. an Ace is presently acting as an 11.
 */
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

bool Hand::isPair() const { return isTwoCards() && cards[0].rank == cards[1].rank; }

bool Hand::isBlackjack() const { return isTwoCards() && getTotalValue() == BLACKJACK_VALUE; }

bool Hand::isBusted() const { return getRealValue() > 21; }

bool Hand::is21() const { return getRealValue() == 21; }

bool Hand::isSurrendered() const { return surrendered; }

void Hand::printHand() const {
	for (const Card& c : cards) {
		std::cout << c.toString() << ' ';
	}
	std::cout << '\n';
}

void Hand::surrender() { surrendered = true; }

void Hand::doubleDown() { isDoubled = true; }

Card Hand::split() {
	// TODO
}

