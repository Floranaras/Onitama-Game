#ifndef ONITAMA_H
#define ONITAMA_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define STR50 (51)
#define STR30 (31)
#define STR10 (11)
#define BLUE (0) 
#define RED (1)
#define MAX_MOVES (4)
#define SIDE (5)
#define CARDS_PER_PLAYER (2)
#define MAX_CARDS (30)
#define MAX_GAME_MOVES (1000)
#define MASTER_LIST "data/movecards.txt"
#define TEMPLE_WIN (0)
#define SENSEI_WIN (1)

/* Aliases */
typedef char String10[STR10];
typedef char String30[STR30];
typedef char String50[STR50];

/* Structures */

struct pointTag
{
    int row;
    int col;
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

    int playerCards[2][CARDS_PER_PLAYER];
    int neutralCard;

    moveType gameMoves[MAX_GAME_MOVES];
    int gameMovesCtr;

    String50 p1;
    String50 p2;

    int bCurrentPlayer;
    int bGameOver;
    int bWinner;
    int bWinCondition;

	pointType blueTemple;
	pointType redTemple;
 
};

typedef struct databaseTag databaseType;

#endif
