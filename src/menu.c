#include "game.c"

void mainMenu (databaseType *db)
{
    char choice;
 
    do 
    {
        printf("\n===Onimata CLI===\n");
        printf("1] Start Game\n");
        printf("x] Exit\n");

		printf("Enter choice: ");
		scanf(" %c", &choice);

        switch (choice)
        {
            case '1': gameLoop(db); break;
            case 'X':
            case 'x': printf("Exiting...\n"); break;
            default: printf("Invalid Input!\n Please try again\n");
        }
    } while (choice != 'x' && choice != 'X'); 
}
