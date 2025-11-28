# Onitama Game

A complete C implementation of the two-player turn-based strategy game Onitama featuring comprehensive testing and cross-platform build support.

## Game Description

Onitama is a strategic board game where each player controls five pieces (one master and four students). The objective is to either capture the opponent's master or navigate your own master to occupy the opponent's temple.

### Game Components
- 5×5 game board with temple positions
- 2 master pieces (Red 'R' and Blue 'B') 
- 8 student pieces (red 'r' and blue 'b')
- Movement cards with unique patterns
- Neutral card system for turn determination

### Win Conditions
1. **Master Capture**: Capture the opponent's master piece
2. **Temple Victory**: Move your master to the opponent's temple (center of opposite side)
   - Blue wins by reaching (0,2) - Red temple
   - Red wins by reaching (4,2) - Blue temple

## Project Structure

```
Onitama-Game/
├── check.c              # Move validation and game logic
├── data/                # Move card data files
│   ├── movecards.txt    # Master list of available cards
│   ├── Boar.txt         # Individual card movement patterns
│   ├── Cobra.txt        # (16 total card files)
│   ├── Crab.txt
│   ├── Crane.txt
│   ├── Dragon.txt
│   ├── Eel.txt
│   ├── Elephant.txt
│   ├── Frog.txt
│   ├── Goose.txt
│   ├── Horse.txt
│   ├── Mantis.txt
│   ├── Monkey.txt
│   ├── Ox.txt
│   ├── Rabbit.txt
│   ├── Rooster.txt
│   └── Tiger.txt
├── display.c            # Display and UI functions  
├── game.c               # Core game mechanics and loop
├── load.c               # Card loading and file parsing
├── main.c               # Program entry point
├── menu.c               # Main menu system
├── onitama.h            # Main header with all definitions
├── start.c              # Board setup and initialization
├── testmain.c           # Comprehensive test suite
├── Makefile             # Build automation
├── README.md            # This documentation
```

## Requirements

### All Platforms
- GCC compiler with C99 support
- Standard C library
- Terminal/Command prompt

### Build Tools
- **Make utility** (recommended)
- **Manual compilation** (alternative if Make unavailable)

## Compilation Guide

### Option 1: Using Makefile (Recommended)

#### Available Commands
```bash
make           # Build the main game executable
make run       # Build and run the game
make test      # Build and run comprehensive test suite
make clean     # Remove compiled executables
make help      # Show all available commands
```

#### Quick Start
```bash
# Build and play the game
make run

# Run comprehensive tests
make test

# Clean build artifacts
make clean
```

### Option 2: Manual Compilation

#### Compile Main Game
```bash
# Linux/macOS/WSL
gcc -Wall -std=c99 -o onitama main.c

# Windows
gcc -Wall -std=c99 -o onitama.exe main.c
```

#### Compile Test Suite
```bash
# Linux/macOS/WSL
gcc -Wall -std=c99 -o test_onitama testmain.c

# Windows
gcc -Wall -std=c99 -o test_onitama.exe testmain.c
```

#### Run Programs
```bash
# Linux/macOS/WSL
./onitama           # Run main game
./test_onitama      # Run test suite

# Windows
onitama.exe         # Run main game
test_onitama.exe    # Run test suite
```

### Platform-Specific Setup

#### Windows
```cmd
# Using Command Prompt
gcc -Wall -std=c99 -o onitama.exe main.c
onitama.exe

# Using Git Bash (if available)
make run
```

#### Linux
```bash
# Install GCC if needed (Ubuntu/Debian)
sudo apt update
sudo apt install build-essential

# Compile and run
gcc -Wall -std=c99 -o onitama main.c
./onitama
```

#### macOS
```bash
# Install Xcode command line tools if needed
xcode-select --install

# Compile and run
gcc -Wall -std=c99 -o onitama main.c
./onitama
```

## Game Data Files

The game requires a `data/` directory with card definition files.

### Required Files Structure
- `data/movecards.txt` - Master list containing names of 16 cards
- `data/[CardName].txt` - Individual card pattern files (16 files total)

### Card File Format
Each card file contains:
```
[color]     # "blue" or "red" (starting player for this card)
[pattern]   # 5×5 grid with:
            # 'X' = piece position (center)
            # 'x' = valid move destination
            # '.' = empty/invalid position
```

**Example** (`data/Crane.txt`):
```
blue
.....
..x..
..X..
.x.x.
.....
```

### Master Card List (`data/movecards.txt`):
```
16
Boar
Cobra
Crab
Crane
Dragon
Eel
Elephant
Frog
Goose
Horse
Mantis
Monkey
Ox
Rabbit
Rooster
Tiger
```

## Testing the Implementation

### Running the Test Suite

#### Using Makefile
```bash
make test
```

#### Manual Testing
```bash
# Compile test suite
gcc -Wall -std=c99 -o test_onitama testmain.c

# Run tests
./test_onitama          # Linux/macOS
test_onitama.exe        # Windows
```

### Test Coverage

The test suite in `testmain.c` validates comprehensive functionality across multiple categories:

#### Core Game Functions
1. **Master List Loading** - File parsing and card name loading
2. **Card Pattern Loading** - Individual card file parsing  
3. **Move Calculations** - Blue/Red move pattern generation
4. **Board Initialization** - Starting piece placement
5. **Card Dealing** - Random card distribution and uniqueness
6. **Display Functions** - UI and board rendering
7. **Basic Game Logic** - Piece ownership and range validation
8. **Win Conditions** - Temple capture and sensei elimination
9. **Card Operations** - Card swapping and existence checking
10. **Movement Functions** - Piece movement and temple handling

#### Advanced Testing
11. **Pattern Following** - Move pattern validation against cards
12. **Complete Move Validation** - Multi-condition move checking
13. **Move Discovery** - Finding available moves for pieces
14. **Player Mobility** - Detecting if players have valid moves
15. **Temple Recognition** - Temple position validation
16. **Complete Win Logic** - Integrated win condition checking
17. **Edge Cases** - Boundary conditions and error scenarios
18. **Card Dealing Edge Cases** - Randomization and uniqueness validation
19. **Complete Game Flow** - End-to-end initialization testing

### Test Output
```
=== ONITAMA COMPREHENSIVE TESTING ===

1. Testing Master List Loading...
PASS

2. Testing Card Loading...
===Crane Card===
Color: BLUE
===Card PATTERN===
...

=== TESTING COMPLETE ===
Total test categories: 19
```

## How to Play

### Game Setup
1. Run the game: `./onitama` or `make run`
2. Enter player names for Blue and Red players
3. Cards are shuffled and dealt (2 per player, 1 neutral)
4. Starting player is determined by neutral card color

### Gameplay Flow
Each turn consists of:
1. **View Current State**: Board displays from player's perspective
2. **Choose Action** from Player Menu:
   - `1] Make a Move` - Execute a game move
   - `2] View Your Cards` - See your available movement cards
   - `3] View Opponent's Cards` - See opponent's cards
   - `4] View Neutral Card` - See the card that will be swapped
   - `5] Clear Screen` - Clear display for better visibility

### Making Moves
1. **Select Card**: Choose one of your two cards (0 or 1)
2. **Choose Piece**: Enter coordinates of piece to move (row col)
3. **Choose Destination**: Enter destination coordinates (row col)
4. **Automatic Validation**: Game checks move legality
5. **Card Swap**: Used card exchanges with neutral card

### Move Card System
- Each card shows movement patterns relative to piece position
- `X` marks the piece's current position on the card
- `x` marks valid destination squares
- Red and Blue players see mirrored movement patterns
- Cards rotate between players via the neutral card

### Input Format
- **Coordinates**: `row col` (e.g., `2 3` for row 2, column 3)
- **Board Range**: 0-4 for both rows and columns
- **Card Selection**: 0 or 1 for your two available cards

### Special Features
- **Dynamic Board Perspective**: Board rotates based on current player
- **Comprehensive Move Validation**: Prevents illegal moves with clear error messages
- **Automatic Win Detection**: Game ends immediately when win conditions are met
- **Stalemate Handling**: Automatic card swap when no moves available

## Technical Implementation

### Architecture Overview
- **Modular Design**: Each .c file handles specific game aspects
- **Include Chain**: Files include each other in dependency order
- **Centralized Data**: Single `databaseType` structure manages game state
- **Memory Safe**: Proper bounds checking and validation
- **Comprehensive Testing**: 19 test categories ensure reliability

### File Include Chain
```
main.c → menu.c → game.c → check.c → display.c → start.c → load.c → onitama.h
```

### Key Data Structures

```c
// Main game database containing all game state
typedef struct databaseTag {
    char board[SIDE][SIDE];                    // 5×5 game board
    cardType cardDb[MAX_CARDS];               // All loaded cards
    int playerCards[2][CARDS_PER_PLAYER];     // Player card indices
    int neutralCard;                          // Neutral card index
    String50 p1, p2;                         // Player names
    int bCurrentPlayer;                       // Current turn (BLUE/RED)
    int bGameOver;                            // Game over flag
    int bWinner;                              // Winner (BLUE/RED)
    int bWinCondition;                        // Win type (TEMPLE/SENSEI)
    pointType blueTemple, redTemple;          // Temple coordinates
    moveType gameMoves[MAX_GAME_MOVES];       // Move history
    int gameMovesCtr;                         // Move counter
} databaseType;

// Individual move card representation
typedef struct cardTag {
    String10 name;                            // Card name
    char card[SIDE][SIDE];                    // Visual pattern
    int bColor;                               // Starting player color
    pointType moves[2][MAX_MOVES];            // Blue/Red move offsets
    int movesCtr;                             // Number of moves
} cardType;

// Board position
typedef struct pointTag {
    int row, col;                             // Coordinates (0-4)
} pointType;
```

### Core Algorithms

#### Move Validation Process
1. **Piece Ownership**: `isOwnPiece()` - Verify player owns the piece
2. **Pattern Compliance**: `followsPattern()` - Check move matches card
3. **Boundary Check**: `isInRange()` - Ensure destination is on board
4. **Destination Valid**: Verify not moving onto own piece
5. **Complete Validation**: `isValid()` - Combine all checks

#### Win Detection Logic
1. **Sensei Capture**: `checkForSensei()` - Scan board for masters
2. **Temple Capture**: `checkForTempleWin()` - Check temple occupancy
3. **Game State Update**: `checkForWin()` - Set winner and condition

#### Card Movement Calculation
1. **Pattern Parsing**: Extract 'x' positions from card pattern
2. **Offset Calculation**: Convert to relative row/col offsets
3. **Blue Moves**: Direct offset calculation from center (2,2)
4. **Red Moves**: Mirror blue moves (negate offsets)

## Troubleshooting

### Common Build Issues

#### Compilation Errors
```bash
# Verify GCC installation
gcc --version

# Clean rebuild using Makefile
make clean
make

# Manual compilation
gcc -Wall -std=c99 -o onitama main.c
```

#### File Not Found Errors
```bash
# Verify data directory structure
ls data/
# Should show movecards.txt and 16 card files

# Check specific files
ls data/movecards.txt
ls data/Crane.txt
```

#### Missing Make Command
```bash
# Linux/Ubuntu - Install build tools
sudo apt install build-essential

# macOS - Install Xcode command line tools
xcode-select --install

# Windows - Use manual compilation or install Make via:
# - Git for Windows (includes Make in Git Bash)
# - MinGW-w64
# - WSL (Windows Subsystem for Linux)
```

### Common Runtime Issues

#### Game Won't Start
1. Verify `data/movecards.txt` exists and contains 16 card names
2. Ensure all individual card files exist in `data/` directory
3. Check file permissions are readable
4. Verify file format matches specification

#### Invalid Moves Rejected
1. Verify coordinates are in range 0-4
2. Check that piece belongs to current player
3. Ensure move follows selected card's pattern
4. Confirm destination is empty or contains opponent piece

#### Test Failures
```bash
# Run test suite with detailed output
make test

# Look for specific failure messages
# Each test shows expected vs actual values
# Fix implementation based on test output
```

### Debugging Tips

#### Enable Verbose Mode
```c
// Enable detailed move validation messages
isValid(db, src, dest, cardIdx, 1);  // 1 = verbose
```

#### Verify Game State
Add debug prints to check:
- Current player value
- Card indices in player hands  
- Board state after moves
- Win condition detection

## Build System Details

### Makefile Contents
The project includes a simple Makefile with essential targets:

```makefile
CC = gcc
CFLAGS = -Wall -std=c99
TARGET = onitama

all: $(TARGET)

$(TARGET): main.c
	$(CC) $(CFLAGS) -o $(TARGET) main.c

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
```

This enables proper syntax highlighting and error detection in modern editors.

## Advanced Features

### Game State Management
- **Move History**: Complete game record for replay/analysis
- **Undo Capability**: Framework exists for implementing move undo
- **Save/Load**: Structure supports game state serialization

### Testing Framework
- **Modular Tests**: Each function tested independently
- **Integration Tests**: Complex game scenarios validated
- **Edge Case Coverage**: Boundary conditions thoroughly tested
- **Regression Testing**: Prevents functionality breaking

### Extensibility
- **Additional Cards**: Easy to add new movement cards
- **Board Variants**: Structure supports different board sizes
- **Rule Modifications**: Modular design allows rule changes
- **AI Integration**: Framework supports computer players

## Performance Considerations

### Optimization Features
- **Efficient Move Generation**: Direct offset calculation
- **Fast Win Detection**: Early termination on win conditions
- **Minimal Memory Usage**: Stack-based structures
- **Quick Validation**: Short-circuit boolean logic

### Scalability
- **Card System**: Supports up to 30 different cards
- **Move History**: Tracks up to 1000 moves per game
- **Memory Footprint**: Approximately 50KB total usage

## Contributing

### Development Guidelines
1. **Code Standards**: Follow C99 standard with `-Wall` compliance
2. **Testing**: Add tests for new functionality in `testmain.c`
3. **Documentation**: Update comments and README for changes
4. **Validation**: Ensure all existing tests pass

### Adding New Features

#### New Movement Cards
1. Create card pattern file in `data/[CardName].txt`
2. Add card name to `data/movecards.txt`
3. Test with existing card loading system

#### New Game Mechanics
1. Add function to appropriate module (check.c, game.c, etc.)
2. Add function prototype to `onitama.h`
3. Add comprehensive tests to `testmain.c`
4. Update documentation

### Testing New Code
```bash
# Test incremental changes
make test

# Verify integration by playing complete games
make run
```

---

## Quick Reference

### Build Commands
```bash
make           # Build game
make run       # Build and play
make test      # Run tests
make clean     # Clean build
```

### Manual Compilation
```bash
# Main game
gcc -Wall -std=c99 -o onitama main.c

# Test suite  
gcc -Wall -std=c99 -o test_onitama testmain.c
```

### File Requirements
- All source files (.c and .h) in project root
- `data/` directory with movecards.txt and 16 card files
- Proper file permissions for reading data files
