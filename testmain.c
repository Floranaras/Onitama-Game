#include <stdio.h>
#include <string.h>
#include "menu.c"

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

void testGameLogic(databaseType *db)
{
	// Test isOwnPiece function
	printf("\n===TESTING isOwnPiece===\n");
	
	db->board[2][2] = 'b';
	printf("EXPECTED (1) = %d\n", isOwnPiece(db, (pointType){2, 2}, 'b', 'B')); // student
	
	db->board[3][1] = 'B';
	printf("EXPECTED (1) = %d\n", isOwnPiece(db, (pointType){3, 1}, 'b', 'B')); // sensei
	
	db->board[1][0] = 'r';
	printf("EXPECTED (0) = %d\n", isOwnPiece(db, (pointType){1, 0}, 'b', 'B')); // opponent's piece
	
	db->board[4][4] = '.';
	printf("EXPECTED (0) = %d\n", isOwnPiece(db, (pointType){4, 4}, 'b', 'B')); // empty space
	
	db->board[0][0] = 'X';
	printf("EXPECTED (0) = %d\n", isOwnPiece(db, (pointType){0, 0}, 'b', 'B')); // invalid piece

	// Test isInRange function
	printf("\n===TESTING isInRange===\n");
	printf("EXPECTED (1) = %d\n", isInRange((pointType){0, 0})); // valid corner
	printf("EXPECTED (1) = %d\n", isInRange((pointType){4, 4})); // valid corner
	printf("EXPECTED (0) = %d\n", isInRange((pointType){-1, 2})); // invalid row
	printf("EXPECTED (0) = %d\n", isInRange((pointType){3, 5})); // invalid col
	printf("EXPECTED (0) = %d\n", isInRange((pointType){9, -1})); // both invalid

	// Test getPieces function
	printf("\n===TESTING getPieces===\n");
	char student, sensei;
	
	getPieces(&student, &sensei, BLUE);
	printf("Blue pieces: student='%c', sensei='%c' (Expected: 'b', 'B')\n", student, sensei);
	
	getPieces(&student, &sensei, RED);
	printf("Red pieces: student='%c', sensei='%c' (Expected: 'r', 'R')\n", student, sensei);
}

void testWinConditions(databaseType *db)
{
	printf("\n===TESTING Win Conditions===\n");
	
	// Clear board first
	for (int i = 0; i < SIDE; i++) {
		for (int j = 0; j < SIDE; j++) {
			db->board[i][j] = '.';
		}
	}
	
	// Test checkForSensei
	int redFound, blueFound;
	
	// Both senseis present
	db->board[1][2] = 'R';
	db->board[4][2] = 'B';
	redFound = blueFound = 0;
	checkForSensei(db, &redFound, &blueFound);
	printf("Both senseis present: Red=%d, Blue=%d (Expected: 1, 1)\n", redFound, blueFound);
	
	// Only red sensei
	db->board[4][2] = '.';
	redFound = blueFound = 0;
	checkForSensei(db, &redFound, &blueFound);
	printf("Only red sensei: Red=%d, Blue=%d (Expected: 1, 0)\n", redFound, blueFound);
	
	// Test temple win conditions
	int redTempleCapture, blueTempleCapture;
	
	// Red piece in blue temple
	db->board[4][2] = 'R'; // Blue temple at (4,2)
	redTempleCapture = blueTempleCapture = 0;
	checkForTempleWin(db, &redTempleCapture, &blueTempleCapture);
	printf("Red in blue temple: RedCapture=%d, BlueCapture=%d (Expected: 0, 1)\n", 
		   redTempleCapture, blueTempleCapture);
	
	// Blue piece in red temple
	db->board[4][2] = '.';
	db->board[0][2] = 'B'; // Red temple at (0,2)
	redTempleCapture = blueTempleCapture = 0;
	checkForTempleWin(db, &redTempleCapture, &blueTempleCapture);
	printf("Blue in red temple: RedCapture=%d, BlueCapture=%d (Expected: 1, 0)\n", 
		   redTempleCapture, blueTempleCapture);
}

void testCardOperations(databaseType *db)
{
	printf("\n===TESTING Card Operations===\n");
	
	// Test switchCards
	db->bCurrentPlayer = BLUE;
	db->playerCards[BLUE][0] = 1;
	db->neutralCard = 5;
	
	printf("Before switch: Player card=%d, Neutral=%d\n", 
		   db->playerCards[BLUE][0], db->neutralCard);
	
	switchCards(db, 0);
	
	printf("After switch: Player card=%d, Neutral=%d (Expected: 5, 1)\n", 
		   db->playerCards[BLUE][0], db->neutralCard);
	
	// Test cardExists
	int cardIdx[] = {2, 4, 7, 1, 9};
	printf("Card 4 exists in [2,4,7]: %d (Expected: 1)\n", cardExists(cardIdx, 3, 4));
	printf("Card 9 exists in [2,4,7]: %d (Expected: 0)\n", cardExists(cardIdx, 3, 9));
	printf("Card 2 exists in [2,4,7,1,9]: %d (Expected: 1)\n", cardExists(cardIdx, 5, 2));
}

void testMovement(databaseType *db)
{
	printf("\n===TESTING Movement===\n");
	
	// Test movePiece
	pointType src = {2, 2};
	pointType dest = {3, 2};
	
	db->board[2][2] = 'b';
	db->board[3][2] = '.';
	
	printf("Before move: src='%c', dest='%c'\n", 
		   db->board[src.row][src.col], db->board[dest.row][dest.col]);
	
	movePiece(db, src, dest);
	
	printf("After move: src='%c', dest='%c' (Expected: '.', 'b')\n", 
		   db->board[src.row][src.col], db->board[dest.row][dest.col]);
	
	// Test temple move
	src.row = 0; src.col = 2; // Red temple position
	dest.row = 1; dest.col = 2;
	
	db->board[0][2] = 'b';
	
	printf("Before temple move: src='%c'\n", db->board[src.row][src.col]);
	
	movePiece(db, src, dest);
	
	printf("After temple move: src='%c', dest='%c' (Expected: '*', 'b')\n", 
		   db->board[src.row][src.col], db->board[dest.row][dest.col]);
}

// NEW COMPREHENSIVE TESTS BELOW

void testFollowsPattern(databaseType *db)
{
	printf("\n===TESTING followsPattern===\n");
	
	// Initialize a simple test database with one card
	loadCardsFromFile(db);
	
	if (db->numCards > 0) {
		// Test with first available card
		int cardIdx = 0;
		pointType src = {2, 2}; // Center position
		pointType dest;
		
		printf("Testing card: %s\n", db->cardDb[cardIdx].name);
		printf("Move count: %d\n", db->cardDb[cardIdx].movesCtr);
		
		// Test for BLUE player
		db->bCurrentPlayer = BLUE;
		for (int i = 0; i < db->cardDb[cardIdx].movesCtr; i++) {
			dest.row = src.row + db->cardDb[cardIdx].moves[BLUE][i].row;
			dest.col = src.col + db->cardDb[cardIdx].moves[BLUE][i].col;
			
			int result = followsPattern(db, src, dest, cardIdx);
			printf("Blue move %d: (%d,%d) -> (%d,%d) = %d (Expected: 1)\n", 
				   i, src.row, src.col, dest.row, dest.col, result);
		}
		
		// Test invalid move
		dest.row = src.row + 3;
		dest.col = src.col + 3;
		int result = followsPattern(db, src, dest, cardIdx);
		printf("Invalid move: (%d,%d) -> (%d,%d) = %d (Expected: 0)\n", 
			   src.row, src.col, dest.row, dest.col, result);
	}
}

void testIsValid(databaseType *db)
{
	printf("\n===TESTING isValid===\n");
	
	// Setup a test scenario
	initBoard(db);
	loadCardsFromFile(db);
	dealCards(db);
	
	if (db->numCards > 0) {
		db->bCurrentPlayer = BLUE;
		int cardIdx = db->playerCards[BLUE][0];
		
		pointType src = {4, 0}; // Blue student position
		pointType dest;
		
		// Test valid move (if possible)
		if (db->cardDb[cardIdx].movesCtr > 0) {
			dest.row = src.row + db->cardDb[cardIdx].moves[BLUE][0].row;
			dest.col = src.col + db->cardDb[cardIdx].moves[BLUE][0].col;
			
			if (isInRange(dest)) {
				int result = isValid(db, src, dest, cardIdx, 0);
				printf("Valid move test: %d\n", result);
			}
		}
		
		// Test moving opponent's piece
		src.row = 0; src.col = 0; // Red piece position
		dest.row = 1; dest.col = 0;
		int result = isValid(db, src, dest, cardIdx, 0);
		printf("Moving opponent's piece: %d (Expected: 0)\n", result);
		
		// Test out of range
		src.row = 4; src.col = 0; // Blue piece
		dest.row = 5; dest.col = 0; // Out of bounds
		result = isValid(db, src, dest, cardIdx, 0);
		printf("Out of range move: %d (Expected: 0)\n", result);
		
		// Test moving to own piece
		src.row = 4; src.col = 0; // Blue piece
		dest.row = 4; dest.col = 1; // Another blue piece
		result = isValid(db, src, dest, cardIdx, 0);
		printf("Moving to own piece: %d (Expected: 0)\n", result);
	}
}

void testFindMoves(databaseType *db)
{
	printf("\n===TESTING findMoves===\n");
	
	initBoard(db);
	loadCardsFromFile(db);
	dealCards(db);
	
	db->bCurrentPlayer = BLUE;
	
	// Test blue student position
	pointType src = {4, 0};
	int result = findMoves(db, src);
	printf("Blue student at (4,0) has moves: %d\n", result);
	
	// Test blue sensei position
	src.row = 4; src.col = 2;
	result = findMoves(db, src);
	printf("Blue sensei at (4,2) has moves: %d\n", result);
	
	// Test empty position
	src.row = 2; src.col = 2;
	result = findMoves(db, src);
	printf("Empty position (2,2) has moves: %d (Expected: 0)\n", result);
	
	// Test red piece (should fail since current player is blue)
	src.row = 0; src.col = 0;
	result = findMoves(db, src);
	printf("Red piece (0,0) when blue player: %d (Expected: 0)\n", result);
}

void testHasAnyValidMoves(databaseType *db)
{
	printf("\n===TESTING hasAnyValidMoves===\n");
	
	// Test normal starting position
	initBoard(db);
	loadCardsFromFile(db);
	dealCards(db);
	
	db->bCurrentPlayer = BLUE;
	int result = hasAnyValidMoves(db);
	printf("Blue player starting position has moves: %d (Expected: 1)\n", result);
	
	db->bCurrentPlayer = RED;
	result = hasAnyValidMoves(db);
	printf("Red player starting position has moves: %d (Expected: 1)\n", result);
	
	// Test blocked scenario
	// Clear board and place only senseis in corners
	for (int i = 0; i < SIDE; i++) {
		for (int j = 0; j < SIDE; j++) {
			db->board[i][j] = '.';
		}
	}
	
	db->board[0][0] = 'B'; // Blue sensei in corner
	db->board[4][4] = 'R'; // Red sensei in opposite corner
	
	db->bCurrentPlayer = BLUE;
	result = hasAnyValidMoves(db);
	printf("Blue sensei in corner (limited cards): %d\n", result);
}

void testIsEqualToTemple(databaseType *db)
{
	printf("\n===TESTING isEqualToTemple===\n");
	
	initDatabase(db);
	
	pointType blueTemple = {4, 2};
	pointType redTemple = {0, 2};
	pointType randomPos = {2, 1};
	
	int result = isEqualToTemple(db, blueTemple);
	printf("Blue temple position (4,2): %d (Expected: 1)\n", result);
	
	result = isEqualToTemple(db, redTemple);
	printf("Red temple position (0,2): %d (Expected: 1)\n", result);
	
	result = isEqualToTemple(db, randomPos);
	printf("Random position (2,1): %d (Expected: 0)\n", result);
}

void testCheckForWin(databaseType *db)
{
	printf("\n===TESTING checkForWin (Complete Win Logic)===\n");
	
	initDatabase(db);
	
	// Test 1: Red sensei capture
	for (int i = 0; i < SIDE; i++) {
		for (int j = 0; j < SIDE; j++) {
			db->board[i][j] = '.';
		}
	}
	db->board[2][2] = 'B'; // Only blue sensei remains
	db->bGameOver = 0;
	
	checkForWin(db);
	printf("Red sensei captured - Winner: %s, Condition: %s, GameOver: %d\n",
		   (db->bWinner == BLUE) ? "BLUE" : "RED",
		   (db->bWinCondition == SENSEI_WIN) ? "SENSEI" : "TEMPLE",
		   db->bGameOver);
	
	// Test 2: Blue temple capture
	initBoard(db);
	db->board[4][2] = 'r'; // Red student in blue temple
	db->bGameOver = 0;
	
	checkForWin(db);
	printf("Blue temple captured - Winner: %s, Condition: %s, GameOver: %d\n",
		   (db->bWinner == BLUE) ? "BLUE" : "RED",
		   (db->bWinCondition == SENSEI_WIN) ? "SENSEI" : "TEMPLE",
		   db->bGameOver);
	
	// Test 3: No win condition
	initBoard(db);
	db->bGameOver = 0;
	
	checkForWin(db);
	printf("Normal game state - GameOver: %d (Expected: 0)\n", db->bGameOver);
}

void testEdgeCases(databaseType *db)
{
	printf("\n===TESTING Edge Cases===\n");
	
	// Test boundary positions
	printf("Boundary position tests:\n");
	printf("(0,0) in range: %d (Expected: 1)\n", isInRange((pointType){0, 0}));
	printf("(4,4) in range: %d (Expected: 1)\n", isInRange((pointType){4, 4}));
	printf("(-1,-1) in range: %d (Expected: 0)\n", isInRange((pointType){-1, -1}));
	printf("(5,5) in range: %d (Expected: 0)\n", isInRange((pointType){5, 5}));
	
	// Test piece recognition edge cases
	char student, sensei;
	getPieces(&student, &sensei, BLUE);
	
	// Test with various board characters
	db->board[1][1] = 'b';
	db->board[1][2] = 'B';
	db->board[1][3] = 'r';
	db->board[1][4] = 'R';
	db->board[2][1] = '.';
	db->board[2][2] = '*';
	db->board[2][3] = 'X';
	
	printf("Blue student 'b': %d (Expected: 1)\n", isOwnPiece(db, (pointType){1, 1}, student, sensei));
	printf("Blue sensei 'B': %d (Expected: 1)\n", isOwnPiece(db, (pointType){1, 2}, student, sensei));
	printf("Red student 'r': %d (Expected: 0)\n", isOwnPiece(db, (pointType){1, 3}, student, sensei));
	printf("Red sensei 'R': %d (Expected: 0)\n", isOwnPiece(db, (pointType){1, 4}, student, sensei));
	printf("Empty '.': %d (Expected: 0)\n", isOwnPiece(db, (pointType){2, 1}, student, sensei));
	printf("Temple '*': %d (Expected: 0)\n", isOwnPiece(db, (pointType){2, 2}, student, sensei));
	printf("Invalid 'X': %d (Expected: 0)\n", isOwnPiece(db, (pointType){2, 3}, student, sensei));
}

void testCardDealingEdgeCases(databaseType *db)
{
	printf("\n===TESTING Card Dealing Edge Cases===\n");
	
	loadCardsFromFile(db);
	
	// Test multiple dealing runs for uniqueness
	printf("Testing card dealing uniqueness:\n");
	for (int run = 0; run < 3; run++) {
		dealCards(db);
		printf("Run %d - Cards: [%d,%d] [%d,%d] Neutral: %d\n", 
			   run + 1,
			   db->playerCards[0][0], db->playerCards[0][1],
			   db->playerCards[1][0], db->playerCards[1][1],
			   db->neutralCard);
		
		// Verify no duplicates
		int cards[5] = {
			db->playerCards[0][0], db->playerCards[0][1],
			db->playerCards[1][0], db->playerCards[1][1],
			db->neutralCard
		};
		
		int duplicates = 0;
		for (int i = 0; i < 5; i++) {
			for (int j = i + 1; j < 5; j++) {
				if (cards[i] == cards[j]) {
					duplicates++;
				}
			}
		}
		printf("  Duplicates found: %d (Expected: 0)\n", duplicates);
	}
}

void testCompleteGameFlow(databaseType *db)
{
	printf("\n===TESTING Complete Game Flow===\n");
	
	initDatabase(db);
	
	printf("Initial game state:\n");
	printf("  Current player: %s\n", (db->bCurrentPlayer == BLUE) ? "BLUE" : "RED");
	printf("  Game over: %d (Expected: 0)\n", db->bGameOver);
	printf("  Blue temple at: (%d,%d)\n", db->blueTemple.row, db->blueTemple.col);
	printf("  Red temple at: (%d,%d)\n", db->redTemple.row, db->redTemple.col);
	
	// Test starting player is determined by neutral card color
	printf("  Neutral card: %s (color: %s)\n", 
		   db->cardDb[db->neutralCard].name,
		   (db->cardDb[db->neutralCard].bColor == BLUE) ? "BLUE" : "RED");
	printf("  Starting player matches neutral card color: %s\n",
		   (db->bCurrentPlayer == db->cardDb[db->neutralCard].bColor) ? "YES" : "NO");
	
	// Test that all pieces are in correct starting positions
	int bluePieces = 0, redPieces = 0;
	for (int i = 0; i < SIDE; i++) {
		for (int j = 0; j < SIDE; j++) {
			if (db->board[i][j] == 'b' || db->board[i][j] == 'B') bluePieces++;
			if (db->board[i][j] == 'r' || db->board[i][j] == 'R') redPieces++;
		}
	}
	printf("  Blue pieces on board: %d (Expected: 5)\n", bluePieces);
	printf("  Red pieces on board: %d (Expected: 5)\n", redPieces);
}

int main ()
{
	databaseType db;

	printf("=== ONITAMA COMPREHENSIVE TESTING ===\n");

	printf("\n1. Testing Master List Loading...\n");
	testMasterList(&db);
	
	printf("\n2. Testing Card Loading...\n");
	testCard(&db);
	
	printf("\n3. Testing Move Calculations...\n");
	testCalc(&db);
	
	printf("\n4. Testing Board Initialization...\n");
	testBoard(&db);
	
	printf("\n5. Testing Card Dealing...\n");
	printf("Number of cards: %d\n", db.numCards);
	testDealing(&db);
	
	printf("\n6. Testing Display Functions...\n");
	viewAvailableCards(&db);
	viewDealtCard(&db);
	viewBlueBoard(&db);
	viewRedBoard(&db);
	
	printf("\n7. Testing Game Logic Functions...\n");
	testGameLogic(&db);
	
	printf("\n8. Testing Win Conditions...\n");
	testWinConditions(&db);
	
	printf("\n9. Testing Card Operations...\n");
	testCardOperations(&db);
	
	printf("\n10. Testing Movement Functions...\n");
	testMovement(&db);

	// NEW COMPREHENSIVE TESTS
	printf("\n11. Testing followsPattern Function...\n");
	testFollowsPattern(&db);
	
	printf("\n12. Testing isValid Function...\n");
	testIsValid(&db);
	
	printf("\n13. Testing findMoves Function...\n");
	testFindMoves(&db);
	
	printf("\n14. Testing hasAnyValidMoves Function...\n");
	testHasAnyValidMoves(&db);
	
	printf("\n15. Testing isEqualToTemple Function...\n");
	testIsEqualToTemple(&db);
	
	printf("\n16. Testing Complete Win Logic...\n");
	testCheckForWin(&db);
	
	printf("\n17. Testing Edge Cases...\n");
	testEdgeCases(&db);
	
	printf("\n18. Testing Card Dealing Edge Cases...\n");
	testCardDealingEdgeCases(&db);
	
	printf("\n19. Testing Complete Game Flow...\n");
	testCompleteGameFlow(&db);
	
	printf("\n=== TESTING COMPLETE ===\n");
	printf("Review the output above to verify all functions work correctly.\n");
	printf("Expected values are shown in parentheses for comparison.\n");
	printf("Total test categories: 19\n");

    return 0;
}
