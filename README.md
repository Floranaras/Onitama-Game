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

We provide a unified, cross-platform build system that works on Windows, Linux, and macOS with the same simple commands.

### Universal Method (All Platforms)

**Prerequisites:**
- GCC compiler with C99 support
- Make utility (see [Getting Make on Windows](#getting-make-on-windows) if needed)

**Basic Commands:**
```bash
# Build and run the game
make run

# Run comprehensive tests  
make test

# Quick test (no build artifacts)
make quick-test

# See all available commands
make help

# Clean build artifacts
make clean
```

### Getting Make on Windows

#### Option 1: Git Bash (Recommended if you have Git)
```bash
# Git for Windows includes make
# Right-click in project folder → "Git Bash Here"
make run
```

#### Option 2: Use build.cmd (No installation needed)
If you don't have make, use our Windows build script:
```cmd
# Replace make commands with build.cmd
build.cmd run       # Instead of make run
build.cmd test      # Instead of make test  
build.cmd help      # Instead of make help
build.cmd clean     # Instead of make clean
```

#### Option 3: Install Make
```cmd
# Using Chocolatey
choco install make

# Using WSL (Windows 10/11)
wsl --install

# Using winget
winget install GnuWin32.Make
```

### Available Build Commands

| **Command** | **Description** |
|-------------|-----------------|
| `make` | Build the main game |
| `make run` | Build and run the game |
| `make test` | Build and run comprehensive test suite |
| `make quick-test` | Fast test compilation and run |
| `make both` | Build both game and tests |
| `make clean` | Remove all build artifacts |
| `make debug` | Build with debug symbols (-g -DDEBUG) |
| `make release` | Build optimized release (-O2) |
| `make check` | Verify all required files exist |
| `make info` | Show project and platform information |
| `make help` | Show all available commands |

### Build Output Features

Our build system provides:
-  **Colorful output** with emojis for better readability
-  **Smart platform detection** (Windows/Linux/macOS)
-  **Automatic directory creation**
-  **Fast compilation** with dependency tracking
-  **Integrated testing** support

Example output:
```bash
 Starting Onitama Game...
 Running Test Suite...
Build complete
 Missing file
  Warning message
```

## Testing the Implementation

We provide a comprehensive test suite to verify the correctness of the game implementation. The test script validates all major game functions and provides colorful output with pass/fail indicators.

### Running the Test Suite

#### Quick Test Commands

```bash
# Using make (recommended)
make test           # Build and run full test suite
make quick-test     # Fast test without build artifacts

# Using Windows build script (if no make)
build.cmd test      # Build and run full test suite  
build.cmd quick-test # Fast test without build artifacts
```

#### Manual Test Compilation (if needed)

**Note**: Place the test script as `testing/testscript.c` before running these commands.

```bash
# Linux/macOS/WSL
gcc -Wall -Wextra -std=c99 -Iinclude testing/testscript.c src/*.c -o testing/test_onitama
./testing/test_onitama

# Windows
gcc -Wall -Wextra -std=c99 -Iinclude testing/testscript.c src/*.c -o testing/test_onitama.exe
testing\test_onitama.exe
```

### Test Output

The test suite provides colorful output:
-  **Green [PASS]**: Test passed successfully
-  **Red [FAIL]**: Test failed (implementation issue)

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

### Platform-Specific Issues

#### Windows
- **Make not found**: See [Getting Make on Windows](#getting-make-on-windows) section
- **Permission errors**: Run Command Prompt as Administrator if needed
- **Path issues**: Use `build.cmd` if make commands don't work

#### Linux/macOS
- **GCC not installed**: Install build tools (`sudo apt install build-essential` on Ubuntu)
- **Permission denied**: Check file permissions (`chmod +x` for executables)

### Debugging

#### Verify Setup
```bash
make check          # Verify all files present
make info           # Show build configuration
make platform-info  # Show platform details
```

#### Clean Rebuild
```bash
make clean          # Remove all build artifacts
make                # Clean build
```

#### Debug Build
```bash
make debug          # Build with debug symbols
gdb obj/onitama     # Debug with GDB (Linux/macOS)
```

#### Test Debugging
```bash
make test           # Run full test suite
make quick-test     # Fast test run
```

If tests fail, the test suite provides detailed error messages showing exactly which functions need attention.

### Getting Help

- **Build commands**: `make help` or `build.cmd help`
- **Project info**: `make info`
- **File verification**: `make check`
- **Test the build system**: `make quick-test`

### Performance Tips

- Use `make quick-test` for faster testing during development
- Use `make release` for optimized builds
- Use `make clean` if you encounter strange linking issues

## Contributing

When making changes to the codebase:
1. Ensure all existing tests pass
2. Add new tests for new functionality
3. Follow the established coding standards
4. Update documentation as needed
5. Test on multiple platforms if possible


