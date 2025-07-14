#include "start.c"
/*
   This function displays the welcome message and basic instructions for the Onitama game.

   @return this function does not return a value, it prints the welcome message to the screen
*/
void displayWelcomeMessage ()
{
	printf("\n===Welcome to Onitama===\n");
	printf("Pieces: R/r = Red Master/Student, B/b = Blue Master/Student\n");
	printf("Goal: Capture enemy master or reach their temple (middle of opposite side)\n");
}

/*
   This function displays the win conditions for the Onitama game.

   @return this function does not return a value, it prints the win conditions to the screen
*/
void displayWinCondition ()
{
	printf("Win Conditions:\n"); 
	printf("- Capture opponent's master (R or B)\n");
	printf("RED wins by reaching (4,2) | BLUE wins by reaching (0,2)\n");
}


/*
   This function displays the available cards in the Onitama game.
   Precondition: The databaseType structure is initialized and contains the card data.

   @param db a pointer to the databaseType structure containing the game data

   @return this function does not return a value, it prints the available cards to the screen
*/
void viewAvailableCards (databaseType *db)
{
	int j;

	printf("\n===Available Cards===\n");
	
	for (j = 0; j < db->numCards; j++)
	{
		printf("%s ", db->cardDb[j].name);
	}

	printf("\n");
}

/*
   This function displays the cards that have been dealt to the players and the neutral card.
   Precondition: The databaseType structure is initialized and contains the player cards and neutral card.

   @param db a pointer to the databaseType structure containing the game data

   @return this function does not return a value, it prints the dealt cards to the screen
*/
void viewDealtCard (databaseType *db)
{
	int j;

	printf("\n===Dealt Cards===\n");
	printf("Blue: ");

	for (j = 0; j < 2; j++)
	{
		printf("%s ", db->cardDb[db->playerCards[0][j]].name);
	}

	printf("\n");

	printf("Red: ");
	for (j = 0; j < 2; j++)
	{
		printf("%s ", db->cardDb[db->playerCards[1][j]].name);
	}

	printf("\n");
	
	printf("Neutral: ");
	printf("%s ", db->cardDb[db->neutralCard].name);

	printf("\n");
}

/*
   This function displays the column guide for the game board based on the player's perspective.
   Precondition: The key parameter is either BLUE or RED to determine the perspective.

   @param key an integer representing the player's color (BLUE for 0 or RED for 1)

   @return this function does not return a value, it prints the column guide to the screen
*/
void viewColumnGuide (int key)
{
	int j;

	if (key == BLUE)
	{
		for (j = 0; j < SIDE; j++)
		{
			printf("%d ", j);
		}
	}

	else if (key == RED)
	{
		for (j = SIDE - 1; j >= 0; j--)
		{
			printf("%d ", j);
		}
	}
}

void printColoredPiece (char piece)
{
    if (piece == 'R' || piece == 'r')
        printf(RED_COLOR "%c" RESET_COLOR " ", piece);
    else if (piece == 'B' || piece == 'b')
        printf(BLUE_COLOR "%c" RESET_COLOR " ", piece);
    else
        printf("%c ", piece);
}

void printCardCol (cardType *card, int cardRow, int *moveNum, char *color)
{
    int j;
    char ch;

    for (j = 0; j < SIDE; j++)
    { 
        ch = card->card[cardRow][j];

        if (ch == 'x')
        {
            printf("%s%d" RESET_COLOR " ",color, *moveNum);
            (*moveNum)++;
        }

        else
            printf("%s%c" RESET_COLOR " ",color, ch);
    }
}

void printNeutralCol (cardType *card, int cardRow, int *moveNum)
{
    int j;
    char ch;

    for (j = 0; j < SIDE; j++)
    { 
        ch = card->card[cardRow][j];

        if (ch == 'x')
        {
            printf("%d ", *moveNum);
            (*moveNum)++;
        }

        else
            printf("%c ", ch);
    }
}

void printBlueCardRow (databaseType *db, int cardRow, int *moveNum)
{
    int j = 0;
    cardType *card;
    cardType *yourCard1 = &db->cardDb[db->playerCards[db->bCurrentPlayer][0]]; 
    cardType *yourCard2 = &db->cardDb[db->playerCards[db->bCurrentPlayer][1]]; 
    int opponent = !db->bCurrentPlayer;
    cardType *oppCard1 = &db->cardDb[db->playerCards[opponent][0]];
    cardType *oppCard2 = &db->cardDb[db->playerCards[opponent][1]];
    cardType *neutralCard  = &db->cardDb[db->neutralCard];

    printf("\t\t");

    while (j < 2)
    {
        if (!j)
            card = yourCard1;
        else
            card = yourCard2;
        printCardCol(card, cardRow, &moveNum[j], BLUE_COLOR);
        printf("\t");
        j++;
    }

    j = 0;

    while (j < 2)
    {
        if (!j)
            card = oppCard1;
        else
            card = oppCard2;

        printCardCol(card, cardRow, &moveNum[2 + j], RED_COLOR);
        printf("\t");
        j++;
    }

    printNeutralCol (neutralCard, cardRow, &moveNum[4]);
}
/*
   This function displays the game board from the perspective of the blue player.
   Precondition: The databaseType structure is initialized and contains the game board data.

   @param db a pointer to the databaseType structure containing the game data

   @return this function does not return a value, it prints the blue player's perspective of the game board to the screen
*/
void viewBlueBoard (databaseType *db)
{
    int row, col, cardRow;
	char piece;
	int moveNum[5] = {0}; 

	cardType *yourCard1 = &db->cardDb[db->playerCards[db->bCurrentPlayer][0]];
	cardType *yourCard2 = &db->cardDb[db->playerCards[db->bCurrentPlayer][1]];
	int opponent = !db->bCurrentPlayer;
	cardType *oppCard1 = &db->cardDb[db->playerCards[opponent][0]];
	cardType *oppCard2 = &db->cardDb[db->playerCards[opponent][1]];
	cardType *neutralCard = &db->cardDb[db->neutralCard];

	printf("\n=== GAME BOARD ===\t\033[1;34m======= YOUR CARDS =======\033[0m\t\033[1;31m===== OPPONENT CARDS =====\033[0m\t=== NEUTRAL CARD ===\n");
	
	printf("  ");
	viewColumnGuide(BLUE); 
	printf("\t\t\033[1;34m%-10s\t%-10s\033[0m\t\033[1;31m%-10s\t%-10s\033[0m\t%-10s\n", yourCard1->name, yourCard2->name, oppCard1->name, oppCard2->name, neutralCard->name);

	for (row = 0, cardRow = 0; row < SIDE; row++, cardRow++)
	{
		printf("%d ", row);
		for (col = 0; col < SIDE; col++)
		{
			piece = db->board[row][col];
            printColoredPiece (piece);
		}

        printBlueCardRow (db, cardRow, moveNum);
		printf("\n");
	}
}

void printRedCardRow (databaseType *db, int cardRow, int *moveNum)
{
    int j = 0;
    cardType *card;
	cardType *yourCard1 = &db->cardDb[db->playerCards[db->bCurrentPlayer][0]];
	cardType *yourCard2 = &db->cardDb[db->playerCards[db->bCurrentPlayer][1]];
	int opponent = !db->bCurrentPlayer;
	cardType *oppCard1 = &db->cardDb[db->playerCards[opponent][0]];
	cardType *oppCard2 = &db->cardDb[db->playerCards[opponent][1]];
	cardType *neutralCard = &db->cardDb[db->neutralCard];

    printf("\t\t");

    while (j < 2)
    {
        if (!j)
            card = yourCard1;
        else
            card = yourCard2;

        printCardCol (card, cardRow, &moveNum[j], RED_COLOR);
        printf("\t");
        j++;
    }

    j = 0;

    while (j < 2)
    {
        if (!j)
            card = oppCard1;
        else
            card = oppCard2;

        printCardCol (card, cardRow, &moveNum[j], BLUE_COLOR);
        printf("\t");
        j++;
    }
    
    printNeutralCol(neutralCard, cardRow, &moveNum[4]);
}

/*
   This function displays the game board from the perspective of the red player.
   Precondition: The databaseType structure is initialized and contains the game board data.

   @param db a pointer to the databaseType structure containing the game data

   @return this function does not return a value, it prints the red player's perspective of the game board to the screen
*/
void viewRedBoard (databaseType *db)
{
	int row, col, cardRow;
	char piece;
	int moveNum[5] = {0}; // One for each card

	cardType *yourCard1 = &db->cardDb[db->playerCards[db->bCurrentPlayer][0]];
	cardType *yourCard2 = &db->cardDb[db->playerCards[db->bCurrentPlayer][1]];
	int opponent = !db->bCurrentPlayer;
	cardType *oppCard1 = &db->cardDb[db->playerCards[opponent][0]];
	cardType *oppCard2 = &db->cardDb[db->playerCards[opponent][1]];
	cardType *neutralCard = &db->cardDb[db->neutralCard];

	printf("\n=== GAME BOARD ===\t\033[1;31m======= YOUR CARDS =======\033[0m\t\033[1;34m===== OPPONENT CARDS =====\033[0m\t=== NEUTRAL CARD ===\n");
	printf("  ");
	viewColumnGuide(RED);
	printf("\t\t\033[1;31m%-10s\t%-10s\033[0m\t\033[1;34m%-10s\t%-10s\033[0m\t%-10s\n", yourCard1->name, yourCard2->name, oppCard1->name, oppCard2->name, neutralCard->name);

	for (row = SIDE - 1, cardRow = 0; row >= 0; row--, cardRow++)
	{
		printf("%d ", row);
		for (col = SIDE - 1; col >= 0; col--)
		{
			piece = db->board[row][col];
            printColoredPiece (piece);
    	}
        
        printRedCardRow (db, cardRow, moveNum);
    	printf("\n");
	}
}

/*
   This function displays the current game board based on the active player.
   Precondition: The databaseType structure is initialized and contains the current player's information.

   @param db a pointer to the databaseType structure containing the game data

   @return this function does not return a value, it prints the game board to the screen
*/
void displayBoard (databaseType *db)
{
	if (db->bCurrentPlayer == BLUE)
	{
		viewBlueBoard(db);
	}

	if (db->bCurrentPlayer == RED)
	{
		viewRedBoard(db);
	}
}

/*
   This function displays the winner of the game based on the game state stored in the database.
   Precondition: The databaseType structure is initialized and contains the game outcome information.

   @param db a pointer to the databaseType structure containing the game's data

   @return this function does not return a value, it prints the winner and win condition to the screen
*/
void viewWinner (databaseType *db)
{
    printf("\n=== GAME OVER ===\n");
    
    if (db->bWinner == BLUE && db->bWinCondition == TEMPLE_WIN) 
	{
        printf("%s (Blue) wins by Temple Capture!\n", db->p1);
    }
    else if (db->bWinner == BLUE && db->bWinCondition == SENSEI_WIN) 
	{
        printf("%s (Blue) wins by Master Capture!\n", db->p1);
    }
    else if (db->bWinner == RED && db->bWinCondition == TEMPLE_WIN) 
	{
        printf("%s (Red) wins by Temple Capture!\n", db->p2);
    }
    else if (db->bWinner == RED && db->bWinCondition == SENSEI_WIN) 
	{
        printf("%s (Red) wins by Master Capture!\n", db->p2);
    }
}






















