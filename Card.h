#ifndef CARD_H
#define CARD_H

#include <string>

#include "Enums.h"

struct Card {
	Rank rank;
	Suit suit;
	bool faceDown;

	int getValue() const;
	int getCountValue() const;
	std::string toString() const;
};

#endif
