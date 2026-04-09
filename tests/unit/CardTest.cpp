#include <gtest/gtest.h>
#include "Card.hpp"

class CardTest : public ::testing::Test {
protected:
    CardTest() = default;
};

// Test default constructor values
TEST_F(CardTest, DefaultConstructor) {
    Card card;
    EXPECT_EQ(card.rank, Rank::ACE);
    EXPECT_EQ(card.suit, Suit::SPADES);
    EXPECT_FALSE(card.faceDown);
}

// Test getValue() for all card ranks
TEST_F(CardTest, GetValueForAce) {
    Card card;
    card.rank = Rank::ACE;
    EXPECT_EQ(card.getValue(), 11);
}

TEST_F(CardTest, GetValueForNumberCards) {
    Card card;
    // Test cards 2-10
    card.rank = Rank::TWO;
    EXPECT_EQ(card.getValue(), 2);
    
    card.rank = Rank::THREE;
    EXPECT_EQ(card.getValue(), 3);
    
    card.rank = Rank::FOUR;
    EXPECT_EQ(card.getValue(), 4);
    
    card.rank = Rank::FIVE;
    EXPECT_EQ(card.getValue(), 5);
    
    card.rank = Rank::SIX;
    EXPECT_EQ(card.getValue(), 6);
    
    card.rank = Rank::SEVEN;
    EXPECT_EQ(card.getValue(), 7);
    
    card.rank = Rank::EIGHT;
    EXPECT_EQ(card.getValue(), 8);
    
    card.rank = Rank::NINE;
    EXPECT_EQ(card.getValue(), 9);
    
    card.rank = Rank::TEN;
    EXPECT_EQ(card.getValue(), 10);
}

TEST_F(CardTest, GetValueForFaceCards) {
    Card card;
    // All face cards should return 10
    card.rank = Rank::JACK;
    EXPECT_EQ(card.getValue(), 10);
    
    card.rank = Rank::QUEEN;
    EXPECT_EQ(card.getValue(), 10);
    
    card.rank = Rank::KING;
    EXPECT_EQ(card.getValue(), 10);
}

// Test getHiLoValue() for all card types
TEST_F(CardTest, HiLoValueForLowCards) {
    Card card;
    // Cards 2-6 should return +1
    card.rank = Rank::TWO;
    EXPECT_EQ(card.getHiLoValue(), 1);
    
    card.rank = Rank::THREE;
    EXPECT_EQ(card.getHiLoValue(), 1);
    
    card.rank = Rank::FOUR;
    EXPECT_EQ(card.getHiLoValue(), 1);
    
    card.rank = Rank::FIVE;
    EXPECT_EQ(card.getHiLoValue(), 1);
    
    card.rank = Rank::SIX;
    EXPECT_EQ(card.getHiLoValue(), 1);
}

TEST_F(CardTest, HiLoValueForNeutralCards) {
    Card card;
    // Cards 7-9 should return 0
    card.rank = Rank::SEVEN;
    EXPECT_EQ(card.getHiLoValue(), 0);
    
    card.rank = Rank::EIGHT;
    EXPECT_EQ(card.getHiLoValue(), 0);
    
    card.rank = Rank::NINE;
    EXPECT_EQ(card.getHiLoValue(), 0);
}

TEST_F(CardTest, HiLoValueForHighCards) {
    Card card;
    // 10, J, Q, K, A should return -1
    card.rank = Rank::TEN;
    EXPECT_EQ(card.getHiLoValue(), -1);
    
    card.rank = Rank::JACK;
    EXPECT_EQ(card.getHiLoValue(), -1);
    
    card.rank = Rank::QUEEN;
    EXPECT_EQ(card.getHiLoValue(), -1);
    
    card.rank = Rank::KING;
    EXPECT_EQ(card.getHiLoValue(), -1);
    
    card.rank = Rank::ACE;
    EXPECT_EQ(card.getHiLoValue(), -1);
}

// Test toString() method
TEST_F(CardTest, ToStringForFaceUpCards) {
    Card card;
    card.faceDown = false;
    
    card.rank = Rank::ACE;
    EXPECT_EQ(card.toString(), "A");
    
    card.rank = Rank::TWO;
    EXPECT_EQ(card.toString(), "2");
    
    card.rank = Rank::TEN;
    EXPECT_EQ(card.toString(), "10");
    
    card.rank = Rank::JACK;
    EXPECT_EQ(card.toString(), "J");
    
    card.rank = Rank::QUEEN;
    EXPECT_EQ(card.toString(), "Q");
    
    card.rank = Rank::KING;
    EXPECT_EQ(card.toString(), "K");
}

TEST_F(CardTest, ToStringForFaceDownCards) {
    Card card;
    card.faceDown = true;
    card.rank = Rank::ACE;  // Should still show as [XX] when face down
    EXPECT_EQ(card.toString(), "[XX]");
}

// Test all suits
TEST_F(CardTest, AllSuits) {
    Card card;
    
    card.suit = Suit::SPADES;
    EXPECT_EQ(card.suit, Suit::SPADES);
    
    card.suit = Suit::HEARTS;
    EXPECT_EQ(card.suit, Suit::HEARTS);
    
    card.suit = Suit::DIAMONDS;
    EXPECT_EQ(card.suit, Suit::DIAMONDS);
    
    card.suit = Suit::CLUBS;
    EXPECT_EQ(card.suit, Suit::CLUBS);
}

// Test faceDown property
TEST_F(CardTest, FaceDownProperty) {
    Card card;
    EXPECT_FALSE(card.faceDown);
    
    card.faceDown = true;
    EXPECT_TRUE(card.faceDown);
    
    card.faceDown = false;
    EXPECT_FALSE(card.faceDown);
}

// Test combinations of rank and suit
TEST_F(CardTest, RankAndSuitCombination) {
    Card aceOfSpades;
    aceOfSpades.rank = Rank::ACE;
    aceOfSpades.suit = Suit::SPADES;
    EXPECT_EQ(aceOfSpades.rank, Rank::ACE);
    EXPECT_EQ(aceOfSpades.suit, Suit::SPADES);
    EXPECT_EQ(aceOfSpades.getValue(), 11);
    EXPECT_EQ(aceOfSpades.getHiLoValue(), -1);
    EXPECT_EQ(aceOfSpades.toString(), "A");
    
    Card kingOfHearts;
    kingOfHearts.rank = Rank::KING;
    kingOfHearts.suit = Suit::HEARTS;
    EXPECT_EQ(kingOfHearts.rank, Rank::KING);
    EXPECT_EQ(kingOfHearts.suit, Suit::HEARTS);
    EXPECT_EQ(kingOfHearts.getValue(), 10);
    EXPECT_EQ(kingOfHearts.getHiLoValue(), -1);
    EXPECT_EQ(kingOfHearts.toString(), "K");
    
    Card fiveOfClubs;
    fiveOfClubs.rank = Rank::FIVE;
    fiveOfClubs.suit = Suit::CLUBS;
    EXPECT_EQ(fiveOfClubs.rank, Rank::FIVE);
    EXPECT_EQ(fiveOfClubs.suit, Suit::CLUBS);
    EXPECT_EQ(fiveOfClubs.getValue(), 5);
    EXPECT_EQ(fiveOfClubs.getHiLoValue(), 1);
    EXPECT_EQ(fiveOfClubs.toString(), "5");
}

// Test constants
TEST_F(CardTest, Constants) {
    EXPECT_EQ(NUM_RANKS, 13);
    EXPECT_EQ(NUM_SUITS, 4);
    EXPECT_EQ(NUM_CARDS_IN_DECK, 52);
}

// Test that face cards (JACK, QUEEN, KING) are correctly identified as > TEN
TEST_F(CardTest, FaceCardsGreaterThanTen) {
    Card card;
    EXPECT_TRUE(Rank::JACK > Rank::TEN);
    EXPECT_TRUE(Rank::QUEEN > Rank::TEN);
    EXPECT_TRUE(Rank::KING > Rank::TEN);
}

// Test enum ordering
TEST_F(CardTest, RankEnumOrdering) {
    EXPECT_TRUE(Rank::ACE < Rank::TWO);
    EXPECT_TRUE(Rank::TWO < Rank::THREE);
    EXPECT_TRUE(Rank::NINE < Rank::TEN);
    EXPECT_TRUE(Rank::TEN < Rank::JACK);
    EXPECT_TRUE(Rank::JACK < Rank::QUEEN);
    EXPECT_TRUE(Rank::QUEEN < Rank::KING);
}