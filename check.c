#include "display.c"

/*
   This function modifies the characters used to represent the student's and sensei's pieces for the given player.
   Precondition: currentPlayer is either BLUE or RED.

   @param student a pointer to a character where the student piece symbol will be stored ('b' or 'r')
   @param sensei a pointer to a character where the sensei piece symbol will be stored ('B' or 'R')
   @param currentPlayer the current player (BLUE or RED)

   @return this function does not return a value; it modifies the values pointed to by student and sensei
*/
void getPieces (char* student, char* sensei, int currentPlayer)
{
	if (currentPlayer == BLUE)
	{
		*student = 'b';
		*sensei = 'B';
	}

	if (currentPlayer == RED)
	{
		*student = 'r';
		*sensei = 'R';
	}
}

/*
   This function returns 1 if the piece at the src position on the board belongs to the current player (student or sensei), otherwise returns 0.
   Precondition: The src coordinates are within the bounds of the board (0–4) and the board has been initialized.

   @param db the pointer to the game database containing the board
   @param src the position on the board to check
   @param student the character representing the player's student piece ('b' or 'r')
   @param sensei the character representing the player's sensei piece ('B' or 'R')

   @return 1 if the piece at src belongs to the player (student or sensei), otherwise 0
*/
int isOwnPiece (databaseType *db, pointType src, char student, char sensei)
{
	return db->board[src.row][src.col] == student || db->board[src.row][src.col] == sensei;
}

/*
   This function checks whether a given board position is within the valid 5x5 board boundaries.
   Precondition: dest is a point structure with initialized row and col values.

   @param dest the destination position to check

   @return 1 if the position is within the board (0–4 for both row and col), otherwise 0
*/
int isInRange(pointType dest)
{
	return (dest.row >= 0 && dest.row <=4) && (dest.col >= 0 && dest.col <=4);
}

/*
   This function checks if there is at least one valid move for a piece at the given source position using any of the current player's available move cards.
   Precondition: src contains a valid board position, and the board and cards are initialized.

   @param db the pointer to the game database containing the board and move cards
   @param src the position of the piece to check for possible moves

   @return 1 if at least one valid move exists using the current player's cards, otherwise 0
*/
int findMoves (databaseType *db, pointType src)
{
	int j, card, cardIdx;
	int bFound = 0;

	for (card = 0; card < CARDS_PER_PLAYER && !bFound; card++)
	{
		cardIdx = db->playerCards[db->bCurrentPlayer][card];
		
		for (j = 0; j < db->cardDb[cardIdx].movesCtr; j++)
		{
			if (isValidForRareCase(db,src,j,cardIdx))
				bFound = 1;
		}
	}
	return bFound;
}

/*
   This function checks if there are any valid moves available for the current player by iterating through all pieces on the board.
   Precondition: The board is initialized, and the current player is set.

   @param db the pointer to the game database containing the board and current player info
   
   @return 1 if at least one valid move exists for any piece of the current player, otherwise 0
*/
int hasAnyValidMoves (databaseType *db)
{
	int bFound = 0;
	pointType src;
	char student, sensei;

	getPieces(&student, &sensei, db->bCurrentPlayer);

	for (src.row = 0; src.row < SIDE && !bFound; src.row++)
	{
		for (src.col = 0; src.col < SIDE && !bFound; src.col++)
		{
			if (isOwnPiece(db, src, student, sensei))
				bFound = findMoves(db, src);
		}
	}
	
	return bFound;
}

/*
   This function checks if the piece at the source position belongs to the current player and if the move index is valid for the selected card.
   Precondition: The databaseType structure is initialized and contains the game state.

   @param db a pointer to the databaseType structure containing the game data
   @param src a pointType structure representing the source coordinates
   @param moveIdx an integer representing the move index to check
   @param cardIdx an integer representing the card index to check

   @return 1 if the piece is valid and the move index is valid, otherwise 0
*/
int isValidPiece (databaseType *db, pointType src)
{
	char sensei, student;
	getPieces(&student, &sensei, db->bCurrentPlayer);
    return isOwnPiece(db, src, student, sensei);
}

/*
   This function checks if the move index is valid for the given card index.
   Precondition: The databaseType structure is initialized and contains the card data.

   @param db a pointer to the databaseType structure containing the game data
   @param moveIdx an integer representing the move index to check
   @param cardIdx an integer representing the card index to check

   @return 1 if the move index is valid, otherwise 0
*/
int isValidMoveIdx (databaseType *db, int moveIdx, int cardIdx)
{
	return moveIdx >= 0 && moveIdx < db->cardDb[cardIdx].movesCtr;
}

/*
   This function retrieves the destination coordinates based on the source coordinates, move index, and card index.
   Precondition: The databaseType structure is initialized and contains the card data.

   @param db a pointer to the databaseType structure containing the game data
   @param src a pointType structure representing the source coordinates
   @param moveIdx an integer representing the move index
   @param cardIdx an integer representing the card index

   @return a pointType structure representing the destination coordinates
*/
pointType getDestinationFromMoveIdx (databaseType *db, pointType src, int moveIdx, int cardIdx)
{
	pointType dest;

	dest.row = src.row + db->cardDb[cardIdx].moves[db->bCurrentPlayer][moveIdx].row;
    dest.col = src.col + db->cardDb[cardIdx].moves[db->bCurrentPlayer][moveIdx].col;

	return dest;
}

/*
   This function checks if the destination coordinates are valid for the current player.
   Precondition: The databaseType structure is initialized and contains the game data.

   @param db a pointer to the databaseType structure containing the game data
   @param dest a pointType structure representing the destination coordinates

   @return 1 if the destination is valid, otherwise 0
*/
int isValidDest (databaseType *db, pointType dest)
{
	char student, sensei;
	getPieces(&student, &sensei, db->bCurrentPlayer);
    
    if (!isInRange(dest)) 
		return 0;
    if (isOwnPiece(db, dest, student, sensei)) 
		return 0;

    return 1;
}

/*
   This function checks if the destination coordinates are valid for a rare case where the player has no valid moves.
   Precondition: The databaseType structure is initialized and contains the game data.

   @param db a pointer to the databaseType structure containing the game data
   @param src a pointType structure representing the source coordinates
   @param moveIdx an integer representing the move index
   @param cardIdx an integer representing the card index

   @return 1 if the destination is valid, otherwise 0
*/
int isValidForRareCase (databaseType *db, pointType src, int moveIdx, int cardIdx)
{
	if (!isValidMoveIdx(db, moveIdx, cardIdx)) 
		return 0;
    
    pointType dest = getDestinationFromMoveIdx(db, src, moveIdx, cardIdx);

    return isValidDest(db, dest);
}

/*
   This function prompts the user for the source and destination coordinates of a piece to move.
   Precondition: The databaseType structure is initialized and contains the game state.

   @param db a pointer to the databaseType structure containing the game data
   @param src a pointer to a pointType structure where the source coordinates will be stored
   @param dest a pointer to a pointType structure where the destination coordinates will be stored
   @param cardIdx an integer representing the card index used for the move

   @return this function does not return a value, it updates src and dest based on user input
*/
int isValidUserMove (databaseType *db, pointType src, int moveIdx, int cardIdx)
{
    char student, sensei;
    pointType dest = getDestinationFromMoveIdx (db, src, moveIdx, cardIdx);
    getPieces(&student, &sensei, db->bCurrentPlayer);

	if (!isValidPiece(db, src)) 
	{
        printf("Invalid move: selected piece is not your own.\n");
        return 0;
    }
    
	else if (!isValidMoveIdx (db, moveIdx, cardIdx)) 
	{
        printf("Invalid move: move index out of range (0-%d).\n", 
               db->cardDb[cardIdx].movesCtr - 1);
        return 0;
    } 
    
	else if (!isInRange(dest)) 
	{
        printf("Invalid move: destination is out of board range.\n");
        return 0;
    }
    
	else if (isOwnPiece(db, dest, student, sensei)) 
	{
        printf("Invalid move: cannot move onto your own piece.\n");
        return 0;
    }
    
    return 1;
}
