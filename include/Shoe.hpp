#ifndef SHOE_H
#define SHOE_H

#include <vector>

#include "Card.hpp"

class Shoe {
public:
	Shoe(int totalDecks, double penetration);
	void initialise();
	void shuffle();
	Card draw();
	bool needsShuffle() const;
	int getCardsRemaining() const;
	double getDecksRemaining() const;
	int getSystemRunningCount() const;

private:
	std::vector<Card> cards {};
	int totalDecks {};
	int cardsDealtIndex {};
	int cutCardIndex {};
	int systemRunningCount {};
};

#endif // !SHOE_H
