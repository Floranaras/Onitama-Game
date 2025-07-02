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
│   ├── onitama.h     # Main definitions and structures
│   ├── load.h        # File loading functions
│   ├── start.h       # Game initialization
│   ├── display.h     # Game display functions
│   ├── check.h       # Move validation
│   ├── game.h        # Core game logic
│   └── menu.h        # Menu system
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
├── testing/          # Test files
│   ├── testmain.c    # Test implementation
│   └── test.txt      # Test output
├── obj/              # Build artifacts (auto-generated)
├── main.c            # Program entry point
├── Makefile          # Build system
└── README.md         # This file
```

## Getting Started

### Prerequisites
- GCC compiler with C99 support
- Make utility
- Unix-like environment (Linux, macOS, WSL)

### Building the Game

```bash
# Build the project
make

# Build and run immediately
make run

# Clean build artifacts
make clean

# Show all available commands
make help
```

### Available Make Targets

| Command | Description |
|---------|-------------|
| `make` | Build the project (default) |
| `make run` | Build and run the game |
| `make clean` | Remove all build artifacts |
| `make debug` | Build with debug symbols |
| `make release` | Build optimized release version |
| `make test` | Compile and run test suite |
| `make check` | Verify all required files exist |
| `make info` | Show project information |
| `make help` | Display all available commands |

## How to Play

### Game Setup
1. Run the game using `make run`
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
   - Select one of your two move cards
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
- **Header System**: Professional C header organization
- **Memory Safe**: Proper memory management and bounds checking
- **Error Handling**: Comprehensive input validation

### Key Data Structures

```c
// Game state database
typedef struct databaseTag {
    char board[SIDE][SIDE];           // 5x5 game board
    cardType cardDb[MAX_CARDS];       // All available cards
    int playerCards[2][CARDS_PER_PLAYER]; // Player hand indices
    int neutralCard;                  // Neutral card index
    String10 p1, p2;                 // Player names
    int bCurrentPlayer;               // Current turn (BLUE/RED)
    int bGameOver;                    // Game state flag
    int bWinner;                      // Winner (BLUE/RED)
    int bWinCondition;                // Win type (TEMPLE/SENSEI)
    pointType blueTemple, redTemple;  // Temple positions
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

## Testing

### Running Tests
```bash
# Run test suite
make test

# Clean test artifacts
make cleantest
```

### Test Coverage
- Move validation (boundary checking, pattern matching)
- Win condition detection (capture and temple)
- Card loading and parsing
- Board state management
- Input validation and error handling

## Development

### Commit Conventions

| Type | Purpose | Example |
|------|---------|---------|
| `feat` | New feature | `feat: implement move validation system` |
| `fix` | Bug fix | `fix: resolve card rotation logic error` |
| `refactor` | Code improvement | `refactor: optimize board display function` |
| `test` | Add tests | `test: add boundary tests for piece movement` |
| `docs` | Documentation | `docs: update README with build instructions` |
| `build` | Build system | `build: update Makefile compiler flags` |

### Code Standards
- **C99 Compliance**: Strict adherence to C99 standard
- **Wall Flag**: All warnings enabled and addressed
- **No Global Variables**: Proper parameter passing
- **Consistent Naming**: Clear, descriptive function and variable names
- **Documentation**: Comprehensive comments and function headers

### Adding New Features
1. Update appropriate header file in `include/`
2. Implement function in corresponding `src/` file
3. Add tests in `testing/testmain.c`
4. Update Makefile if needed
5. Document changes in README
``
