# Idea
Advantaged Blackjack is playing Blackjack while holding an advantage (usually 1-2%) over the dealer that allows for positive EV.

This usually has a lot of prerequisites, such as high deck penetration (less decks in play), specific min/max bet amounts, and no auto shuffler.

This project aims to teach users how to play advantaged blackjack using the hi-lo counting method and perfect basic strategy. One can find many examples of blackjack counting on youtube.

# Hi-lo Counting Method
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

# Perfect Basic Strategy
When evolving project to web app, maybe a cheatsheet page would be awesome

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
