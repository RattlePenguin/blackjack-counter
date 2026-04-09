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

	/**
	 *  Draws a card from the shoe and updates the system running count.
	 *  If shoe is empty (dealing index past size), initialises again (but this shouldn't happen).
	 */
	Card draw();

	/**
	 *  Returns true if the cut card has been encountered.
	 */
	bool needsShuffle() const;

	/**
	 *  Returns the number of cards remaining in the shoe.
	 */
	int getCardsRemaining() const;

	/**
	 *  Evaluates and returns the number of decks remaining in play.
	 */
	double getDecksRemaining() const;

	/**
	 *  Getter for systemRunningCount.
	 */
	int getSystemRunningCount() const;

private:
	std::vector<Card> cards {};
	int totalDecks { 4 };
	double penetration { 0.75 };
	int cardsDealtIndex {};
	int cutCardIndex { 156 };
	unsigned int seed {};

	int systemRunningCount {};
};

#endif // !SHOE_H
