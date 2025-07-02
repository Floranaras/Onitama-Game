#ifndef LOAD_H
#define LOAD_H

#include "onitama.h"

// Function declarations
int loadMasterList(databaseType *db);
int getCardPatterns(databaseType *db, String30 filename, int idx);
int getCards(databaseType *db);
void blueMoves(cardType *card, pointType center);
void redMoves(cardType *card);
void getMoves(cardType *card);
void initCards(databaseType *db);
void loadCardsFromFile(databaseType *db);

#endif
