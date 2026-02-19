# Installation
```
git clone
cd blackjack-counter
```

To run the program:
```

```

# Premise
Advantage Blackjack allows the player to hold an advantage (usually 1-2%) over the house that results in positive EV.
In theory with the right conditions and strategies, one can expect a profit over the house over a long period of time.
However, you will win and you will lose. There is no such thing as no losses.

This project aims to teach users how to play advantaged blackjack using the hi-lo counting method and basic strategy with deviations.
One can find many examples and POVs of blackjack counting on youtube.

# Game Conditions
Card counting usually has a lot of prerequisites, and factors that affect profitability such as:
- No Continuous Shuffle Machines (CSM). This makes it impossible to obtain an accurate representation of the deck for counting.
- Deck penetration. Deeper deck penetration allows the player to see more of the deck throughout the game, which may allow for longer periods of advantage.
- Min / max bet amounts. This depends on you, but the goal is to minimise your bet when you do not have an advantage, and increase your bets as you gain advantage.

This is not an exhaustive list, nor does it account for the fact that advantage blackjack requires a lot of focus.
This may result in casinos backing you off if they decide that you are counting cards.

# Blackjack Rules
[Blackjack](https://en.wikipedia.org/wiki/Blackjack)

# Strategies
## Hi-lo Counting Method
Cards are placed in three categories:
- 2-6 are considered low (+1)
- 7-9 are considered neutral (0)
- 10-A are considered high (-1)

To count cards, there are two values to keep track of. The running count (RC) and true count (TC).

RC is found by adding up the frequencies of each category of card.

If the first 10 cards to be dealt are:
- `K, 10, 3, 6, 2, 7, 7, A, J, A`

Then the RC =
```-1 - 1 + 1 + 1 + 1 + 0 + 0 - 1 - 1 - 1
   = -2
```

TC is found by dividing RC by the number of remaining decks in play.
For example, if RC is +7 and there are about 4 remaining decks in the shoe, then the TC is +7/4 = +1.75.
One could round this up to +2 for simplicity.

The higher the TC, the higher the chances of encountering "high" cards. This could increase your odds of a blackjack or a good hand.

## Basic Strategy
Basic strategy involves picking the optimal move at every stage of the game.
This is usually done by referring to charts that have been vetted thousands of times.
An example can be seen [here](https://www.blackjackapprenticeship.com/blackjack-strategy-charts/).

Playing perfect basic strategy reduces the house edge to 0.5\%.

Not every blackjack table is the same.
Some dealers may hit on a soft 17 (H17) or otherwise, and may or may not allow surrendering.
Make sure to use the correct basic strategy chart for your ruleset.

## Basic Strategy Deviations
With card counting, some moves change in basic strategy.
For example, you may want to stand in situations you normally hit if the count is too high.
These (deviations) simply make more money than just basic strategy.

An example chart can be found [here](https://www.blackjackapprenticeship.com/wp-content/uploads/2019/07/BJA_H17.pdf)

# Glossary
- Shoe:
