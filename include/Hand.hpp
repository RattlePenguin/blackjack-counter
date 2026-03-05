#ifndef HAND_H
#define HAND_H

#include <vector>

#include "Card.hpp"

class Hand {
public:
	Hand(double initialBet);
	void addCard(Card c);
	
	std::vector<Card>& getCards();
	int getTotalValue() const;
	int getNumAces() const;
	int getRealValue() const;
	double getBet() const;

	bool isSoft() const;
	bool isTwoCards() const;
	bool isPair() const; // Returns true if two cards and both same value
	bool isBlackjack() const; // Must be two cards
	bool isBusted() const; // RealValue > 21
	bool is21() const;
	bool isSurrendered() const;
	void printHand() const;

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
