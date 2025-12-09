#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>
#include "common.h"
// tolower 함수 사용을 위해 추가

#define ROWS 9
#define COLS 9
// #define MINES 10    // 삭제됨

int g_mines = 0; // 전역 변수
bool mineBoard[ROWS][COLS];
int adjacentMines[ROWS][COLS];
char displayBoard[ROWS][COLS];
int totalRevealed = 0;

int dx[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
int dy[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };

// --- 유틸리티 함수 ---
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// --- 게임 로직 함수 (기존 코드 유지) ---

/**
 * Initializes the display board with '?' for hidden cells.
 */
void initDisplay() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            displayBoard[i][j] = '?';
        }
    }
}

/**
 * Randomly places MINES on the board without overlaps.
 */
void placeMines(int g_mines) { // g_mines를 인자로 받도록 수정
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            mineBoard[i][j] = false;
        }
    }
    int placed = 0;
    while (placed < g_mines) { // MINES -> g_mines
        int r = rand() % ROWS;
        int c = rand() % COLS;
        if (!mineBoard[r][c]) {
            mineBoard[r][c] = true;
            placed++;
        }
    }
}

/**
 * Computes the number of adjacent mines for each safe cell.
 */
void computeAdjacent() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (mineBoard[i][j]) {
                adjacentMines[i][j] = -1; // Marker for mine
                continue;
            }
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

/**
 * Prints the current state of the board.
 */
void printBoard(int MINES_count) { // 인자로 mines_count 받도록 수정
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

/**
 * Recursively reveals a safe cell and auto-reveals adjacent safe empties (flood fill).
 */
void reveal(int r, int c) {
    if (r < 0 || r >= ROWS || c < 0 || c >= COLS || displayBoard[r][c] != '?') {
        return;
    }
    // 지뢰가 없는 셀만 드러냄
    if (mineBoard[r][c]) {
        return;
    }

    // 이 부분에서 totalRevealed가 증가해야 합니다.
    displayBoard[r][c] = (adjacentMines[r][c] == 0) ? ' ' : ('0' + adjacentMines[r][c]);
    totalRevealed++;

    if (adjacentMines[r][c] == 0) {
        for (int d = 0; d < 8; d++) {
            reveal(r + dx[d], c + dy[d]);
        }
    }
}

/**
 * Checks if the player has won (all safe cells revealed).
 */
bool hasWon(int MINES_count) { // 인자로 mines_count 받도록 수정
    return totalRevealed == (ROWS * COLS - MINES_count);
}

// --- 메인 메뉴 및 난이도 선택 함수 추가 ---

int select_difficulty() {
    int choice;
    int mines_count = 0;

    while (true) {
        printf("\n--- 난이도 선택 (9x9) ---\n");
        printf("1. 하 (20 Mines)\n");
        printf("2. 중 (30 Mines)\n");
        printf("3. 상 (40 Mines)\n");
        printf("4. 메인 메뉴로 돌아가기\n");
        printf("선택: ");

        if (scanf("%d", &choice) != 1) {
            printf("유효하지 않은 입력입니다. 숫자를 입력하세요.\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();

        switch (choice) {
        case 1: mines_count = 20; break;
        case 2: mines_count = 30; break;
        case 3: mines_count = 40; break;
        case 4: return 0; // 메인 메뉴로 돌아가기 위해 0 반환
        default:
            printf("1에서 4 사이의 유효한 숫자를 입력하세요.\n");
            continue;
        }
        return mines_count; // 유효한 지뢰 개수 반환
    }
}

// --- main 함수 (메뉴 루프를 포함하도록 수정) ---

int mineFinder() {
    srand(time(NULL));

    while (true) {
        int menu_choice;

        printf("\n====================================\n");
        printf("=== 텍스트 기반 지뢰 찾기 ===\n");
        printf("====================================\n");
        printf("1. 게임 시작 (난이도 선택)\n");
        printf("2. 창 닫기 (종료)\n");
        printf("선택: ");

        if (scanf("%d", &menu_choice) != 1) {
            printf("1 또는 2를 입력하세요.\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();

        if (menu_choice == 2) {
            printf("게임을 종료합니다.\n");
            break; // 프로그램 종료
        }

        if (menu_choice == 1) {
            int selected_mines = select_difficulty();

            if (selected_mines == 0) {
                // 난이도 선택에서 '메인 메뉴로 돌아가기(4)'를 선택한 경우
                continue;
            }

            // --- 게임 초기화 및 시작 로직 (기존 main 함수 로직) ---
            g_mines = selected_mines;

            initDisplay();
            placeMines(g_mines);
            computeAdjacent();
            totalRevealed = 0; // 초기화

            printf("=== Text-Based Minesweeper (%dx%d, %d mines) ===\n", ROWS, COLS, g_mines);
            printf("Commands:\n");
            printf("  r <row> <col>  : Reveal cell (0-based indices)\n");
            printf("  f <row> <col>  : Toggle flag on hidden cell\n");
            printf("  q              : Quit\n\n");

            printBoard(g_mines);

            while (true) {
                char cmd_char;
                int row = -1, col = -1;

                printf("Enter command: ");

                // 명령어 문자만 먼저 읽음 (r, f, q)
                if (scanf(" %c", &cmd_char) != 1) {
                    printf("Invalid input!\n");
                    clear_input_buffer();
                    continue;
                }

                // q나 Q는 즉시 처리하고 게임 루프 종료 (메인 메뉴로 돌아감)
                if (tolower(cmd_char) == 'q') {
                    printf("Quit game. Returning to main menu.\n");
                    clear_input_buffer();
                    break;
                }

                // r이나 f의 경우, row와 col을 읽어야 함
                if (scanf("%d %d", &row, &col) != 2) {
                    printf("Invalid input! Expected: r/f followed by row col\n");
                    clear_input_buffer();
                    continue;
                }
                clear_input_buffer(); // 숫자 읽은 후 버퍼 비우기

                if (row < 0 || row >= ROWS || col < 0 || col >= COLS) {
                    printf("Invalid position! Rows/cols must be 0-%d\n", ROWS - 1);
                    continue;
                }

                char cmd = tolower(cmd_char);

                if (cmd == 'r') {
                    if (displayBoard[row][col] == 'F') {
                        printf("Unflag the cell first!\n");
                        continue;
                    }
                    if (displayBoard[row][col] != '?') {
                        printf("Cell already revealed or flagged.\n");
                        continue;
                    }

                    if (mineBoard[row][col]) {
                        // Game over: reveal all mines
                        for (int i = 0; i < ROWS; i++) {
                            for (int j = 0; j < COLS; j++) {
                                if (mineBoard[i][j]) {
                                    displayBoard[i][j] = '*';
                                }
                            }
                        }
                        printBoard(g_mines);
                        printf("BOOM! You hit a mine. GAME OVER!\n");
                        goto END_GAME; // 게임 종료 후 메인 메뉴로 돌아감
                    }

                    // Safe to reveal
                    reveal(row, col);
                    printBoard(g_mines);

                    if (hasWon(g_mines)) {
                        printBoard(g_mines);
                        printf("YOU WIN! All safe cells revealed!\n");
                        goto END_GAME; // 게임 종료 후 메인 메뉴로 돌아감
                    }
                }
                else if (cmd == 'f') {
                    if (displayBoard[row][col] != '?' && displayBoard[row][col] != 'F') {
                        printf("Cannot flag a revealed cell!\n");
                        continue;
                    }
                    displayBoard[row][col] = (displayBoard[row][col] == 'F') ? '?' : 'F';
                    printBoard(g_mines);
                }
                else {
                    printf("Unknown command '%c'! Use r, f, or q.\n", cmd_char);
                }
            } // end of game loop

        END_GAME:; // 게임 종료 후 메인 메뉴로 돌아옴

        }
        else {
            printf("유효하지 않은 선택입니다.\n");
        }
    } // end of main menu loop

    return 0;
}