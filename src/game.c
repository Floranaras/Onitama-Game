#include "../include/game.h"

/*
	This function initializes the game database with default values, including the board setup, player names, and card database.
	Precondition: The databaseType structure is defined and the card database is loaded.
	
	@param db a pointer to the databaseType structure to initialize

	@return this function does not return a value, it sets up the initial game state
*/
void startGame (databaseType *db)
{
	initDatabase(db);
	displayWelcomeMessage();
	printf("Blue Player: \n");
	getName(db->p1);
	printf("Red Player: \n");
	getName(db->p2);

	printf("\nShuffling Cards...\n");
	viewAvailableCards(db);
	viewDealtCard(db);	
}

/*
	This function checks if the current player has any valid moves available.
	Precondition: The databaseType structure is initialized and contains the game state.

	@param db a pointer to the databaseType structure containing the game data

	@return 1 if there are valid moves, otherwise 0
*/
void switchCards (databaseType *db, int cardDecIdx)
{
	int temp;

	temp = db->playerCards[db->bCurrentPlayer][cardDecIdx];
	db->playerCards[db->bCurrentPlayer][cardDecIdx] = db->neutralCard;
	db->neutralCard = temp;
}

/*
	This function handles the case when there are no valid moves available for the current player.
	Precondition: The databaseType structure is initialized and contains the game state.

	@param db a pointer to the databaseType structure containing the game data

	@return this function does not return a value, it prints a message and switches cards
*/
void rareCase (databaseType *db)
{
	switchCards(db, 0);
	printf("No valid moves available. Neutral card automatically swapped.\n");
}

/*
	This function prompts the user to select a card from their available cards.
	Precondition: The databaseType structure is initialized and contains the player's cards.

	@param db a pointer to the databaseType structure containing the game data
	@param cardDecIdx a pointer to an integer where the selected card index will be stored
	@param cardIdx a pointer to an integer where the actual card index will be stored

	@return this function does not return a value, it updates the card indices based on user input
*/
void getInputCard (databaseType *db, int *cardDecIdx, int *cardIdx)
{
	do 
	{
		printf("Select a card: \n");
		printf("0] %s\n", db->cardDb[db->playerCards[db->bCurrentPlayer][0]].name);
		printf("1] %s\n", db->cardDb[db->playerCards[db->bCurrentPlayer][1]].name);
		printf("Enter card of choice: ");
		scanf("%d", cardDecIdx);
	

	} while (!(*cardDecIdx == 1 || *cardDecIdx == 0));
	
	*cardIdx = db->playerCards[db->bCurrentPlayer][*cardDecIdx];
}

void getInputMove (databaseType *db, pointType *src, pointType *dest, int cardIdx)
{
	int bValid = 0;
    int srcRow, srcCol, destRow, destCol;

    do 
    {
        int bInputOK = 1;

        printf("Format: row col\n");

        printf("Coordinates of Piece to Move: ");
        if (scanf("%d %d", &srcRow, &srcCol) != 2)
            bInputOK = 0;

        printf("Destination of Piece: ");
        if (scanf("%d %d", &destRow, &destCol) != 2)
            bInputOK = 0;

        if (bInputOK)
        {
            src->row = srcRow;
            src->col = srcCol;
            dest->row = destRow;
            dest->col = destCol;

            if (isValid(db, *src, *dest, cardIdx, 1))
                bValid = 1;
            else
                printf("Invalid move.\n");
        }
        else
        {
            printf("Invalid input. Please enter numbers in 'row col' format.\n");
        }

        // flush buffer (only needed if scanf fails and extra junk remains)
        while (getchar() != '\n');  // only if allowed
    } while (!bValid);
}

int isEqualToTemple (databaseType *db, pointType dest)
{	
	return (dest.row == db->redTemple.row && dest.col == db->redTemple.col) ||
	(dest.row == db->blueTemple.row && dest.col == db->blueTemple.col);
}

void movePiece (databaseType *db, pointType src, pointType dest)
{
	char temp;
	char empty = '.';

	if (isEqualToTemple(db,src))
	{
		empty = '*';
	}

	temp = db->board[src.row][src.col];
	db->board[src.row][src.col] = empty;
	db->board[dest.row][dest.col] = temp;

}

void checkForTempleWin (databaseType *db, int *redTempleCapture, int *blueTempleCapture)
{

	if (db->board[db->blueTemple.row][db->blueTemple.col] == 'R' 
		|| db->board[db->blueTemple.row][db->blueTemple.col] == 'r')
	{
		*blueTempleCapture = 1;
	}

	if (db->board[db->redTemple.row][db->redTemple.col] == 'B' 
		|| db->board[db->redTemple.row][db->redTemple.col] == 'b')
	{
		*redTempleCapture = 1; 
	}

}

void checkForSensei (databaseType *db, int *redFound, int *blueFound)
{
	int j, k;

	for (j = 0; j < SIDE && !(*redFound); j++)
	{
		for (k = 0; k < SIDE && !(*redFound); k++)
		{
			if (db->board[j][k] == 'R')	
				*redFound = 1;
		}
	}
	
	for (j = 0; j < SIDE && !(*blueFound); j++)
	{
		for (k = 0; k < SIDE && !(*blueFound); k++)
		{
			if (db->board[j][k] == 'B')	
				*blueFound = 1;
		}
	}
}

void checkForWin (databaseType *db)
{
	int blueSenseiFound = 0;
	int redSenseiFound = 0;
	int blueTempleCapture = 0;
	int redTempleCapture = 0;

	checkForTempleWin(db, &redTempleCapture, &blueTempleCapture);
	checkForSensei(db, &redSenseiFound, &blueSenseiFound);

	if (blueTempleCapture)
	{
		db->bGameOver = 1;
		db->bWinner = RED;
		db->bWinCondition = TEMPLE_WIN;
	}

	if (redTempleCapture)
	{
		db->bGameOver = 1;
		db->bWinner = BLUE;
		db->bWinCondition = TEMPLE_WIN;
	}

	if (!blueSenseiFound)
	{
		db->bGameOver = 1;
		db->bWinner = RED;
		db->bWinCondition = SENSEI_WIN;
	}

	if (!redSenseiFound)
	{
		db->bGameOver = 1;
		db->bWinner = BLUE;
		db->bWinCondition = SENSEI_WIN;
	}
}

void makeMove (databaseType *db)
{
	pointType src, dest;
	int cardIdx;
	int cardDecIdx;

	if (!hasAnyValidMoves(db))
	{
		//Function to skip
		rareCase(db);
	}

	else
	{
		getInputCard(db, &cardDecIdx, &cardIdx);
		displayCard(db->cardDb[cardIdx]);
		getInputMove(db, &src, &dest, cardIdx);
		movePiece(db, src, dest);
		switchCards(db, cardDecIdx);
		//recordMoves(db); future feature to record moves for game save and hall of fame
	}
}

void clearScreen()
{
	#ifdef _WIN32
		system("cls");

	#else
		system("clear");
	#endif
}

void playerMenu (databaseType *db)
{
	int choice;

	do 
	{
		displayPlayerMenu();
		printf("Enter choice: ");
		scanf("%d", &choice);
		
		switch (choice)
		{
			case 1: makeMove(db); break;
			case 2: displayYourCard(db); break;
			case 3: displayOpponentsCard(db); break;
			case 4: displayNeutral(db); break;
			case 5: clearScreen(); displayBoard(db); break;
			default: printf("Invalid Input!\n");
		}
	}while (choice != 1);
	

}
void gameLoop (databaseType *db)
{
	startGame(db);

	while (!db->bGameOver)
	{
		displayBoard(db);
		viewDealtCard(db);
		displayWinCondition();
		playerMenu(db);
		checkForWin(db);

		db->bCurrentPlayer = !db->bCurrentPlayer;
	}

	if (db->bGameOver)
	{
		viewWinner(db);
	}
}
