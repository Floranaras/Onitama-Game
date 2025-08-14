#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Include your existing game logic
#include "menu.c"

// UI state structure
typedef struct {
    databaseType *db;
    int cursor_row, cursor_col;
    pointType selected_src;
    int selected_card;
    int selected_card_deck_idx;
    int move_index;
    int src_selected;
    int card_selected;
    int game_state; // 0=select_card, 1=select_piece, 2=select_dest
} GameState;

// Color pairs
#define COLOR_BLUE_PIECE 1
#define COLOR_RED_PIECE 2
#define COLOR_SELECTED 3
#define COLOR_POSSIBLE_MOVE 4
#define COLOR_CURSOR 5
#define COLOR_TEMPLE 6

// Function prototypes
void init_colors(void);
void draw_board_and_cards(GameState *state);
void draw_card_row(GameState *state, int card_row);
void draw_status(GameState *state);
void draw_instructions(GameState *state);
void highlight_possible_moves(GameState *state);
int handle_input(GameState *state, int ch);
void reset_selections(GameState *state);
int find_move_index(GameState *state, pointType dest);
void show_win_message(GameState *state);
void run_enhanced_game(databaseType *db);

int main(int argc, char **argv) {
    (void)argc; // Suppress unused parameter warning
    (void)argv; // Suppress unused parameter warning
    
    databaseType db;
    
    printf("Choose game mode:\n");
    printf("1. Enhanced Console (Arrow Keys)\n");
    printf("2. Original Console\n");
    printf("Enter choice (1-2): ");
    
    int choice;
    if (scanf("%d", &choice) == 1 && choice == 1) {
        // Enhanced mode
        initDatabase(&db);
        strcpy(db.p1, "Blue Player");
        strcpy(db.p2, "Red Player");
        run_enhanced_game(&db);
    } else {
        // Original mode
        mainMenu(&db);
    }
    
    return 0;
}

void run_enhanced_game(databaseType *db) {
    // Initialize ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    
    // Initialize colors if terminal supports it
    if (has_colors()) {
        start_color();
        init_colors();
    }
    
    // Initialize game state
    GameState state = {0};
    state.db = db;
    state.cursor_row = 2;
    state.cursor_col = 2;
    state.game_state = 0; // Start with card selection
    
    // Main game loop
    while (!db->bGameOver) {
        clear();
        
        // Draw game components
        draw_board_and_cards(&state);
        draw_status(&state);
        draw_instructions(&state);
        
        refresh();
        
        // Handle input
        int ch = getch();
        if (handle_input(&state, ch)) {
            break; // Exit requested
        }
        
        // Check for win condition
        checkForWin(db);
        if (db->bGameOver) {
            show_win_message(&state);
            break;
        }
    }
    
    // Cleanup
    endwin();
}

void init_colors(void) {
    init_pair(COLOR_BLUE_PIECE, COLOR_BLUE, COLOR_BLACK);
    init_pair(COLOR_RED_PIECE, COLOR_RED, COLOR_BLACK);
    init_pair(COLOR_SELECTED, COLOR_BLACK, COLOR_GREEN);
    init_pair(COLOR_POSSIBLE_MOVE, COLOR_BLACK, COLOR_YELLOW);
    init_pair(COLOR_CURSOR, COLOR_BLACK, COLOR_WHITE);
    init_pair(COLOR_TEMPLE, COLOR_YELLOW, COLOR_BLACK);
}

void draw_board_and_cards(GameState *state) {
    // Main title
    mvprintw(0, 25, "=== ONITAMA - ENHANCED CONSOLE ===");
    
    // Board section with player-specific perspective
    mvprintw(2, 2, "=== GAME BOARD ===");
    mvprintw(2, 25, "==== YOUR CARDS ====");
    mvprintw(2, 50, "== OPPONENT CARDS ==");
    mvprintw(2, 75, "= NEUTRAL CARD =");
    
    // Column headers for board (flip based on current player)
    if (state->db->bCurrentPlayer == BLUE) {
        mvprintw(3, 4, "0 1 2 3 4");
    } else {
        mvprintw(3, 4, "4 3 2 1 0");
    }
    
    // Draw board and cards side by side
    for (int display_row = 0; display_row < 5; display_row++) {
        // Determine actual board row based on player perspective
        int actual_row;
        if (state->db->bCurrentPlayer == BLUE) {
            actual_row = display_row;
        } else {
            actual_row = 4 - display_row;  // Flip for red player
        }
        
        // Board row number (flip for red player)
        if (state->db->bCurrentPlayer == BLUE) {
            mvprintw(4 + display_row, 2, "%d", actual_row);
        } else {
            mvprintw(4 + display_row, 2, "%d", actual_row);
        }
        
        // Draw board pieces
        for (int display_col = 0; display_col < 5; display_col++) {
            // Determine actual board column based on player perspective
            int actual_col;
            if (state->db->bCurrentPlayer == BLUE) {
                actual_col = display_col;
            } else {
                actual_col = 4 - display_col;  // Flip for red player
            }
            
            int y = 4 + display_row;
            int x = 4 + display_col * 2;
            
            char piece = state->db->board[actual_row][actual_col];
            char display_char;
            int color_pair = 0;
            
            // Determine piece display
            if (piece == '.') {
                display_char = '.';
            } else if (piece == '*') {
                display_char = '*';
                color_pair = COLOR_TEMPLE;
            } else if (piece == 'b') {
                display_char = 'b';
                color_pair = COLOR_BLUE_PIECE;
            } else if (piece == 'B') {
                display_char = 'B';
                color_pair = COLOR_BLUE_PIECE;
            } else if (piece == 'r') {
                display_char = 'r';
                color_pair = COLOR_RED_PIECE;
            } else if (piece == 'R') {
                display_char = 'R';
                color_pair = COLOR_RED_PIECE;
            } else {
                display_char = piece;
            }
            
            // Apply special highlighting (adjust cursor position for flipped board)
            if (state->cursor_row == actual_row && state->cursor_col == actual_col) {
                color_pair = COLOR_CURSOR;
            } else if (state->src_selected && 
                      state->selected_src.row == actual_row && 
                      state->selected_src.col == actual_col) {
                color_pair = COLOR_SELECTED;
            }
            
            // Draw the piece
            if (color_pair > 0 && has_colors()) {
                attron(COLOR_PAIR(color_pair));
                mvaddch(y, x, display_char);
                attroff(COLOR_PAIR(color_pair));
            } else {
                mvaddch(y, x, display_char);
            }
        }
        
        // Draw card patterns horizontally
        draw_card_row(state, display_row);
    }
    
    // Highlight possible moves
    if (state->src_selected && state->card_selected) {
        highlight_possible_moves(state);
    }
}

void draw_card_row(GameState *state, int card_row) {
    int current_player = state->db->bCurrentPlayer;
    int opponent = !current_player;
    static int move_counters[5] = {0}; // For numbering moves
    
    // Reset move counters at the start of each card display
    if (card_row == 0) {
        for (int i = 0; i < 5; i++) {
            move_counters[i] = 0;
        }
    }
    
    // Your cards (current player)
    for (int card_slot = 0; card_slot < 2; card_slot++) {
        int cardIdx = state->db->playerCards[current_player][card_slot];
        int start_x = 25 + (card_slot * 11); // 11 chars spacing between cards
        
        if (card_row == 0) {
            // Card name and selection indicator
            if (state->card_selected && state->selected_card == cardIdx) {
                if (has_colors()) {
                    attron(COLOR_PAIR(COLOR_SELECTED));
                }
                mvprintw(3, start_x, "[%d]%s*SEL*", card_slot, state->db->cardDb[cardIdx].name);
                if (has_colors()) {
                    attroff(COLOR_PAIR(COLOR_SELECTED));
                }
            } else {
                mvprintw(3, start_x, "[%d]%s", card_slot, state->db->cardDb[cardIdx].name);
            }
        }
        
        // Draw card pattern row (from current player's perspective)
        for (int col = 0; col < 5; col++) {
            char ch = state->db->cardDb[cardIdx].card[card_row][col];
            int y = 4 + card_row;
            int x = start_x + col;
            
            if (ch == 'x') {
                // This is a move position - show numbered move
                if (has_colors()) {
                    if (current_player == BLUE) {
                        attron(COLOR_PAIR(COLOR_BLUE_PIECE));
                    } else {
                        attron(COLOR_PAIR(COLOR_RED_PIECE));
                    }
                }
                mvaddch(y, x, '0' + move_counters[card_slot]);
                if (has_colors()) {
                    if (current_player == BLUE) {
                        attroff(COLOR_PAIR(COLOR_BLUE_PIECE));
                    } else {
                        attroff(COLOR_PAIR(COLOR_RED_PIECE));
                    }
                }
                move_counters[card_slot]++;
            } else if (ch == 'S') {
                // Center piece position
                mvaddch(y, x, 'S');
            } else {
                mvaddch(y, x, ch);
            }
        }
    }
    
    // Opponent cards
    for (int card_slot = 0; card_slot < 2; card_slot++) {
        int cardIdx = state->db->playerCards[opponent][card_slot];
        int start_x = 50 + (card_slot * 11);
        
        if (card_row == 0) {
            mvprintw(3, start_x, "%s", state->db->cardDb[cardIdx].name);
        }
        
        // Draw opponent card pattern (from their perspective - flipped)
        for (int col = 0; col < 5; col++) {
            char ch = state->db->cardDb[cardIdx].card[card_row][col];
            int y = 4 + card_row;
            int x = start_x + col;
            
            if (ch == 'x') {
                if (has_colors()) {
                    if (opponent == BLUE) {
                        attron(COLOR_PAIR(COLOR_BLUE_PIECE));
                    } else {
                        attron(COLOR_PAIR(COLOR_RED_PIECE));
                    }
                }
                mvaddch(y, x, '0' + move_counters[2 + card_slot]);
                if (has_colors()) {
                    if (opponent == BLUE) {
                        attroff(COLOR_PAIR(COLOR_BLUE_PIECE));
                    } else {
                        attroff(COLOR_PAIR(COLOR_RED_PIECE));
                    }
                }
                move_counters[2 + card_slot]++;
            } else if (ch == 'S') {
                mvaddch(y, x, 'S');
            } else {
                mvaddch(y, x, ch);
            }
        }
    }
    
    // Neutral card
    int neutralIdx = state->db->neutralCard;
    int start_x = 75;
    
    if (card_row == 0) {
        mvprintw(3, start_x, "%s", state->db->cardDb[neutralIdx].name);
    }
    
    // Draw neutral card pattern
    for (int col = 0; col < 5; col++) {
        char ch = state->db->cardDb[neutralIdx].card[card_row][col];
        int y = 4 + card_row;
        int x = start_x + col;
        
        if (ch == 'x') {
            mvaddch(y, x, '0' + move_counters[4]);
            move_counters[4]++;
        } else if (ch == 'S') {
            mvaddch(y, x, 'S');
        } else {
            mvaddch(y, x, ch);
        }
    }
}

void highlight_possible_moves(GameState *state) {
    if (!state->card_selected || !state->src_selected) return;
    
    int cardIdx = state->selected_card;
    
    for (int i = 0; i < state->db->cardDb[cardIdx].movesCtr; i++) {
        pointType dest = getDestinationFromMoveIdx(state->db, state->selected_src, i, cardIdx);
        
        if (isInRange(dest) && isValidUserMove(state->db, state->selected_src, i, cardIdx)) {
            // Convert actual board position to display position based on current player
            int display_row, display_col;
            if (state->db->bCurrentPlayer == BLUE) {
                display_row = dest.row;
                display_col = dest.col;
            } else {
                display_row = 4 - dest.row;
                display_col = 4 - dest.col;
            }
            
            int y = 4 + display_row;
            int x = 4 + display_col * 2;
            
            if (has_colors()) {
                attron(COLOR_PAIR(COLOR_POSSIBLE_MOVE));
                mvaddch(y, x, state->db->board[dest.row][dest.col] == '.' ? 'X' : state->db->board[dest.row][dest.col]);
                attroff(COLOR_PAIR(COLOR_POSSIBLE_MOVE));
            } else {
                attron(A_REVERSE);
                mvaddch(y, x, state->db->board[dest.row][dest.col] == '.' ? 'X' : state->db->board[dest.row][dest.col]);
                attroff(A_REVERSE);
            }
        }
    }
}

void draw_status(GameState *state) {
    int start_y = 11;
    
    // Current player
    const char *player_name = (state->db->bCurrentPlayer == BLUE) ? "BLUE" : "RED";
    if (has_colors()) {
        if (state->db->bCurrentPlayer == BLUE) {
            attron(COLOR_PAIR(COLOR_BLUE_PIECE));
        } else {
            attron(COLOR_PAIR(COLOR_RED_PIECE));
        }
    }
    mvprintw(start_y, 2, "Current Player: %s", player_name);
    if (has_colors()) {
        if (state->db->bCurrentPlayer == BLUE) {
            attroff(COLOR_PAIR(COLOR_BLUE_PIECE));
        } else {
            attroff(COLOR_PAIR(COLOR_RED_PIECE));
        }
    }
    
    // Game state message
    switch (state->game_state) {
        case 0:
            mvprintw(start_y + 1, 2, "Phase: Select a card (Press 0 or 1)");
            break;
        case 1:
            mvprintw(start_y + 1, 2, "Phase: Select your piece to move (arrows + enter)");
            break;
        case 2:
            mvprintw(start_y + 1, 2, "Phase: Select destination (highlighted squares)");
            break;
    }
    
    // Selection status
    if (state->card_selected) {
        mvprintw(start_y + 2, 2, "Selected Card: %s", state->db->cardDb[state->selected_card].name);
    }
    if (state->src_selected) {
        mvprintw(start_y + 3, 2, "Selected Piece: (%d,%d)", 
                state->selected_src.row, state->selected_src.col);
    }
    
    // Cursor position
    mvprintw(start_y + 4, 2, "Cursor: (%d,%d)", state->cursor_row, state->cursor_col);
}

void draw_instructions(GameState *state) {
    (void)state; // Suppress unused parameter warning
    
    int start_y = 17;
    
    mvprintw(start_y, 2, "=== CONTROLS ===");
    mvprintw(start_y + 1, 2, "Arrow Keys: Move cursor around board");
    mvprintw(start_y + 2, 2, "ENTER/SPACE: Select piece/destination");
    mvprintw(start_y + 3, 2, "0-1: Select your cards");
    mvprintw(start_y + 4, 2, "r: Reset selections");
    mvprintw(start_y + 5, 2, "q: Quit to original console");
    mvprintw(start_y + 6, 2, "n: New game");
    
    mvprintw(start_y, 40, "=== CARD PATTERNS ===");
    mvprintw(start_y + 1, 40, "Numbers show possible moves");
    mvprintw(start_y + 2, 40, "Center (S) is your piece position");
    mvprintw(start_y + 3, 40, "Patterns are from your perspective");
    
    // Win conditions
    mvprintw(start_y + 5, 40, "=== WIN CONDITIONS ===");
    mvprintw(start_y + 6, 40, "* Capture opponent's master (B/R)");
    mvprintw(start_y + 7, 40, "* Move your master to opponent's temple");
    mvprintw(start_y + 8, 40, "BLUE temple: (0,2)  RED temple: (4,2)");
}

int handle_input(GameState *state, int ch) {
    switch (ch) {
        case KEY_UP:
            if (state->db->bCurrentPlayer == BLUE) {
                if (state->cursor_row > 0) state->cursor_row--;
            } else {
                if (state->cursor_row < 4) state->cursor_row++;
            }
            break;
            
        case KEY_DOWN:
            if (state->db->bCurrentPlayer == BLUE) {
                if (state->cursor_row < 4) state->cursor_row++;
            } else {
                if (state->cursor_row > 0) state->cursor_row--;
            }
            break;
            
        case KEY_LEFT:
            if (state->db->bCurrentPlayer == BLUE) {
                if (state->cursor_col > 0) state->cursor_col--;
            } else {
                if (state->cursor_col < 4) state->cursor_col++;
            }
            break;
            
        case KEY_RIGHT:
            if (state->db->bCurrentPlayer == BLUE) {
                if (state->cursor_col < 4) state->cursor_col++;
            } else {
                if (state->cursor_col > 0) state->cursor_col--;
            }
            break;
            
        case '\n':
        case '\r':
        case ' ':
            // Handle selection based on current game state
            if (state->game_state == 1) {
                // Selecting piece
                pointType cursor_pos = {state->cursor_row, state->cursor_col};
                if (isValidPiece(state->db, cursor_pos)) {
                    state->selected_src = cursor_pos;
                    state->src_selected = 1;
                    state->game_state = 2;
                }
            } else if (state->game_state == 2) {
                // Selecting destination
                pointType cursor_pos = {state->cursor_row, state->cursor_col};
                int move_idx = find_move_index(state, cursor_pos);
                if (move_idx >= 0) {
                    // Execute move
                    movePiece(state->db, state->selected_src, cursor_pos);
                    switchCards(state->db, state->selected_card_deck_idx);
                    recordMoves(state->db, state->selected_src, cursor_pos, state->selected_card);
                    
                    // Switch players
                    state->db->bCurrentPlayer = !state->db->bCurrentPlayer;
                    
                    // Check for rare case
                    if (!hasAnyValidMoves(state->db)) {
                        rareCase(state->db);
                        state->db->bCurrentPlayer = !state->db->bCurrentPlayer;
                    }
                    
                    // Reset cursor to center for new player
                    state->cursor_row = 2;
                    state->cursor_col = 2;
                    
                    reset_selections(state);
                }
            }
            break;
            
        case '0':
        case '1':
            // Card selection
            if (state->game_state == 0) {
                int card_num = ch - '0';
                int current_player = state->db->bCurrentPlayer;
                state->selected_card = state->db->playerCards[current_player][card_num];
                state->selected_card_deck_idx = card_num;
                state->card_selected = 1;
                state->game_state = 1;
            }
            break;
            
        case 'r':
        case 'R':
            reset_selections(state);
            break;
            
        case 'n':
        case 'N':
            // New game
            initDatabase(state->db);
            strcpy(state->db->p1, "Blue Player");
            strcpy(state->db->p2, "Red Player");
            state->cursor_row = 2;
            state->cursor_col = 2;
            reset_selections(state);
            break;
            
        case 'q':
        case 'Q':
            return 1; // Exit enhanced mode
            
        case 27: // ESC
            return 1;
    }
    
    return 0;
}

void reset_selections(GameState *state) {
    state->src_selected = 0;
    state->card_selected = 0;
    state->selected_card = -1;
    state->selected_card_deck_idx = -1;
    state->move_index = -1;
    state->game_state = 0;
}

int find_move_index(GameState *state, pointType dest) {
    if (!state->card_selected || !state->src_selected) return -1;
    
    int cardIdx = state->selected_card;
    
    for (int i = 0; i < state->db->cardDb[cardIdx].movesCtr; i++) {
        pointType test_dest = getDestinationFromMoveIdx(state->db, state->selected_src, i, cardIdx);
        if (test_dest.row == dest.row && test_dest.col == dest.col) {
            if (isValidUserMove(state->db, state->selected_src, i, cardIdx)) {
                return i;
            }
        }
    }
    
    return -1;
}

void show_win_message(GameState *state) {
    clear();
    
    char message[256];
    if (state->db->bWinner == BLUE && state->db->bWinCondition == TEMPLE_WIN) {
        sprintf(message, "%s (Blue) wins by Temple Capture!", state->db->p1);
    } else if (state->db->bWinner == BLUE && state->db->bWinCondition == SENSEI_WIN) {
        sprintf(message, "%s (Blue) wins by Master Capture!", state->db->p1);
    } else if (state->db->bWinner == RED && state->db->bWinCondition == TEMPLE_WIN) {
        sprintf(message, "%s (Red) wins by Temple Capture!", state->db->p2);
    } else if (state->db->bWinner == RED && state->db->bWinCondition == SENSEI_WIN) {
        sprintf(message, "%s (Red) wins by Master Capture!", state->db->p2);
    }
    
    mvprintw(10, 10, "=== GAME OVER ===");
    mvprintw(12, 10, "%s", message);
    mvprintw(14, 10, "Press any key to continue...");
    
    refresh();
    getch();
}
