#ifndef START_H
#define START_H

#include "onitama.h"
#include "load.h"

// Function declarations
void initBoard(databaseType *db);
int cardExists(int cardIdx[], int count, int key);
void dealCards(databaseType *db);
void getName(String10 name);
void initDatabase(databaseType *db);

#endif
