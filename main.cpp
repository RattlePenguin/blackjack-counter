#include <iostream>

#include "Card.h"
#include "Shoe.h"
#include "Enums.h"

int main() {
	Shoe shoe(2, 0.75);
	
	Card card = shoe.draw();
	std::cout << card.getValue() << '\n';
	card = shoe.draw();
	std::cout << card.getValue() << '\n';
	card = shoe.draw();
	std::cout << card.getValue() << '\n';

}
