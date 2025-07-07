#include "game.c"
/*
    This function displays the main menu of the Onitama game and handles user input for starting the game or exiting.
    Precondition: The databaseType structure is initialized and contains the game data.

    @param db a pointer to the databaseType structure containing the game data

    @return this function does not return a value, it runs the main menu loop
*/
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
