#include "onitama.h"
/*
	This function loads the master list of cards from a TXT file into the database.
	Precondition: The databaseType structure is defined and the master list file exists
	              inside the required "data/" directory.

	@param db a pointer to the databaseType structure where the card data will be loaded

	@return 1 if the master list is loaded successfully, otherwise 0
*/
int loadMasterList (databaseType *db)
{
	FILE* fp = fopen(MASTER_LIST,"r");
	int bSuccess = 1;
	int j = 0;

	if (fp == NULL)
	{
		fprintf (stderr, "Masterlist file not found!\n");
		bSuccess = 0;
	}

	if (bSuccess)
	{
		if (fscanf(fp,"%d", &db->numCards) != 1)
		{
			fprintf (stderr, "Invalid Card Count in Masterlist \n");
			bSuccess = 0;
		}
	}

	while (j < db->numCards && bSuccess)
	{
		if (fscanf(fp,"%s", db->cardDb[j].name) != 1)
		{
			fprintf (stderr, "Error cannot read card name\n");
			bSuccess = 0;
		}

		j++;
	}

	fclose (fp);

	return bSuccess;
}

/*
	This function retrieves the card patterns from a file and stores them in the database.
	Precondition: The databaseType structure is defined and the card file exists
	              inside the required "data/" directory.
				  
	@param db a pointer to the databaseType structure where the card patterns will be stored
	@param filename the name of the file containing the card patterns
	@param idx the index of the card in the database

	@return 1 if the card patterns are loaded successfully, otherwise 0
*/
int getCardPatterns (databaseType *db, String30 filename, int idx)
{
	int bSuccess = 1;
	int j;
	int k;
	FILE *fp = fopen(filename, "r");
	char buff[10];
	String10 tempColor;
	
	if (fp == NULL)
	{
		printf("%s not found\n", filename);
		bSuccess = 0;
	}

	if (bSuccess)
	{
		if (fscanf(fp,"%s", tempColor) != 1)
		{
			bSuccess = 0;
		}

		else 
		{
			if (!strcmp(tempColor,"blue"))	
			{
				db->cardDb[idx].bColor = BLUE; 
			}

			if (!strcmp(tempColor,"red"))	
			{
				db->cardDb[idx].bColor = RED; 
			}
		}
	}

	for (j = 0; j < SIDE && bSuccess; j++)
	{
		if (fscanf(fp,"%5s",buff) != 1)
		{
			fprintf(fp,"Error in the pattern reading\n");
			bSuccess = 0;
		}

		else 
		{
			for (k = 0; k < SIDE ; k++)	
			{
				db->cardDb[idx].card[j][k] = buff[k];
			}
		}
	}

	fclose(fp);

	return bSuccess;
}

/*
	This function retrieves the card patterns for all cards in the database from their respective files.
	Precondition: The databaseType structure is defined and the card file exists
	              inside the required "data/" directory.

	@param db a pointer to the databaseType structure where the card patterns will be stored

	@return 1 if all card patterns are loaded successfully, otherwise 0
*/
int getCards (databaseType *db)
{
	String30 filename;
	int j;
	int bSuccess = 1;

	for (j = 0; j < db->numCards && bSuccess; j++)
	{
		strcpy(filename, "data/");
		strcat(filename, db->cardDb[j].name);
		strcat(filename, ".txt");
		
		if (!getCardPatterns(db, filename, j))
		{	
			printf("Problems with reading %s\n", filename);
			bSuccess = 0;	
		}
	}

	return bSuccess;
}

/*
	This function calculates the possible moves for the blue player based on the current card and center position using relative move coordinates.
	Precondition: The cardType structure is initialized and contains the card data.

	@param card a pointer to the cardType structure containing the card data
	@param center the center point of the board

	@return this function does not return a value, it updates the moves array in the cardType structure
*/
void blueMoves (cardType *card, pointType center)
{
	int j, k;
	pointType dest[MAX_MOVES];
	card->movesCtr = 0;			 

	for (j = 0; j < SIDE; j++)
	{
		for (k = 0; k < SIDE; k++)
		{
			if (card->card[j][k] == 'x')
			{
				dest[card->movesCtr].row = j;
				dest[card->movesCtr].col = k;	
				card->movesCtr++;			 
			}
		}
	}

	for (j = 0; j < card->movesCtr; j++)
	{
		card->moves[0][j].row = dest[j].row - center.row;
		card->moves[0][j].col = dest[j].col - center.col;
	}	
}

/*
	This function calculates the possible moves for the red player based on the blue player's moves by negating the relative move coordinates.
	Precondition: The cardType structure is initialized and contains the card data.

	@param card a pointer to the cardType structure containing the card data

	@return this function does not return a value, it updates the moves array in the cardType structure
*/
void redMoves (cardType *card)
{
	int j;

	for (j = 0; j < card->movesCtr; j++)
	{
		card->moves[1][j].row = -card->moves[0][j].row;
		card->moves[1][j].col = -card->moves[0][j].col;
	}
}

/*
	This function initializes the moves for all cards in the database by calculating the possible moves for each card.
	Precondition: The databaseType structure is initialized and contains the card data.

	@param db a pointer to the databaseType structure containing the game data

	@return this function does not return a value, it updates the moves for each card in the database
*/
void getMoves (cardType *card)
{
	pointType center;
	
	center.row = 2;
	center.col = 2;

	blueMoves(card, center);
	redMoves(card);	
}

/*
	This function initializes the moves for all cards in the database by calling getMoves for each card.
	Precondition: The databaseType structure is initialized and contains the card data.

	@param db a pointer to the databaseType structure containing the game data

	@return this function does not return a value, it updates the moves for each card in the database
*/
void initCards (databaseType *db)
{
	int j;

	for (j = 0; j < db->numCards; j++)
	{
		getMoves(&db->cardDb[j]);
	}
}

/*
	This function loads the master list of cards, retrieves the card patterns, and initializes the moves for all cards in the database.
	Precondition: The databaseType structure is defined and the card file exists
	              inside the required "data/" directory.

	@param db a pointer to the databaseType structure where the card data will be loaded

	@return this function does not return a value, it updates the database with card data
*/
void loadCardsFromFile (databaseType *db)
{
    loadMasterList(db);
	getCards(db);
	initCards(db);
}
