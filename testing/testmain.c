#include <stdio.h>
#include <string.h>
#include "../include/game.h"

void printArr (char arr[][SIDE])
{
	int j;
	int k;

	printf("\n{\n");

	for (j = 0; j < SIDE; j++)
	{
		for (k = 0; k < SIDE; k++)
		{
			printf("%c ", arr[j][k]);
		}
		printf("\n");
	}


	printf("\n}\n");
}


void displayInfo (String10 name, int color, char card[][SIDE])
{
	String10 colour;

	if (color == RED)
	{
		strcpy(colour,"RED");
	}

	else 
	{
		strcpy(colour,"BLUE");
	}

	printf("\n===%s Card===\n", name);
	printf("Color: %s", colour);
	printf("\n===Card PATTERN===\n");
	printArr(card);

}
void testCard (databaseType *db)
{	
	int j;
	getCards(db);

	for (j = 0; j < db->numCards; j++)
	{
		displayInfo(db->cardDb[j].name,
		db->cardDb[j].bColor,db->cardDb[j].card);
	}
}

void dbMasterList(databaseType *db)
{
    int j = 0;

    for (j = 0; j < db->numCards; j++)
    {
        printf("%s\n", db->cardDb[j].name);
    }
}

void testMasterList (databaseType *db)
{

    if (loadMasterList(db))
    {
        printf("PASS\n");
    }

    else 
    {
        printf("FAIL\n");
    }

    printf("\n===PRINTF DEBUG===\n");
    
    dbMasterList(db);

}

void displayCardCal (cardType card)
{
	int j;

	printf("\n===%s Card===\n", card.name);

	printf("Blue Moves : \n");
	for (j = 0; j < card.movesCtr; j++)
	{
		printf("[%d %d]\n", card.moves[0][j].row, card.moves[0][j].col);
	}
	printf("\nRed Moves : \n");

	for (j = 0; j < card.movesCtr; j++)
	{ 
		printf("[%d %d]\n", card.moves[1][j].row, card.moves[1][j].col);
	}

}
void testCalc (databaseType *db)
{	
	int j;

	initCards(db);
	
	for (j = 0; j < db->numCards; j++)
	{
		displayCardCal(db->cardDb[j]);
	}

}

void testBoard (databaseType *db)
{
	initBoard(db);
	printf("\n===DEBUG BOARD TEST===\n");
	printArr(db->board);
}

void testDealing (databaseType *db)
{	
	int j, k;
	dealCards(db);
	
	printf("Neutral: %d\n", db->neutralCard);

	for (j = 0; j < CARDS_PER_PLAYER; j++)
	{
		for (k = 0; k < CARDS_PER_PLAYER; k++)
		{
			printf("%d ", db->playerCards[j][k]);
		}

		printf("\n");
	}


}
int main ()
{
	databaseType db;

	testMasterList(&db);
	testCard(&db);
	testCalc(&db);
	testBoard(&db);
	printf("%d\n", db.numCards);
	testDealing(&db);
	viewAvailableCards(&db);
	viewDealtCard(&db);
	viewBlueBoard(&db);
	viewRedBoard(&db);
	
	db.board[2][2] = 'b';
	printf("\nEXPECTED (1) = %d\n", isOwnPiece(&db, (pointType){2, 2}, 'b', 'B')); // student
	db.board[3][1] = 'B';
	printf("EXPECTED (1) = %d\n", isOwnPiece(&db, (pointType){3, 1}, 'b', 'B')); // sensei
	db.board[1][0] = 'r';
	printf("EXPECTED (0) = %d\n", isOwnPiece(&db, (pointType){1, 0}, 'b', 'B')); // opponent's piece
	db.board[4][4] = '.';
	printf("EXPECTED (0) = %d\n", isOwnPiece(&db, (pointType){4, 4}, 'b', 'B')); // empty space
	db.board[0][0] = 'X';
	printf("EXPECTED (0) = %d\n\n", isOwnPiece(&db, (pointType){4, 4}, 'b', 'B')); // invalid piece

	db.cardDb[db.neutralCard].card[0][1] = 1;
	displayCard(db.cardDb[db.neutralCard]);

    return 0;
}
