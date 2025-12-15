#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>  // Required for tolower function
#include "common.h"

#define ROWS 9  // Number of rows in the game board
#define COLS 9  // Number of columns in the game board

// Global variables for game state
int g_mines = 0;                    // Current number of mines
bool mineBoard[ROWS][COLS];         // True if cell contains a mine
int adjacentMines[ROWS][COLS];      // Count of adjacent mines for each cell
char displayBoard[ROWS][COLS];      // Display state: '?', 'F', ' ', '1'-'8', '*'
int totalRevealed = 0;              // Number of safe cells revealed

// Direction vectors for 8 adjacent cells (N, NE, E, SE, S, SW, W, NW)
int dx[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
int dy[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };

// Reads and discards all characters from stdin until
// a newline or EOF is encountered.
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


 
 // Sets all cells on the display board to '?' indicating
 // they are hidden and have not been revealed yet.

void initDisplay() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            displayBoard[i][j] = '?';
        }
    }
}


 // Clears the mine board and randomly places the specified
 // number of mines without overlapping.
 
void placeMines(int g_mines) {
    // Clear all cells
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            mineBoard[i][j] = false;
        }
    }

    // Place mines randomly
    int placed = 0;
    while (placed < g_mines) {
        int r = rand() % ROWS;
        int c = rand() % COLS;
        if (!mineBoard[r][c]) {
            mineBoard[r][c] = true;
            placed++;
        }
    }
}


 // Calculates and stores the number of adjacent mines for
 // each safe cell. Mine cells are marked with -1.
 
void computeAdjacent() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (mineBoard[i][j]) {
                adjacentMines[i][j] = -1;  /* Mark as mine */
                continue;
            }

            /* Count adjacent mines */
            int count = 0;
            for (int d = 0; d < 8; d++) {
                int ni = i + dx[d];
                int nj = j + dy[d];
                if (ni >= 0 && ni < ROWS && nj >= 0 && nj < COLS && mineBoard[ni][nj]) {
                    count++;
                }
            }
            adjacentMines[i][j] = count;
        }
    }
}


 // Displays the board with row/column indices and shows
 // the current progress (revealed cells vs total safe cells).
 
void printBoard(int MINES_count) {
    printf("\n  0 1 2 3 4 5 6 7 8\n");
    for (int i = 0; i < ROWS; i++) {
        printf("%d ", i);
        for (int j = 0; j < COLS; j++) {
            printf("%c ", displayBoard[i][j]);
        }
        printf("\n");
    }
    printf("Legend: ? = hidden, F = flag, ' ' = safe (0), 1-8 = adjacent mines, * = mine\n");
    printf("Safe cells revealed: %d / %d\n\n", totalRevealed, ROWS * COLS - MINES_count);
}


 // Recursively reveals cells starting from the specified position.
 // If the cell has no adjacent mines, automatically reveals all
 // adjacent safe cells (flood-fill algorithm).

void reveal(int r, int c) {
    // Boundary and already-revealed checks
    if (r < 0 || r >= ROWS || c < 0 || c >= COLS || displayBoard[r][c] != '?') {
        return;
    }

    // Don't reveal mine cells through flood-fill
    if (mineBoard[r][c]) {
        return;
    }

    // Reveal this cell
    displayBoard[r][c] = (adjacentMines[r][c] == 0) ? ' ' : ('0' + adjacentMines[r][c]);
    totalRevealed++;

    // Flood-fill
    if (adjacentMines[r][c] == 0) {
        for (int d = 0; d < 8; d++) {
            reveal(r + dx[d], c + dy[d]);
        }
    }
}


 // The player wins when all safe (non-mine) cells have been revealed.
 
bool hasWon(int MINES_count) {
    return totalRevealed == (ROWS * COLS - MINES_count);
}


 // Allows the player to choose between Easy, Medium, and Hard
 // difficulty levels, each with different mine counts.
 
int select_difficulty() {
    int choice;
    int mines_count = 0;

    while (true) {
        printf("\n--- Difficulty Selection (9x9) ---\n");
        printf("1. Easy (20 Mines)\n");
        printf("2. Medium (30 Mines)\n");
        printf("3. Hard (40 Mines)\n");
        printf("4. Return to Main Menu\n");
        printf("Select: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();

        switch (choice) {
        case 1: mines_count = 20; break;
        case 2: mines_count = 30; break;
        case 3: mines_count = 40; break;
        case 4: return 0;  /* Return to main menu */
        default:
            printf("Please enter a valid number between 1 and 4.\n");
            continue;
        }
        return mines_count;
    }
}


 // Displays the game menu, handles difficulty selection, and runs
 // the game loop. Supports revealing cells, flagging, and quitting.
 
int mineFinder() {
    srand((unsigned int)time(NULL));

    while (true) {
        int menu_choice;

        printf("\n====================================\n");
        printf("=== Text-Based Minesweeper ===\n");
        printf("====================================\n");
        printf("1. Start Game (Select Difficulty)\n");
        printf("2. Exit Game\n");
        printf("Select: ");

        if (scanf("%d", &menu_choice) != 1) {
            printf("Please enter 1 or 2.\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();

        if (menu_choice == 2) {
            printf("Exiting the game.\n");
            break;
        }

        if (menu_choice == 1) {
            int selected_mines = select_difficulty();

            if (selected_mines == 0) {
                /* User chose to return to main menu */
                continue;
            }

            /* Initialize game with selected difficulty */
            g_mines = selected_mines;

            initDisplay();
            placeMines(g_mines);
            computeAdjacent();
            totalRevealed = 0;

            printf("=== Text-Based Minesweeper (%dx%d, %d mines) ===\n", ROWS, COLS, g_mines);
            printf("Commands:\n");
            printf("  r <row> <col>  : Reveal cell (0-based indices)\n");
            printf("  f <row> <col>  : Toggle flag on hidden cell\n");
            printf("  q              : Quit\n\n");

            printBoard(g_mines);

            /* Game loop */
            while (true) {
                char cmd_char;
                int row = -1, col = -1;

                printf("Enter command: ");

                /* Read command character (r, f, or q) */
                if (scanf(" %c", &cmd_char) != 1) {
                    printf("Invalid input!\n");
                    clear_input_buffer();
                    continue;
                }

                /* Handle quit command immediately */
                if (tolower(cmd_char) == 'q') {
                    printf("Quit game. Returning to main menu.\n");
                    clear_input_buffer();
                    break;
                }

                /* Read row and column for r/f commands */
                if (scanf("%d %d", &row, &col) != 2) {
                    printf("Invalid input! Expected: r/f followed by row col\n");
                    clear_input_buffer();
                    continue;
                }
                clear_input_buffer();

                /* Validate position bounds */
                if (row < 0 || row >= ROWS || col < 0 || col >= COLS) {
                    printf("Invalid position! Rows/cols must be 0-%d\n", ROWS - 1);
                    continue;
                }

                char cmd = tolower(cmd_char);

                if (cmd == 'r') {
                    /* Handle reveal command */
                    if (displayBoard[row][col] == 'F') {
                        printf("Unflag the cell first!\n");
                        continue;
                    }
                    if (displayBoard[row][col] != '?') {
                        printf("Cell already revealed or flagged.\n");
                        continue;
                    }

                    if (mineBoard[row][col]) {
                        /* Game over: hit a mine */
                        for (int i = 0; i < ROWS; i++) {
                            for (int j = 0; j < COLS; j++) {
                                if (mineBoard[i][j]) {
                                    displayBoard[i][j] = '*';
                                }
                            }
                        }
                        printBoard(g_mines);
                        printf("BOOM! You hit a mine. GAME OVER!\n");
                        goto END_GAME;
                    }

                    /* Safe cell - reveal it */
                    reveal(row, col);
                    printBoard(g_mines);

                    /* Check win condition */
                    if (hasWon(g_mines)) {
                        printBoard(g_mines);
                        printf("YOU WIN! All safe cells revealed!\n");
                        goto END_GAME;
                    }
                }
                else if (cmd == 'f') {
                    /* Handle flag command */
                    if (displayBoard[row][col] != '?' && displayBoard[row][col] != 'F') {
                        printf("Cannot flag a revealed cell!\n");
                        continue;
                    }
                    /* Toggle flag */
                    displayBoard[row][col] = (displayBoard[row][col] == 'F') ? '?' : 'F';
                    printBoard(g_mines);
                }
                else {
                    printf("Unknown command '%c'! Use r, f, or q.\n", cmd_char);
                }
            }

        END_GAME:;  /* Label for jumping after game ends */

        }
        else {
            printf("Invalid selection.\n");
        }
    }

    return 0;
}
