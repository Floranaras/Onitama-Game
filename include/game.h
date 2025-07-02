#ifndef GAME_H
#define GAME_H

#include "onitama.h"
#include "check.h"

// Function declarations
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
void playerMenu(databaseType *db);
void gameLoop(databaseType *db);

#endif
