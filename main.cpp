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

    std::cout << "Show strategy hints during play? (y/n): ";
    std::string hintChoice;
    if (std::getline(std::cin >> std::ws, hintChoice)) {
        if (hintChoice == "y" || hintChoice == "Y") {
            static_cast<HumanPlayer*>(user)->setHints(true);
        }
    }

    bool showSummary = true;
    std::cout << "Show strategy summary at end of session? (y/n): ";
    std::string summaryChoice;
    if (std::getline(std::cin >> std::ws, summaryChoice)) {
        if (summaryChoice == "n" || summaryChoice == "N") {
            showSummary = false;
        }
    }

    int roundNumber = 1;

	// Core loop
    while (true) {
        std::cout << "\n--- Round " << roundNumber << " ---\n";
        
        // Run the game state machine
        engine.playRound();

        roundNumber++;

        std::cout << "\nPlay another round? (y/n): ";
        std::string choice;
        if (!std::getline(std::cin >> std::ws, choice) || choice == "n" || choice == "N") {
            break;
        }
    }

    // Wrap up
    std::cout << "\nSession ended.\n";
    if (showSummary) {
        static_cast<HumanPlayer*>(user)->printStrategySummary();
    }
    std::cout << "\n" << user->getName() << "'s Final P/L Bankroll: $" << user->getBankroll() << "\n";

    // Clean up our dynamically allocated memory to prevent leaks
    delete user;

    return 0;
}
