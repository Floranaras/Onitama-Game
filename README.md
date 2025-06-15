# Onitama Game

A C implementation of the two-player turn-based strategy game Onitama for CCPROG2 Project.

## Game Description

Onitama is a strategic board game where each player controls five pieces (one sensei and four students). The objective is to either capture the opponent's sensei or navigate your own sensei to occupy the opponent's base.

### Game Components
- 5x5 game board
- 2 sensei pieces (one per player)
- 8 student pieces (four per player)
- 16 move cards with unique movement patterns

### Win Conditions
1. **Capture Victory**: Capture the opponent's sensei
2. **Base Victory**: Move your sensei to the opponent's base

## Getting Started

### Prerequisites
- GCC compiler (C99 standard)
- DEV-C++ IDE (recommended for development)
- Command line interface

### Installation

1. Clone or download the project files
2. Ensure all move card files (.txt) are in the same directory
3. Compile using the provided Makefile

## Features

### Core Features
- Menu-driven interface
- Two-player gameplay
- Move card system with 16 unique cards
- Card shuffling and rotation
- Piece movement validation
- Win condition detection
- Game state display

### Bonus Features
- **Replay System**: Watch a replay of completed games
- **Hall of Fame**: Track top 10 players by move efficiency

## How to Play

### Setup
1. Each player chooses red or blue pieces
2. Place sensei at the base, students on the same row beside the sensei
3. Shuffle and distribute move cards (2 per player, 1 extra)
4. The player color indicated on the extra card goes first

### Gameplay
1. Choose one of your two move cards
2. Select a piece to move
3. Choose a valid destination based on the card's movement pattern
4. The used card goes to the side, and you take the card from the opposite side
5. Continue until someone wins

### Move Cards
Each move card shows possible movements relative to the piece's current position:
- `X` marks the piece's current position
- `x` marks valid destination squares

### Commit Conventions

Follow these conventional commit types for consistent version control:

| Type | Purpose | Example |
|------|---------|---------|
| `feat` | Add a new feature (functions, logic) | `feat: implement move validation system` |
| `fix` | Fix a bug (incorrect output, logic errors) | `fix: resolve card rotation logic error` |
| `refactor` | Improve code without changing behavior | `refactor: optimize board display function` |
| `perf` | Optimize performance (faster loops, better memory usage) | `perf: improve game state rendering speed` |
| `style` | Formatting changes (indentation, comments) | `style: fix code indentation and spacing` |
| `test` | Add or update test cases | `test: add boundary tests for piece movement` |
| `build` | Modify Makefile or compilation setup | `build: update compiler flags in Makefile` |
| `docs` | Update README, specs, or comments | `docs: add installation instructions` |
| `chore` | Non-code maintenance (renaming files, updating .gitignore) | `chore: organize move card files` |

**Example commit messages:**
```bash
git commit -m "feat: add sensei capture detection"
git commit -m "fix: prevent invalid moves outside board boundaries"
git commit -m "docs: update README with gameplay instructions"
git commit -m "test: add move card loading validation tests"
```

### Code Standards
- C99 standard compliance
- Proper use of arrays, strings, structures, and functions
- Comprehensive commenting and documentation
- No global variables or prohibited constructs

### Testing
Run the test script to verify functionality:
- Minimum 3 test cases per function
- Black box and white box testing
- Input validation and edge cases

### File Formats

**Move Card Format** (example: Rabbit.txt):
```
red
.....
...x.
..X.x
.x...
.....
```

**Move Cards List** (movecards.txt):
```
16
Boar
Crab
Crane
...
```

## Requirements

### Technical Requirements
- Implemented in C (C99 standard)
- Menu-driven interface (no yes/no prompts)
- File I/O for move cards
- Proper memory management
- Error handling and validation

