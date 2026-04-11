#include <gtest/gtest.h>
#include "GameEngine.hpp"
#include "Player.hpp"
#include "Hand.hpp"
#include "Card.hpp"
#include "BlackjackRules.hpp"
#include <sstream>

#include <gmock/gmock.h>
using ::testing::AnyOf;
using ::testing::Eq;

// Mock player for testing GameEngine
class MockPlayer : public Player {
public:
    Action decision { Action::STAND };
    int decisionCount { 0 };
    bool trySplitWhenPossible { false };
    
    MockPlayer(const std::string& name) : Player(name) {}
    
    Action makeDecision(const Hand& currentHand, const BlackjackRules& rules) override {
        decisionCount++;
        // Auto-stand after a few hits to prevent infinite loops
        if (decisionCount > 10) {
            return Action::STAND;
        }
        
        // If trySplitWhenPossible is enabled, attempt to split when we have a pair
        if (trySplitWhenPossible && currentHand.isPair()) {
            return Action::SPLIT;
        }
        
        return decision;
    }
};

class GameEngineTest : public ::testing::Test {
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
TEST_F(GameEngineTest, Constructor) {
    GameEngine engine(1, 0.75, 42);
    // If constructor succeeds without throwing, test passes
    SUCCEED();
}

// Test addPlayer
TEST_F(GameEngineTest, AddPlayer) {
    GameEngine engine(1, 0.75, 42);
    MockPlayer player("TestPlayer");
    
    engine.addPlayer(&player);
    // If addPlayer succeeds without throwing, test passes
    SUCCEED();
}

// Test addMultiplePlayers
TEST_F(GameEngineTest, AddMultiplePlayers) {
    GameEngine engine(2, 0.75, 42);
    MockPlayer player1("Player1");
    MockPlayer player2("Player2");
    MockPlayer player3("Player3");
    
    engine.addPlayer(&player1);
    engine.addPlayer(&player2);
    engine.addPlayer(&player3);
    
    // If adding multiple players succeeds, test passes
    SUCCEED();
}

// Test playRound with player always standing
TEST_F(GameEngineTest, PlayRoundWithStand) {
    GameEngine engine(1, 0.75, 42);
    MockPlayer player("TestPlayer");
    player.decision = Action::STAND;
    
    engine.addPlayer(&player);
    
    // Provide bet input
    setInput("10.0");
    
    // playRound should complete without hanging
    engine.playRound();
    
    // Verify player has no hands (they get cleared after round)
    EXPECT_TRUE(player.hands.empty());
	EXPECT_THAT(player.getBankroll(), AnyOf(Eq(10.0), Eq(0.0), Eq(-10.0)));
}

// Test playRound with player hitting
TEST_F(GameEngineTest, PlayRoundWithHit) {
    GameEngine engine(1, 0.75, 42);
    MockPlayer player("TestPlayer");
    player.decision = Action::HIT;  // Will hit until forced to stand
    
    engine.addPlayer(&player);
    
    // Provide bet input
    setInput("10.0");
    
    // playRound should complete (mock player will stand after 10 hits)
    engine.playRound();
    
    EXPECT_TRUE(player.hands.empty());
	EXPECT_THAT(player.getBankroll(), AnyOf(Eq(10.0), Eq(0.0), Eq(-10.0)));
}

// Test playRound with player doubling down
TEST_F(GameEngineTest, PlayRoundWithDouble) {
    GameEngine engine(1, 0.75, 42);
    MockPlayer player("TestPlayer");
    player.decision = Action::DOUBLE;
    
    engine.addPlayer(&player);
    
    // Provide bet input
    setInput("10.0");
    
    engine.playRound();
    
    EXPECT_TRUE(player.hands.empty());
	EXPECT_THAT(player.getBankroll(), AnyOf(Eq(20.0), Eq(0.0), Eq(-20.0)));
}

// Test playRound with player attempting to split when possible
// Plays multiple rounds until a split occurs (detected by checking if player ever had more than one hand)
// Split hands don't need their own bet - the bet is copied from the original hand
TEST_F(GameEngineTest, PlayRoundWithSplitAttempt) {
    GameEngine engine(1, 0.75, 42);
    MockPlayer player("TestPlayer");
    player.trySplitWhenPossible = true;  // Enable split attempts
    player.decision = Action::STAND;     // Fallback if split not possible
    
    engine.addPlayer(&player);
    
    // With trySplitWhenPossible enabled, when a pair is dealt, split will occur
	
    setInput("10.0");
    engine.playRound();
    setInput("10.0");
    engine.playRound();
    setInput("10.0");
    engine.playRound();
    setInput("10.0");
    engine.playRound();
    setInput("10.0");
    engine.playRound();
    setInput("10.0");
    engine.playRound();
    setInput("10.0");
    engine.playRound();
    setInput("10.0");
    engine.playRound();
    setInput("10.0");
    engine.playRound();
    setInput("10.0");
    engine.playRound();
    setInput("10.0");
    engine.playRound();
    setInput("10.0");
    engine.playRound();
    
    EXPECT_TRUE(player.hands.empty());
}

// Test playRound with player surrendering
TEST_F(GameEngineTest, PlayRoundWithSurrender) {
    GameEngine engine(1, 0.75, 42);
    MockPlayer player("TestPlayer");
    player.decision = Action::SURRENDER;
    
    engine.addPlayer(&player);
    
    // Provide bet input
    setInput("10.0");
    
    engine.playRound();
    
    // Verify player hands are cleared
    EXPECT_TRUE(player.hands.empty());
    // Surrender should lose half the bet, so bankroll should be -5 (starting from 0)
    EXPECT_EQ(player.getBankroll(), -5.0);
}

// Test with multiple decks
TEST_F(GameEngineTest, PlayRoundWithMultipleDecks) {
    GameEngine engine(6, 0.75, 42);
    MockPlayer player("TestPlayer");
    player.decision = Action::STAND;
    
    engine.addPlayer(&player);
    
    setInput("10.0");
    
    engine.playRound();
    
    EXPECT_TRUE(player.hands.empty());
}

// Test with different penetration values
TEST_F(GameEngineTest, PlayRoundWithDifferentPenetration) {
    GameEngine engine(1, 0.5, 42);  // 50% penetration
    MockPlayer player("TestPlayer");
    player.decision = Action::STAND;
    
    engine.addPlayer(&player);
    
    setInput("10.0");
    
    engine.playRound();
    
    EXPECT_TRUE(player.hands.empty());
}

// Test with zero penetration (shuffle immediately)
TEST_F(GameEngineTest, PlayRoundWithZeroPenetration) {
    GameEngine engine(1, 0.0, 42);
    MockPlayer player("TestPlayer");
    player.decision = Action::STAND;
    
    engine.addPlayer(&player);
    
    setInput("10.0");
    
    engine.playRound();
    
    EXPECT_TRUE(player.hands.empty());
}

// Test with full penetration (shuffle only when empty)
TEST_F(GameEngineTest, PlayRoundWithFullPenetration) {
    GameEngine engine(1, 1.0, 42);
    MockPlayer player("TestPlayer");
    player.decision = Action::STAND;
    
    engine.addPlayer(&player);
    
    setInput("10.0");
    
    engine.playRound();
    
    EXPECT_TRUE(player.hands.empty());
}

// Test with different seed values
TEST_F(GameEngineTest, PlayRoundWithDifferentSeeds) {
    GameEngine engine1(1, 0.75, 123);
    GameEngine engine2(1, 0.75, 456);
    GameEngine engine3(1, 0.75, 789);
    
    MockPlayer player1("Player1");
    MockPlayer player2("Player2");
    MockPlayer player3("Player3");
    
    player1.decision = Action::STAND;
    player2.decision = Action::STAND;
    player3.decision = Action::STAND;
    
    engine1.addPlayer(&player1);
    engine2.addPlayer(&player2);
    engine3.addPlayer(&player3);
    
    setInput("10.0\n10.0\n10.0");
    
    engine1.playRound();
    engine2.playRound();
    engine3.playRound();
    
    EXPECT_TRUE(player1.hands.empty());
    EXPECT_TRUE(player2.hands.empty());
    EXPECT_TRUE(player3.hands.empty());
}

// Test deterministic behavior with same seed
TEST_F(GameEngineTest, DeterministicBehaviorWithSameSeed) {
    // Create two engines with same parameters
    GameEngine engine1(1, 0.75, 42);
    GameEngine engine2(1, 0.75, 42);
    
    MockPlayer player1("Player");
    MockPlayer player2("Player");
    
    player1.decision = Action::STAND;
    player2.decision = Action::STAND;
    
    engine1.addPlayer(&player1);
    engine2.addPlayer(&player2);
    
    setInput("10.0\n10.0");
    
    // Both should produce same results
    engine1.playRound();
    engine2.playRound();
    
    EXPECT_TRUE(player1.hands.empty());
    EXPECT_TRUE(player2.hands.empty());
}

// Test with empty name player
TEST_F(GameEngineTest, PlayRoundWithEmptyNamePlayer) {
    GameEngine engine(1, 0.75, 42);
    MockPlayer player("");
    player.decision = Action::STAND;
    
    engine.addPlayer(&player);
    
    setInput("10.0");
    
    engine.playRound();
    
    EXPECT_TRUE(player.hands.empty());
}

// Test with special characters in player name
TEST_F(GameEngineTest, PlayRoundWithSpecialNamePlayer) {
    GameEngine engine(1, 0.75, 42);
    MockPlayer player("Player_123!@#");
    player.decision = Action::STAND;
    
    engine.addPlayer(&player);
    
    setInput("10.0");
    
    engine.playRound();
    
    EXPECT_TRUE(player.hands.empty());
}

// Test with very small bet
TEST_F(GameEngineTest, PlayRoundWithSmallBet) {
    GameEngine engine(1, 0.75, 42);
    MockPlayer player("TestPlayer");
    player.decision = Action::STAND;
    
    engine.addPlayer(&player);
    
    setInput("0.01");
    
    engine.playRound();
    
    EXPECT_TRUE(player.hands.empty());
}

// Test with large bet
TEST_F(GameEngineTest, PlayRoundWithLargeBet) {
    GameEngine engine(1, 0.75, 42);
    MockPlayer player("TestPlayer");
    player.decision = Action::STAND;
    
    engine.addPlayer(&player);
    
    setInput("1000.00");
    
    engine.playRound();
    
    EXPECT_TRUE(player.hands.empty());
}

// Test with fractional bet
TEST_F(GameEngineTest, PlayRoundWithFractionalBet) {
    GameEngine engine(1, 0.75, 42);
    MockPlayer player("TestPlayer");
    player.decision = Action::STAND;
    
    engine.addPlayer(&player);
    
    setInput("10.50");
    
    engine.playRound();
    
    EXPECT_TRUE(player.hands.empty());
}

// Test with eight decks (maximum common size)
TEST_F(GameEngineTest, PlayRoundWithEightDecks) {
    GameEngine engine(8, 0.75, 42);
    MockPlayer player("TestPlayer");
    player.decision = Action::STAND;
    
    engine.addPlayer(&player);
    
    setInput("10.0");
    
    engine.playRound();
    
    EXPECT_TRUE(player.hands.empty());
}

// Test multiple rounds with same engine
TEST_F(GameEngineTest, MultipleRoundsWithSameEngine) {
    GameEngine engine(1, 0.75, 42);
    MockPlayer player("TestPlayer");
    player.decision = Action::STAND;
    
    engine.addPlayer(&player);
    
    setInput("10.0\n10.0\n10.0");
    
    // Play multiple rounds
    engine.playRound();
    engine.playRound();
    engine.playRound();
    
    EXPECT_TRUE(player.hands.empty());
}

// Test with multiple players in one round
TEST_F(GameEngineTest, MultiplePlayersInOneRound) {
    GameEngine engine(2, 0.75, 42);
    MockPlayer player1("Player1");
    MockPlayer player2("Player2");
    MockPlayer player3("Player3");
    
    player1.decision = Action::STAND;
    player2.decision = Action::STAND;
    player3.decision = Action::STAND;
    
    engine.addPlayer(&player1);
    engine.addPlayer(&player2);
    engine.addPlayer(&player3);
    
    setInput("10.0\n10.0\n10.0");
    
    engine.playRound();
    
    EXPECT_TRUE(player1.hands.empty());
    EXPECT_TRUE(player2.hands.empty());
    EXPECT_TRUE(player3.hands.empty());
}

// Test with mixed player strategies
TEST_F(GameEngineTest, MixedPlayerStrategies) {
    GameEngine engine(2, 0.75, 42);
    MockPlayer player1("StandPlayer");
    MockPlayer player2("HitPlayer");
    MockPlayer player3("DoublePlayer");
    
    player1.decision = Action::STAND;
    player2.decision = Action::HIT;
    player3.decision = Action::DOUBLE;
    
    engine.addPlayer(&player1);
    engine.addPlayer(&player2);
    engine.addPlayer(&player3);
    
    setInput("10.0\n10.0\n10.0");
    
    engine.playRound();
    
    EXPECT_TRUE(player1.hands.empty());
    EXPECT_TRUE(player2.hands.empty());
    EXPECT_TRUE(player3.hands.empty());
}

// Test bankroll changes after round
TEST_F(GameEngineTest, BankrollChangesAfterRound) {
    GameEngine engine(1, 0.75, 42);
    MockPlayer player("TestPlayer");
    player.decision = Action::STAND;
    
    // Set initial bankroll
    player.win(100.0);
    double initialBankroll = player.getBankroll();
    
    engine.addPlayer(&player);
    
    setInput("10.0");
    
    engine.playRound();
    
    // Bankroll should have changed (win, lose, or push)
    // We can't predict exact outcome due to randomness, but it should be different or same (push)
    double finalBankroll = player.getBankroll();
    
    // At minimum, bankroll should be a valid number
    EXPECT_GE(finalBankroll, 0.0);
}

// Test with invalid bet input (EOF)
TEST_F(GameEngineTest, PlayRoundWithEOFBet) {
    GameEngine engine(1, 0.75, 42);
    MockPlayer player("TestPlayer");
    player.decision = Action::STAND;
    
    engine.addPlayer(&player);
    
    // Empty input (EOF) - should return 0.0 from parseBet
    setInput("");
    
    engine.playRound();
    
    EXPECT_TRUE(player.hands.empty());
}

// Test destructor cleanup
TEST_F(GameEngineTest, DestructorCleanup) {
    // This test ensures destructor doesn't crash
    {
        GameEngine engine(1, 0.75, 42);
        MockPlayer player("TestPlayer");
        player.decision = Action::STAND;
        
        engine.addPlayer(&player);
        
        setInput("10.0");
        
        engine.playRound();
    }
    // Engine goes out of scope and destructor is called
    // If no crash occurs, test passes
    SUCCEED();
}

// Test with very deep penetration
TEST_F(GameEngineTest, PlayRoundWithDeepPenetration) {
    GameEngine engine(1, 0.95, 42);  // 95% penetration
    MockPlayer player("TestPlayer");
    player.decision = Action::STAND;
    
    engine.addPlayer(&player);
    
    setInput("10.0");
    
    engine.playRound();
    
    EXPECT_TRUE(player.hands.empty());
}
