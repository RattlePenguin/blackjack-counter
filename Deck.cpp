#include <iostream>
#include <vector>
#include <algorithm>

class Deck {
private:
	std::vector<int> cards {};

public:
	Deck() {
		for (int i = 0; i < 52; ++i) {
			cards.emplace_back(i);
		}
		std::shuffle(cards.begin(), cards.end(), 1);
	}
};
