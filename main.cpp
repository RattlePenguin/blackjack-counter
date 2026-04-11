#include <iostream>
#include <cctype> // For toupper
#include "GameEngine.hpp"
#include "HumanPlayer.hpp"

int main() {
    std::cout << "========================================\n";
    std::cout << "  Blackjack Advantage Trainer - v0.2\n";
    std::cout << "========================================\n\n";

    // Initialize the engine with 2 decks, 75% pen
    GameEngine engine(2, 0.75, 42);

    // Create our user.
	// We dynamically allocate this so it matches the Player* expected by engine.addPlayer(). 
    Player* user = new HumanPlayer("CardCounter99");

    // Seat the player at the table
    engine.addPlayer(user);

    int roundNumber = 1;

	// Core loop
    while (true) {
        std::cout << "\n--- Round " << roundNumber << " ---\n";
        
        // Run the game state machine
        engine.playRound();

        roundNumber++;
    }

    // Wrap up
    std::cout << "\nSession ended.\n";
    std::cout << user->getName() << "'s Final P/L Bankroll: $" << user->getBankroll() << "\n";

    // Clean up our dynamically allocated memory to prevent leaks
    delete user;

    return 0;
}
