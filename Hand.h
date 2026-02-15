#ifndef HAND_H
#define HAND_H

#include <vector>

#include "Card.h"

class Hand {
public:
	Hand(double initialBet);
	void addCard(Card c);
	
	int getTotalValue() const;
	int getNumAces() const;
	int getRealValue() const;
	bool isSoft() const;
	double getBet() const;
	bool isPair() const;
	bool isBlackjack() const;
	bool isBusted() const;
	bool isSurrendered() const;

	void surrender();
	void doubleDown();
	Card split();

private:
	std::vector<Card> cards {};
	double bet {};
	bool surrendered {};
	bool isDoubled {};
};

#endif // !HAND_H
