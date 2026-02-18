#include <cstdlib>

#include "HumanPlayer.h"
#include "BlackjackRules.h"
#include "Card.h"

void testMakeDecision() {
	HumanPlayer player { HumanPlayer("Allan") };
	Hand hand { Hand(100) };
	hand.addCard({});
	hand.addCard({});
	Card dealerUpCard {};
	BlackjackRules rules {};
	player.makeDecision(hand, dealerUpCard, rules);

	Hand hand2 { Hand(100) };
	hand2.addCard( { .rank = Rank::TWO });
	hand2.addCard({});
	player.makeDecision(hand2, dealerUpCard, rules);
}

int main() {
	testMakeDecision();
	return EXIT_SUCCESS;
}
