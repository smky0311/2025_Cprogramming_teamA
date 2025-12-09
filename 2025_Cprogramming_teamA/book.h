/**
 * @file book.h
 * @brief Header file for book management module
 *
 * Declares functions for loading, saving, and managing books.
 */

#pragma once

/**
 * @brief Loads book data from binary file
 *
 * Reads books from 'books.dat' into the global g_books array.
 */
void loadBooks();

/**
 * @brief Saves book data to binary file
 *
 * Writes the global g_books array to 'books.dat'.
 */
void saveBooks();

/**
 * @brief Displays book management menu for administrators
 *
 * Allows adding books and viewing the book list.
 */
void manageBooks();
