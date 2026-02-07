#include <random>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>

/**
 *  Program needs to initialize the deck of cards (shuffled) then play the game.
 *  The program loop should be something like:
 *  Dealer hand:   X 10
 *  Your hand:     2 7
 *  Player 2 hand: 5 2
 *  ...
 *  
 *  h - hit
 *  s - stand
 *  d - double down
 *  t - split
 *  y - surrender
 *  q - quit game
 *  ? - show actions
 */

void playBlackjack();
std::vector<int> ShoeCreateUnshuffled(int numDecks);
void ShoeShuffle(std::vector<int>& shoe);
void printHands(std::vector<int> dealerHand, std::vector<int> playerHand, bool dealerDownCard);

int main() {

	std::cout << "Enter 1 to play Blackjack. ";

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
	std::vector<int> shoe = ShoeCreateUnshuffled(2);
	ShoeShuffle(shoe);

	// Burn a card
	shoe.pop_back();

	std::cout << "How much do you want to bet? ";
	int bet {};
	std::cin >> bet;

	std::vector<int> dealerHand {}; // First is the down card, second is the up card.
	std::vector<int> playerHand {};
	
	// Deal cards
	playerHand.emplace_back(shoe.back());
	shoe.pop_back();
	dealerHand.emplace_back(shoe.back());
	shoe.pop_back();
	playerHand.emplace_back(shoe.back());
	shoe.pop_back();
	dealerHand.emplace_back(shoe.back());
	shoe.pop_back();

	// Show pre-action hands
	printHands(dealerHand, playerHand, true);

	// Actions
	char action {};
	std::cin >> action;
	switch (action) {
		case 'h':
			playerHand.emplace_back(shoe.back());
			shoe.pop_back();
			break;
		case 's':
			break;
		case 'd':
			break;
		case 't':
			break;
		case 'y':
			break;
		case 'q':
			break;
		case '?':
		default:
			std::cout << "h - hit\ns - stand\nd - double down\nt - split\ny - surrender\nq - quit game\n? - show actions\n";
	}
}

/**
 *  Create a shoe with a given number of decks, unshuffled deck by deck.
 */
std::vector<int> ShoeCreateUnshuffled(int numDecks) {
	std::vector<int> shoe {};
	for (int i = 0; i < numDecks; ++i) {
		for (int j = 0; j < 13; ++j) {
			for (int k = 0; k < 4; ++k) {
				// Add 4 of each card type to deck
				shoe.emplace_back(j);
			}
		}
	}
	return shoe;
}

/**
 *  Shuffles a shoe given its address.
 *  Random each time, TODO give a seed to shuffle deterministically.
 */
void ShoeShuffle(std::vector<int>& shoe) {
	std::random_device rd;
	std::mt19937 g(rd());

	std::shuffle(shoe.begin(), shoe.end(), g);
}

/**
 *  Prints the given hands in card acquisition order.
 *  If dealerDownCard is true, the first card in the dealer's hand will not be shown.
 */
void printHands(std::vector<int> dealerHand, std::vector<int> playerHand, bool dealerDownCard) {
	std::cout << "Dealer's Hand: ";
	if (dealerDownCard) {
		std::cout << 'X';
	} else {
		std::cout << dealerHand[0];
	}
	std::cout << ' ' << dealerHand[1] << '\n';

	std::cout << "Player's Hand:";
	for (const int card : playerHand) {
		std::cout << ' ' << card;
	}
	std::cout << '\n';
}
