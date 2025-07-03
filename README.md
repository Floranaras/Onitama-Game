# Onitama Game

A complete C implementation of the two-player turn-based strategy game Onitama.

## Game Description

Onitama is a strategic board game where each player controls five pieces (one master and four students). The objective is to either capture the opponent's master or navigate your own master to occupy the opponent's temple.

### Game Components
- 5x5 game board with temple positions
- 2 master pieces (Red 'R' and Blue 'B')
- 8 student pieces (red 'r' and blue 'b')
- 16 move cards with unique movement patterns
- Neutral card system for turn determination

### Win Conditions
1. **Master Capture**: Capture the opponent's master piece
2. **Temple Victory**: Move your master to the opponent's temple (center of opposite side)
   - Blue wins by reaching (0,2)
   - Red wins by reaching (4,2)

## Project Structure

```
Onitama-Game/
├── include/           # Header files
│   ├── onitama.h     # Main definitions and structures
│   ├── check.h       # Move validation headers
│   ├── display.h     # Display function headers
│   ├── game.h        # Game logic headers
│   ├── load.h        # File loading headers
│   ├── menu.h        # Menu system headers
│   └── start.h       # Initialization headers
├── src/              # Source files
│   ├── load.c        # Card loading and parsing
│   ├── start.c       # Board and game setup
│   ├── display.c     # Display and UI functions
│   ├── check.c       # Move validation logic
│   ├── game.c        # Game loop and mechanics
│   └── menu.c        # Main menu system
├── data/             # Move card data files
│   ├── movecards.txt # List of available cards
│   └── [Card].txt    # Individual card movement patterns
├── testing/          # Test files and utilities
│   ├── testscript.c  # Comprehensive test suite
│   └── test_onitama  # Compiled test executable
├── obj/              # Compiled object files
│   └── src/          # Source object files
├── main.c            # Program entry point
├── Makefile          # Build automation
├── build.bat         # Windows build script
└── README.md         # This file
```

## Requirements

### Unix/Linux/macOS
- GCC compiler with C99 support
- Make utility
- POSIX shell

### Windows
- MinGW-w64 or TDM-GCC
- Make (optional)
- Alternatively, use WSL or Git Bash

## Building the Game

### Option 1: Using Make (Linux/macOS/WSL)

```bash
# Build the project
make

# Build and run immediately
make run

# Clean build artifacts
make clean

# Build with debug symbols
make debug

# Build optimized release version
make release

# Show all available commands
make help
```

### Option 2: Using build.bat (Windows)

For Windows users, we provide a convenient batch script:

```cmd
# Simply double-click build.bat or run from command prompt:
build.bat
```

This will:
- Create necessary directories (`obj` and `obj\src`)
- Compile all source files with proper flags
- Link everything into `onitama.exe`
- Display completion message

Then run the game:
```cmd
onitama.exe
```

### Option 3: Manual Compilation

**Step 1: Create output directories**
```bash
# Linux/macOS
mkdir -p obj/src

# Windows
mkdir obj
mkdir obj\src
```

**Step 2: Compile source files**
```bash
gcc -Wall -std=c99 -Iinclude -c main.c -o obj/main.o
gcc -Wall -std=c99 -Iinclude -c src/load.c -o obj/src/load.o
gcc -Wall -std=c99 -Iinclude -c src/start.c -o obj/src/start.o
gcc -Wall -std=c99 -Iinclude -c src/display.c -o obj/src/display.o
gcc -Wall -std=c99 -Iinclude -c src/check.c -o obj/src/check.o
gcc -Wall -std=c99 -Iinclude -c src/game.c -o obj/src/game.o
gcc -Wall -std=c99 -Iinclude -c src/menu.c -o obj/src/menu.o
```

**Step 3: Link all object files**
```bash
# Linux/macOS
gcc obj/main.o obj/src/*.o -o onitama

# Windows
gcc obj/main.o obj/src/*.o -o onitama.exe
```

**Step 4: Run the game**
```bash
# Linux/macOS
./onitama

# Windows
onitama.exe
```

### Option 4: Simple One-Line Compilation

```bash
# Linux/macOS
gcc -Wall -std=c99 -Iinclude main.c src/*.c -o onitama

# Windows
gcc -Wall -std=c99 -Iinclude main.c src/*.c -o onitama.exe
```

## Testing the Implementation

We provide a comprehensive test suite to verify the correctness of the game implementation. The test script validates all major game functions and provides colorful output with pass/fail indicators.

### Running the Test Suite

**Note**: Place the test script as `testing/testscript.c` before running these commands.

#### Option 1: Quick Test Compilation and Run

```bash
# Linux/macOS/WSL
gcc -Wall -Wextra -std=c99 -Iinclude testing/testscript.c src/*.c -o testing/test_onitama
./testing/test_onitama

# Windows
gcc -Wall -Wextra -std=c99 -Iinclude testing/testscript.c src/*.c -o testing/test_onitama.exe
testing\test_onitama.exe
```

#### Option 2: Step-by-Step Compilation

**Create testing directory (if not exists):**
```bash
# Linux/macOS
mkdir -p testing

# Windows
mkdir testing
```

**Compile the test suite:**
```bash
# Linux/macOS
gcc -Wall -Wextra -std=c99 -Iinclude \
    testing/testscript.c \
    src/check.c \
    src/display.c \
    src/game.c \
    src/load.c \
    src/menu.c \
    src/start.c \
    -o testing/test_onitama

# Windows
gcc -Wall -Wextra -std=c99 -Iinclude testing/testscript.c src/check.c src/display.c src/game.c src/load.c src/menu.c src/start.c -o testing/test_onitama.exe
```

**Run the tests:**
```bash
# Linux/macOS
./testing/test_onitama

# Windows
testing\test_onitama.exe
```

#### Option 3: Using Test Build Script

Create a `testbuild.sh` script (Linux/macOS):
```bash
#!/bin/bash
echo "Building Onitama Test Suite..."
gcc -Wall -Wextra -std=c99 -Iinclude testing/testscript.c src/*.c -o testing/test_onitama

if [ $? -eq 0 ]; then
    echo "Build successful! Running tests..."
    ./testing/test_onitama
else
    echo "Build failed!"
fi
```

Make executable and run:
```bash
chmod +x testbuild.sh
./testbuild.sh
```

Or create `testbuild.bat` (Windows):
```batch
@echo off
echo Building Onitama Test Suite...
gcc -Wall -Wextra -std=c99 -Iinclude testing/testscript.c src/*.c -o testing/test_onitama.exe

if %errorlevel% == 0 (
    echo Build successful! Running tests...
    testing\test_onitama.exe
) else (
    echo Build failed!
)
```

### Test Output

The test suite provides colorful output:
- **Green [PASS]**: Test passed successfully
- **Red [FAIL]**: Test failed (implementation issue)

Example output:
```
=== Onitama Game Test Suite ===
Running comprehensive tests based on PDF test cases...

=== Testing getPieces ===
[PASS] Test for Blue player piece character assignment
[PASS] Test for Red player piece character assignment

=== Testing isOwnPiece ===
[PASS] Test for Own piece detection - player student
[PASS] Test for Own piece detection - player sensei
[PASS] Test for Own piece detection - opponent piece rejection
...

=== FINAL TEST RESULTS ===
Total tests executed: 75
Tests passed: 75
Tests failed: 0
Success rate: 100.0%

🎉 ALL TESTS PASSED! Game implementation verified! 🎉
🎵 Opening your reward... 🎵
You've been Rick Rolled for your excellent coding! 🕺
```

### Test Coverage

The test suite validates:

- **Move Validation Functions**:
  - `getPieces()` - Player piece character assignment
  - `isOwnPiece()` - Piece ownership detection
  - `followsPattern()` - Card pattern compliance
  - `isInRange()` - Board boundary validation
  - `isValid()` - Complete move validation

- **Game Logic Functions**:
  - `findMoves()` - Individual piece move detection
  - `hasAnyValidMoves()` - Player mobility status
  - `checkForWin()` - Victory condition evaluation
  - `checkForSensei()` - Master piece detection
  - `checkForTempleWin()` - Temple capture detection

- **Board Management**:
  - `movePiece()` - Piece movement execution
  - `initBoard()` - Board initialization
  - `isEqualToTemple()` - Temple position identification

- **Card System**:
  - `switchCards()` - Card exchange mechanism
  - `cardExists()` - Card existence verification
  - `dealCards()` - Card distribution
  - `rareCase()` - Forced card swap handling

- **Pattern Processing**:
  - `blueMoves()` - Blue player move extraction
  - `redMoves()` - Red player move calculation
  - `getMoves()` - Integrated move pattern generation

### Special Test Features

- **Cross-platform compatibility**: Works on Windows, macOS, and Linux
- **Comprehensive coverage**: Tests all major game functions
- **Edge case testing**: Boundary conditions and error scenarios
- **Visual feedback**: Color-coded pass/fail indicators
- **Rick Roll reward**: Browser opens to celebrate all tests passing! 🎵

## How to Play

### Game Setup
1. Run the game using `./onitama` or `make run`
2. Enter player names for Blue and Red players
3. Cards are automatically shuffled and dealt (2 per player, 1 neutral)
4. The player matching the neutral card's color goes first

### Gameplay Flow
1. **View Board**: See current game state from your perspective
2. **Choose Action**: 
   - Make a Move
   - View Your Cards
   - View Opponent's Cards
   - View Neutral Card
   - Clear Screen
3. **Make Move**:
   - Select one of your two move cards (0 or 1)
   - Choose coordinates of piece to move (row col format)
   - Choose destination coordinates
   - Used card swaps with neutral card

### Move Card System
- Each card shows movement patterns relative to piece position
- `X` marks the piece's current position
- `x` marks valid destination squares
- Cards have different patterns for Red and Blue players
- Movement is mirrored for opposite colors

### Special Features
- **Perspective Switching**: Board rotates based on current player
- **Move Validation**: Prevents invalid moves with helpful error messages
- **Automatic Win Detection**: Game ends when win conditions are met
- **No Valid Moves**: Automatic card swap when no moves available

## Technical Implementation

### Architecture
- **Modular Design**: Separate files for different game aspects
- **Header System**: Centralized definitions in onitama.h with specific headers
- **Memory Safe**: Proper memory management and bounds checking
- **Error Handling**: Comprehensive input validation
- **Test Coverage**: Complete test suite for quality assurance

### Key Data Structures

```c
// Game state database
typedef struct databaseTag {
    char board[SIDE][SIDE];                    // 5x5 game board
    cardType cardDb[MAX_CARDS];               // All available cards
    int playerCards[2][CARDS_PER_PLAYER];     // Player hand indices
    int neutralCard;                          // Neutral card index
    String50 p1, p2;                         // Player names
    int bCurrentPlayer;                       // Current turn (BLUE/RED)
    int bGameOver;                            // Game state flag
    int bWinner;                              // Winner (BLUE/RED)
    int bWinCondition;                        // Win type (TEMPLE/SENSEI)
    pointType blueTemple, redTemple;          // Temple positions
    moveType gameMoves[MAX_GAME_MOVES];       // Move history
    int gameMovesCtr;                         // Move counter
} databaseType;
```

### File Formats

**Move Card Data** (example: `Crane.txt`):
```
blue
.....
..x..
..X..
.x.x.
.....
```

**Master Card List** (`movecards.txt`):
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

## Development

### Code Standards
- **C99 Compliance**: Strict adherence to C99 standard
- **Wall Flag**: All warnings enabled and addressed
- **No Global Variables**: Proper parameter passing
- **Consistent Naming**: Clear, descriptive function and variable names
- **Documentation**: Comprehensive comments and function headers
- **Test-Driven**: Comprehensive test suite ensures code quality

### File Dependencies
The project uses a modular include system:
- `main.c` includes `include/menu.h`
- Each module includes its specific header file
- All headers include `onitama.h` for common definitions
- Test suite includes all necessary headers for validation

## Troubleshooting

### Common Issues

1. **File not found errors**: Ensure `data/` directory contains `movecards.txt` and individual card files
2. **Compilation errors**: Check that all source files are in the correct directories
3. **Link errors**: Make sure all object files are properly compiled before linking
4. **Test failures**: Run the test suite to identify specific implementation issues
5. **Missing headers**: Ensure all header files are in the `include/` directory

## Contributing

When making changes to the codebase:
1. Ensure all existing tests pass
2. Add new tests for new functionality
3. Follow the established coding standards
4. Update documentation as needed
5. Test on multiple platforms if possible

