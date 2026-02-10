#ifndef CARD_H
#define CARD_H

#include <string>

#include "Enums.h"

class Card {
	Rank rank;
	Suit suit;
	bool faceDown;

	int getValue() const;
	int getCountValue() const;
	std::string toString() const;
};

#endif
