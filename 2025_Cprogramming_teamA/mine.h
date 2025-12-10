/**
 * @file mine.h
 * @brief Header file for Minesweeper game module
 *
 * Declares functions for the text-based Minesweeper game.
 */

#pragma once

/**
 * @brief Main entry point for Minesweeper game
 *
 * Displays game menu and runs the game loop.
 *
 * @return 0 on normal exit
 */
int mineFinder();

/**
 * @brief Displays difficulty selection menu
 *
 * @return Number of mines for selected difficulty, 0 to return to menu
 */
int select_difficulty();

/**
 * @brief Reveals a cell and performs flood-fill
 *
 * @param r Row index
 * @param c Column index
 */
void reveal(int r, int c);

/**
 * @brief Prints the current game board state
 *
 * @param MINES_count Total number of mines
 */
void printBoard(int MINES_count);

/**
 * @brief Computes adjacent mine counts for all cells
 */
void computeAdjacent();

/**
 * @brief Places mines randomly on the board
 *
 * @param g_mines Number of mines to place
 */
void placeMines(int g_mines);

/**
 * @brief Initializes display board with hidden cells
 */
void initDisplay();

/**
 * @brief Clears the input buffer
 */
void clear_input_buffer();
