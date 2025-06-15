/*
Description: Onitama game implementation - a two-player turn-based strategy game
Programmed by: [Your Name] [Section]
Last modified: June 2, 2025
Version: 2.0
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BOARD_SIZE 5
#define NUM_CARDS 16
#define CARDS_PER_PLAYER 2
#define MAX_MOVES 8
#define NAME_LENGTH 50
#define CARD_NAME_LENGTH 20
#define FILENAME_LENGTH 100
#define MAX_GAME_MOVES 1000
#define TRUE 1
#define FALSE 0

/* Piece types */
#define EMPTY 0
#define RED_PAWN 1
#define RED_MASTER 2
#define BLUE_PAWN 3
#define BLUE_MASTER 4

/* Player colors */
#define RED 0
#define BLUE 1

/* Menu options */
#define START_GAME 1
#define EXIT_PROGRAM 2

/* Menu options for player turn */
#define MAKE_MOVE 1
#define VIEW_OPPONENT_CARDS 2
#define VIEW_NEUTRAL_CARD 3
#define VIEW_MY_CARDS 4
#define CLEAR_AND_SHOW_BOARD 5

/* Win conditions */
#define WIN_CAPTURE 1
#define WIN_TEMPLE 2

typedef char String20[CARD_NAME_LENGTH];
typedef char String50[NAME_LENGTH];
typedef char String100[FILENAME_LENGTH];

/* Move structure */
struct moveTag {
    int nDx;
    int nDy;
};
typedef struct moveTag moveType;

/* Card structure */
struct cardTag {
    String20 szName;
    moveType arrMoves[MAX_MOVES];
    int nNumMoves;
    int nColor;
};
typedef struct cardTag cardType;

/* Game move record structure */
struct gameMoveTag {
    int nPlayer;
    int nFromRow;
    int nFromCol;
    int nToRow;
    int nToCol;
    String20 szCardUsed;
};
typedef struct gameMoveTag gameMoveType;

/* Complete game database structure */
struct gameDatabaseTag {
    /* Game state */
    int arrBoard[BOARD_SIZE][BOARD_SIZE];
    cardType arrPlayerCards[2][CARDS_PER_PLAYER];
    cardType neutralCard;
    int nCurrentPlayer;
    int bGameOver;
    int nWinner;
    int nWinCondition;
    
    /* Player information */
    String50 szRedPlayerName;
    String50 szBluePlayerName;
    
    /* All available cards */
    cardType arrAllCards[NUM_CARDS];
    String20 arrCardNames[NUM_CARDS];
    int nTotalCards;
    
    /* Game move history */
    gameMoveType arrGameMoves[MAX_GAME_MOVES];
    int nMoveCount;
    
    /* Temporary variables for operations */
    int arrCardIndices[NUM_CARDS];
    int nTempFromRow;
    int nTempFromCol;
    int nTempToRow;
    int nTempToCol;
    int nTempCardChoice;
    int bTempValidInput;
    int bTempValidMove;
    int bTempRedMasterFound;
    int bTempBlueMasterFound;
    int nTempMenuChoice;
    int bHasValidMoves;
    cardType tempCard;
};
typedef struct gameDatabaseTag gameDatabaseType;

/* Function prototypes - File Operations */
int loadCardNames(gameDatabaseType* pDb);
int loadMoveCard(gameDatabaseType* pDb, String20 szCardName, int nCardIndex);
int loadAllCards(gameDatabaseType* pDb);

/* Function prototypes - Initialization */
void initializeBoard(gameDatabaseType* pDb);
void placePieces(gameDatabaseType* pDb);
void shuffleCardIndices(gameDatabaseType* pDb);
void dealCards(gameDatabaseType* pDb);
void initializeTempVariables(gameDatabaseType* pDb);
void initializeGameDatabase(gameDatabaseType* pDb);

/* Function prototypes - Validation */
void checkMoveInCard(cardType* pCard, int nPlayer, int nDx, int nDy, int* pbFound);
void checkValidPosition(gameDatabaseType* pDb, int nRow, int nCol);
void checkOwnPiece(gameDatabaseType* pDb, int nPiece, int nPlayer);
void checkMasterCapture(gameDatabaseType* pDb);
void checkTempleWin(gameDatabaseType* pDb, int nRow, int nCol);
void checkForVictory(gameDatabaseType* pDb);
void validatePositions(gameDatabaseType* pDb, int nFromRow, int nFromCol, int nToRow, int nToCol);
void validateDestination(gameDatabaseType* pDb, int nToRow, int nToCol);
void validateCardMove(gameDatabaseType* pDb, int nFromRow, int nFromCol, int nToRow, int nToCol, int nCardIndex);
void validatePieceOwnership(gameDatabaseType* pDb, int nFromRow, int nFromCol);

/* Function prototypes - Display */
void displayMenu();
void displayPlayerTurnMenu(gameDatabaseType* pDb);
void displayOpponentCards(gameDatabaseType* pDb);
void displayNeutralCard(gameDatabaseType* pDb);
void displayMyCards(gameDatabaseType* pDb);
void displayWelcomeMessage();
void displayShuffleResult(gameDatabaseType* pDb);
void displayBoard(gameDatabaseType* pDb);
void displayCardMoves(gameDatabaseType* pDb, int nCardIndex);
void displayGameResult(gameDatabaseType* pDb);
void printBoardHeader();
void printBoardRow(gameDatabaseType* pDb, int nRow);
void printGameInfo(gameDatabaseType* pDb);
void printCardHeader(cardType* pCard);
void printCardMoveRow(cardType* pCard, int nPlayer, int nRowOffset);

/* Function prototypes - Input */
void getPlayerNames(gameDatabaseType* pDb);
void getMenuChoice(gameDatabaseType* pDb);
void getPlayerTurnChoice(gameDatabaseType* pDb);
void getCardChoice(gameDatabaseType* pDb);
void getMoveInput(gameDatabaseType* pDb);

/* Function prototypes - Game Engine */
void executeMove(gameDatabaseType* pDb, int nFromRow, int nFromCol, int nToRow, int nToCol);
void recordMove(gameDatabaseType* pDb, int nFromRow, int nFromCol, int nToRow, int nToCol, int nCardIndex);
void rotateCards(gameDatabaseType* pDb, int nCardIndex);
void switchPlayer(gameDatabaseType* pDb);
void processMove(gameDatabaseType* pDb, int nFromRow, int nFromCol, int nToRow, int nToCol, int nCardIndex);
void handlePlayerInput(gameDatabaseType* pDb);
void checkForValidMoves(gameDatabaseType* pDb);
void handleNoValidMoves(gameDatabaseType* pDb);
void runGameLoop(gameDatabaseType* pDb);
void runMainLoop(gameDatabaseType* pDb);

/* File Operations */
int loadCardNames(gameDatabaseType* pDb) 
{
    FILE* pFile;
    int i;
    int nScanResult;
    int bSuccess;
    
    bSuccess = TRUE;
    pFile = fopen("movecards.txt", "r");
    if (pFile == NULL) {
        printf("Error: Cannot open movecards.txt\n");
        bSuccess = FALSE;
    }
    
    if (bSuccess == TRUE) {
        nScanResult = fscanf(pFile, "%d", &pDb->nTotalCards);
        if (nScanResult != 1 || pDb->nTotalCards > NUM_CARDS) {
            printf("Error: Invalid card count in movecards.txt\n");
            bSuccess = FALSE;
        }
    }
    
    if (bSuccess == TRUE) {
        i = 0;
        while (i < pDb->nTotalCards && bSuccess == TRUE) {
            nScanResult = fscanf(pFile, "%s", pDb->arrCardNames[i]);
            if (nScanResult != 1) {
                printf("Error: Cannot read card name %d\n", i);
                bSuccess = FALSE;
            }
            i = i + 1;
        }
    }
    
    if (pFile != NULL) {
        fclose(pFile);
    }
    
    return bSuccess;
}

int loadMoveCard(gameDatabaseType* pDb, String20 szCardName, int nCardIndex) 
{
    FILE* pFile;
    String100 szFilename;
    String20 szColor;
    char arrGrid[BOARD_SIZE][BOARD_SIZE + 1];
    int i;
    int j;
    int nScanResult;
    int nPieceRow;
    int nPieceCol;
    int nMoveCount;
    int bSuccess;
    
    bSuccess = TRUE;
    strcpy(szFilename, szCardName);
    strcat(szFilename, ".txt");
    
    pFile = fopen(szFilename, "r");
    if (pFile == NULL) {
        printf("Error: Cannot open %s\n", szFilename);
        bSuccess = FALSE;
    }
    
    if (bSuccess == TRUE) {
        /* Read color */
        nScanResult = fscanf(pFile, "%s", szColor);
        if (nScanResult != 1) {
            printf("Error: Cannot read color from %s\n", szFilename);
            bSuccess = FALSE;
        }
    }
    
    if (bSuccess == TRUE) {
        /* Set card properties */
        strcpy(pDb->arrAllCards[nCardIndex].szName, szCardName);
        if (strcmp(szColor, "red") == 0) {
            pDb->arrAllCards[nCardIndex].nColor = RED;
        } else {
            pDb->arrAllCards[nCardIndex].nColor = BLUE;
        }
        
        /* Read grid */
        i = 0;
        while (i < BOARD_SIZE && bSuccess == TRUE) {
            nScanResult = fscanf(pFile, "%s", arrGrid[i]);
            if (nScanResult != 1) {
                printf("Error: Cannot read grid row %d from %s\n", i, szFilename);
                bSuccess = FALSE;
            }
            i = i + 1;
        }
    }
    
    if (bSuccess == TRUE) {
        /* Find piece position and moves - X is at center (2,2) */
        nPieceRow = 2;
        nPieceCol = 2;
        nMoveCount = 0;
        
        i = 0;
        while (i < BOARD_SIZE) {
            j = 0;
            while (j < BOARD_SIZE) {
                if (arrGrid[i][j] == 'x') {
                    if (nMoveCount < MAX_MOVES) {
                        /* Calculate relative movement from center position */
                        pDb->arrAllCards[nCardIndex].arrMoves[nMoveCount].nDx = j - nPieceCol;
                        pDb->arrAllCards[nCardIndex].arrMoves[nMoveCount].nDy = i - nPieceRow;
                        nMoveCount = nMoveCount + 1;
                    }
                }
                j = j + 1;
            }
            i = i + 1;
        }
        
        pDb->arrAllCards[nCardIndex].nNumMoves = nMoveCount;
    }
    
    if (pFile != NULL) {
        fclose(pFile);
    }
    
    return bSuccess;
}

int loadAllCards(gameDatabaseType* pDb) 
{
    int i;
    int bSuccess;
    
    bSuccess = loadCardNames(pDb);
    if (bSuccess == FALSE) {
        return FALSE;
    }
    
    i = 0;
    while (i < pDb->nTotalCards) {
        bSuccess = loadMoveCard(pDb, pDb->arrCardNames[i], i);
        if (bSuccess == FALSE) {
            return FALSE;
        }
        i = i + 1;
    }
    
    return TRUE;
}

/* Initialization Functions */
void initializeBoard(gameDatabaseType* pDb) 
{
    int i;
    int j;
    
    i = 0;
    while (i < BOARD_SIZE) {
        j = 0;
        while (j < BOARD_SIZE) {
            pDb->arrBoard[i][j] = EMPTY;
            j = j + 1;
        }
        i = i + 1;
    }
}

void placePieces(gameDatabaseType* pDb) 
{
    /* Red pieces (top row) */
    pDb->arrBoard[0][0] = RED_PAWN;
    pDb->arrBoard[0][1] = RED_PAWN;
    pDb->arrBoard[0][2] = RED_MASTER;
    pDb->arrBoard[0][3] = RED_PAWN;
    pDb->arrBoard[0][4] = RED_PAWN;
    
    /* Blue pieces (bottom row) */
    pDb->arrBoard[4][0] = BLUE_PAWN;
    pDb->arrBoard[4][1] = BLUE_PAWN;
    pDb->arrBoard[4][2] = BLUE_MASTER;
    pDb->arrBoard[4][3] = BLUE_PAWN;
    pDb->arrBoard[4][4] = BLUE_PAWN;
}

void shuffleCardIndices(gameDatabaseType* pDb) 
{
    int i;
    int j;
    int nTemp;
    
    /* Initialize indices */
    i = 0;
    while (i < pDb->nTotalCards) {
        pDb->arrCardIndices[i] = i;
        i = i + 1;
    }
    
    /* Fisher-Yates shuffle */
    i = pDb->nTotalCards - 1;
    while (i > 0) {
        j = rand() % (i + 1);
        nTemp = pDb->arrCardIndices[i];
        pDb->arrCardIndices[i] = pDb->arrCardIndices[j];
        pDb->arrCardIndices[j] = nTemp;
        i = i - 1;
    }
}

void dealCards(gameDatabaseType* pDb) 
{
    int i;
    
    /* Deal 2 cards to each player and 1 neutral */
    i = 0;
    while (i < CARDS_PER_PLAYER) {
        pDb->arrPlayerCards[RED][i] = pDb->arrAllCards[pDb->arrCardIndices[i]];
        pDb->arrPlayerCards[BLUE][i] = pDb->arrAllCards[pDb->arrCardIndices[i + 2]];
        i = i + 1;
    }
    pDb->neutralCard = pDb->arrAllCards[pDb->arrCardIndices[4]];
    
    /* Set starting player based on neutral card color */
    pDb->nCurrentPlayer = pDb->neutralCard.nColor;
}

void initializeTempVariables(gameDatabaseType* pDb)
{
    pDb->nTempFromRow = 0;
    pDb->nTempFromCol = 0;
    pDb->nTempToRow = 0;
    pDb->nTempToCol = 0;
    pDb->nTempCardChoice = 0;
    pDb->nTempMenuChoice = 0;
    pDb->bTempValidInput = FALSE;
    pDb->bTempValidMove = FALSE;
    pDb->bTempRedMasterFound = FALSE;
    pDb->bTempBlueMasterFound = FALSE;
    pDb->bHasValidMoves = TRUE;
}

void initializeGameDatabase(gameDatabaseType* pDb) 
{
    initializeBoard(pDb);
    placePieces(pDb);
    shuffleCardIndices(pDb);
    dealCards(pDb);
    
    pDb->bGameOver = FALSE;
    pDb->nWinner = -1;
    pDb->nWinCondition = 0;
    pDb->nMoveCount = 0;
    
    initializeTempVariables(pDb);
}

/* Validation Functions */
void checkMoveInCard(cardType* pCard, int nPlayer, int nDx, int nDy, int* pbFound) 
{
    int i;
    int nCardDx;
    int nCardDy;

    *pbFound = FALSE;
    i = 0;
    while (i < pCard->nNumMoves && *pbFound == FALSE) {
        nCardDx = pCard->arrMoves[i].nDx;
        nCardDy = pCard->arrMoves[i].nDy;

        /* Flip moves for blue player */
        if (nPlayer == BLUE) {
            nCardDx = -nCardDx;
            nCardDy = -nCardDy;
        }

        if (nCardDx == nDx && nCardDy == nDy) {
            *pbFound = TRUE;
        }
        i = i + 1;
    }
}

void checkValidPosition(gameDatabaseType* pDb, int nRow, int nCol) 
{
    if (nRow >= 0 && nRow < BOARD_SIZE && nCol >= 0 && nCol < BOARD_SIZE) {
        pDb->bTempValidMove = TRUE;
    } else {
        pDb->bTempValidMove = FALSE;
    }
}

void checkOwnPiece(gameDatabaseType* pDb, int nPiece, int nPlayer) 
{
    pDb->bTempValidMove = FALSE;
    if (nPlayer == RED) {
        if (nPiece == RED_PAWN || nPiece == RED_MASTER) {
            pDb->bTempValidMove = TRUE;
        }
    } else {
        if (nPiece == BLUE_PAWN || nPiece == BLUE_MASTER) {
            pDb->bTempValidMove = TRUE;
        }
    }
}

void checkMasterCapture(gameDatabaseType* pDb) 
{
    if (pDb->bTempRedMasterFound == FALSE) {
        pDb->nWinner = BLUE;
        pDb->nWinCondition = WIN_CAPTURE;
        pDb->bGameOver = TRUE;
    }
    if (pDb->bTempBlueMasterFound == FALSE) {
        pDb->nWinner = RED;
        pDb->nWinCondition = WIN_CAPTURE;
        pDb->bGameOver = TRUE;
    }
}

void checkTempleWin(gameDatabaseType* pDb, int nRow, int nCol) 
{
    if (pDb->arrBoard[nRow][nCol] == RED_MASTER) {
        pDb->bTempRedMasterFound = TRUE;
        /* Check if red master reached blue temple */
        if (nRow == 4 && nCol == 2) {
            pDb->nWinner = RED;
            pDb->nWinCondition = WIN_TEMPLE;
            pDb->bGameOver = TRUE;
        }
    }
    if (pDb->arrBoard[nRow][nCol] == BLUE_MASTER) {
        pDb->bTempBlueMasterFound = TRUE;
        /* Check if blue master reached red temple */
        if (nRow == 0 && nCol == 2) {
            pDb->nWinner = BLUE;
            pDb->nWinCondition = WIN_TEMPLE;
            pDb->bGameOver = TRUE;
        }
    }
}

void checkForVictory(gameDatabaseType* pDb) 
{
    int i;
    int j;

    pDb->bTempRedMasterFound = FALSE;
    pDb->bTempBlueMasterFound = FALSE;

    /* Check board for masters and temple wins */
    i = 0;
    while (i < BOARD_SIZE) {
        j = 0;
        while (j < BOARD_SIZE) {
            checkTempleWin(pDb, i, j);
            j = j + 1;
        }
        i = i + 1;
    }

    checkMasterCapture(pDb);
}

void validatePositions(gameDatabaseType* pDb, int nFromRow, int nFromCol, int nToRow, int nToCol) 
{
    checkValidPosition(pDb, nFromRow, nFromCol);
    if (pDb->bTempValidMove == TRUE) {
        checkValidPosition(pDb, nToRow, nToCol);
    }
}

void validatePieceOwnership(gameDatabaseType* pDb, int nFromRow, int nFromCol) 
{
    if (pDb->bTempValidMove == TRUE) {
        checkOwnPiece(pDb, pDb->arrBoard[nFromRow][nFromCol], pDb->nCurrentPlayer);
    }
}

void validateDestination(gameDatabaseType* pDb, int nToRow, int nToCol) 
{
    if (pDb->bTempValidMove == TRUE) {
        checkOwnPiece(pDb, pDb->arrBoard[nToRow][nToCol], pDb->nCurrentPlayer);
        if (pDb->bTempValidMove == TRUE) {
            pDb->bTempValidMove = FALSE;
        } else {
            pDb->bTempValidMove = TRUE;
        }
    }
}

void validateCardMove(gameDatabaseType* pDb, int nFromRow, int nFromCol, int nToRow, int nToCol, int nCardIndex) 
{
    cardType* pCard;
    int nDx;
    int nDy;
    int nCardDx;
    int nCardDy;
    int i;

    if (pDb->bTempValidMove == TRUE) {
        pCard = &pDb->arrPlayerCards[pDb->nCurrentPlayer][nCardIndex];
        nDx = nToCol - nFromCol;
        nDy = nToRow - nFromRow;

        printf("DEBUG: Move delta: dx=%d, dy=%d\n", nDx, nDy);
        printf("DEBUG: Card %s has %d moves:\n", pCard->szName, pCard->nNumMoves);

        pDb->bTempValidMove = FALSE;
        i = 0;
        while (i < pCard->nNumMoves && pDb->bTempValidMove == FALSE) {
            nCardDx = pCard->arrMoves[i].nDx;
            nCardDy = pCard->arrMoves[i].nDy;
            
            /* Both players need coordinate adjustment since both see board from their perspective */
            if (pDb->nCurrentPlayer == RED) {
                /* Red player: flip both x and y coordinates */
                nCardDx = -nCardDx;
                nCardDy = -nCardDy;
            } else {
                /* Blue player: flip both x and y coordinates */
                nCardDx = -nCardDx;
                nCardDy = -nCardDy;
            }
            
            printf("DEBUG: Card move %d: original(%d,%d) -> adjusted(%d,%d)\n", 
                   i, pCard->arrMoves[i].nDx, pCard->arrMoves[i].nDy, nCardDx, nCardDy);
            
            if (nCardDx == nDx && nCardDy == nDy) {
                pDb->bTempValidMove = TRUE;
                printf("DEBUG: Move matched!\n");
            }
            i = i + 1;
        }
        
        if (pDb->bTempValidMove == FALSE) {
            printf("DEBUG: No matching move found\n");
        }
    }
}

/* Display Functions */
void displayMenu() 
{
    printf("\n=== ONITAMA GAME ===\n");
    printf("1. Start New Game\n");
    printf("2. Exit\n");
    printf("Enter your choice: ");
}

void displayWelcomeMessage() 
{
    printf("\n=== Welcome to Onitama! ===\n");
    printf("Pieces: R/r = Red Master/Student, B/b = Blue Master/Student\n");
    printf("Goal: Capture enemy master or reach their temple (middle of opposite side)\n\n");
}

void displayShuffleResult(gameDatabaseType* pDb) 
{
    int i;
    
    printf("=== Card Shuffling Process ===\n");
    printf("Available cards: ");
    i = 0;
    while (i < pDb->nTotalCards) {
        printf("%s", pDb->arrAllCards[i].szName);
        if (i < pDb->nTotalCards - 1) {
            printf(", ");
        }
        i = i + 1;
    }
    printf("\n\nShuffling cards...\n");
    
    printf("Cards selected for this game:\n");
    i = 0;
    while (i < 5) {
        printf("%d. %s", i + 1, pDb->arrAllCards[pDb->arrCardIndices[i]].szName);
        if (i < 2) {
            printf(" (Red player)");
        } else if (i < 4) {
            printf(" (Blue player)");
        } else {
            printf(" (Neutral card)");
        }
        printf("\n");
        i = i + 1;
    }
    
    printf("\nStarting player: ");
    if (pDb->neutralCard.nColor == RED) {
        printf("RED (determined by neutral card: %s)\n", pDb->neutralCard.szName);
    } else {
        printf("BLUE (determined by neutral card: %s)\n", pDb->neutralCard.szName);
    }
    printf("\n");
}

void printBoardHeader() 
{
    printf("    0   1   2   3   4\n");
    printf("  +---+---+---+---+---+\n");
}

void printBoardRow(gameDatabaseType* pDb, int nRow) 
{
    int j;
    char cPiece;

    printf("%d |", nRow);
    j = 0;
    while (j < BOARD_SIZE) {
        cPiece = ' ';
        
        /* Check for pieces first */
        if (pDb->arrBoard[nRow][j] == RED_PAWN) {
            cPiece = 'r';
        } else if (pDb->arrBoard[nRow][j] == RED_MASTER) {
            cPiece = 'R';
        } else if (pDb->arrBoard[nRow][j] == BLUE_PAWN) {
            cPiece = 'b';
        } else if (pDb->arrBoard[nRow][j] == BLUE_MASTER) {
            cPiece = 'B';
        } else {
            /* Show temple positions when empty */
            if (nRow == 0 && j == 2) {
                cPiece = '*'; /* Red temple (Blue's target) */
            } else if (nRow == 4 && j == 2) {
                cPiece = '*'; /* Blue temple (Red's target) */
            }
        }
        
        printf(" %c |", cPiece);
        j = j + 1;
    }
    printf("\n  +---+---+---+---+---+\n");
}

void printGameInfo(gameDatabaseType* pDb) 
{
    printf("\nGame Status:\n");
    printf("RED (%s): %s, %s\n", 
           pDb->szRedPlayerName,
           pDb->arrPlayerCards[RED][0].szName, 
           pDb->arrPlayerCards[RED][1].szName);
    printf("BLUE (%s): %s, %s\n", 
           pDb->szBluePlayerName,
           pDb->arrPlayerCards[BLUE][0].szName, 
           pDb->arrPlayerCards[BLUE][1].szName);
    printf("Neutral Card: %s\n", pDb->neutralCard.szName);
    
    printf("\nWin Conditions:\n");
    printf("- Capture opponent's master (R or B)\n");
    printf("- Reach opponent's temple (*)\n");
    printf("  RED wins by reaching (4,2) | BLUE wins by reaching (0,2)\n");
}

void displayBoard(gameDatabaseType* pDb) 
{
    int i;

    printf("\n");
    
    /* Each player sees their pieces at the bottom of their view */
    if (pDb->nCurrentPlayer == BLUE) {
        printf("BLUE PLAYER'S VIEW:\n");
        printBoardHeader();
        
        /* Display board normally for Blue player (their pieces at bottom) */
        i = 0;
        while (i < BOARD_SIZE) {
            printBoardRow(pDb, i);
            i = i + 1;
        }
    } else {
        printf("RED PLAYER'S VIEW:\n");
        printBoardHeader();
        
        /* Display board flipped for Red player (their pieces at bottom) */
        i = BOARD_SIZE - 1;
        while (i >= 0) {
            printBoardRow(pDb, i);
            i = i - 1;
        }
    }

    printGameInfo(pDb);
}

void printCardHeader(cardType* pCard) 
{
    printf("\n%s card moves:\n", pCard->szName);
    printf("  +---+---+---+---+---+\n");
}

void printCardMoveRow(cardType* pCard, int nPlayer, int nRowOffset) 
{
    int j;
    int bFound;
    int nDx;
    int nDy;

    printf("  |");
    j = -2;
    while (j <= 2) {
        nDx = j;
        nDy = nRowOffset;
        
        /* Check if this position matches any move in the card */
        checkMoveInCard(pCard, nPlayer, nDx, nDy, &bFound);
        
        if (nRowOffset == 0 && j == 0) {
            printf(" S |"); /* Starting position - center */
        } else if (bFound == TRUE) {
            printf(" X |"); /* Valid move */
        } else {
            printf("   |"); /* Empty */
        }
        j = j + 1;
    }
    printf("\n  +---+---+---+---+---+\n");
}

void displayCardMoves(gameDatabaseType* pDb, int nCardIndex) 
{
    cardType* pCard;
    int i;

    pCard = &pDb->arrPlayerCards[pDb->nCurrentPlayer][nCardIndex];

    printCardHeader(pCard);

    i = -2;
    while (i <= 2) {
        printCardMoveRow(pCard, pDb->nCurrentPlayer, i);
        i = i + 1;
    }
}

void displayPlayerTurnMenu(gameDatabaseType* pDb) 
{
    if (pDb->nCurrentPlayer == RED) {
        printf("\n=== %s's Turn (RED) ===\n", pDb->szRedPlayerName);
    } else {
        printf("\n=== %s's Turn (BLUE) ===\n", pDb->szBluePlayerName);
    }
    printf("1. Make a move\n");
    printf("2. View opponent's cards\n");
    printf("3. View neutral card\n");
    printf("4. View my cards\n");
    printf("5. Clear screen and show board\n");
    printf("Choose an option: ");
}

void displayOpponentCards(gameDatabaseType* pDb) 
{
    int nOpponent;
    int i;
    int j;
    cardType* pCard;
    
    printf("\n\n");
    
    if (pDb->nCurrentPlayer == RED) {
        nOpponent = BLUE;
        printf("=== %s's Cards (BLUE) ===\n", pDb->szBluePlayerName);
    } else {
        nOpponent = RED;
        printf("=== %s's Cards (RED) ===\n", pDb->szRedPlayerName);
    }
    
    i = 0;
    while (i < CARDS_PER_PLAYER) {
        pCard = &pDb->arrPlayerCards[nOpponent][i];
        printf("\nCard %d: %s\n", i, pCard->szName);
        
        /* Show card pattern from opponent's perspective */
        printCardHeader(pCard);
        j = -2;
        while (j <= 2) {
            printCardMoveRow(pCard, nOpponent, j);
            j = j + 1;
        }
        i = i + 1;
    }
    
    printf("\nPress Enter to continue...");
    scanf("%*[^\n]");
    scanf("%*c");
}

void displayNeutralCard(gameDatabaseType* pDb) 
{
    int i;
    
    printf("\n\n");
    
    printf("=== Neutral Card ===\n");
    printf("Card: %s\n", pDb->neutralCard.szName);
    printf("(This card will be available after the next move)\n");
    
    /* Display neutral card pattern */
    printCardHeader(&pDb->neutralCard);
    
    /* Show pattern from current player's perspective */
    i = -2;
    while (i <= 2) {
        printCardMoveRow(&pDb->neutralCard, pDb->nCurrentPlayer, i);
        i = i + 1;
    }
    
    printf("\nPress Enter to continue...");
    scanf("%*[^\n]");
    scanf("%*c");
}

void displayMyCards(gameDatabaseType* pDb) 
{
    int i;
    
    printf("\n\n");
    
    if (pDb->nCurrentPlayer == RED) {
        printf("=== %s's Cards (RED) ===\n", pDb->szRedPlayerName);
    } else {
        printf("=== %s's Cards (BLUE) ===\n", pDb->szBluePlayerName);
    }
    
    i = 0;
    while (i < CARDS_PER_PLAYER) {
        printf("\nCard %d: %s\n", i, pDb->arrPlayerCards[pDb->nCurrentPlayer][i].szName);
        displayCardMoves(pDb, i);
        i = i + 1;
    }
    
    printf("\nPress Enter to continue...");
    scanf("%*[^\n]");
    scanf("%*c");
}

void displayGameResult(gameDatabaseType* pDb) 
{
    displayBoard(pDb);
    printf("\n");
    printf("========================================\n");
    printf("              GAME OVER!                \n");
    printf("========================================\n");
    
    if (pDb->nWinner == RED) {
        printf("🏆 Winner: %s (RED)\n", pDb->szRedPlayerName);
    } else {
        printf("🏆 Winner: %s (BLUE)\n", pDb->szBluePlayerName);
    }
    
    if (pDb->nWinCondition == WIN_CAPTURE) {
        printf("Victory Condition: Master Capture\n");
        printf("The opponent's master was captured!\n");
    } else {
        printf("Victory Condition: Temple Occupation\n");
        if (pDb->nWinner == RED) {
            printf("Red master reached Blue's temple at (4,2)!\n");
        } else {
            printf("Blue master reached Red's temple at (0,2)!\n");
        }
    }
    
    printf("Game Statistics:\n");
    printf("- Total moves played: %d\n", pDb->nMoveCount);
    printf("- Average moves per player: %.1f\n", (float)pDb->nMoveCount / 2.0);
    printf("========================================\n");
}

/* Input Functions */
void getPlayerNames(gameDatabaseType* pDb) 
{
    printf("Enter Red player name: ");
    scanf("%s", pDb->szRedPlayerName);
    printf("Enter Blue player name: ");
    scanf("%s", pDb->szBluePlayerName);
}

void getMenuChoice(gameDatabaseType* pDb) 
{
    int nScanResult;
    
    pDb->bTempValidInput = FALSE;
    while (pDb->bTempValidInput == FALSE) {
        displayMenu();
        nScanResult = scanf("%d", &pDb->nTempMenuChoice);
        if (nScanResult == 1) {
            if (pDb->nTempMenuChoice == START_GAME || pDb->nTempMenuChoice == EXIT_PROGRAM) {
                pDb->bTempValidInput = TRUE;
            } else {
                printf("Invalid choice! Please enter 1 or 2.\n");
            }
        } else {
            printf("Invalid input! Please enter a number.\n");
            scanf("%*[^\n]");
            scanf("%*c");
        }
    }
}

void getPlayerTurnChoice(gameDatabaseType* pDb) 
{
    int nScanResult;
    
    pDb->bTempValidInput = FALSE;
    while (pDb->bTempValidInput == FALSE) {
        displayPlayerTurnMenu(pDb);
        nScanResult = scanf("%d", &pDb->nTempMenuChoice);
        if (nScanResult == 1) {
            if (pDb->nTempMenuChoice >= MAKE_MOVE && pDb->nTempMenuChoice <= CLEAR_AND_SHOW_BOARD) {
                pDb->bTempValidInput = TRUE;
            } else {
                printf("Invalid choice! Please enter 1-5.\n");
            }
        } else {
            printf("Invalid input! Please enter a number.\n");
            scanf("%*[^\n]");
            scanf("%*c");
        }
    }
}

void getCardChoice(gameDatabaseType* pDb) 
{
    int nScanResult;

    pDb->bTempValidInput = FALSE;
    while (pDb->bTempValidInput == FALSE) {
        printf("Choose a card (0 for %s, 1 for %s): ", 
               pDb->arrPlayerCards[pDb->nCurrentPlayer][0].szName,
               pDb->arrPlayerCards[pDb->nCurrentPlayer][1].szName);
        nScanResult = scanf("%d", &pDb->nTempCardChoice);
        if (nScanResult == 1) {
            if (pDb->nTempCardChoice >= 0 && pDb->nTempCardChoice < CARDS_PER_PLAYER) {
                pDb->bTempValidInput = TRUE;
            } else {
                printf("Invalid card choice! Please enter 0 or 1.\n");
            }
        } else {
            printf("Invalid input! Please enter a number.\n");
            scanf("%*[^\n]");
            scanf("%*c");
        }
    }
}

void getMoveInput(gameDatabaseType* pDb) 
{
    int nScanResult;

    pDb->bTempValidInput = FALSE;
    while (pDb->bTempValidInput == FALSE) {
        printf("Enter your move (from_row from_col to_row to_col): ");
        nScanResult = scanf("%d %d %d %d", &pDb->nTempFromRow, &pDb->nTempFromCol, 
                          &pDb->nTempToRow, &pDb->nTempToCol);
        if (nScanResult == 4) {
            processMove(pDb, pDb->nTempFromRow, pDb->nTempFromCol, 
                       pDb->nTempToRow, pDb->nTempToCol, pDb->nTempCardChoice);
            pDb->bTempValidInput = TRUE; /* Always exit the input loop, validation happens in handlePlayerInput */
        } else {
            printf("Invalid input! Please enter 4 numbers (example: 0 2 1 2).\n");
            scanf("%*[^\n]");
            scanf("%*c");
        }
    }
}

/* Game Engine Functions */
void executeMove(gameDatabaseType* pDb, int nFromRow, int nFromCol, int nToRow, int nToCol) 
{
    pDb->arrBoard[nToRow][nToCol] = pDb->arrBoard[nFromRow][nFromCol];
    pDb->arrBoard[nFromRow][nFromCol] = EMPTY;
}

void recordMove(gameDatabaseType* pDb, int nFromRow, int nFromCol, int nToRow, int nToCol, int nCardIndex) 
{
    if (pDb->nMoveCount < MAX_GAME_MOVES) {
        pDb->arrGameMoves[pDb->nMoveCount].nPlayer = pDb->nCurrentPlayer;
        pDb->arrGameMoves[pDb->nMoveCount].nFromRow = nFromRow;
        pDb->arrGameMoves[pDb->nMoveCount].nFromCol = nFromCol;
        pDb->arrGameMoves[pDb->nMoveCount].nToRow = nToRow;
        pDb->arrGameMoves[pDb->nMoveCount].nToCol = nToCol;
        strcpy(pDb->arrGameMoves[pDb->nMoveCount].szCardUsed, 
               pDb->arrPlayerCards[pDb->nCurrentPlayer][nCardIndex].szName);
        pDb->nMoveCount = pDb->nMoveCount + 1;
    }
}

void rotateCards(gameDatabaseType* pDb, int nCardIndex) 
{
    pDb->tempCard = pDb->arrPlayerCards[pDb->nCurrentPlayer][nCardIndex];
    pDb->arrPlayerCards[pDb->nCurrentPlayer][nCardIndex] = pDb->neutralCard;
    pDb->neutralCard = pDb->tempCard;
}

void switchPlayer(gameDatabaseType* pDb) 
{
    if (pDb->nCurrentPlayer == RED) {
        pDb->nCurrentPlayer = BLUE;
    } else {
        pDb->nCurrentPlayer = RED;
    }
}

void processMove(gameDatabaseType* pDb, int nFromRow, int nFromCol, int nToRow, int nToCol, int nCardIndex) 
{
    pDb->bTempValidMove = TRUE;

    validatePositions(pDb, nFromRow, nFromCol, nToRow, nToCol);
    if (pDb->bTempValidMove == TRUE) {
        validatePieceOwnership(pDb, nFromRow, nFromCol);
        if (pDb->bTempValidMove == TRUE) {
            validateDestination(pDb, nToRow, nToCol);
            if (pDb->bTempValidMove == TRUE) {
                validateCardMove(pDb, nFromRow, nFromCol, nToRow, nToCol, nCardIndex);
                if (pDb->bTempValidMove == TRUE) {
                    recordMove(pDb, nFromRow, nFromCol, nToRow, nToCol, nCardIndex);
                    executeMove(pDb, nFromRow, nFromCol, nToRow, nToCol);
                    rotateCards(pDb, nCardIndex);
                    checkForVictory(pDb);
                    if (pDb->bGameOver == FALSE) {
                        switchPlayer(pDb);
                    }
                }
            }
        }
    }
}

void handlePlayerInput(gameDatabaseType* pDb) 
{
    int bMadeMove;
    int bValidMove;
    int bFirstTime;
    
    /* Check if player has any valid moves */
    checkForValidMoves(pDb);
    
    if (pDb->bHasValidMoves == FALSE) {
        handleNoValidMoves(pDb);
    } else {
        bMadeMove = FALSE;
        bFirstTime = TRUE;
        
        /* Keep showing menu until player makes a move */
        while (bMadeMove == FALSE) {
            /* Only show board on first time or after clearing */
            if (bFirstTime == TRUE) {
                displayBoard(pDb);
                bFirstTime = FALSE;
            }
            
            getPlayerTurnChoice(pDb);
            
            if (pDb->nTempMenuChoice == MAKE_MOVE) {
                /* Step 1: Player chooses a card */
                getCardChoice(pDb);
                
                /* Step 2: Show the card pattern */
                printf("\n");
                displayCardMoves(pDb, pDb->nTempCardChoice);
                
                /* Step 3: Player makes moves until they get a valid one */
                bValidMove = FALSE;
                while (bValidMove == FALSE) {
                    getMoveInput(pDb);
                    if (pDb->bTempValidMove == TRUE) {
                        bValidMove = TRUE;
                        bMadeMove = TRUE;
                    } else {
                        printf("\nThat move doesn't work with the %s card. Try again!\n", 
                               pDb->arrPlayerCards[pDb->nCurrentPlayer][pDb->nTempCardChoice].szName);
                        printf("Remember: S = your piece position, X = where it can move\n\n");
                    }
                }
            } else if (pDb->nTempMenuChoice == VIEW_OPPONENT_CARDS) {
                displayOpponentCards(pDb);
            } else if (pDb->nTempMenuChoice == VIEW_NEUTRAL_CARD) {
                displayNeutralCard(pDb);
            } else if (pDb->nTempMenuChoice == VIEW_MY_CARDS) {
                displayMyCards(pDb);
            } else if (pDb->nTempMenuChoice == CLEAR_AND_SHOW_BOARD) {
                system("clear");
                displayBoard(pDb);
            }
        }
    }
}

void runMainLoop(gameDatabaseType* pDb) 
{
    int bRunning;
    int bCardsLoaded;
    
    bRunning = TRUE;
    
    printf("Loading game cards...\n");
    bCardsLoaded = loadAllCards(pDb);
    
    if (bCardsLoaded == FALSE) {
        printf("Failed to load game cards. Exiting.\n");
        bRunning = FALSE;
    }
    
    while (bRunning == TRUE) {
        getMenuChoice(pDb);
        
        if (pDb->nTempMenuChoice == START_GAME) {
            initializeGameDatabase(pDb);
            runGameLoop(pDb);
        } else if (pDb->nTempMenuChoice == EXIT_PROGRAM) {
            printf("Thank you for playing Onitama!\n");
            bRunning = FALSE;
        }
    }
}

void runGameLoop(gameDatabaseType* pDb) 
{
    printf("\n");
    displayWelcomeMessage();
    getPlayerNames(pDb);
    
    printf("\n");
    displayShuffleResult(pDb);
    printf("Press Enter to start the game...");
    scanf("%*[^\n]");
    scanf("%*c");

    while (pDb->bGameOver == FALSE) {
        handlePlayerInput(pDb);
    }

    printf("\n");
    displayGameResult(pDb);
}

void checkForValidMoves(gameDatabaseType* pDb) 
{
    int nPieceRow;
    int nPieceCol;
    int nDestRow;
    int nDestCol;
    int nCardIndex;
    int nMoveIndex;
    int nCardDx;
    int nCardDy;
    cardType* pCard;
    
    pDb->bHasValidMoves = FALSE;
    
    /* Check both cards */
    nCardIndex = 0;
    while (nCardIndex < CARDS_PER_PLAYER && pDb->bHasValidMoves == FALSE) {
        pCard = &pDb->arrPlayerCards[pDb->nCurrentPlayer][nCardIndex];
        
        /* Check all pieces on board */
        nPieceRow = 0;
        while (nPieceRow < BOARD_SIZE && pDb->bHasValidMoves == FALSE) {
            nPieceCol = 0;
            while (nPieceCol < BOARD_SIZE && pDb->bHasValidMoves == FALSE) {
                /* Check if this is player's piece */
                if ((pDb->nCurrentPlayer == RED && (pDb->arrBoard[nPieceRow][nPieceCol] == RED_PAWN || pDb->arrBoard[nPieceRow][nPieceCol] == RED_MASTER)) ||
                    (pDb->nCurrentPlayer == BLUE && (pDb->arrBoard[nPieceRow][nPieceCol] == BLUE_PAWN || pDb->arrBoard[nPieceRow][nPieceCol] == BLUE_MASTER))) {
                    
                    /* Check all moves for this card */
                    nMoveIndex = 0;
                    while (nMoveIndex < pCard->nNumMoves && pDb->bHasValidMoves == FALSE) {
                        nCardDx = pCard->arrMoves[nMoveIndex].nDx;
                        nCardDy = pCard->arrMoves[nMoveIndex].nDy;
                        
                        /* Adjust for player perspective */
                        if (pDb->nCurrentPlayer == RED) {
                            nCardDx = -nCardDx;
                            nCardDy = -nCardDy;
                        } else {
                            nCardDx = -nCardDx;
                            nCardDy = -nCardDy;
                        }
                        
                        nDestRow = nPieceRow + nCardDy;
                        nDestCol = nPieceCol + nCardDx;
                        
                        /* Check if destination is valid */
                        if (nDestRow >= 0 && nDestRow < BOARD_SIZE && nDestCol >= 0 && nDestCol < BOARD_SIZE) {
                            /* Check if destination is not occupied by own piece */
                            if ((pDb->nCurrentPlayer == RED && pDb->arrBoard[nDestRow][nDestCol] != RED_PAWN && pDb->arrBoard[nDestRow][nDestCol] != RED_MASTER) ||
                                (pDb->nCurrentPlayer == BLUE && pDb->arrBoard[nDestRow][nDestCol] != BLUE_PAWN && pDb->arrBoard[nDestRow][nDestCol] != BLUE_MASTER)) {
                                pDb->bHasValidMoves = TRUE;
                            }
                        }
                        
                        nMoveIndex = nMoveIndex + 1;
                    }
                }
                nPieceCol = nPieceCol + 1;
            }
            nPieceRow = nPieceRow + 1;
        }
        nCardIndex = nCardIndex + 1;
    }
}

void handleNoValidMoves(gameDatabaseType* pDb) 
{
    printf("\nNo valid moves available with either card!\n");
    printf("You must still play a card to pass your turn.\n");
    
    getCardChoice(pDb);
    printf("Playing %s card and passing turn...\n", 
           pDb->arrPlayerCards[pDb->nCurrentPlayer][pDb->nTempCardChoice].szName);
    
    /* Rotate cards but don't move any piece */
    rotateCards(pDb, pDb->nTempCardChoice);
    switchPlayer(pDb);
    
    printf("Press Enter to continue...");
    scanf("%*[^\n]");
    scanf("%*c");
}

int main() 
{
    gameDatabaseType gameDb;
    
    srand(time(NULL));
    runMainLoop(&gameDb);
    
    return 0;
}
