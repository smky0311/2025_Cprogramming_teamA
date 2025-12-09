#pragma once

int mineFinder();
int select_difficulty();
void reveal(int r, int c);
void printBoard(int MINES_count);
void computeAdjacent();
void placeMines(int g_mines);
void initDisplay();
void clear_input_buffer();