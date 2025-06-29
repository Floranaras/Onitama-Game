#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_STR (11)
#define BLUE (0) 
#define RED (1)
#define MAX_MOVES (4)
#define SIDE (5)
#define CARDS_PER_PLAYER (2)
#define MAX_CARDS (30)
#define MAX_MOVES (1000)

/* Aliases */
typedef char String10[MAX_STR];

/* Structures */

struct pointTag
{
    int x;
    int y;
};

typedef struct pointTag pointType;

struct cardTag
{
    String10 name;
    char card[SIDE][SIDE];
    int bColor;
    pointType moves[2][MAX_MOVES];
    int movesCtr;
};

typedef struct cardTag cardType;

struct moveTag
{
    int bPlayer;
    int fromRow;
    int fromCol;
    int toRow;
    int toCol;
    String10 cardUsed;
};

typedef struct moveTag moveType;

struct databaseTag
{
    char board[SIDE][SIDE];

    cardType cardDb[MAX_CARDS];
    int numCards;

    cardType playerCards[2][CARDS_PER_PLAYER];
    cardType neutralCard;

    moveType gameMoves[MAX_MOVES];
    int gameMovesCtr;

    String10 p1;
    String10 p2;

    int bCurrentPlayer;
    int bGameOver;
    int bWinner;
    int bWinCondition;

    
};

typedef struct databaseTag databaseType;