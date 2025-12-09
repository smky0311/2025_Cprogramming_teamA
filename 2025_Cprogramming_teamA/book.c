/**
 * @file book.c
 * @brief Book management module for the library system
 *
 * This file handles loading, saving, and managing book data.
 * It provides functionality for adding books, viewing the book list,
 * and persisting book data to a binary file.
 */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>  /* Required for strcspn function */
#include "common.h"
#include "book.h"

/**
 * @brief Loads book data from the binary file
 *
 * Reads book information from 'books.dat' file into the global
 * g_books array. If the file doesn't exist, initializes with
 * an empty book list.
 */
void loadBooks() {
    FILE *fp = fopen("books.dat", "rb");
    if (fp == NULL) {
        printf("[System] books.dat file not found. Starting fresh.\n");
        g_bookCount = 0;
        return;
    }

    /* Read all book records from file */
    fread(g_books, sizeof(Book), MAX_BOOKS, fp);
    fclose(fp);

    /* Count valid books (id[0] being '\0' indicates empty slot) */
    g_bookCount = 0;
    while (g_bookCount < MAX_BOOKS && g_books[g_bookCount].id[0] != '\0')
        g_bookCount++;

    printf("[System] Loaded %d book(s) successfully!\n", g_bookCount);
}

/**
 * @brief Saves book data to the binary file
 *
 * Writes all book information from the global g_books array
 * to 'books.dat' file for persistent storage.
 */
void saveBooks() {
    FILE *fp = fopen("books.dat", "wb");
    if (fp == NULL) {
        printf("[Error] Failed to save!\n");
        return;
    }
    fwrite(g_books, sizeof(Book), MAX_BOOKS, fp);
    fclose(fp);
    printf("[System] Book data saved successfully!\n");
}

/**
 * @brief Displays the book management menu for administrators
 *
 * Provides options to add new books or view the current book list.
 * Runs in a loop until the user chooses to return to the main menu.
 */
void manageBooks() {
    int ch;
    while (1) {
        printf("\n=== Book Management (Admin) ===\n");
        printf("1. Add Book\n2. Book List\n0. Back\nSelect: ");

        /* Read menu choice with input validation */
        if (scanf("%d", &ch) != 1) {
            printf("[Error] Input error! Please enter a number.\n");
            while (getchar() != '\n');  /* Clear invalid input from buffer */
            continue;
        }
        while (getchar() != '\n');  /* Clear buffer after scanf */

        if (ch == 1) {
            /* Check if book limit has been reached */
            if (g_bookCount >= MAX_BOOKS) {
                printf("Cannot add more books!\n");
                continue;
            }

            /* Get pointer to the next available book slot */
            Book *b = &g_books[g_bookCount];

            /* Input book ID */
            printf("ID: ");
            fgets(b->id, sizeof(b->id), stdin);
            b->id[strcspn(b->id, "\n")] = '\0';  /* Remove newline */

            /* Input book title */
            printf("Title: ");
            fgets(b->title, sizeof(b->title), stdin);
            b->title[strcspn(b->title, "\n")] = '\0';

            /* Input book author */
            printf("Author: ");
            fgets(b->author, sizeof(b->author), stdin);
            b->author[strcspn(b->author, "\n")] = '\0';

            /* Set book as available for borrowing */
            b->available = 1;
            g_bookCount++;
            printf("Book added! Current total: %d\n", g_bookCount);
        }
        else if (ch == 2) {
            /* Display all books in the system */
            printf("\nBook List (%d books)\n", g_bookCount);
            for (int i = 0; i < g_bookCount; i++) {
                printf("%s | %s | %s | %s\n",
                       g_books[i].id,
                       g_books[i].title,
                       g_books[i].author,
                       g_books[i].available ? "Available" : "Borrowed");
            }
        }
        else if (ch == 0) {
            break;  /* Return to main menu */
        }
    }
}
