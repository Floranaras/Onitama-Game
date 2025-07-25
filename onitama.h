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

/* Load Function Prototypes */
int loadMasterList(databaseType *db);
int getCardPatterns(databaseType *db, String30 filename, int idx);
int getCards(databaseType *db);
void blueMoves(cardType *card, pointType center);
void redMoves(cardType *card);
void getMoves(cardType *card);
void initCards(databaseType *db);
void loadCardsFromFile(databaseType *db);

/* Start Function Prototypes */
void initBoard(databaseType *db);
int cardExists(int cardIdx[], int count, int key);
void dealCards(databaseType *db);
void getName(String50 name);
void initDatabase(databaseType *db);

/* Display Function Prototypes */
void displayWelcomeMessage(void);
void displayWinCondition(void);
void displayPlayerMenu(void);
void viewAvailableCards(databaseType *db);
void viewDealtCard(databaseType *db);
void viewColumnGuide(int key);
void viewBlueBoard(databaseType *db);
void viewRedBoard(databaseType *db);
void displayCard(cardType card);
void displayYourCard(databaseType *db);
void displayOpponentsCard(databaseType *db);
void displayNeutral(databaseType *db);
void displayBoard(databaseType *db);
void viewWinner(databaseType *db);

/* Check Function Prototypes */
void getPieces(char* student, char* sensei, int currentPlayer);
int isOwnPiece(databaseType *db, pointType src, char student, char sensei);
int followsPattern(databaseType *db, pointType src, pointType dest, int cardIdx);
int isInRange(pointType dest);
int isValid(databaseType *db, pointType src, pointType dest, int cardIdx, int verbose);
int findMoves(databaseType *db, pointType src);
int hasAnyValidMoves(databaseType *db);


/* Game Function Prototypes */
void startGame(databaseType *db);
void switchCards(databaseType *db, int cardDecIdx);
void rareCase(databaseType *db);
void getInputCard(databaseType *db, int *cardDecIdx, int *cardIdx);
void getInputMove(databaseType *db, pointType *src, pointType *dest, int cardIdx);
int isEqualToTemple(databaseType *db, pointType dest);
void movePiece(databaseType *db, pointType src, pointType dest);
void checkForTempleWin(databaseType *db, int *redTempleCapture, int *blueTempleCapture);
void checkForSensei(databaseType *db, int *redFound, int *blueFound);
void checkForWin(databaseType *db);
void makeMove(databaseType *db);
void clearScreen();
void playerMenu(databaseType *db);
void gameLoop(databaseType *db);


/* Menu Function Prototypes */
void mainMenu(databaseType *db);

