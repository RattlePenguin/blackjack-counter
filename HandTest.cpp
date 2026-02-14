#include <iostream>

#include "Card.h"
#include "Shoe.h"
#include "Hand.h"

int main() {
	Shoe shoe(2, 0.75);
	
	Hand hand {};
	hand.addCard(shoe.draw());
	std::cout << "Total: " << hand.getTotalValue() << '\n';
	std::cout << "Number of Aces: " << hand.getNumAces() << '\n';
	std::cout << "Real: " << hand.getRealValue() << '\n';

	hand.addCard(shoe.draw());
	std::cout << "Total: " << hand.getTotalValue() << '\n';
	std::cout << "Number of Aces: " << hand.getNumAces() << '\n';
	std::cout << "Real: " << hand.getRealValue() << '\n';
}
