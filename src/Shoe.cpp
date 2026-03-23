#include <random>
#include <algorithm>
#include <iostream>

#include "Shoe.hpp"

Shoe::Shoe(int totalDecks, double penetration, unsigned int seed = 0)
	: seed { seed }
	, totalDecks { totalDecks }
	, cardsDealtIndex { 0 }
	, systemRunningCount { 0 }
{
	cutCardIndex = static_cast<int>(totalDecks * NUM_CARDS_IN_DECK * penetration);
	initialise();
}

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

void Shoe::shuffle() {
	std::mt19937 g(seed == 0 ? std::random_device{}() : seed);
	std::shuffle(cards.begin(), cards.end(), g);

	cardsDealtIndex = 0;
	systemRunningCount = 0; // Reset shoe, reset count
	std::cout << "Shoe has shuffled " << totalDecks << " decks.\n";
}

/**
 *  Draws a card from the shoe and updates the system running count.
 *  If shoe is empty (dealing index past size), initialises again (but this shouldn't happen).
 */
Card Shoe::draw() {
	if (cardsDealtIndex >= static_cast<int>(cards.size())) initialise();
	Card c = cards[static_cast<std::vector<Card>::size_type>(cardsDealtIndex++)];
	systemRunningCount += c.getHiLoValue();
	return c;
}

/**
 *  Returns true if the cut card has been encountered.
 */
bool Shoe::needsShuffle() const {
	return cardsDealtIndex >= cutCardIndex;
}

/**
 *  Returns the number of cards remaining in the shoe.
 */
int Shoe::getCardsRemaining() const {
	return static_cast<int>(cards.size()) - cardsDealtIndex;
}

/**
 *  Evaluates and returns the number of decks remaining in play.
 */
double Shoe::getDecksRemaining() const {
	return static_cast<double>(getCardsRemaining()) / NUM_CARDS_IN_DECK;
}

/**
 *  Getter for systemRunningCount.
 */
int Shoe::getSystemRunningCount() const {
	return systemRunningCount;
}
