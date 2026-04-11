#include <gtest/gtest.h>
#include "Player.hpp"
#include "Hand.hpp"
#include "Card.hpp"
#include "BlackjackRules.hpp"

// Concrete implementation of Player for testing (since Player is abstract)
class TestPlayer : public Player {
public:
    TestPlayer(const std::string& name) : Player(name) {}
    
    Action makeDecision(const Hand& currentHand, const BlackjackRules& rules) override {
        return Action::STAND;  // Default action for testing
    }
};

class PlayerTest : public ::testing::Test {
protected:
    void SetUp() override {
        player = std::make_unique<TestPlayer>("TestPlayer");
    }
    
    std::unique_ptr<TestPlayer> player;
};

// Test constructor and name
TEST_F(PlayerTest, ConstructorAndName) {
    TestPlayer p("Alice");
    EXPECT_EQ(p.getName(), "Alice");
    
    TestPlayer p2("Bob");
    EXPECT_EQ(p2.getName(), "Bob");
}

// Test default bankroll
TEST_F(PlayerTest, DefaultBankroll) {
    TestPlayer p("Test");
    EXPECT_EQ(p.getBankroll(), 0.0);
}

// Test win() method
TEST_F(PlayerTest, WinIncreasesBankroll) {
    TestPlayer p("Test");
    EXPECT_EQ(p.getBankroll(), 0.0);
    
    p.win(100.0);
    EXPECT_EQ(p.getBankroll(), 100.0);
    
    p.win(50.0);
    EXPECT_EQ(p.getBankroll(), 150.0);
    
    p.win(25.50);
    EXPECT_EQ(p.getBankroll(), 175.50);
}

// Test lose() method
TEST_F(PlayerTest, LoseDecreasesBankroll) {
    TestPlayer p("Test");
    p.win(100.0);  // Start with some bankroll
    EXPECT_EQ(p.getBankroll(), 100.0);
    
    p.lose(30.0);
    EXPECT_EQ(p.getBankroll(), 70.0);
    
    p.lose(20.0);
    EXPECT_EQ(p.getBankroll(), 50.0);
}

// Test negative bankroll (can go into debt)
TEST_F(PlayerTest, CanGoIntoDebt) {
    TestPlayer p("Test");
    EXPECT_EQ(p.getBankroll(), 0.0);
    
    p.lose(50.0);
    EXPECT_EQ(p.getBankroll(), -50.0);
}

// Test clearHands()
TEST_F(PlayerTest, ClearHandsRemovesAllHands) {
    TestPlayer p("Test");
    
    // Add some hands
    p.startNewHand(10.0);
    p.startNewHand(20.0);
    p.startNewHand(30.0);
    
    EXPECT_EQ(p.hands.size(), 3);
    
    p.clearHands();
    EXPECT_EQ(p.hands.size(), 0);
}

// Test startNewHand()
TEST_F(PlayerTest, StartNewHandCreatesHand) {
    TestPlayer p("Test");
    EXPECT_EQ(p.hands.size(), 0);
    
    Hand h1 = p.startNewHand(10.0);
    EXPECT_EQ(p.hands.size(), 1);
    EXPECT_EQ(h1.getBet(), 10.0);
    
    Hand h2 = p.startNewHand(25.0);
    EXPECT_EQ(p.hands.size(), 2);
    EXPECT_EQ(h2.getBet(), 25.0);
}

// Test startNewHand returns correct bet
TEST_F(PlayerTest, StartNewHandBetAmount) {
    TestPlayer p("Test");
    
    Hand h1 = p.startNewHand(50.0);
    EXPECT_EQ(h1.getBet(), 50.0);
    
    Hand h2 = p.startNewHand(100.0);
    EXPECT_EQ(h2.getBet(), 100.0);
    
    Hand h3 = p.startNewHand(0.50);
    EXPECT_EQ(h3.getBet(), 0.50);
}

// Test multiple hands management
TEST_F(PlayerTest, MultipleHandsManagement) {
    TestPlayer p("Test");
    
    // Create multiple hands (simulating split)
    Hand h1 = p.startNewHand(10.0);
    Hand h2 = p.startNewHand(10.0);
    
    EXPECT_EQ(p.hands.size(), 2);
    EXPECT_EQ(p.hands[0].getBet(), 10.0);
    EXPECT_EQ(p.hands[1].getBet(), 10.0);
    
    // Clear and verify
    p.clearHands();
    EXPECT_EQ(p.hands.size(), 0);
}

// Test win and lose combinations
TEST_F(PlayerTest, WinAndLoseCombinations) {
    TestPlayer p("Test");
    
    p.win(100.0);
    EXPECT_EQ(p.getBankroll(), 100.0);
    
    p.lose(30.0);
    EXPECT_EQ(p.getBankroll(), 70.0);
    
    p.win(50.0);
    EXPECT_EQ(p.getBankroll(), 120.0);
    
    p.lose(120.0);
    EXPECT_EQ(p.getBankroll(), 0.0);
}

// Test fractional bankroll amounts
TEST_F(PlayerTest, FractionalBankroll) {
    TestPlayer p("Test");
    
    p.win(99.99);
    EXPECT_EQ(p.getBankroll(), 99.99);
    
    p.lose(0.99);
    EXPECT_EQ(p.getBankroll(), 99.00);
}

// Test that hands vector is initially empty
TEST_F(PlayerTest, HandsInitiallyEmpty) {
    TestPlayer p("Test");
    EXPECT_TRUE(p.hands.empty());
}

// Test makeDecision is called (via polymorphism)
TEST_F(PlayerTest, MakeDecisionCalled) {
    // This test verifies that the polymorphic method works
    TestPlayer p("Test");
    
    // Create a simple hand for testing
    Hand hand(10.0);
    Card ace;
    ace.rank = Rank::ACE;
    hand.addCard(ace);
    
    Card ten;
    ten.rank = Rank::TEN;
    hand.addCard(ten);
    
    // Create minimal rules for testing
    BlackjackRules rules {};
    
    // Call makeDecision - should return STAND (our default implementation)
    Action action = p.makeDecision(hand, rules);
    EXPECT_EQ(action, Action::STAND);
}

// Test player with empty name
TEST_F(PlayerTest, EmptyName) {
    TestPlayer p("");
    EXPECT_EQ(p.getName(), "");
}

// Test player with special characters in name
TEST_F(PlayerTest, SpecialCharactersInName) {
    TestPlayer p("Player 123!@#");
    EXPECT_EQ(p.getName(), "Player 123!@#");
}

// Test bankroll precision
TEST_F(PlayerTest, BankrollPrecision) {
    TestPlayer p("Test");
    
    p.win(100.123456);
    // Floating point comparison with tolerance
    EXPECT_NEAR(p.getBankroll(), 100.123456, 0.000001);
    
    p.lose(0.123456);
    EXPECT_NEAR(p.getBankroll(), 100.0, 0.000001);
}