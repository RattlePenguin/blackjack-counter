#ifndef ENUMS_H
#define ENUMS_H

enum class Action {
	HIT,
	STAND,
	DOUBLE,
	SPLIT,
	SURRENDER,
};

struct BlackjackRules {
	int numDecks { 2 };
	double penetration { 0.75 };
	bool hitSoft17 { true };
	bool doubleAfterSplit { true };
	bool resplitAces { false };
	bool surrenderAllowed { true };
};

#endif
