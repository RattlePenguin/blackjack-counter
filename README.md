# Blackjack Advantage Trainer

A C++ based blackjack trainer designed to teach advantage play techniques including card counting (Hi-Lo method) and basic strategy with deviations.

## Overview

This project simulates a realistic blackjack environment to help users practice and master advantage blackjack techniques.
The trainer focuses on teaching the Hi-Lo counting method and basic strategy to give players a mathematical edge over the house.

In a classic game of Blackjack, playing perfect basic strategy reduces the house edge to 0.5\%.
Counting cards is required to tip advantage over to the player instead.

## Key Features

- **Full Blackjack Simulation**: Complete game with standard rules
- **Hi-Lo Card Counting**: Track running and true counts
- **Interactive Gameplay**: Make real-time decisions (Hit, Stand, Double, Split, Surrender)
- **Bankroll Management**: Track your profit/loss over sessions
- **Configurable Rules**: Adjustable deck count, penetration, and game rules
- **Educational Focus**: Learn advantage play techniques

## Prerequisites

- **C++17 compatible compiler** (GCC 7+, Clang 5+, MSVC 2019+)
- **Make** or **CMake** for building
- **GoogleTest** (optional, for running unit tests)

## Development Setup

### LSP/Editor Support

For optimal development experience with clangd, clang-format, or other LSP tools:

```bash
# Create build directory and generate compile commands
mkdir build
cd build
cmake ..

# Return to project root
cd ..
```

The `.clangd` configuration file automatically points to the `build/` directory for compile commands, enabling:
- Autocomplete and go-to-definition
- Real-time syntax checking
- Code formatting with clang-format
- Static analysis and error detection

## 🛠️ Installation

### Clone the Repository

```bash
git clone git@github.com:RattlePenguin/blackjack-counter.git
cd blackjack-counter
```

### Build with Make

```bash
make clean    # Clean previous builds
make          # Build the project
```

### Build with CMake

```bash
mkdir build
cd build
cmake ..
make
```

## Usage

### Running the Game

After building, run the executable:

```bash
./blackjack_trainer
```

### Gameplay Commands

During your turn, you'll be presented with options:

| Command | Action | Description |
|---------|--------|-------------|
| `h` | Hit | Request another card |
| `s` | Stand | End your turn |
| `d` | Double Down | Double your bet and receive one more card (available on first two cards) |
| `t` | Split | Split a pair into two separate hands (available when dealt a pair) |
| `y` | Surrender | Forfeit half your bet (available on first two cards) |

### Example Session

```
========================================
  Blackjack Advantage Trainer - v0.1
========================================

Shoe has shuffled 2 decks.

--- Round 1 ---
Enter your bet: 10

[Dealer] Hand: 4 [XX]
CardCounter99 Hands: 6 10

--- CardCounter99 TURN ---
[Dealer] Hand: 4 [XX]
Your Hand: 6 10
h: hit
s: stand
d: double down
y: surrender
> s
---> STAND

[Dealer] Hand: 4 10
---> [Dealer] HITS
[Dealer] Hand: 4 10 5
---> [Dealer] STANDS

---> CardCounter99 results
Hand: 6 10
Lost 10

Play another round? (Y/N):
```

## Hi-Lo Counting Method

The Hi-Lo system assigns values to cards:
- **2-6**: +1 (Low cards)
- **7-9**: 0 (Neutral cards)
- **10-A**: -1 (High cards)

**Running Count (RC)**: The cumulative total of card values dealt.

**True Count (TC)**: Running count divided by remaining decks. This normalizes the count for multi-deck games.

Example:
```
Cards dealt: K, 10, 3, 6, 2, 7, 7, A, J, A
RC = -1 -1 +1 +1 +1 +0 +0 -1 -1 -1 = -2
```

## Basic Strategy

Basic strategy provides the mathematically optimal play for every hand combination.
Following basic strategy reduces the house edge to approximately 0.5\%.

**Key Principles:**
- Always hit on 8 or less
- Stand on 17 or more (unless soft)
- Double down on 11 against dealer 2-10
- Split Aces and 8s
- Never split 10s or 5s

### Strategy Deviations

When the true count is high (more high cards remaining), adjust your strategy:
- Stand on hands you would normally hit
- Take insurance when TC is high
- Increase bet size as advantage increases

## Game Configuration

The game uses these default settings (configurable in code):

| Setting | Default | Description |
|---------|---------|-------------|
| Decks | 2 | Number of decks in the shoe |
| Penetration | 75% | How deep into the shoe before reshuffle |
| Hit Soft 17 | Yes | Dealer hits on soft 17 |
| Double After Split | Yes | Can double after splitting |
| Resplit Aces | No | Cannot re-split aces |
| Surrender | Yes | Late surrender allowed |
| Blackjack Payout | 3:2 | Standard 1.5x payout |

## Project Structure

```
blackjack-counter/
├── include/              # Header files
│   ├── BlackjackRules.hpp
│   ├── Card.hpp
│   ├── GameEngine.hpp
│   ├── Hand.hpp
│   ├── HumanPlayer.hpp
│   ├── Player.hpp
│   └── Shoe.hpp
├── src/                  # Source files
│   ├── Card.cpp
│   ├── GameEngine.cpp
│   ├── Hand.cpp
│   ├── HumanPlayer.cpp
│   ├── Player.cpp
│   └── Shoe.cpp
├── tests/               # GoogleTest files
│   └── unit/
├── CMakeLists.txt       # CMake configuration
├── Makefile            # Make configuration
├── main.cpp            # Entry point
└── README.md           # This file
```

## Testing

### Running Unit Tests

If you have GoogleTest installed:

```bash
# Build tests
mkdir build && cd build
cmake ..
make tests

# Run tests
./tests/blackjack_tests
```

### Test Coverage (WIP)

The test suite covers:
- Card value calculations (Hi-Lo)
- Hand value computation (including soft/hard hands)
- Blackjack detection
- Bust detection
- Split and double down mechanics
- Shoe shuffling and card counting

## Known Issues

- Input handling may have edge cases with piped input
- Dealer may incorrectly play after all players bust
- Some formatting inconsistencies in output

## Additional Resources

- [Blackjack Apprenticeship](https://www.blackjackapprenticeship.com/) - Comprehensive training resources
- [Wizard of Odds - Blackjack](https://wizardofodds.com/games/blackjack/) - Mathematical analysis
- [Basic Strategy Charts](https://www.blackjackapprenticeship.com/blackjack-strategy-charts/)
- [Hi-Lo Deviation Charts](https://www.blackjackapprenticeship.com/wp-content/uploads/2019/07/BJA_H17.pdf)

