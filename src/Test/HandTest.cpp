#include <iostream>

#include "Card.hpp"
#include "Shoe.hpp"
#include "Hand.hpp"

int main() {
	Shoe shoe(2, 0.75);

	Hand hand(100);
	hand.addCard(shoe.draw());
	std::cout << "Total: " << hand.getTotalValue() << '\n';
	std::cout << "Number of Aces: " << hand.getNumAces() << '\n';
	std::cout << "Real: " << hand.getRealValue() << '\n';

	hand.addCard(shoe.draw());
	std::cout << "Total: " << hand.getTotalValue() << '\n';
	std::cout << "Number of Aces: " << hand.getNumAces() << '\n';
	std::cout << "Real: " << hand.getRealValue() << '\n';
}
