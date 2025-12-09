/**
 * @file main.c
 * @brief Main entry point for the Library Management Program
 *
 * This file contains the main function and the primary menu loop
 * for the library management system. It handles user input validation
 * and routes to different modules (auth, book, user, mine).
 */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include "common.h"
#include "book.h"
#include "user.h"
#include "auth.h"
#include "mine.h"

/* Global arrays and counters for books and users */
Book g_books[MAX_BOOKS];
User g_users[MAX_USERS];
int g_bookCount = 0;
int g_userCount = 0;

/**
 * @brief Main entry point of the program
 *
 * Initializes the console for UTF-8, loads existing data,
 * and runs the main menu loop until the user chooses to exit.
 *
 * @return 0 on successful program termination
 */
int main() {
    /* Set console code page to UTF-8 for proper character display */
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    /* Load existing books and users from data files */
    loadBooks();
    loadUsers();

    char choiceStr[10];   /* Buffer for storing user input */
    int choice;           /* Variable for switch statement */
    int isLoggedIn = 0;   /* Login status flag (0: logged out, 1: logged in) */

    /* Main menu loop */
    while (1) {
        printf("\n=== Library Management Program ===\n");
        printf("1. Sign Up\n");
        printf("2. Login\n");
        printf("3. Book Management (Admin)\n");
        printf("4. User Management (Admin)\n");
        printf("5. Minesweeper (Game)\n");
        printf("0. Exit\n");
        printf("Select: ");

        /* Step 1: Read user input */
        if (fgets(choiceStr, sizeof(choiceStr), stdin) == NULL) {
            /* fgets returns NULL on input error or buffer overflow */
            printf("Input error.\n");
            continue;
        }

        /* Step 2: Remove newline character from input */
        choiceStr[strcspn(choiceStr, "\r\n")] = '\0';

        /* Step 3: Check for empty input (user pressed Enter only) */
        if (choiceStr[0] == '\0') {
            printf("No input provided.\n");
            continue;
        }

        /* Step 4: Validate that input contains only digits */
        int isNumber = 1;  /* Assume input is a number initially */
        for (int i = 0; choiceStr[i] != '\0'; i++) {
            /* isdigit returns true if character is '0'-'9' */
            if (!isdigit(choiceStr[i])) {
                isNumber = 0;  /* Non-digit character found */
                break;
            }
        }

        /* Step 5: Display error if input is not a valid number */
        if (isNumber == 0) {
            printf("Please enter numbers only.\n");
            continue;
        }

        /* Convert string input to integer for switch statement */
        choice = atoi(choiceStr);

        switch (choice) {
        case 1:
            signUp();  /* Call sign-up function */
            break;
        case 2:
            isLoggedIn = login();  /* Returns login success status */
            break;
        case 3:
            manageBooks();  /* Call book management function */
            break;
        case 4:
            manageUsers();  /* Call user management function */
            break;
        case 5:
            mineFinder();  /* Call minesweeper game function */
            break;
        case 0:
            /* Save data before exiting */
            saveBooks();  /* Save book information */
            saveUsers();  /* Save user information */
            printf("Exiting the program.\n");
            return 0;
        default:
            printf("Invalid input.\n");
        }
    }
    return 0;
}
