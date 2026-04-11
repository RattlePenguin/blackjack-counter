#ifndef HAND_H
#define HAND_H

#include <vector>

#include "Card.hpp"

class Hand {
public:
	Hand(double initialBet);

	/**
	 *  Adds a given card to the Hand.
	 */
	void addCard(Card c);
	
	/**
	 *  Getter for cards
	 */
	std::vector<Card>& getCards();

	/**
	 *  Returns the total value of the Hand, with all Aces at 11.
	 */
	int getTotalValue() const;

	/**
	 *  Returns the number of Aces in the Hand.
	 */
	int getNumAces() const;

	/**
	 *  Returns the play value of the Hand.
	 *  I.e. highest possible value under 21. Aces are counted as 11 until they need to be 1.
	 */
	int getRealValue() const;
	double getBet() const;

	/**
	 *  Returns whether the Hand is soft, i.e. an Ace is presently acting as an 11.
	 */
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

	/**
	 *  Doubles the bet.
	 */
	void doubleDown();

	/**
	 *  Sets the isSplit field to true.
	 *  Does NOT modify the Hand.
	 */
	void split();

	/**
	 *  Sets bet to zero.
	 */
	void zeroBet();

	/**
	 *  Returns the Card at the back of the Hand, and removes it from the Hand.
	 */
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
