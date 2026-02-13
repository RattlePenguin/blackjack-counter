# Idea
Advantage Blackjack allows the player to hold an advantage (usually 1-2%) over the house that results in positive EV.
You will win and you will lose. There is no such thing as no losses.
However, in theory with the right conditions and strategies, one can expect a profit over the house over a long period of time.

This project aims to teach users how to play advantaged blackjack using the hi-lo counting method and basic strategy with deviations. One can find many examples and POVs of blackjack counting on youtube.

This usually has a lot of prerequisites, as well as factors that affect the effectiveness of advantageous strategies such as:
- No Continuous Shuffle Machines (CSM). This makes it impossible to obtain an accurate representation of the deck.
- Deck penetration. Deeper deck penetration allows the player to see more of the deck throughout the game, allowing for more periods of advantage.
- Min / max bet amounts. This depends on you, but the goal is to minimise your bet when you do not have an advantage, and increase your bets as you gain advantage.

This is not an exhaustive list, nor does it account for the fact that advantage blackjack requires a lot of focus. This may result in casinos backing you off if they decide that you are counting cards.

# Blackjack Rules
Better off watching a video for now, I'll fill out this section once the project is more complete.

# Guide
## Hi-lo Counting Method
This method puts cards in three categories:
- 2-6 are considered low (+1)
- 7-9 are considered neutral (0)
- 10-A are considered high (-1)

To count cards, there are two values to keep track of. The running count (RC) and true count (TC).

RC is found by adding up the frequencies of each category of card.

For example on the first hand:
- Dealer 2 10
- Player 7 10
- 2 High (-2) 1 Neutral (0) 1 Low (+1)
- RC = -2 + 1 = -1

This continues for every subsequent hand in the shoe.

TC is found by dividing RC by the number of remaining decks in play.
For example, if RC is +7 and there are about 4 remaining decks in the shoe, then the TC is +7/4 = +1.75. One could round this up to +2 for simplicity.

## Basic Strategy
There are 5 actions you can take as a blackjack player.
- Hit
    - You tap on the table with your finger. This signals to the dealer that you want to draw another card from the shoe, adding to your hand total. You can hit multiple times.
- Stand
    - You wave over your cards (like in a "no" fashion). This signals that you wish to stick with your current hand.
- Double Down (Double)
    - You place an additional bet next to your original bet and hold up one finger. This signals that you want to draw one additional card and double your bet. You cannot double after a hit or hit after a double.
- Split
    - You can only split if both your cards have the same value (any face mix allowed). You place an additional bet next to your original bet and hold up two fingers. The dealer will separate your cards into two hands and draw an additional card for each hand. You can play each hand as if it were a new hand.
- Surrender
    - Some casinos may offer surrendering. You can only surrender as the first action. You draw a horizontal line behind your bet. This signals that you will forfeit half of your bet to the dealer.

Perfect basic strategy involves always picking the most optimal move at every stage of the game. This is usually done by referring to charts that have been vetted thousands of times. An example can be seen [here](https://www.blackjackapprenticeship.com/blackjack-strategy-charts/).

When evolving project to web app, maybe a cheatsheet page would be awesome, not sure how to display as a console app.

## BS Deviations
Not every blackjack table is the same. Some will hit on a soft 17 (H17) or stand instead (S17), or do something else. The basic strategy chart shown above is based on a commonly seen H17 game.

# Program Details
Mimicks a real game of Blackjack
- No auto shuffler
- Number of cards are actually limited (don't just produce random cards)
- Maybe ways to implement environment, like sounds or smth

Default is 2 decks, player can maybe specify how many

Keep track of the player's moves and also the highest EV moves (perfect moves basically)

Essentially, this is a full blackjack simulator as pt 1. Pt 2 is the card counting aspect.

# Implementation Notes

# Glossary
- Shoe:
