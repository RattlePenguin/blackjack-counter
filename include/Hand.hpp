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
	bool isBlackjack() const; // Must be two cards, cannot be a split hand
	bool isBusted() const; // RealValue > 21
	bool is21() const;
	bool isSurrendered() const;
	bool isDoubled() const;
	bool isSplitHand() const;
	bool isFinished() const;
	void printHand() const;

	void surrender();
	void doubleDown();
	void split();
	Card pop_back();
	void finish();

private:
	std::vector<Card> cards {};
	double bet {};
	bool surrendered {};
	bool doubled {};
	bool isSplit {};
	bool finished {};
};

#endif // !HAND_H
