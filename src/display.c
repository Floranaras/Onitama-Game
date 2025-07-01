#include "start.c"

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

void viewDealtCard (databaseType *db)
{
	int j;

	printf("\n===Dealth Cards===\n");
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
}

void viewRowGuide (int key)
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

	if (key == RED)
	{
		for (j = SIDE - 1; j >= 0; j--)
		{
			printf("%d ", j);
		}
		
		printf("\n");
	}
}
void viewBlueBoard (databaseType *db)
{
	int j, k;

	
	printf("\n===GAME BOARD===\n");
	viewRowGuide(BLUE);
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

void viewRedBoard (databaseType *db)
{
	int j, k;
	
	printf("\n===GAME BOARD===\n");
	viewRowGuide(RED);
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

void displayCard (cardType card)
{
	int j;
	int k;

	printf("\n{\n");

	for (j = 0; j < SIDE; j++)
	{
		for (k = 0; k < SIDE; k++)
		{
			printf("%c ", card.card[j][k]);
		}
		printf("\n");
	}

	printf("\n}\n");
}


























