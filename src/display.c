#include "../include/display.h"

void displayWelcomeMessage ()
{
	printf("\n===Welcome to Onitama===\n");
	printf("Pieces: R/r = Red Master/Student, B/b = Blue Master/Student\n");
	printf("Goal: Capture enemy master or reach their temple (middle of opposite side)\n");
	
}

void displayWinCondition ()
{
	printf("Win Conditions:\n"); 
	printf("- Capture opponent's master (R or B)\n");
	printf("RED wins by reaching (4,2) | BLUE wins by reaching (0,2)\n");
}

void displayPlayerMenu()
{
	printf("\n===Player Menu===\n");
	printf("1] Make a Move\n");
	printf("2] View Your Cards\n");
	printf("3] View Your Opponents Cards\n");
	printf("4] View Neutral Card\n");
	printf("5] Clear Screen\n");
}

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

	else if (key == RED)
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

	
	printf("\n===GAME BOARD===\n(%s's Perspective - BLUE)\n", db->p1);
	viewRowGuide(BLUE);
	for (j = 0; j < SIDE; j++)
	{
		for (k = 0; k < SIDE; k++)
		{
			if (db->board[j][k] == 'b' || db->board[j][k] == 'B')
			{
				printf("\033[1;34m%c \033[0m", db->board[j][k]);
			}
			else if (db->board[j][k] == 'r' || db->board[j][k] == 'R')
			{
				printf("\033[1;31m%c \033[0m", db->board[j][k]);
			}
			else
			{
				printf("%c ", db->board[j][k]);
			}
		}
		
		printf("%d", j);
		printf("\n");
	}
}

void viewRedBoard (databaseType *db)
{
	int j, k;
	
	printf("\n===GAME BOARD===\n(%s's Perspective - RED)\n", db->p2);
	viewRowGuide(RED);
	for (j = SIDE - 1; j >= 0; j--)
	{
		for (k = SIDE - 1; k >= 0; k--)
		{
			if (db->board[j][k] == 'b' || db->board[j][k] == 'B')
			{
				printf("\033[1;34m%c \033[0m", db->board[j][k]);
			}
			else if (db->board[j][k] == 'r' || db->board[j][k] == 'R')
			{
				printf("\033[1;31m%c \033[0m", db->board[j][k]);
			}
			else
			{
				printf("%c ", db->board[j][k]);
			}
		}

		printf("%d", j);
		printf("\n");
	}
}

void displayCard (cardType card)
{
	int j;
	int k;
	
	printf("\n%s Card", card.name);
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

void displayYourCard (databaseType *db)
{
	int j;

	for (j = 0; j < 2; j++)
	{
		displayCard(db->cardDb[db->playerCards[db->bCurrentPlayer][j]]);
	}
}

void displayOpponentsCard (databaseType *db)
{
	int j;
	int opp = !db->bCurrentPlayer;

	for (j = 0; j < 2; j++)
	{
		displayCard(db->cardDb[db->playerCards[opp][j]]);
	}
}

void displayNeutral (databaseType *db)
{
	displayCard(db->cardDb[db->neutralCard]);
}

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






















