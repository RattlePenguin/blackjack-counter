#include <gtest/gtest.h>
#include "Hand.hpp"
#include "Card.hpp"

class HandTest : public testing::Test {
protected:
    void SetUp() override {}

    // Helper to create a card
    Card createCard(Rank rank, Suit suit = Suit::SPADES) {
        Card c;
        c.rank = rank;
        c.suit = suit;
        c.faceDown = false;
        return c;
    }
};

// ==================== Constructor Tests ====================

TEST_F(HandTest, ConstructorSetsInitialBet) {
    Hand hand(10.0);
    EXPECT_DOUBLE_EQ(hand.getBet(), 10.0);
}

TEST_F(HandTest, ConstructorWithZeroBet) {
    Hand hand(0.0);
    EXPECT_DOUBLE_EQ(hand.getBet(), 0.0);
}

TEST_F(HandTest, ConstructorInitializesEmptyHand) {
    Hand hand(10.0);
    EXPECT_TRUE(hand.getCards().empty());
}

// ==================== addCard Tests ====================

TEST_F(HandTest, AddCardAddsSingleCard) {
    Hand hand(10.0);
    hand.addCard(createCard(Rank::ACE));
    EXPECT_EQ(hand.getCards().size(), 1u);
    EXPECT_EQ(hand.getCards()[0].rank, Rank::ACE);
}

TEST_F(HandTest, AddCardAddsMultipleCards) {
    Hand hand(10.0);
    hand.addCard(createCard(Rank::ACE));
    hand.addCard(createCard(Rank::KING));
    EXPECT_EQ(hand.getCards().size(), 2u);
    EXPECT_EQ(hand.getCards()[0].rank, Rank::ACE);
    EXPECT_EQ(hand.getCards()[1].rank, Rank::KING);
}

// ==================== getTotalValue Tests ====================

TEST_F(HandTest, getTotalValueWithNumberCards) {
    Hand hand(10.0);
    hand.addCard(createCard(Rank::FIVE));
    hand.addCard(createCard(Rank::SEVEN));
    EXPECT_EQ(hand.getTotalValue(), 12);
}

TEST_F(HandTest, getTotalValueWithFaceCards) {
    Hand hand(10.0);
    hand.addCard(createCard(Rank::JACK));
    hand.addCard(createCard(Rank::QUEEN));
    EXPECT_EQ(hand.getTotalValue(), 20);
}

TEST_F(HandTest, getTotalValueWithAces) {
    Hand hand(10.0);
    hand.addCard(createCard(Rank::ACE));
    hand.addCard(createCard(Rank::ACE));
    EXPECT_EQ(hand.getTotalValue(), 22);  // Both aces counted as 11
}

TEST_F(HandTest, getTotalValueWithMixedCards) {
    Hand hand(10.0);
    hand.addCard(createCard(Rank::ACE));
    hand.addCard(createCard(Rank::EIGHT));
    hand.addCard(createCard(Rank::THREE));
    EXPECT_EQ(hand.getTotalValue(), 22);  // Ace=11, 8, 3
}

TEST_F(HandTest, getTotalValueEmptyHand) {
    Hand hand(10.0);
    EXPECT_EQ(hand.getTotalValue(), 0);
}

// ==================== getNumAces Tests ====================

TEST_F(HandTest, getNumAcesWithNoAces) {
    Hand hand(10.0);
    hand.addCard(createCard(Rank::KING));
    hand.addCard(createCard(Rank::QUEEN));
    EXPECT_EQ(hand.getNumAces(), 0);
}

TEST_F(HandTest, getNumAcesWithOneAce) {
    Hand hand(10.0);
    hand.addCard(createCard(Rank::ACE));
    hand.addCard(createCard(Rank::TEN));
    EXPECT_EQ(hand.getNumAces(), 1);
}

TEST_F(HandTest, getNumAcesWithMultipleAces) {
    Hand hand(10.0);
    hand.addCard(createCard(Rank::ACE));
    hand.addCard(createCard(Rank::ACE));
    hand.addCard(createCard(Rank::ACE));
    EXPECT_EQ(hand.getNumAces(), 3);
}

TEST_F(HandTest, getNumAcesEmptyHand) {
    Hand hand(10.0);
    EXPECT_EQ(hand.getNumAces(), 0);
}

// ==================== getRealValue Tests ====================

TEST_F(HandTest, getRealValueWithNoAces) {
    Hand hand(10.0);
    hand.addCard(createCard(Rank::KING));
    hand.addCard(createCard(Rank::EIGHT));
    EXPECT_EQ(hand.getRealValue(), 18);
}

TEST_F(HandTest, getRealValueWithOneAceUnder21) {
    Hand hand(10.0);
    hand.addCard(createCard(Rank::ACE));
    hand.addCard(createCard(Rank::SIX));
    EXPECT_EQ(hand.getRealValue(), 17);  // Ace counted as 11
}

TEST_F(HandTest, getRealValueWithOneAceOver21) {
    Hand hand(10.0);
    hand.addCard(createCard(Rank::ACE));
    hand.addCard(createCard(Rank::KING));
    hand.addCard(createCard(Rank::FIVE));
    EXPECT_EQ(hand.getRealValue(), 16);  // Ace counted as 1
}

TEST_F(HandTest, getRealValueWithTwoAces) {
    Hand hand(10.0);
    hand.addCard(createCard(Rank::ACE));
    hand.addCard(createCard(Rank::ACE));
    hand.addCard(createCard(Rank::NINE));
    EXPECT_EQ(hand.getRealValue(), 21);  // One ace as 11, one as 1
}

TEST_F(HandTest, getRealValueWithThreeAces) {
    Hand hand(10.0);
    hand.addCard(createCard(Rank::ACE));
    hand.addCard(createCard(Rank::ACE));
    hand.addCard(createCard(Rank::ACE));
    hand.addCard(createCard(Rank::NINE));
    EXPECT_EQ(hand.getRealValue(), 12);  // All aces as 1 (1+1+1+9)
}

TEST_F(HandTest, getRealValueBlackjack) {
    Hand hand(10.0);
    hand.addCard(createCard(Rank::ACE));
    hand.addCard(createCard(Rank::TEN));
    EXPECT_EQ(hand.getRealValue(), 21);
}

TEST_F(HandTest, getRealValueEmptyHand) {
    Hand hand(10.0);
    EXPECT_EQ(hand.getRealValue(), 0);
}

// ==================== isSoft Tests ====================

TEST_F(HandTest, isSoftWithAceCountedAs11) {
    Hand hand(10.0);
    hand.addCard(createCard(Rank::ACE));
    hand.addCard(createCard(Rank::SIX));
    EXPECT_TRUE(hand.isSoft());
}

TEST_F(HandTest, isSoftWithAceCountedAs1) {
    Hand hand(10.0);
    hand.addCard(createCard(Rank::ACE));
    hand.addCard(createCard(Rank::KING));
    hand.addCard(createCard(Rank::NINE));
    EXPECT_FALSE(hand.isSoft());  // Ace must be 1 to avoid bust
}

TEST_F(HandTest, isSoftWithNoAces) {
    Hand hand(10.0);
    hand.addCard(createCard(Rank::TEN));
    hand.addCard(createCard(Rank::EIGHT));
    EXPECT_FALSE(hand.isSoft());
}

TEST_F(HandTest, isSoftWithTwoAcesOneCountedAs11) {
    Hand hand(10.0);
    hand.addCard(createCard(Rank::ACE));
    hand.addCard(createCard(Rank::ACE));
    hand.addCard(createCard(Rank::NINE));
    EXPECT_TRUE(hand.isSoft());  // One ace still counted as 11
}

TEST_F(HandTest, isSoftEmptyHand) {
    Hand hand(10.0);
    EXPECT_FALSE(hand.isSoft());
}

// ==================== isTwoCards Tests ====================

TEST_F(HandTest, isTwoCardsWithTwoCards) {
    Hand hand(10.0);
    hand.addCard(createCard(Rank::ACE));
    hand.addCard(createCard(Rank::KING));
    EXPECT_TRUE(hand.isTwoCards());
}

TEST_F(HandTest, isTwoCardsWithOneCard) {
    Hand hand(10.0);
    hand.addCard(createCard(Rank::ACE));
    EXPECT_FALSE(hand.isTwoCards());
}

TEST_F(HandTest, isTwoCardsWithThreeCards) {
    Hand hand(10.0);
    hand.addCard(createCard(Rank::ACE));
    hand.addCard(createCard(Rank::KING));
    hand.addCard(createCard(Rank::TWO));
    EXPECT_FALSE(hand.isTwoCards());
}

TEST_F(HandTest, isTwoCardsEmptyHand) {
    Hand hand(10.0);
    EXPECT_FALSE(hand.isTwoCards());
}

// ==================== isPair Tests ====================

TEST_F(HandTest, isPairWithSameRank) {
    Hand hand(10.0);
    hand.addCard(createCard(Rank::EIGHT, Suit::SPADES));
    hand.addCard(createCard(Rank::EIGHT, Suit::HEARTS));
    EXPECT_TRUE(hand.isPair());
}

TEST_F(HandTest, isPairWithDifferentRank) {
    Hand hand(10.0);
    hand.addCard(createCard(Rank::EIGHT));
    hand.addCard(createCard(Rank::KING));
    EXPECT_FALSE(hand.isPair());
}

TEST_F(HandTest, isPairWithOneCard) {
    Hand hand(10.0);
    hand.addCard(createCard(Rank::EIGHT));
    EXPECT_FALSE(hand.isPair());
}

TEST_F(HandTest, isPairWithThreeCards) {
    Hand hand(10.0);
    hand.addCard(createCard(Rank::EIGHT));
    hand.addCard(createCard(Rank::EIGHT));
    hand.addCard(createCard(Rank::EIGHT));
    EXPECT_FALSE(hand.isPair());
}

// ==================== isBlackjack Tests ====================

TEST_F(HandTest, isBlackjackWithAceAndTen) {
    Hand hand(10.0);
    hand.addCard(createCard(Rank::ACE));
    hand.addCard(createCard(Rank::TEN));
    EXPECT_TRUE(hand.isBlackjack());
}

TEST_F(HandTest, isBlackjackWithAceAndFaceCard) {
    Hand hand(10.0);
    hand.addCard(createCard(Rank::ACE));
    hand.addCard(createCard(Rank::KING));
    EXPECT_TRUE(hand.isBlackjack());
}

TEST_F(HandTest, isBlackjackWithAceAndJack) {
    Hand hand(10.0);
    hand.addCard(createCard(Rank::ACE));
    hand.addCard(createCard(Rank::JACK));
    EXPECT_TRUE(hand.isBlackjack());
}

TEST_F(HandTest, isBlackjackWithAceAndQueen) {
    Hand hand(10.0);
    hand.addCard(createCard(Rank::ACE));
    hand.addCard(createCard(Rank::QUEEN));
    EXPECT_TRUE(hand.isBlackjack());
}

TEST_F(HandTest, isBlackjackWithThreeCardsMaking21) {
    Hand hand(10.0);
    hand.addCard(createCard(Rank::NINE));
    hand.addCard(createCard(Rank::ACE));
    hand.addCard(createCard(Rank::ACE));
    EXPECT_FALSE(hand.isBlackjack());  // Not two cards
}

TEST_F(HandTest, isBlackjackOnSplitHand) {
    Hand hand(10.0);
    hand.split();
    hand.addCard(createCard(Rank::ACE));
    hand.addCard(createCard(Rank::TEN));
    EXPECT_FALSE(hand.isBlackjack());  // Is a split hand
}

TEST_F(HandTest, isBlackjackWithNonTwentyOne) {
    Hand hand(10.0);
    hand.addCard(createCard(Rank::KING));
    hand.addCard(createCard(Rank::NINE));
    EXPECT_FALSE(hand.isBlackjack());
}

// ==================== isBusted Tests ====================

TEST_F(HandTest, isBustedWhenOver21) {
    Hand hand(10.0);
    hand.addCard(createCard(Rank::KING));
    hand.addCard(createCard(Rank::EIGHT));
    hand.addCard(createCard(Rank::FIVE));
    EXPECT_TRUE(hand.isBusted());
}

TEST_F(HandTest, isBustedWhenExactly21) {
    Hand hand(10.0);
    hand.addCard(createCard(Rank::ACE));
    hand.addCard(createCard(Rank::TEN));
    EXPECT_FALSE(hand.isBusted());
}

TEST_F(HandTest, isBustedWhenUnder21) {
    Hand hand(10.0);
    hand.addCard(createCard(Rank::KING));
    hand.addCard(createCard(Rank::NINE));
    EXPECT_FALSE(hand.isBusted());
}

TEST_F(HandTest, isBustedWithAcesNotBusted) {
    Hand hand(10.0);
    hand.addCard(createCard(Rank::ACE));
    hand.addCard(createCard(Rank::ACE));
    hand.addCard(createCard(Rank::NINE));
    EXPECT_FALSE(hand.isBusted());  // Real value is 21
}

// ==================== is21 Tests ====================

TEST_F(HandTest, is21WithBlackjack) {
    Hand hand(10.0);
    hand.addCard(createCard(Rank::ACE));
    hand.addCard(createCard(Rank::TEN));
    EXPECT_TRUE(hand.is21());
}

TEST_F(HandTest, is21WithThreeCards) {
    Hand hand(10.0);
    hand.addCard(createCard(Rank::NINE));
    hand.addCard(createCard(Rank::SIX));
    hand.addCard(createCard(Rank::SIX));
    EXPECT_TRUE(hand.is21());
}

TEST_F(HandTest, is21WithAces) {
    Hand hand(10.0);
    hand.addCard(createCard(Rank::ACE));
    hand.addCard(createCard(Rank::ACE));
    hand.addCard(createCard(Rank::NINE));
    EXPECT_TRUE(hand.is21());
}

TEST_F(HandTest, is21WhenNot21) {
    Hand hand(10.0);
    hand.addCard(createCard(Rank::KING));
    hand.addCard(createCard(Rank::NINE));
    EXPECT_FALSE(hand.is21());
}

// ==================== surrender Tests ====================

TEST_F(HandTest, surrenderSetsSurrenderedFlag) {
    Hand hand(10.0);
    hand.surrender();
    EXPECT_TRUE(hand.isSurrendered());
}

TEST_F(HandTest, surrenderHalvesBet) {
    Hand hand(10.0);
    hand.surrender();
    EXPECT_DOUBLE_EQ(hand.getBet(), 5.0);
}

TEST_F(HandTest, surrenderWithZeroBet) {
    Hand hand(0.0);
    hand.surrender();
    EXPECT_DOUBLE_EQ(hand.getBet(), 0.0);
}

TEST_F(HandTest, isSurrenderedInitiallyFalse) {
    Hand hand(10.0);
    EXPECT_FALSE(hand.isSurrendered());
}

// ==================== doubleDown Tests ====================

TEST_F(HandTest, doubleDownDoublesBet) {
    Hand hand(10.0);
    hand.doubleDown();
    EXPECT_DOUBLE_EQ(hand.getBet(), 20.0);
}

TEST_F(HandTest, doubleDownSetsDoubledFlag) {
    Hand hand(10.0);
    hand.doubleDown();
    EXPECT_TRUE(hand.isDoubled());
}

TEST_F(HandTest, doubleDownWithZeroBet) {
    Hand hand(0.0);
    hand.doubleDown();
    EXPECT_DOUBLE_EQ(hand.getBet(), 0.0);
}

TEST_F(HandTest, isDoubledInitiallyFalse) {
    Hand hand(10.0);
    EXPECT_FALSE(hand.isDoubled());
}

// ==================== split Tests ====================

TEST_F(HandTest, splitSetsIsSplitFlag) {
    Hand hand(10.0);
    hand.split();
    EXPECT_TRUE(hand.isSplitHand());
}

TEST_F(HandTest, isSplitHandInitiallyFalse) {
    Hand hand(10.0);
    EXPECT_FALSE(hand.isSplitHand());
}

TEST_F(HandTest, splitDoesNotModifyCards) {
    Hand hand(10.0);
    hand.addCard(createCard(Rank::EIGHT));
    hand.addCard(createCard(Rank::EIGHT));
    hand.split();
    EXPECT_EQ(hand.getCards().size(), 2u);
}

// ==================== pop_back Tests ====================

TEST_F(HandTest, pop_backRemovesAndReturnsLastCard) {
    Hand hand(10.0);
    hand.addCard(createCard(Rank::ACE));
    hand.addCard(createCard(Rank::KING));
    Card removed = hand.pop_back();
    EXPECT_EQ(removed.rank, Rank::KING);
    EXPECT_EQ(hand.getCards().size(), 1u);
    EXPECT_EQ(hand.getCards()[0].rank, Rank::ACE);
}

TEST_F(HandTest, pop_backOnSingleCardHand) {
    Hand hand(10.0);
    hand.addCard(createCard(Rank::ACE));
    Card removed = hand.pop_back();
    EXPECT_EQ(removed.rank, Rank::ACE);
    EXPECT_TRUE(hand.getCards().empty());
}

// ==================== finish Tests ====================

TEST_F(HandTest, finishSetsFinishedFlag) {
    Hand hand(10.0);
    hand.finish();
    EXPECT_TRUE(hand.isFinished());
}

TEST_F(HandTest, isFinishedInitiallyFalse) {
    Hand hand(10.0);
    EXPECT_FALSE(hand.isFinished());
}

// ==================== getBet Tests ====================

TEST_F(HandTest, getBetReturnsCorrectValue) {
    Hand hand(15.5);
    EXPECT_DOUBLE_EQ(hand.getBet(), 15.5);
}

TEST_F(HandTest, getBetAfterDoubleDown) {
    Hand hand(10.0);
    hand.doubleDown();
    EXPECT_DOUBLE_EQ(hand.getBet(), 20.0);
}

TEST_F(HandTest, getBetAfterSurrender) {
    Hand hand(10.0);
    hand.surrender();
    EXPECT_DOUBLE_EQ(hand.getBet(), 5.0);
}

// ==================== getCards Tests ====================

TEST_F(HandTest, getCardsReturnsReference) {
    Hand hand(10.0);
    hand.addCard(createCard(Rank::ACE));
    hand.addCard(createCard(Rank::KING));
    std::vector<Card>& cards = hand.getCards();
    EXPECT_EQ(cards.size(), 2u);
    EXPECT_EQ(cards[0].rank, Rank::ACE);
    EXPECT_EQ(cards[1].rank, Rank::KING);
}

// ==================== Complex Scenario Tests ====================

TEST_F(HandTest, FullHandScenario) {
    Hand hand(10.0);
    
    // Initially empty
    EXPECT_TRUE(hand.getCards().empty());
    EXPECT_EQ(hand.getTotalValue(), 0);
    EXPECT_EQ(hand.getRealValue(), 0);
    EXPECT_FALSE(hand.isBusted());
    EXPECT_FALSE(hand.is21());
    
    // Add two cards (Ace + King = Blackjack)
    hand.addCard(createCard(Rank::ACE));
    hand.addCard(createCard(Rank::KING));
    EXPECT_TRUE(hand.isTwoCards());
    EXPECT_TRUE(hand.isBlackjack());
    EXPECT_TRUE(hand.is21());
    EXPECT_EQ(hand.getRealValue(), 21);
    EXPECT_TRUE(hand.isSoft());
    
    // Double down
    hand.doubleDown();
    EXPECT_DOUBLE_EQ(hand.getBet(), 20.0);
    EXPECT_TRUE(hand.isDoubled());
    
    // Finish hand
    hand.finish();
    EXPECT_TRUE(hand.isFinished());
}

TEST_F(HandTest, SplitHandScenario) {
    Hand hand(10.0);
    hand.addCard(createCard(Rank::EIGHT, Suit::SPADES));
    hand.addCard(createCard(Rank::EIGHT, Suit::HEARTS));
    
    EXPECT_TRUE(hand.isPair());
    EXPECT_TRUE(hand.isTwoCards());
    
    // Split the hand
    hand.split();
    EXPECT_TRUE(hand.isSplitHand());
    
    // Remove one card (simulate split)
    Card removed = hand.pop_back();
    EXPECT_EQ(removed.rank, Rank::EIGHT);
    EXPECT_EQ(hand.getCards().size(), 1u);
    
    // Add new card
    hand.addCard(createCard(Rank::ACE));
    EXPECT_EQ(hand.getRealValue(), 19);
    EXPECT_TRUE(hand.isSoft());
}

TEST_F(HandTest, BustedHandScenario) {
    Hand hand(10.0);
    hand.addCard(createCard(Rank::KING));
    hand.addCard(createCard(Rank::NINE));
    
    EXPECT_EQ(hand.getRealValue(), 19);
    EXPECT_FALSE(hand.isBusted());
    
    hand.addCard(createCard(Rank::FIVE));
    
    EXPECT_TRUE(hand.isBusted());
    EXPECT_EQ(hand.getRealValue(), 24);
}

TEST_F(HandTest, MultipleAcesScenario) {
    Hand hand(10.0);
    hand.addCard(createCard(Rank::ACE));
    hand.addCard(createCard(Rank::ACE));
    
    EXPECT_EQ(hand.getTotalValue(), 22);  // Both aces as 11
    EXPECT_EQ(hand.getRealValue(), 12);   // Both aces as 1
    EXPECT_EQ(hand.getNumAces(), 2);
    EXPECT_FALSE(hand.isSoft());  // No ace can be 11 without busting
    
    hand.addCard(createCard(Rank::TWO));
    
    EXPECT_EQ(hand.getRealValue(), 14);
    EXPECT_TRUE(hand.isSoft());  // One ace can now be 11 (1+11+2=14)
}
