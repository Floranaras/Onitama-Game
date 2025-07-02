# Onitama Game

A complete C implementation of the two-player turn-based strategy game Onitama for CCPROG2 Project.

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
│   └── head.h        # Main definitions and structures
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
├── main.c            # Program entry point
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

### Option 2: Manual Compilation

**Step 1: Create output directories**
```bash
mkdir -p obj/src
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
gcc obj/main.o obj/src/*.o -o onitama
```

**Step 4: Run the game**
```bash
./onitama
```

### Option 3: Simple One-Line Compilation

```bash
gcc -Wall -std=c99 -Iinclude main.c src/*.c -o onitama
```

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
- **Header System**: Centralized definitions in head.h
- **Memory Safe**: Proper memory management and bounds checking
- **Error Handling**: Comprehensive input validation

### Key Data Structures

```c
// Game state database
typedef struct databaseTag {
    char board[SIDE][SIDE];                    // 5x5 game board
    cardType cardDb[MAX_CARDS];               // All available cards
    int playerCards[2][CARDS_PER_PLAYER];     // Player hand indices
    int neutralCard;                          // Neutral card index
    String10 p1, p2;                         // Player names
    int bCurrentPlayer;                       // Current turn (BLUE/RED)
    int bGameOver;                            // Game state flag
    int bWinner;                              // Winner (BLUE/RED)
    int bWinCondition;                        // Win type (TEMPLE/SENSEI)
    pointType blueTemple, redTemple;          // Temple positions
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

### File Dependencies
The project uses a specific include order to manage dependencies:
- `main.c` includes `src/menu.c`
- `menu.c` includes `game.c`
- `game.c` includes `check.c`
- `check.c` includes `display.c`
- `display.c` includes `start.c`
- `start.c` includes `load.c`
- `load.c` includes `../include/head.h`

## Troubleshooting

### Common Issues

1. **File not found errors**: Ensure `data/` directory contains `movecards.txt` and individual card files
2. **Compilation errors**: Check that all source files are in the correct directories
3. **Link errors**: Make sure all object files are properly compiled before linking

