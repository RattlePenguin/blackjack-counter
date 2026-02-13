#ifndef CARD_H
#define CARD_H

#include <string>

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
	Rank rank;
	Suit suit;
	bool faceDown;

	int getValue() const;
	int getHiLoValue() const;
	std::string toString() const;
};

#endif
