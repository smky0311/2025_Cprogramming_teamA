/**
 * @file utils.h
 * @brief Header file for utility functions
 *
 * This file declares utility functions used across
 * the library management system.
 */

#ifndef UTILS_H
#define UTILS_H

#include "book.h"

/* ============================================
 * UTILITY FUNCTION DECLARATIONS
 * ============================================ */

/**
 * @brief Displays an ASCII art book cover
 *
 * Creates a visual representation of a book with
 * title centered inside a box frame.
 *
 * @param book Pointer to the book to display
 */
void displayBookCover(struct Book* book);

/**
 * @brief Clears the input buffer
 *
 * Removes any remaining characters from stdin
 * to prevent input issues.
 */
void clearInputBuffer(void);

/**
 * @brief Safely reads a string from user input
 *
 * Reads input using fgets and removes trailing newline.
 *
 * @param buffer Buffer to store the input
 * @param size Size of the buffer
 */
void readString(char* buffer, int size);

/**
 * @brief Finds a book by its ID
 *
 * Searches the global book array for a matching ID.
 *
 * @param bookID The ID to search for
 * @return Index in g_books array, or -1 if not found
 */
int findBookByID(int bookID);

/**
 * @brief Finds a user by their ID
 *
 * Searches the global user array for a matching ID.
 *
 * @param userID The ID to search for
 * @return Index in g_users array, or -1 if not found
 */
int findUserByID(int userID);

/**
 * @brief Generates the next available book ID
 *
 * Finds the maximum existing book ID and returns +1.
 *
 * @return Next available book ID
 */
int getNextBookID(void);

/**
 * @brief Generates the next available user ID
 *
 * Finds the maximum existing user ID and returns +1.
 *
 * @return Next available user ID
 */
int getNextUserID(void);

#endif /* UTILS_H */
