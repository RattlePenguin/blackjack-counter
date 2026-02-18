#include "GameEngine.h"

GameEngine::GameEngine(int numDecks, int penetration)
	: shoe(numDecks, penetration)
	, dealerHand { nullptr }
{
}
