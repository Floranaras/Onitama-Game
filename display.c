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
            printf("%s%d" RESET_COLOR " ", color, *moveNum);
            (*moveNum)++;
        }
        else
            printf("%s%c" RESET_COLOR " ", color, ch);
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
    int opponent = !db->bCurrentPlayer;

    printf("\t\t");

    // Your cards (Blue)
    printCardCol(&db->cardDb[db->playerCards[db->bCurrentPlayer][0]], 
                 cardRow, &moveNum[0], BLUE_COLOR);
    printf("\t");
    printCardCol(&db->cardDb[db->playerCards[db->bCurrentPlayer][1]], 
                 cardRow, &moveNum[1], BLUE_COLOR);
    printf("\t");

    // Opponent cards (Red)
    printCardCol(&db->cardDb[db->playerCards[opponent][0]], 
                 cardRow, &moveNum[2], RED_COLOR);
    printf("\t");
    printCardCol(&db->cardDb[db->playerCards[opponent][1]], 
                 cardRow, &moveNum[3], RED_COLOR);
    printf("\t");

    // Neutral card
    printNeutralCol(&db->cardDb[db->neutralCard], cardRow, &moveNum[4]);
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
            printf("%s%d" RESET_COLOR " ", color, *moveNum);
            (*moveNum)++;
        }
        else
            printf("%s%c" RESET_COLOR " ", color, ch);
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
    int opponent = !db->bCurrentPlayer;

    printf("\t\t");

    // Your cards (Blue)
    printCardCol(&db->cardDb[db->playerCards[db->bCurrentPlayer][0]], 
                 cardRow, &moveNum[0], BLUE_COLOR);
    printf("\t");
    printCardCol(&db->cardDb[db->playerCards[db->bCurrentPlayer][1]], 
                 cardRow, &moveNum[1], BLUE_COLOR);
    printf("\t");

    // Opponent cards (Red)
    printCardCol(&db->cardDb[db->playerCards[opponent][0]], 
                 cardRow, &moveNum[2], RED_COLOR);
    printf("\t");
    printCardCol(&db->cardDb[db->playerCards[opponent][1]], 
                 cardRow, &moveNum[3], RED_COLOR);
    printf("\t");

    // Neutral card
    printNeutralCol(&db->cardDb[db->neutralCard], cardRow, &moveNum[4]);
}

/*
   This function displays the game board from the perspective of the blue player, including the player's cards, opponent's cards and the neutral card horizontally.
   Precondition: The databaseType structure is initialized and contains the game board data.

   @param db a pointer to the databaseType structure containing the game data

   @return this function does not return a value, it prints the blue player's perspective of the game board to the screen
*/
void viewBlueBoard (databaseType *db)
{
    int row, col, cardRow;
	char piece;
	int moveNum[5] = {0}; 
	int opponent = !db->bCurrentPlayer;

	printf("\n=== GAME BOARD ===\t\033[1;34m======= YOUR CARDS =======\033[0m\t\033[1;31m===== OPPONENT CARDS =====\033[0m\t=== NEUTRAL CARD ===\n");
	
	printf("  ");
	viewColumnGuide(BLUE); 
	printf("\t\t\033[1;34m%-10s\t%-10s\033[0m\t\033[1;31m%-10s\t%-10s\033[0m\t%-10s\n", 
		db->cardDb[db->playerCards[db->bCurrentPlayer][0]].name, 
		db->cardDb[db->playerCards[db->bCurrentPlayer][1]].name, 
		db->cardDb[db->playerCards[opponent][0]].name, 
		db->cardDb[db->playerCards[opponent][1]].name, 
		db->cardDb[db->neutralCard].name);

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
    int opponent = !db->bCurrentPlayer;

    printf("\t\t");

    // Your cards (Red)
    printCardCol(&db->cardDb[db->playerCards[db->bCurrentPlayer][0]], 
                 cardRow, &moveNum[0], RED_COLOR);
    printf("\t");
    printCardCol(&db->cardDb[db->playerCards[db->bCurrentPlayer][1]], 
                 cardRow, &moveNum[1], RED_COLOR);
    printf("\t");

    // Opponent cards (Blue)
    printCardCol(&db->cardDb[db->playerCards[opponent][0]], 
                 cardRow, &moveNum[2], BLUE_COLOR);
    printf("\t");
    printCardCol(&db->cardDb[db->playerCards[opponent][1]], 
                 cardRow, &moveNum[3], BLUE_COLOR);
    printf("\t");

    // Neutral card
    printNeutralCol(&db->cardDb[db->neutralCard], cardRow, &moveNum[4]);
}

void printRedCardRow (databaseType *db, int cardRow, int *moveNum)
{
    int opponent = !db->bCurrentPlayer;

    printf("\t\t");

    // Your cards (Red)
    printCardCol(&db->cardDb[db->playerCards[db->bCurrentPlayer][0]], 
                 cardRow, &moveNum[0], RED_COLOR);
    printf("\t");
    printCardCol(&db->cardDb[db->playerCards[db->bCurrentPlayer][1]], 
                 cardRow, &moveNum[1], RED_COLOR);
    printf("\t");

    // Opponent cards (Blue)
    printCardCol(&db->cardDb[db->playerCards[opponent][0]], 
                 cardRow, &moveNum[2], BLUE_COLOR);
    printf("\t");
    printCardCol(&db->cardDb[db->playerCards[opponent][1]], 
                 cardRow, &moveNum[3], BLUE_COLOR);
    printf("\t");

    // Neutral card
    printNeutralCol(&db->cardDb[db->neutralCard], cardRow, &moveNum[4]);
}

/*
   This function displays the game board from the perspective of the red player, including the player's cards, opponent's cards and the neutral card horizontally.
   Precondition: The databaseType structure is initialized and contains the game board data.

   @param db a pointer to the databaseType structure containing the game data

   @return this function does not return a value, it prints the red player's perspective of the game board to the screen
*/
void viewRedBoard (databaseType *db)
{
	int row, col, cardRow;
	char piece;
	int moveNum[5] = {0};
	int opponent = !db->bCurrentPlayer;

	printf("\n=== GAME BOARD ===\t\033[1;31m======= YOUR CARDS =======\033[0m\t\033[1;34m===== OPPONENT CARDS =====\033[0m\t=== NEUTRAL CARD ===\n");
	printf("  ");
	viewColumnGuide(RED);
	printf("\t\t\033[1;31m%-10s\t%-10s\033[0m\t\033[1;34m%-10s\t%-10s\033[0m\t%-10s\n", 
		db->cardDb[db->playerCards[db->bCurrentPlayer][0]].name, 
		db->cardDb[db->playerCards[db->bCurrentPlayer][1]].name, 
		db->cardDb[db->playerCards[opponent][0]].name, 
		db->cardDb[db->playerCards[opponent][1]].name, 
		db->cardDb[db->neutralCard].name);

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

// int findMoveIndex(databaseType *db, int cardIdx, int row, int col)
// {
//     int moveIdx = 0;
    
//     while (moveIdx < db->cardDb[cardIdx].movesCtr) 
//     {
//         pointType movePos;
//         movePos.row = 2 + db->cardDb[cardIdx].moves[db->bCurrentPlayer][moveIdx].row;
//         movePos.col = 2 + db->cardDb[cardIdx].moves[db->bCurrentPlayer][moveIdx].col;
        
//         if (movePos.row == row && movePos.col == col) 
//         {
//             return moveIdx;
//         }
        
//         moveIdx++;
//     }
    
//     return -1; // Should never happen for valid 'x' positions
// }

/*
   This function displays the details of a specific card, including its name and movement pattern.
   Precondition: The cardType structure is initialized and contains the card data.

   @param card a cardType structure containing the card information to display

   @return this function does not return a value, it prints the card details to the screen
*/
void displayCard (cardType card[])
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
	int moveNum[CARDS_PER_PLAYER] = {0};

	for (i = 0; i < CARDS_PER_PLAYER; i++)
	{
		printf("%s\t\t", card[i].name);
	}
	printf("\n{\n");

	for (row = 0; row < SIDE; row++)
	{
		for (i = 0; i < CARDS_PER_PLAYER; i++)
		{
			for (col = 0; col < SIDE; col++)
			{
				if (card[i].card[row][col] == 'x')
					printf("%d ", moveNum[i]++);
				else
					printf("%c ", card[i].card[row][col]);
			}
			printf("\t");
		}
		printf("\n");
	}
	printf("}\n");
}

/*
   This function displays the chosen card based on the card index provided.
   Precondition: The databaseType structure is initialized and contains the card data.

   @param db a pointer to the databaseType structure containing the game data
   @param cardIdx the index of the card to display

   @return this function does not return a value, it prints the chosen card to the screen
*/
void displayChosenCard(databaseType *db, int cardIdx)
{
	int row, col;
	char output;
	int moveNum = 0;
	cardType card = db->cardDb[cardIdx];

	printf("\n%s Card", card.name);
	printf("\n{\n");

	for (row = 0; row < SIDE; row++)
	{
		for (col = 0; col < SIDE; col++)
		{
			output = card.card[row][col];

			if (output == 'x')
			{
				printf("%d ", moveNum);
				moveNum++;
			}
			else
			{
				printf("%c ", output);
			}
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

	displayCard(cards);
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

	displayCard(cards);
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
		viewBlueBoard(db);
	else if (db->bCurrentPlayer == RED)
		viewRedBoard(db);
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
        printf("%s (Blue) wins by Temple Capture!\n", db->p1);
    else if (db->bWinner == BLUE && db->bWinCondition == SENSEI_WIN) 
        printf("%s (Blue) wins by Master Capture!\n", db->p1);
    else if (db->bWinner == RED && db->bWinCondition == TEMPLE_WIN) 
        printf("%s (Red) wins by Temple Capture!\n", db->p2);
    else if (db->bWinner == RED && db->bWinCondition == SENSEI_WIN) 
        printf("%s (Red) wins by Master Capture!\n", db->p2);
}
