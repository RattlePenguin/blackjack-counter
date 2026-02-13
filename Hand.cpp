#include "Hand.h"
#include "Card.h"

const int BLACKJACK_VALUE { 21 };
const int ACE_DIFF_VALUE { 10 };

/**
 *  Adds a given card to the Hand.
 */
void Hand::addCard(Card c) {
	cards.push_back(c);
}

/**
 *  Returns the total value of all cards in the Hand.
 *  For Aces, default value is 11 unless the Hand is over 21.
 *		Aces are individually reduced to value 1 until the Hand is under 21.
 */
int Hand::getTotalValue() const {
	int total { 0 };
	int numAces { 0 };
	for (const Card& c : cards) {
		total += c.getValue();
		if (c.rank == Rank::ACE) ++numAces;
	}
	
	while (total > BLACKJACK_VALUE && numAces > 0) {
		--numAces;
		total -= ACE_DIFF_VALUE;
	}

	return total;

}

double Hand::getBet() const { return bet; }

bool Hand::isSoft() const;
bool Hand::isPair() const;
bool Hand::isBlackjack() const { return getTotalValue() == BLACKJACK_VALUE; }
bool Hand::isBusted() const;
bool Hand::isSurrendered() const;

// Setters
void Hand::surrender();
void Hand::doubleDown();
Card Hand::split();

