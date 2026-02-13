#include <vector>

#include "Card.h"

class Hand {
public:
	void addCard(Card c);

	int getTotalValue() const;
	double getBet() const;
	bool isSoft() const;
	bool isPair() const;
	bool isBlackjack() const;
	bool isBusted() const;
	bool isSurrendered() const;

	// Setters
	void surrender();
	void doubleDown();
	Card split();

private:
	std::vector<Card> cards {};
	double bet {};
	bool surrendered {};
	bool isDoubled {};
};
