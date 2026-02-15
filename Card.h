#ifndef CARD_H
#define CARD_H

#include <string>

const int NUM_RANKS { 13 };
const int NUM_SUITS { 4 };
const int NUM_CARDS_IN_DECK { 52 };

enum class Suit {
	SPADES,
	HEARTS,
	DIAMONDS,
	CLUBS,
};

enum class Rank {
	ACE = 1,
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	TEN,
	JACK,
	QUEEN,
	KING,
};

struct Card {
	Rank rank { Rank::ACE };
	Suit suit { Suit::SPADES };
	bool faceDown { false };

	int getValue() const;
	int getHiLoValue() const;
	std::string toString() const;
};

#endif
