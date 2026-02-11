#include <iostream>

#include "Card.h"
#include "Enums.h"

int main() {
	Card card {};
	card.rank = Rank::ACE;
	card.suit = Suit::SPADES;
	
	std::cout << card.getValue() << '\n';
	std::cout << card.getCountValue() << '\n';
	std::cout << card.toString() << '\n';

}
