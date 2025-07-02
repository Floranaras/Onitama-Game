#include "../include/start.h"

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
void dealCards (databaseType *db)
{
	int j = 0;
	int k = 0;
	int ctr = 0;
	int randNum;
	int cardIdx[5];

	for (j = 0; j < 5; j++)
	{
		cardIdx[j] = -1;
	}

	do
	{
		randNum = rand() % db->numCards;

		if (!cardExists(cardIdx, j, randNum))
		{
			cardIdx[j] = randNum;
			j++;
		}

	} while (j < 5);

	for (j = 0; j < CARDS_PER_PLAYER; j++)
	{
		for (k = 0; k < CARDS_PER_PLAYER; k++)
		{
			db->playerCards[j][k] = cardIdx[ctr];
			ctr++;
		}
	}

	db->neutralCard = cardIdx[ctr];
}
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

void getName(String10 name)
{
	printf("Input Name: ");
	scanf("%s", name);
}


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
