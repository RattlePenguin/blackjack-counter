#include <random>
#include <algorithm>
#include <iostream>

#include "Shoe.hpp"

Shoe::Shoe(int totalDecks, double penetration, unsigned int seed = 0)
	: totalDecks { totalDecks }
	, penetration { penetration }
	, cardsDealtIndex { 0 }
	, cutCardIndex { static_cast<int>(totalDecks * NUM_CARDS_IN_DECK * penetration) }
	, seed { seed }
	, systemRunningCount { 0 }
{
	initialise();
}

void Shoe::initialise() {
	cards.clear();
	for (int d = 0; d < totalDecks; ++d) {
		for (int s = 0; s < NUM_SUITS; ++s) {
			for (int r = 1; r <= NUM_RANKS; ++r) {
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
	systemRunningCount = 0; // Reset shoe, so reset count
	std::cout << "Shoe has shuffled " << totalDecks << " decks.\n";
}

Card Shoe::draw() {
	if (cardsDealtIndex >= static_cast<int>(cards.size())) initialise();
	Card c = cards[static_cast<std::vector<Card>::size_type>(cardsDealtIndex++)];
	systemRunningCount += c.getHiLoValue();
	return c;
}

bool Shoe::needsShuffle() const {
	return cardsDealtIndex >= cutCardIndex;
}

int Shoe::getCardsRemaining() const {
	return static_cast<int>(cards.size()) - cardsDealtIndex;
}

double Shoe::getDecksRemaining() const {
	return static_cast<double>(getCardsRemaining()) / NUM_CARDS_IN_DECK;
}

int Shoe::getSystemRunningCount() const {
	return systemRunningCount;
}
