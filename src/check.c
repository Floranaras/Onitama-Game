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

int isValid (databaseType *db, pointType src, pointType dest, int cardIdx)
{
	char student;
	char sensei;
	
	getPieces(&student, &sensei, db->bCurrentPlayer);

	return  isOwnPiece(db, src, student,sensei) && 
			followsPattern(db, src, dest, cardIdx) &&
			isInRange(dest) &&
			!isOwnPiece(db, dest, student, sensei);
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

			if (isValid(db,src,dest,cardIdx))
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
