#ifndef CHECK_H
#define CHECK_H

#include "onitama.h"
#include "display.h"

// Function declarations
void getPieces(char* student, char* sensei, int currentPlayer);
int isOwnPiece(databaseType *db, pointType src, char student, char sensei);
int followsPattern(databaseType *db, pointType src, pointType dest, int cardIdx);
int isInRange(pointType dest);
int isValid(databaseType *db, pointType src, pointType dest, int cardIdx, int verbose);
int findMoves(databaseType *db, pointType src);
int hasAnyValidMoves(databaseType *db);

#endif
