#include <gtest/gtest.h>
#include "HumanPlayer.hpp"
#include "Hand.hpp"
#include "Card.hpp"
#include "BlackjackRules.hpp"
#include <sstream>

class HumanPlayerTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Save original cin buffer
        original_cin = std::cin.rdbuf();
    }
    
    void TearDown() override {
        // Restore original cin buffer
        std::cin.rdbuf(original_cin);
    }
    
    std::streambuf* original_cin;
    
    // Helper to set up input stream
    void setInput(const std::string& input) {
        inputBuffer.str(input);
        std::cin.rdbuf(inputBuffer.rdbuf());
    }
    
    std::stringstream inputBuffer;
};

// Test constructor
TEST_F(HumanPlayerTest, Constructor) {
    HumanPlayer p("Alice");
    EXPECT_EQ(p.getName(), "Alice");
}

// Test basic inheritance from Player
TEST_F(HumanPlayerTest, InheritsFromPlayer) {
    HumanPlayer p("Bob");
    EXPECT_EQ(p.getName(), "Bob");
    EXPECT_EQ(p.getBankroll(), 0.0);
    
    p.win(100.0);
    EXPECT_EQ(p.getBankroll(), 100.0);
    
    p.lose(25.0);
    EXPECT_EQ(p.getBankroll(), 75.0);
}

// Test makeDecision with HIT input
TEST_F(HumanPlayerTest, MakeDecisionHit) {
    HumanPlayer p("Test");
    
    Hand hand(10.0);
    Card card1;
    card1.rank = Rank::FIVE;
    hand.addCard(card1);
    
    Card card2;
    card2.rank = Rank::SIX;
    hand.addCard(card2);
    
    BlackjackRules rules;
    
    setInput("h");
    Action action = p.makeDecision(hand, rules);
    EXPECT_EQ(action, Action::HIT);
}

// Test makeDecision with lowercase hit
TEST_F(HumanPlayerTest, MakeDecisionHitLowercase) {
    HumanPlayer p("Test");
    
    Hand hand(10.0);
    Card card1;
    card1.rank = Rank::FIVE;
    hand.addCard(card1);
    
    Card card2;
    card2.rank = Rank::SIX;
    hand.addCard(card2);
    
    BlackjackRules rules;
    
    setInput("h");
    Action action = p.makeDecision(hand, rules);
    EXPECT_EQ(action, Action::HIT);
}

// Test makeDecision with uppercase HIT
TEST_F(HumanPlayerTest, MakeDecisionHitUppercase) {
    HumanPlayer p("Test");
    
    Hand hand(10.0);
    Card card1;
    card1.rank = Rank::FIVE;
    hand.addCard(card1);
    
    Card card2;
    card2.rank = Rank::SIX;
    hand.addCard(card2);
    
    BlackjackRules rules;
    
    setInput("H");
    Action action = p.makeDecision(hand, rules);
    EXPECT_EQ(action, Action::HIT);
}

// Test makeDecision with STAND input
TEST_F(HumanPlayerTest, MakeDecisionStand) {
    HumanPlayer p("Test");
    
    Hand hand(10.0);
    Card card1;
    card1.rank = Rank::TEN;
    hand.addCard(card1);
    
    Card card2;
    card2.rank = Rank::SIX;
    hand.addCard(card2);
    
    BlackjackRules rules;
    
    setInput("s");
    Action action = p.makeDecision(hand, rules);
    EXPECT_EQ(action, Action::STAND);
}

// Test makeDecision with uppercase STAND
TEST_F(HumanPlayerTest, MakeDecisionStandUppercase) {
    HumanPlayer p("Test");
    
    Hand hand(10.0);
    Card card1;
    card1.rank = Rank::TEN;
    hand.addCard(card1);
    
    Card card2;
    card2.rank = Rank::SIX;
    hand.addCard(card2);
    
    BlackjackRules rules;
    
    setInput("S");
    Action action = p.makeDecision(hand, rules);
    EXPECT_EQ(action, Action::STAND);
}

// Test makeDecision with DOUBLE when allowed (two cards)
TEST_F(HumanPlayerTest, MakeDecisionDoubleWhenAllowed) {
    HumanPlayer p("Test");
    
    Hand hand(10.0);
    Card card1;
    card1.rank = Rank::NINE;
    hand.addCard(card1);
    
    Card card2;
    card2.rank = Rank::TWO;
    hand.addCard(card2);
    
    BlackjackRules rules;
    
    setInput("d");
    Action action = p.makeDecision(hand, rules);
    EXPECT_EQ(action, Action::DOUBLE);
}

// Test makeDecision with uppercase DOUBLE
TEST_F(HumanPlayerTest, MakeDecisionDoubleUppercase) {
    HumanPlayer p("Test");
    
    Hand hand(10.0);
    Card card1;
    card1.rank = Rank::NINE;
    hand.addCard(card1);
    
    Card card2;
    card2.rank = Rank::TWO;
    hand.addCard(card2);
    
    BlackjackRules rules;
    
    setInput("D");
    Action action = p.makeDecision(hand, rules);
    EXPECT_EQ(action, Action::DOUBLE);
}

// Test makeDecision with SPLIT when pair
TEST_F(HumanPlayerTest, MakeDecisionSplitWhenPair) {
    HumanPlayer p("Test");
    
    Hand hand(10.0);
    Card card1;
    card1.rank = Rank::EIGHT;
    hand.addCard(card1);
    
    Card card2;
    card2.rank = Rank::EIGHT;  // Pair
    hand.addCard(card2);
    
    BlackjackRules rules;
    
    setInput("t");
    Action action = p.makeDecision(hand, rules);
    EXPECT_EQ(action, Action::SPLIT);
}

// Test makeDecision with uppercase SPLIT
TEST_F(HumanPlayerTest, MakeDecisionSplitUppercase) {
    HumanPlayer p("Test");
    
    Hand hand(10.0);
    Card card1;
    card1.rank = Rank::EIGHT;
    hand.addCard(card1);
    
    Card card2;
    card2.rank = Rank::EIGHT;  // Pair
    hand.addCard(card2);
    
    BlackjackRules rules;
    
    setInput("T");
    Action action = p.makeDecision(hand, rules);
    EXPECT_EQ(action, Action::SPLIT);
}

// Test makeDecision with SURRENDER when allowed
TEST_F(HumanPlayerTest, MakeDecisionSurrenderWhenAllowed) {
    HumanPlayer p("Test");
    
    Hand hand(10.0);
    Card card1;
    card1.rank = Rank::TEN;
    hand.addCard(card1);
    
    Card card2;
    card2.rank = Rank::SIX;
    hand.addCard(card2);
    
    BlackjackRules rules;
    rules.surrenderAllowed = true;
    
    setInput("y");
    Action action = p.makeDecision(hand, rules);
    EXPECT_EQ(action, Action::SURRENDER);
}

// Test makeDecision with uppercase SURRENDER
TEST_F(HumanPlayerTest, MakeDecisionSurrenderUppercase) {
    HumanPlayer p("Test");
    
    Hand hand(10.0);
    Card card1;
    card1.rank = Rank::TEN;
    hand.addCard(card1);
    
    Card card2;
    card2.rank = Rank::SIX;
    hand.addCard(card2);
    
    BlackjackRules rules;
    rules.surrenderAllowed = true;
    
    setInput("Y");
    Action action = p.makeDecision(hand, rules);
    EXPECT_EQ(action, Action::SURRENDER);
}

// Test invalid input followed by valid input
TEST_F(HumanPlayerTest, InvalidInputThenValid) {
    HumanPlayer p("Test");
    
    Hand hand(10.0);
    Card card1;
    card1.rank = Rank::FIVE;
    hand.addCard(card1);
    
    Card card2;
    card2.rank = Rank::SIX;
    hand.addCard(card2);
    
    BlackjackRules rules;
    
    // Invalid input first, then valid
    setInput("x\nh");
    Action action = p.makeDecision(hand, rules);
    EXPECT_EQ(action, Action::HIT);
}

// Test that double is not available with more than two cards
TEST_F(HumanPlayerTest, DoubleNotAvailableWithThreeCards) {
    HumanPlayer p("Test");
    
    Hand hand(10.0);
    Card card1;
    card1.rank = Rank::FIVE;
    hand.addCard(card1);
    
    Card card2;
    card2.rank = Rank::THREE;
    hand.addCard(card2);
    
    Card card3;
    card3.rank = Rank::TWO;
    hand.addCard(card3);
    
    BlackjackRules rules;
    
    // Try to double with 3 cards - should fall through to invalid
    // Then provide valid hit
    setInput("d\nh");
    Action action = p.makeDecision(hand, rules);
    EXPECT_EQ(action, Action::HIT);
}

// Test that split is not available when not a pair
TEST_F(HumanPlayerTest, SplitNotAvailableWhenNotPair) {
    HumanPlayer p("Test");
    
    Hand hand(10.0);
    Card card1;
    card1.rank = Rank::NINE;
    hand.addCard(card1);
    
    Card card2;
    card2.rank = Rank::SEVEN;  // Not a pair
    hand.addCard(card2);
    
    BlackjackRules rules;
    
    // Try to split non-pair - should fall through to invalid
    // Then provide valid stand
    setInput("t\ns");
    Action action = p.makeDecision(hand, rules);
    EXPECT_EQ(action, Action::STAND);
}

// Test EOF handling - should return STAND
TEST_F(HumanPlayerTest, MakeDecisionOnEOFReturnsStand) {
    HumanPlayer p("Test");
    
    Hand hand(10.0);
    Card card1;
    card1.rank = Rank::FIVE;
    hand.addCard(card1);
    
    Card card2;
    card2.rank = Rank::SIX;
    hand.addCard(card2);
    
    BlackjackRules rules;
    
    // Empty input (EOF)
    setInput("");
    Action action = p.makeDecision(hand, rules);
    EXPECT_EQ(action, Action::STAND);
}

// Test case insensitivity
TEST_F(HumanPlayerTest, CaseInsensitivity) {
    HumanPlayer p("Test");
    
    Hand hand(10.0);
    Card card1;
    card1.rank = Rank::FIVE;
    hand.addCard(card1);
    
    Card card2;
    card2.rank = Rank::SIX;
    hand.addCard(card2);
    
    BlackjackRules rules;
    
    // Test all uppercase
    setInput("H");
    EXPECT_EQ(p.makeDecision(hand, rules), Action::HIT);
    
    // Create new hand for next test
    Hand hand2(10.0);
    hand2.addCard(card1);
    hand2.addCard(card2);
    
    setInput("S");
    EXPECT_EQ(p.makeDecision(hand2, rules), Action::STAND);
}

// Test with whitespace in input
TEST_F(HumanPlayerTest, WhitespaceHandling) {
    HumanPlayer p("Test");
    
    Hand hand(10.0);
    Card card1;
    card1.rank = Rank::FIVE;
    hand.addCard(card1);
    
    Card card2;
    card2.rank = Rank::SIX;
    hand.addCard(card2);
    
    BlackjackRules rules;
    
    // Input with leading whitespace
    setInput("   h");
    Action action = p.makeDecision(hand, rules);
    EXPECT_EQ(action, Action::HIT);
}