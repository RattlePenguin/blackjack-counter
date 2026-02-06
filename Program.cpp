#include <cstdlib>
#include <iostream>

/**
 *  Program needs to initialize the deck of cards (shuffled) then play the game.
 *  The program loop should be something like:
 *  Dealer hand:   X 10
 *  Your hand:     2 7
 *  Player 2 hand: 5 2
 *  ...
 *  
 *  h - Hit
 *  s - Stand
 *  d - Double down
 *  t - split
 *  y - surrender
 *
 */

void playBlackjack();

int main() {
	int input {};
	std::cin >> input;

	switch (input) {
		case 1:
			playBlackjack();
			break;
		case 2:
		default:
			std::cout << "You didn't input anything bruh" << '\n';
			exit(EXIT_SUCCESS);
	}
}

void playBlackjack() {
	std::cout << "How much do you want to bet? ";
	int bet {};
	std::cin >> bet;


}
