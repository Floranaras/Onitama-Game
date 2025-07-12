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
   This function displays the player menu options for the Onitama game.

   @return this function does not return a value, it prints the player menu to the screen
*/
void displayPlayerMenu()
{
	printf("\n===Player Menu===\n");
	printf("1] Make a Move\n");
	printf("2] View Your Cards\n");
	printf("3] View Your Opponents Cards\n");
	printf("4] View Neutral Card\n");
	printf("5] Clear Screen\n");
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
		
		printf("\n");
	}

	else if (key == RED)
	{
		for (j = SIDE - 1; j >= 0; j--)
		{
			printf("%d ", j);
		}
		
		printf("\n");
	}
}

/*
   This function displays the game board from the perspective of the blue player.
   Precondition: The databaseType structure is initialized and contains the game board data.

   @param db a pointer to the databaseType structure containing the game data

   @return this function does not return a value, it prints the blue player's perspective of the game board to the screen
*/
void viewBlueBoard (databaseType *db)
{
	int j, k;

	
	printf("\n===GAME BOARD===\n(%s's Perspective - BLUE)\n", db->p1);
	viewColumnGuide(BLUE);
	for (j = 0; j < SIDE; j++)
	{
		for (k = 0; k < SIDE; k++)
		{
			printf("%c ", db->board[j][k]);
		}
		printf("%d", j);
		printf("\n");
	}
}

/*
   This function displays the game board from the perspective of the red player.
   Precondition: The databaseType structure is initialized and contains the game board data.

   @param db a pointer to the databaseType structure containing the game data

   @return this function does not return a value, it prints the red player's perspective of the game board to the screen
*/
void viewRedBoard (databaseType *db)
{
	int j, k;
	
	printf("\n===GAME BOARD===\n(%s's Perspective - RED)\n", db->p2);
	viewColumnGuide(RED);
	for (j = SIDE - 1; j >= 0; j--)
	{
		for (k = SIDE - 1; k >= 0; k--)
		{
			printf("%c ", db->board[j][k]);
		}

		printf("%d", j);
		printf("\n");
	}
}


int findMoveIndex(databaseType *db, int cardIdx, int row, int col)
{
    int moveIdx = 0;
    
    while (moveIdx < db->cardDb[cardIdx].movesCtr) 
    {
        pointType movePos;
        movePos.row = 2 + db->cardDb[cardIdx].moves[db->bCurrentPlayer][moveIdx].row;
        movePos.col = 2 + db->cardDb[cardIdx].moves[db->bCurrentPlayer][moveIdx].col;
        
        if (movePos.row == row && movePos.col == col) 
        {
            return moveIdx;
        }
        
        moveIdx++;
    }
    
    return -1; // Should never happen for valid 'x' positions
}

/*
   This function displays the details of a specific card, including its name and movement pattern.
   Precondition: The cardType structure is initialized and contains the card data.

   @param card a cardType structure containing the card information to display

   @return this function does not return a value, it prints the card details to the screen
*/
void displayCard(databaseType *db, int cardIdx)
{
    int pos = 0;
    cardType card = db->cardDb[cardIdx];
    
    printf("\n%s Card", card.name);
    printf("\n{\n");
    
    while (pos < SIDE * SIDE) 
    {
        int row = pos / SIDE;
        int col = pos % SIDE;
        char output = card.card[row][col];
        
        if (output == 'x') 
        {
            printf("%d ", findMoveIndex(db, cardIdx, row, col));
        } 
        else 
        {
            printf("%c ", output);
        }
        
        if (col == SIDE - 1) 
        {
            printf("\n");
        }
        
        pos++;
    }
    
    printf("\n}\n");
}

/*
   This function displays the player's own cards.
   Precondition: The databaseType structure is initialized and contains the player's card data.

   @param db a pointer to the databaseType structure containing the game data

   @return this function does not return a value, it prints the player's cards to the screen
*/
void displayYourCard (databaseType *db)
{
	int j;

	for (j = 0; j < 2; j++)
	{
		displayCard(db, db->playerCards[db->bCurrentPlayer][j]);
	}
}

/*
   This function displays the opponent's cards.
   Precondition: The databaseType structure is initialized and contains the opponent's card data.

   @param db a pointer to the databaseType structure containing the game data

   @return this function does not return a value, it prints the opponent's cards to the screen
*/
void displayOpponentsCard (databaseType *db)
{
	int j;
	int opp = !db->bCurrentPlayer;

	for (j = 0; j < 2; j++)
	{
		displayCard(db, db->playerCards[opp][j]);
	}
}

/*
   This function displays the neutral card.
   Precondition: The databaseType structure is initialized and contains the neutral card data.

   @param db a pointer to the databaseType structure containing the game data

   @return this function does not return a value, it prints the neutral card to the screen
*/
void displayNeutral (databaseType *db)
{
	displayCard(db, db->neutralCard);
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






















