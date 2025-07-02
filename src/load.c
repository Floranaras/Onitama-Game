#include "../include/load.h"

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

void redMoves (cardType *card)
{
	int j;

	for (j = 0; j < card->movesCtr; j++)
	{
		card->moves[1][j].row = -card->moves[0][j].row;
		card->moves[1][j].col = -card->moves[0][j].col;
	}
}
void getMoves (cardType *card)
{
	pointType center;
	
	center.row = 2;
	center.col = 2;

	blueMoves(card, center);
	redMoves(card);	
}

void initCards (databaseType *db)
{
	int j;

	for (j = 0; j < db->numCards; j++)
	{
		getMoves(&db->cardDb[j]);
	}
}
void loadCardsFromFile (databaseType *db)
{
    loadMasterList(db);
	getCards(db);
	initCards(db);
}
