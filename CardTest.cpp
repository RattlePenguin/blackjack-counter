#include "Card.h"
#include <cassert>
#include <cstdlib>
#include <iostream>

Rank ranks[NUM_RANKS] {
	Rank::ACE,
	Rank::TWO,
	Rank::THREE,
	Rank::FOUR,
	Rank::FIVE,
	Rank::SIX,
	Rank::SEVEN,
	Rank::EIGHT,
	Rank::NINE,
	Rank::TEN,
	Rank::JACK,
	Rank::QUEEN,
	Rank::KING
};

Suit suits[NUM_SUITS] {
	Suit::SPADES,
	Suit::HEARTS,
	Suit::DIAMONDS,
	Suit::CLUBS
};

void testGetValue() {
	for (int r = 0; r < NUM_RANKS; ++r) {
		for (int s = 0; s < NUM_SUITS; ++s) {
			Card c { .rank = ranks[r], .suit = suits[s], .faceDown = false };
			if (ranks[r] == Rank::ACE) {
				assert(c.getValue() == 11);
			} else if (ranks[r] == Rank::JACK || ranks[r] == Rank::QUEEN || ranks[r] == Rank::KING) {
				assert(c.getValue() == 10);
			} else {
				assert(c.getValue() == static_cast<int>(c.rank));
			}
		}
	}
}

void testGetHiLoValue() {
	for (int r = 0; r < NUM_RANKS; ++r) {
		for (int s = 0; s < NUM_SUITS; ++s) {
			Card c { .rank = ranks[r], .suit = suits[s], .faceDown = false };
			if (
				ranks[r] == Rank::TWO ||
				ranks[r] == Rank::THREE ||
				ranks[r] == Rank::FOUR ||
				ranks[r] == Rank::FIVE ||
				ranks[r] == Rank::SIX
			) {
				assert(c.getHiLoValue() == 1);
			} else if (
				ranks[r] == Rank::SEVEN ||
				ranks[r] == Rank::EIGHT ||
				ranks[r] == Rank::NINE
			) {
				assert(c.getHiLoValue() == 0);
			} else {
				assert(c.getHiLoValue() == -1);
			}
		}
	}

}

int main() {
	testGetValue();
	testGetHiLoValue();
	std::cout << "yo\n";
	return EXIT_SUCCESS;
}
