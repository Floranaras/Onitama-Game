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
	}

	else if (key == RED)
	{
		for (j = SIDE - 1; j >= 0; j--)
		{
			printf("%d ", j);
		}
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
	// int j, k;

	// printf("\n===GAME BOARD===\n\033[1;34m(%s's Perspective - BLUE)\033[0m\n", db->p1);
	// displayOpponentsCard(db);
	// viewColumnGuide(BLUE);
	// for (j = 0; j < SIDE; j++)
	// {
	// 	for (k = 0; k < SIDE; k++)
	// 	{
	// 		if (db->board[j][k] == 'R' || db->board[j][k] == 'r')
	// 			printf("\033[1;31m%c\033[0m ", db->board[j][k]); 
	// 		else if (db->board[j][k] == 'B' || db->board[j][k] == 'b')
	// 			printf("\033[1;34m%c\033[0m ", db->board[j][k]); 
	// 		else
	// 			printf("%c ", db->board[j][k]);
	// 	}
	// 	printf("%d", j);
	// 	printf("\n");
	// }
	// displayYourCard(db);

	int row, col;
	char piece;

	printf("\n=== GAME BOARD ===\n\033[1;34m(%s's Perspective - BLUE)\033[0m\n", db->p1);

	displayOpponentsCard(db);
	printf("\n  ");
	viewColumnGuide(BLUE);
	printf("\tNeutral: %s\n", db->cardDb[db->neutralCard].name);

	for (row = 0; row < SIDE; row++)
	{
		printf("%d ", row); 
		for (col = 0; col < SIDE; col++)
		{
			piece = db->board[row][col];
			if (piece == 'R' || piece == 'r')
				printf("\033[1;31m%c\033[0m ", piece); 
			else if (piece == 'B' || piece == 'b')
				printf("\033[1;34m%c\033[0m ", piece);
			else
				printf("%c ", piece); 
		}
		printf(" |  ");

		for (col = 0; col < SIDE; col++)
		{
			printf("%c ", db->cardDb[db->neutralCard].card[row][col]);
		}
		printf("\n");
	}

	printf("\n");
	displayYourCard(db);
}

/*
   This function displays the game board from the perspective of the red player.
   Precondition: The databaseType structure is initialized and contains the game board data.

   @param db a pointer to the databaseType structure containing the game data

   @return this function does not return a value, it prints the red player's perspective of the game board to the screen
*/
void viewRedBoard (databaseType *db)
{
	// int j, k;
	
	// printf("\n===GAME BOARD===\n\033[1;31m(%s's Perspective - RED)\033[0m\n", db->p2);
	// displayOpponentsCard(db);
	// viewColumnGuide(RED);
	// printf("\t\t");
	// for (j = SIDE - 1; j >= 0; j--)
	// {
	// 	for (k = SIDE - 1; k >= 0; k--)
	// 	{
	// 		if (db->board[j][k] == 'R' || db->board[j][k] == 'r')
	// 			printf("\033[1;31m%c\033[0m ", db->board[j][k]); 
	// 		else if (db->board[j][k] == 'B' || db->board[j][k] == 'b')
	// 			printf("\033[1;34m%c\033[0m ", db->board[j][k]); 
	// 		else
	// 			printf("%c ", db->board[j][k]);
	// 	}

	// 	printf("%d", j);
	// 	printf("\n");
	// }
	// displayYourCard(db);

	int row, col;
	char piece;

	printf("\n=== GAME BOARD ===\n\033[1;31m(%s's Perspective - RED)\033[0m\n", db->p2);

	displayOpponentsCard(db);
	printf("\n  ");
	viewColumnGuide(RED);
	printf("\tNeutral: %s\n", db->cardDb[db->neutralCard].name);

	for (row = SIDE - 1; row >= 0; row--)
	{
		printf("%d ", row); 
		for (col = SIDE - 1; col >= 0; col--)
		{
			piece = db->board[row][col];
			if (piece == 'R' || piece == 'r')
				printf("\033[1;31m%c\033[0m ", piece); 
			else if (piece == 'B' || piece == 'b')
				printf("\033[1;34m%c\033[0m ", piece); 
			else
				printf("%c ", piece); 
		}
		printf(" |  "); 
		for (col = 0; col < SIDE; col++)
		{
			printf("%c ", db->cardDb[db->neutralCard].card[SIDE - 1 - row][col]);
		}

		printf("\n");
	}

	printf("\n");
	displayYourCard(db);
}

/*
   This function displays the details of a specific card, including its name and movement pattern.
   Precondition: The cardType structure is initialized and contains the card data.

   @param card a cardType structure containing the card information to display

   @return this function does not return a value, it prints the card details to the screen
*/
void displayCard (cardType card[], int count)
{
	// int j;
	// int k;
	
	// printf("\n%s Card", card.name);
	// printf("\n{\n");

	// for (j = 0; j < SIDE; j++)
	// {
	// 	for (k = 0; k < SIDE; k++)
	// 	{
	// 		printf("%c ", card.card[j][k]);
	// 	}
	// 	printf("\n");
	// }

	// printf("\n}\n");
	
	int row, col, i;

	for (i = 0; i < count; i++)
	{
		printf("%s\t\t", card[i].name);
	}
	printf("\n{\n");

	for (row = 0; row < SIDE; row++)
	{
		for (i = 0; i < count; i++)
		{
			for (col = 0; col < SIDE; col++)
			{
				printf("%c ", card[i].card[row][col]);
			}
			printf("\t");
		}
		printf("\n");
	}
	printf("}\n");
}

/*
   This function displays the player's own cards.
   Precondition: The databaseType structure is initialized and contains the player's card data.

   @param db a pointer to the databaseType structure containing the game data

   @return this function does not return a value, it prints the player's cards to the screen
*/
void displayYourCard (databaseType *db)
{
	// int j;

	// for (j = 0; j < 2; j++)
	// {
	// 	displayCard(db->cardDb[db->playerCards[db->bCurrentPlayer][j]]);
	// }

	cardType cards[2];

	cards[0] = db->cardDb[db->playerCards[db->bCurrentPlayer][0]];
	cards[1] = db->cardDb[db->playerCards[db->bCurrentPlayer][1]];

	displayCard(cards, 2);
}

/*
   This function displays the opponent's cards.
   Precondition: The databaseType structure is initialized and contains the opponent's card data.

   @param db a pointer to the databaseType structure containing the game data

   @return this function does not return a value, it prints the opponent's cards to the screen
*/
void displayOpponentsCard (databaseType *db)
{
	// int j;
	// int opp = !db->bCurrentPlayer;

	// for (j = 0; j < 2; j++)
	// {
	// 	displayCard(db->cardDb[db->playerCards[opp][j]]);
	// }

	cardType cards[2];

	cards[0] = db->cardDb[db->playerCards[!db->bCurrentPlayer][0]];
	cards[1] = db->cardDb[db->playerCards[!db->bCurrentPlayer][1]];

	displayCard(cards, 2);
}

/*
   This function displays the neutral card.
   Precondition: The databaseType structure is initialized and contains the neutral card data.

   @param db a pointer to the databaseType structure containing the game data

   @return this function does not return a value, it prints the neutral card to the screen
*/
void displayNeutral (databaseType *db)
{
	// displayCard(db->cardDb[db->neutralCard]);
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






















