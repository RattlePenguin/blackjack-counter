#ifndef ENUMS_H
#define ENUMS_H

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

enum class Action {
	HIT,
	STAND,
	DOUBLE,
	SPLIT,
	SURRENDER,
};

#endif
