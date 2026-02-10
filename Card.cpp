#include <string>
#include "Enums.h"
#include "Card.h"

/**
 *  Returns the value of the card as per Blackjack rules.
 */
int Card::getValue() const {
	if (rank > Rank::TEN) return 10;
	if (rank == Rank::ACE) return 11;
	return static_cast<int>(rank);
}

/**
 *  Returns the value contributing to the running count as per the Hi-Lo counting method.
 */
int Card::getCountValue() const {
	if (rank >= Rank::TWO && rank <= Rank::SIX) return 1;
	if (rank >= Rank::TEN || rank == Rank::ACE) return -1;
	return 0;
}

std::string Card::toString() const {
	if (faceDown) return "[XX]";
	std::string rankChar[] { "", "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
	return rankChar[static_cast<int>(rank)];
}
