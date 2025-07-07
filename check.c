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
   This function returns 1 if the move from src to dest matches one of the allowed move patterns in the given card for the current player; otherwise, it returns 0.
   Precondition: cardIdx is a valid index in the card database, and the board and move data are initialized.

   @param db the pointer to the game database containing the cards and current player
   @param src the starting position of the piece
   @param dest the intended destination position
   @param cardIdx the index of the move card to use for validating the move pattern

   @return 1 if the destination follows the selected card’s movement pattern, otherwise, 0
*/
int followsPattern (databaseType *db, pointType src, pointType dest, int cardIdx)
{
	int isFound = 0;
	int j;
	pointType temp;

	for (j = 0; j < db->cardDb[cardIdx].movesCtr && !isFound; j++)
	{
		temp.row = src.row + db->cardDb[cardIdx].moves[db->bCurrentPlayer][j].row;
		temp.col = src.col + db->cardDb[cardIdx].moves[db->bCurrentPlayer][j].col;

		if (temp.row == dest.row && temp.col == dest.col)
		{
			isFound = 1;
		}
	}

	return isFound;
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
   This function checks whether a move is valid based on the current player's piece ownership, the card's movement pattern, board boundaries, and whether the destination is occupied by their own piece. If verbose is enabled, it prints the reason for any invalid move.
   Precondition: The board and card data are initialized; src and dest are within board coordinates.

   @param db the pointer to the game database containing board state and current player info
   @param src the source position of the piece to move
   @param dest the intended destination position
   @param cardIdx the index of the move card to validate against
   @param verbose flag to print invalid move reasons (1 = print, 0 = silent)

   @return 1 if the move is valid, otherwise 0
*/
int isValid (databaseType *db, pointType src, pointType dest, int cardIdx, int verbose)
{
	char student, sensei;
	int bValid = 1;

	getPieces(&student, &sensei, db->bCurrentPlayer);

	if (!isOwnPiece(db, src, student, sensei))
	{
		if (verbose)
			printf("Invalid move: selected piece is not your own.\n");
		bValid = 0;
	}
	else if (!followsPattern(db, src, dest, cardIdx))
	{
		if (verbose)
			printf("Invalid move: destination does not follow the selected card's pattern.\n");
		bValid = 0;
	}
	else if (!isInRange(dest))
	{
		if (verbose)
			printf("Invalid move: destination is out of board range.\n");
		bValid = 0;
	}
	else if (isOwnPiece(db, dest, student, sensei))
	{
		if (verbose)
			printf("Invalid move: cannot move onto your own piece.\n");
		bValid = 0;
	}

	return bValid;
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
	pointType dest;

	for (card = 0; card < CARDS_PER_PLAYER && !bFound; card++)
	{
		cardIdx = db->playerCards[db->bCurrentPlayer][card];
		
		for (j = 0; j < db->cardDb[cardIdx].movesCtr; j++)
		{
			dest.row = src.row + db->cardDb[cardIdx].moves[db->bCurrentPlayer][j].row;
			dest.col = src.col + db->cardDb[cardIdx].moves[db->bCurrentPlayer][j].col;

			if (isValid(db,src,dest,cardIdx, 0))
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
