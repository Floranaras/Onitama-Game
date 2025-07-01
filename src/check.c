#include "display.c"

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

int isOwnPiece (databaseType *db, pointType src, char student, char sensei)
{
	return db->board[src.row][src.col] == student || db->board[src.row][src.col] == sensei;
}

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

int isInRange(pointType dest)
{
	return (dest.row >= 0 && dest.row <=4) && (dest.col >= 0 && dest.col <=4);
}

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
