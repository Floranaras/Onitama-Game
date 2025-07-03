#include "../include/start.h"

/*
	This function initializes the game board with the default Onitama setup.
	Precondition: The databaseType structure is defined and the board is a 5x5 grid.

	@param db a pointer to the databaseType structure where the board will be initialized
*/
void initBoard (databaseType *db)
{
	int j, k;
	char temp[SIDE][SIDE] = {
							{'r','r','R','r','r'}, 
							{'.','.','.','.','.'}, 
							{'.','.','.','.','.'}, 
							{'.','.','.','.','.'},
							{'b','b','B','b','b'}
	};

	for (j = 0; j < SIDE; j++) 
	{
		for (k = 0; k < SIDE; k++)
		{
			db->board[j][k] = temp[j][k];
		}
	}
}

/*
	This function checks if a card index already exists in the cardIdx array.
	Precondition: cardIdx is an array of integers, count is the number of elements in cardIdx, and key is the integer to check for existence.

	@param cardIdx an array of integers representing card indices
	@param count the number of elements in cardIdx
	@param key the integer to check for existence in cardIdx

	@return 1 if key exists in cardIdx, otherwise 0
*/
int cardExists (int cardIdx[], int count, int key)
{
	int j;
	int bFound = 0;

	for (j = 0; j < count && !bFound; j++)	
	{	
		if (cardIdx[j] == key)
		{
			bFound = 1;
		}
	}

	return bFound;
}

/*
	This function deals cards to the players and assigns a neutral card.
	Precondition: The databaseType structure is initialized and contains the number of cards available.

	@param db a pointer to the databaseType structure containing the game data

	@return this function does not return a value, it updates the playerCards and neutralCard in the databaseType structure
*/
void dealCards(databaseType *db)
{
	int j = 0, k = 0, ctr = 0;
	int randNum;
	int cardIdx[5]; // CARDS_PER_PLAYER*2 + 1 = 2*2 + 1 = 5

	srand(time(NULL));

	do 
	{
		randNum = rand() % db->numCards;

		if (!cardExists(cardIdx, j, randNum)) 
		{
			cardIdx[j] = randNum;
			j++;
		}

	} while (j < 5);

	ctr = 0;
	for (j = 0; j < 2; j++) 
	{
		for (k = 0; k < 2; k++) 
		{
			db->playerCards[j][k] = cardIdx[ctr];
			ctr++;
		}
	}

	db->neutralCard = cardIdx[ctr];
}

/*
	This function asks  the user to input their name.
	Precondition: The String50 type is defined as a character array of size 50.

	@param name a String50 type where the user's name will be stored

	@return this function does not return a value, it updates the name with user input
*/
void getName(String50 name)
{
	printf("Input Name: ");
    scanf(" %[^\n]", name); 
}

/*
	This function initializes the game database with default values and sets up the game state.
	Precondition: The databaseType structure is defined and contains the necessary fields for the game state.

	@param db a pointer to the databaseType structure where the game state will be initialized

	@return this function does not return a value, it updates the database with initial game state
*/
void initDatabase (databaseType *db)
{
	db->bGameOver = 0;
	initBoard(db);
	loadCardsFromFile(db);
	dealCards(db);
	
	db->bCurrentPlayer = db->cardDb[db->neutralCard].bColor;

	db->blueTemple.row = 4;
	db->blueTemple.col = 2;
	db->redTemple.row = 0;
	db->redTemple.col = 2;	
}
