#ifndef SHOE_H
#define SHOE_H

#include <vector>

#include "Card.hpp"

class Shoe {
public:
	/**
	 *  Constructor that sets number of decks and penetration limit.
	 *  Seed can be given to produce fixed output, 0 is random.
	 */
	Shoe(int totalDecks, double penetration, unsigned int seed);

	/**
	 *  Resets the cards in the shoe based on numDecks and shuffles them randomly or based on the seed field.
	 */
	void initialise();


	/**
	 *  Shuffles the shoe.
	 */
	void shuffle();


	Card draw();
	bool needsShuffle() const;
	int getCardsRemaining() const;
	double getDecksRemaining() const;
	int getSystemRunningCount() const;

private:
	unsigned int seed {};
	std::vector<Card> cards {};
	int totalDecks {};
	int cardsDealtIndex {};
	int cutCardIndex {};
	int systemRunningCount {};
};

#endif // !SHOE_H
