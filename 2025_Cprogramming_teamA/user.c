/**
 * @file user.c
 * @brief User mode module for the library management system
 *
 * This file handles all user-related functionality including:
 * - User registration (sign up)
 * - User authentication (login)
 * - Book searching
 * - Book borrowing and returning
 * - Viewing user information
 */

#define _CRT_SECURE_NO_WARNINGS  /* Disable MSVC security warnings for fopen, strcpy, etc. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "common.h"

/**
 * @brief Displays the user mode main menu
 *
 * Shows options for sign up, login, and exit.
 * After successful login, displays the user menu.
 */
void userMode(void) {
    int choice;
    char input[10];
    int loggedInUserID = -1;

    while (1) {
        printf("\n=== User Mode ===\n");
        printf("1. Sign Up\n");
        printf("2. Login\n");
        printf("0. Back to Main Menu\n");
        printf("Select: ");

        readString(input, sizeof(input));

        /* Validate numeric input */
        if (!isdigit(input[0])) {
            printf("[Error] Please enter a number.\n");
            continue;
        }

        choice = atoi(input);

        switch (choice) {
            case 1:
                signUp();
                break;
            case 2:
                loggedInUserID = login();
                if (loggedInUserID != -1) {
                    /* Login successful, show user menu */
                    userMenu(loggedInUserID);
                }
                break;
            case 0:
                return;  /* Return to main menu */
            default:
                printf("[Error] Invalid selection.\n");
        }
    }
}

/**
 * @brief Registers a new user in the system
 *
 * Prompts for username, password, and real name.
 * Validates that the username is unique before adding.
 * Uses scanf, strcpy, strcmp for string handling.
 */
void signUp(void) {
    struct User newUser;
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    char name[MAX_NAME];

    printf("\n=== Sign Up ===\n");

    /* Check if user limit is reached */
    if (g_userCount >= MAX_USERS) {
        printf("[Error] Maximum user limit reached. Cannot register.\n");
        return;
    }

    /* Get username */
    printf("Enter username: ");
    readString(username, sizeof(username));

    /* Check for empty input */
    if (strlen(username) == 0) {
        printf("[Error] Username cannot be empty.\n");
        return;
    }

    /* Check if username already exists (using strcmp) */
    for (int i = 0; i < g_userCount; i++) {
        if (strcmp(g_users[i].username, username) == 0) {
            printf("[Error] Username '%s' already exists.\n", username);
            return;
        }
    }

    /* Get password */
    printf("Enter password: ");
    readString(password, sizeof(password));

    /* Check for empty password */
    if (strlen(password) == 0) {
        printf("[Error] Password cannot be empty.\n");
        return;
    }

    /* Get real name */
    printf("Enter your name: ");
    readString(name, sizeof(name));

    /* Check for empty name */
    if (strlen(name) == 0) {
        printf("[Error] Name cannot be empty.\n");
        return;
    }

    /* Initialize new user structure */
    newUser.userID = getNextUserID();
    strcpy(newUser.username, username);   /* Copy username using strcpy */
    strcpy(newUser.password, password);   /* Copy password using strcpy */
    strcpy(newUser.name, name);           /* Copy name using strcpy */
    newUser.borrowedCount = 0;

    /* Initialize borrowed book IDs to -1 (no books borrowed) */
    for (int i = 0; i < MAX_BORROW; i++) {
        newUser.borrowedBookIDs[i] = -1;
    }

    /* Add user to global array */
    g_users[g_userCount] = newUser;
    g_userCount++;

    printf("[Success] User '%s' registered with ID %d.\n",
           username, newUser.userID);
}

/**
 * @brief Authenticates a user with credentials
 *
 * Prompts for username and password, validates against
 * stored user data using strcmp.
 *
 * @return User ID on successful login, -1 on failure
 */
int login(void) {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    printf("\n=== Login ===\n");

    /* Check if any users exist */
    if (g_userCount == 0) {
        printf("[Error] No registered users. Please sign up first.\n");
        return -1;
    }

    /* Get username */
    printf("Enter username: ");
    readString(username, sizeof(username));

    /* Get password */
    printf("Enter password: ");
    readString(password, sizeof(password));

    /* Search for matching credentials (using strcmp) */
    for (int i = 0; i < g_userCount; i++) {
        if (strcmp(g_users[i].username, username) == 0) {
            /* Username found, check password */
            if (strcmp(g_users[i].password, password) == 0) {
                printf("[Success] Welcome, %s!\n", g_users[i].name);
                return g_users[i].userID;
            } else {
                printf("[Error] Incorrect password.\n");
                return -1;
            }
        }
    }

    /* Username not found */
    printf("[Error] Username not found.\n");
    return -1;
}

/**
 * @brief Displays the user menu after login
 *
 * Provides options for searching books, borrowing, returning,
 * and viewing personal information.
 *
 * @param loggedInUserID The ID of the currently logged in user
 */
void userMenu(int loggedInUserID) {
    int choice;
    char input[10];
    int userIndex = findUserByID(loggedInUserID);

    if (userIndex == -1) {
        printf("[Error] User session error. Please login again.\n");
        return;
    }

    while (1) {
        printf("\n=== User Menu [%s] ===\n", g_users[userIndex].name);
        printf("1. Search Book\n");
        printf("2. Borrow Book\n");
        printf("3. Return Book\n");
        printf("4. My Information\n");
        printf("0. Logout\n");
        printf("Select: ");

        readString(input, sizeof(input));

        if (!isdigit(input[0])) {
            printf("[Error] Please enter a number.\n");
            continue;
        }

        choice = atoi(input);

        switch (choice) {
            case 1:
                searchBook();
                break;
            case 2:
                loanBook(loggedInUserID);
                break;
            case 3:
                returnBook(loggedInUserID);
                break;
            case 4:
                showMyInfo(loggedInUserID);
                break;
            case 0:
                printf("[Info] Logged out.\n");
                return;
            default:
                printf("[Error] Invalid selection.\n");
        }
    }
}

/**
 * @brief Searches for books by title or author
 *
 * Provides a submenu to choose search type.
 * Uses strstr to find partial matches in strings.
 */
void searchBook(void) {
    int choice;
    char input[10];
    char keyword[MAX_TITLE];
    int found = 0;

    printf("\n=== Search Book ===\n");

    /* Check if any books exist */
    if (g_bookCount == 0) {
        printf("[Info] No books in the library.\n");
        return;
    }

    printf("1. Search by Title\n");
    printf("2. Search by Author\n");
    printf("0. Cancel\n");
    printf("Select: ");

    readString(input, sizeof(input));

    if (!isdigit(input[0])) {
        printf("[Error] Please enter a number.\n");
        return;
    }

    choice = atoi(input);

    if (choice == 0) {
        return;
    }

    if (choice != 1 && choice != 2) {
        printf("[Error] Invalid selection.\n");
        return;
    }

    /* Get search keyword */
    printf("Enter search keyword: ");
    readString(keyword, sizeof(keyword));

    if (strlen(keyword) == 0) {
        printf("[Error] Search keyword cannot be empty.\n");
        return;
    }

    printf("\n=== Search Results ===\n");

    /* Search through all books using strstr for partial matching */
    for (int i = 0; i < g_bookCount; i++) {
        int match = 0;

        if (choice == 1) {
            /* Search by title using strstr */
            if (strstr(g_books[i].title, keyword) != NULL) {
                match = 1;
            }
        } else {
            /* Search by author using strstr */
            if (strstr(g_books[i].author, keyword) != NULL) {
                match = 1;
            }
        }

        if (match) {
            /* Display matching book with ASCII cover */
            displayBookCover(&g_books[i]);
            found++;
        }
    }

    if (found == 0) {
        printf("[Info] No books found matching '%s'.\n", keyword);
    } else {
        printf("[Info] Found %d book(s).\n", found);
    }
}

/**
 * @brief Borrows a book for the logged-in user
 *
 * Validates borrowing conditions:
 * - Book must exist and be available
 * - User must not exceed borrow limit (MAX_BORROW)
 *
 * Uses pointers to modify struct array elements.
 *
 * @param loggedInUserID The ID of the user borrowing the book
 */
void loanBook(int loggedInUserID) {
    int bookID;
    char input[20];
    int userIndex = findUserByID(loggedInUserID);
    int bookIndex;
    struct Book* book;     /* Pointer to book for modification */
    struct User* user;     /* Pointer to user for modification */

    printf("\n=== Borrow Book ===\n");

    /* Validate user */
    if (userIndex == -1) {
        printf("[Error] Invalid user session.\n");
        return;
    }

    user = &g_users[userIndex];  /* Get pointer to user */

    /* Check borrow limit */
    if (user->borrowedCount >= MAX_BORROW) {
        printf("[Error] You have reached the maximum borrow limit (%d books).\n",
               MAX_BORROW);
        printf("[Info] Please return a book before borrowing a new one.\n");
        return;
    }

    /* Show available books */
    printf("\n--- Available Books ---\n");
    int availableCount = 0;
    for (int i = 0; i < g_bookCount; i++) {
        if (g_books[i].status == 0) {  /* 0 = available */
            printf("[ID: %d] %s by %s\n",
                   g_books[i].id, g_books[i].title, g_books[i].author);
            availableCount++;
        }
    }

    if (availableCount == 0) {
        printf("[Info] No books available for borrowing.\n");
        return;
    }

    /* Get book ID to borrow */
    printf("\nEnter Book ID to borrow (0 to cancel): ");
    readString(input, sizeof(input));

    bookID = atoi(input);

    if (bookID == 0) {
        printf("[Info] Borrow cancelled.\n");
        return;
    }

    /* Find the book */
    bookIndex = findBookByID(bookID);

    if (bookIndex == -1) {
        printf("[Error] Book with ID %d not found.\n", bookID);
        return;
    }

    book = &g_books[bookIndex];  /* Get pointer to book */

    /* Check if book is available */
    if (book->status == 1) {  /* 1 = borrowed */
        printf("[Error] This book is already borrowed.\n");
        return;
    }

    /* Process the borrow - Update book status using pointer */
    book->status = 1;                    /* Mark as borrowed */
    book->borrowedByUserID = loggedInUserID;

    /* Update user's borrowed books using pointer */
    user->borrowedBookIDs[user->borrowedCount] = bookID;
    user->borrowedCount++;

    printf("[Success] You have borrowed '%s'.\n", book->title);
    printf("[Info] Current borrowed books: %d/%d\n",
           user->borrowedCount, MAX_BORROW);
}

/**
 * @brief Returns a borrowed book
 *
 * Finds the book in user's borrowed list and:
 * - Updates book status to available
 * - Removes book from user's borrowed list (array element deletion)
 *
 * @param loggedInUserID The ID of the user returning the book
 */
void returnBook(int loggedInUserID) {
    int bookID;
    char input[20];
    int userIndex = findUserByID(loggedInUserID);
    int bookIndex;
    int borrowedIndex = -1;
    struct Book* book;
    struct User* user;

    printf("\n=== Return Book ===\n");

    /* Validate user */
    if (userIndex == -1) {
        printf("[Error] Invalid user session.\n");
        return;
    }

    user = &g_users[userIndex];

    /* Check if user has borrowed books */
    if (user->borrowedCount == 0) {
        printf("[Info] You have no books to return.\n");
        return;
    }

    /* Show user's borrowed books */
    printf("\n--- Your Borrowed Books ---\n");
    for (int i = 0; i < user->borrowedCount; i++) {
        bookIndex = findBookByID(user->borrowedBookIDs[i]);
        if (bookIndex != -1) {
            printf("[ID: %d] %s\n",
                   g_books[bookIndex].id, g_books[bookIndex].title);
        }
    }

    /* Get book ID to return */
    printf("\nEnter Book ID to return (0 to cancel): ");
    readString(input, sizeof(input));

    bookID = atoi(input);

    if (bookID == 0) {
        printf("[Info] Return cancelled.\n");
        return;
    }

    /* Check if user has this book */
    for (int i = 0; i < user->borrowedCount; i++) {
        if (user->borrowedBookIDs[i] == bookID) {
            borrowedIndex = i;
            break;
        }
    }

    if (borrowedIndex == -1) {
        printf("[Error] You haven't borrowed this book.\n");
        return;
    }

    /* Find the book in global array */
    bookIndex = findBookByID(bookID);

    if (bookIndex == -1) {
        printf("[Error] Book not found in system.\n");
        return;
    }

    book = &g_books[bookIndex];

    /* Update book status */
    book->status = 0;           /* Mark as available */
    book->borrowedByUserID = -1;

    /* Remove book from user's borrowed list (array element deletion) */
    /* Shift remaining elements to fill the gap */
    for (int i = borrowedIndex; i < user->borrowedCount - 1; i++) {
        user->borrowedBookIDs[i] = user->borrowedBookIDs[i + 1];
    }
    user->borrowedBookIDs[user->borrowedCount - 1] = -1;
    user->borrowedCount--;

    printf("[Success] You have returned '%s'.\n", book->title);
    printf("[Info] Current borrowed books: %d/%d\n",
           user->borrowedCount, MAX_BORROW);
}

/**
 * @brief Displays user's information and borrowed books
 *
 * Shows user profile and cross-references book data
 * to display borrowed book titles.
 *
 * @param loggedInUserID The ID of the user to display info for
 */
void showMyInfo(int loggedInUserID) {
    int userIndex = findUserByID(loggedInUserID);
    int bookIndex;
    struct User* user;

    printf("\n=== My Information ===\n");

    /* Validate user */
    if (userIndex == -1) {
        printf("[Error] Invalid user session.\n");
        return;
    }

    user = &g_users[userIndex];

    /* Display user information */
    printf("\n--- Profile ---\n");
    printf("User ID: %d\n", user->userID);
    printf("Username: %s\n", user->username);
    printf("Name: %s\n", user->name);
    printf("Borrowed Books: %d/%d\n", user->borrowedCount, MAX_BORROW);

    /* Display borrowed books with cross-reference to book data */
    if (user->borrowedCount > 0) {
        printf("\n--- Currently Borrowed Books ---\n");
        for (int i = 0; i < user->borrowedCount; i++) {
            /* Cross-reference: Find book details using book ID */
            bookIndex = findBookByID(user->borrowedBookIDs[i]);
            if (bookIndex != -1) {
                printf("%d. [ID: %d] %s by %s\n",
                       i + 1,
                       g_books[bookIndex].id,
                       g_books[bookIndex].title,
                       g_books[bookIndex].author);
            }
        }
    } else {
        printf("\n[Info] You have no borrowed books.\n");
    }
}
