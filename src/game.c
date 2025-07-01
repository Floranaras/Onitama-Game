#include "check.c"

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

}

void makeMove (databaseType *db)
{
		
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
			case 5: system("clear"); displayBoard(db); break;
			default: printf("Invalid Input!\n");
		}
	}while (choice == 1);
	

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

		db->bCurrentPlayer = !db->bCurrentPlayer;
	}

	if (db->bGameOver)
	{
		viewWinner(db);
	}
}
