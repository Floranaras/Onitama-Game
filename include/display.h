#ifndef DISPLAY_H
#define DISPLAY_H

#include "onitama.h"
#include "start.h"

// Function declarations
void displayWelcomeMessage(void);
void displayWinCondition(void);
void displayPlayerMenu(void);
void viewAvailableCards(databaseType *db);
void viewDealtCard(databaseType *db);
void viewRowGuide(int key);
void viewBlueBoard(databaseType *db);
void viewRedBoard(databaseType *db);
void displayCard(cardType card);
void displayYourCard(databaseType *db);
void displayOpponentsCard(databaseType *db);
void displayNeutral(databaseType *db);
void displayBoard(databaseType *db);
void viewWinner(databaseType *db);

#endif
