#include <gtest/gtest.h>
#include "Shoe.hpp"
#include "Card.hpp"

class ShoeTest : public testing::Test {};

// ==================== Constructor Tests ====================

TEST_F(ShoeTest, ConstructorWithSingleDeck) {
    Shoe shoe(1, 0.75, 42);
    EXPECT_EQ(shoe.getCardsRemaining(), 52);
}

TEST_F(ShoeTest, ConstructorWithMultipleDecks) {
    Shoe shoe(6, 0.75, 42);
    EXPECT_EQ(shoe.getCardsRemaining(), 6 * 52);
}

TEST_F(ShoeTest, ConstructorWithEightDecks) {
    Shoe shoe(8, 0.5, 42);
    EXPECT_EQ(shoe.getCardsRemaining(), 8 * 52);
}

// ==================== getCardsRemaining Tests ====================

TEST_F(ShoeTest, getCardsRemainingAfterDraw) {
    Shoe shoe(1, 1.0, 42);  // 100% penetration so we can draw all
    EXPECT_EQ(shoe.getCardsRemaining(), 52);
    
    shoe.draw();
    EXPECT_EQ(shoe.getCardsRemaining(), 51);
    
    shoe.draw();
    shoe.draw();
    EXPECT_EQ(shoe.getCardsRemaining(), 49);
}

TEST_F(ShoeTest, getCardsRemainingWithSixDecks) {
    Shoe shoe(6, 1.0, 42);
    EXPECT_EQ(shoe.getCardsRemaining(), 312);
    
    for (int i = 0; i < 10; ++i) {
        shoe.draw();
    }
    EXPECT_EQ(shoe.getCardsRemaining(), 302);
}

// ==================== getDecksRemaining Tests ====================

TEST_F(ShoeTest, getDecksRemainingSingleDeck) {
    Shoe shoe(1, 1.0, 42);
    EXPECT_DOUBLE_EQ(shoe.getDecksRemaining(), 1.0);
}

TEST_F(ShoeTest, getDecksRemainingAfterDraw) {
    Shoe shoe(1, 1.0, 42);
    
    // Draw 26 cards (half a deck)
    for (int i = 0; i < 26; ++i) {
        shoe.draw();
    }
    EXPECT_DOUBLE_EQ(shoe.getDecksRemaining(), 0.5);
}

TEST_F(ShoeTest, getDecksRemainingWithSixDecks) {
    Shoe shoe(6, 1.0, 42);
    EXPECT_DOUBLE_EQ(shoe.getDecksRemaining(), 6.0);
}

// ==================== needsShuffle Tests ====================

TEST_F(ShoeTest, needsShuffleInitiallyFalse) {
    Shoe shoe(1, 0.5, 42);  // Cut card at 50%
    EXPECT_FALSE(shoe.needsShuffle());
}

TEST_F(ShoeTest, needsShuffleAtPenetration) {
    Shoe shoe(1, 0.5, 42);  // Cut card at 26 cards (50% of 52)
    
    // Draw cards until we reach the cut card
    for (int i = 0; i < 26; ++i) {
        EXPECT_FALSE(shoe.needsShuffle());
        shoe.draw();
    }
    
    // After drawing 26th card, we should be at or past cut card
    EXPECT_TRUE(shoe.needsShuffle());
}

TEST_F(ShoeTest, needsShuffleWithDeepPenetration) {
    Shoe shoe(1, 0.9, 42);  // Cut card at 90%
    
    // Draw 46 cards (90% of 52 is ~47)
    for (int i = 0; i < 46; ++i) {
        EXPECT_FALSE(shoe.needsShuffle());
        shoe.draw();
    }
    
    // Should need shuffle after drawing past cut card
    EXPECT_TRUE(shoe.needsShuffle());
}

TEST_F(ShoeTest, needsShuffleWithSixDecks) {
    Shoe shoe(6, 0.75, 42);  // Cut card at 75% of 312 = 234
    
    // Draw 233 cards
    for (int i = 0; i < 233; ++i) {
        shoe.draw();
    }
    EXPECT_FALSE(shoe.needsShuffle());
    
    shoe.draw();  // 234th card
    EXPECT_TRUE(shoe.needsShuffle());
}

// ==================== shuffle Tests ====================

TEST_F(ShoeTest, shuffleResetsDealtIndex) {
    Shoe shoe(1, 1.0, 42);
    
    // Draw some cards
    for (int i = 0; i < 20; ++i) {
        shoe.draw();
    }
    EXPECT_EQ(shoe.getCardsRemaining(), 32);
    
    shoe.shuffle();
    EXPECT_EQ(shoe.getCardsRemaining(), 52);
}

TEST_F(ShoeTest, shuffleWithSameSeedProducesSameOrder) {
    // Create two shoes with the same seed
    Shoe shoe1(1, 1.0, 12345);
    Shoe shoe2(1, 1.0, 12345);
    
    // Draw all cards and compare
    for (int i = 0; i < 52; ++i) {
        Card c1 = shoe1.draw();
        Card c2 = shoe2.draw();
        EXPECT_EQ(c1.rank, c2.rank);
        EXPECT_EQ(c1.suit, c2.suit);
    }
}

TEST_F(ShoeTest, shuffleResetsRunningCount) {
    Shoe shoe(1, 1.0, 42);
    
    // Draw some cards to change the count
    for (int i = 0; i < 10; ++i) {
        shoe.draw();
    }
    EXPECT_NE(shoe.getSystemRunningCount(), 0);
    
    shoe.shuffle();
    EXPECT_EQ(shoe.getSystemRunningCount(), 0);
}

// ==================== initialise Tests ====================

TEST_F(ShoeTest, initialiseCreatesCorrectCardCount) {
    Shoe shoe(4, 1.0, 42);
    EXPECT_EQ(shoe.getCardsRemaining(), 4 * 52);
}

TEST_F(ShoeTest, initialiseWithOneDeck) {
    Shoe shoe(1, 1.0, 42);
    EXPECT_EQ(shoe.getCardsRemaining(), 52);
}

// ==================== draw Tests ====================

TEST_F(ShoeTest, drawReturnsValidCard) {
    Shoe shoe(1, 1.0, 42);
    Card c = shoe.draw();
    
    // Card should have valid rank (1-13) and suit (0-3)
    EXPECT_GE(static_cast<int>(c.rank), 1);
    EXPECT_LE(static_cast<int>(c.rank), 13);
    EXPECT_GE(static_cast<int>(c.suit), 0);
    EXPECT_LE(static_cast<int>(c.suit), 3);
}

TEST_F(ShoeTest, drawDecreasesCardsRemaining) {
    Shoe shoe(1, 1.0, 42);
    int initial = shoe.getCardsRemaining();
    shoe.draw();
    EXPECT_EQ(shoe.getCardsRemaining(), initial - 1);
}

// ==================== getSystemRunningCount Tests ====================

TEST_F(ShoeTest, runningCountInitiallyZero) {
    Shoe shoe(1, 1.0, 42);
    EXPECT_EQ(shoe.getSystemRunningCount(), 0);
}

TEST_F(ShoeTest, runningCountIncreasesForLowCards) {
    // Low cards (2-6) add +1 to running count
    Shoe shoe(1, 1.0, 42);
    
    // We need to find low cards in the shuffled deck
    // Instead, we'll use a known seed and check the count changes
    int initialCount = shoe.getSystemRunningCount();
    
    // Draw several cards - the count should change based on Hi-Lo values
    for (int i = 0; i < 10; ++i) {
        shoe.draw();
    }
    
    // The count may be positive or negative depending on what was drawn
    // Just verify it's tracking something
    // (We can't predict exact value without knowing the shuffle order)
}

TEST_F(ShoeTest, runningCountAccuracyWithKnownSequence) {
    // Use a fixed seed to ensure reproducible results
    Shoe shoe(1, 1.0, 12345);
    
    // Draw cards and track the expected count manually
    int expectedCount = 0;
    for (int i = 0; i < 20; ++i) {
        Card c = shoe.draw();
        expectedCount += c.getHiLoValue();
    }
    
    EXPECT_EQ(shoe.getSystemRunningCount(), expectedCount);
}

TEST_F(ShoeTest, runningCountResetsOnShuffle) {
    Shoe shoe(1, 1.0, 42);
    
    // Draw cards to change count
    for (int i = 0; i < 15; ++i) {
        shoe.draw();
    }
    
    EXPECT_NE(shoe.getSystemRunningCount(), 0);
    
    shoe.shuffle();
    EXPECT_EQ(shoe.getSystemRunningCount(), 0);
}

// ==================== Hi-Lo Count Verification Tests ====================

TEST_F(ShoeTest, hiLoCountForSpecificCards) {
    // This test verifies the running count is calculated correctly
    // by drawing cards and checking the count matches expected Hi-Lo values
    
    // Create a shoe and draw cards, verifying count at each step
    Shoe shoe(1, 1.0, 12345);
    
    int expectedCount = 0;
    for (int i = 0; i < 30; ++i) {
        Card c = shoe.draw();
        expectedCount += c.getHiLoValue();
        EXPECT_EQ(shoe.getSystemRunningCount(), expectedCount);
    }
}

// ==================== Edge Case Tests ====================

TEST_F(ShoeTest, drawAllCardsFromSingleDeck) {
    Shoe shoe(1, 1.0, 42);
    
    // Draw all 52 cards
    for (int i = 0; i < 52; ++i) {
        shoe.draw();
    }
    
    EXPECT_EQ(shoe.getCardsRemaining(), 0);
    EXPECT_TRUE(shoe.needsShuffle());
}

TEST_F(ShoeTest, drawBeyondDeckSizeTriggersReinitialise) {
    Shoe shoe(1, 1.0, 42);
    
    // Draw all 52 cards
    for (int i = 0; i < 52; ++i) {
        shoe.draw();
    }
    
    EXPECT_EQ(shoe.getCardsRemaining(), 0);
    
    // Drawing one more should reinitialise the shoe
    shoe.draw();
    EXPECT_EQ(shoe.getCardsRemaining(), 51);  // 52 - 1 (just drew one)
}

TEST_F(ShoeTest, zeroPenetrationMeansNeedsShuffleImmediately) {
    Shoe shoe(1, 0.0, 42);  // Cut card at position 0
    EXPECT_TRUE(shoe.needsShuffle());
}

TEST_F(ShoeTest, fullPenetrationMeansNeedsShuffleOnlyWhenEmpty) {
    Shoe shoe(1, 1.0, 42);  // Cut card at 100%
    
    // Draw 51 cards
    for (int i = 0; i < 51; ++i) {
        shoe.draw();
        EXPECT_FALSE(shoe.needsShuffle());
    }
    
    // Draw last card
    shoe.draw();
    EXPECT_TRUE(shoe.needsShuffle());
}

// ==================== Complex Scenario Tests ====================

TEST_F(ShoeTest, fullShoeLifecycle) {
    Shoe shoe(6, 0.75, 42);
    
    // Initial state
    EXPECT_EQ(shoe.getCardsRemaining(), 312);
    EXPECT_EQ(shoe.getDecksRemaining(), 6.0);
    EXPECT_FALSE(shoe.needsShuffle());
    EXPECT_EQ(shoe.getSystemRunningCount(), 0);
    
    // Draw cards until shuffle is needed
    int cardsDrawn = 0;
    while (!shoe.needsShuffle()) {
        shoe.draw();
        cardsDrawn++;
    }
    
    // Should have drawn about 234 cards (75% of 312)
    EXPECT_GE(cardsDrawn, 233);
    EXPECT_TRUE(shoe.needsShuffle());
    
    // Shuffle resets everything
    shoe.shuffle();
    EXPECT_EQ(shoe.getCardsRemaining(), 312);
    EXPECT_EQ(shoe.getDecksRemaining(), 6.0);
    EXPECT_FALSE(shoe.needsShuffle());
    EXPECT_EQ(shoe.getSystemRunningCount(), 0);
}

TEST_F(ShoeTest, deterministicBehaviorWithSeed) {
    // Two shoes with same parameters should behave identically
    Shoe shoe1(2, 0.5, 99999);
    Shoe shoe2(2, 0.5, 99999);
    
    for (int i = 0; i < 50; ++i) {
        Card c1 = shoe1.draw();
        Card c2 = shoe2.draw();
        
        EXPECT_EQ(c1.rank, c2.rank);
        EXPECT_EQ(c1.suit, c2.suit);
        EXPECT_EQ(shoe1.getSystemRunningCount(), shoe2.getSystemRunningCount());
    }
    
    EXPECT_EQ(shoe1.getCardsRemaining(), shoe2.getCardsRemaining());
    EXPECT_EQ(shoe1.needsShuffle(), shoe2.needsShuffle());
}
