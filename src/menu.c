#include "../include/head.h"

void gameLoop (databaseType *db)
{
        
}

void mainMenu (databaseType *db)
{
    char choice;
    
    do 
    {
        printf("\n===Onimata CLI===\n");
        printf("1] Start Game\n");
        printf("x] Exit\n");

        switch (choice)
        {
            case '1': gameLoop(db); break;
            case 'X':
            case 'x': printf("Exiting...\n");
            default: printf("Invalid Input!\n Please try again\n");
        }
    } while (choice != 'x' && choice != 'X'); 
}
