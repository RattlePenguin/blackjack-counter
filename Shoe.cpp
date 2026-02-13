#include <random>
#include <algorithm>
#include "Shoe.h"

const int NUM_SUITS { 4 };
const int NUM_RANKS { 13 };

/**
 *  Constructor that sets number of decks and penetration limit.
 */
Shoe::Shoe(int totalDecks, double penetration)
	: totalDecks { totalDecks }
{
	initialise();
}

/**
 *  Resets the cards in the shoe based on numDecks and shuffles them.
 */
void Shoe::initialise() {
	cards.clear();
	for (int d = 0; d < totalDecks; ++d) {
		for (int s = 0; s < NUM_SUITS; ++s) {
			for (int r = 0; r < NUM_RANKS; ++r) {
				cards.push_back({ static_cast<Rank>(r), static_cast<Suit>(s), false });
			}
		}
	}
	shuffle();
}

/**
 *  Shuffles the shoe.
 */
void Shoe::shuffle() {
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(cards.begin(), cards.end(), g);
}

/**
 *  Draws a card from the shoe.
 *  If shoe is empty, initialises again (but this shouldn't happen).
 */
Card Shoe::draw() {
	if (cards.empty()) initialise();
	Card c = cards.back();
	cards.pop_back();
	return c;
}
