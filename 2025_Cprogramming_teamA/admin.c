/**
 * @file admin.c
 * @brief Admin mode module for the library management system
 *
 * This file handles all administrator functionality including:
 * - Admin authentication
 * - Book CRUD operations (Create, Read, Update, Delete)
 * - User management (Read, Update, Delete)
 * - Loan status monitoring with advanced cross-referencing
 */

#define _CRT_SECURE_NO_WARNINGS  /* Disable MSVC security warnings for fopen, strcpy, etc. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "common.h"
#include "admin.h"

/**
 * @brief Authenticates admin user
 *
 * Prompts for admin credentials and validates against
 * predefined ADMIN_ID and ADMIN_PW.
 *
 * @return 1 on successful authentication, 0 on failure
 */
static int adminLogin(void) {
    char id[50];
    char pw[50];

    printf("\n=== Admin Login ===\n");
    printf("Enter Admin ID: ");
    readString(id, sizeof(id));

    printf("Enter Admin Password: ");
    readString(pw, sizeof(pw));

    /* Validate credentials using strcmp */
    if (strcmp(id, ADMIN_ID) == 0 && strcmp(pw, ADMIN_PW) == 0) {
        printf("[Success] Admin authentication successful.\n");
        return 1;
    }

    printf("[Error] Invalid admin credentials.\n");
    return 0;
}

/**
 * @brief Displays admin mode interface
 *
 * First authenticates the admin, then shows the admin menu
 * with options for book management, user management, and
 * loan status viewing.
 */
void adminMode(void) {
    int choice;
    char input[10];

    /* Authenticate admin first */
    if (!adminLogin()) {
        return;
    }

    while (1) {
        printf("\n=== Admin Mode ===\n");
        printf("1. Book Management\n");
        printf("2. User Management\n");
        printf("3. View Loan Status\n");
        printf("0. Back to Main Menu\n");
        printf("Select: ");

        readString(input, sizeof(input));

        if (!isdigit(input[0])) {
            printf("[Error] Please enter a number.\n");
            continue;
        }

        choice = atoi(input);

        switch (choice) {
            case 1:
                manageBooks();
                break;
            case 2:
                manageUsers();
                break;
            case 3:
                viewLoanStatus();
                break;
            case 0:
                printf("[Info] Exiting admin mode.\n");
                return;
            default:
                printf("[Error] Invalid selection.\n");
        }
    }
}

/**
 * @brief Adds a new book to the library
 *
 * Prompts for book details and adds to the global array.
 */
static void addBook(void) {
    struct Book newBook;

    printf("\n=== Add New Book ===\n");

    /* Check if book limit is reached */
    if (g_bookCount >= MAX_BOOKS) {
        printf("[Error] Maximum book limit reached.\n");
        return;
    }

    /* Generate new book ID */
    newBook.id = getNextBookID();

    /* Get book title */
    printf("Enter book title: ");
    readString(newBook.title, sizeof(newBook.title));

    if (strlen(newBook.title) == 0) {
        printf("[Error] Title cannot be empty.\n");
        return;
    }

    /* Get author name */
    printf("Enter author name: ");
    readString(newBook.author, sizeof(newBook.author));

    if (strlen(newBook.author) == 0) {
        printf("[Error] Author cannot be empty.\n");
        return;
    }

    /* Get genre */
    printf("Enter genre: ");
    readString(newBook.genre, sizeof(newBook.genre));

    if (strlen(newBook.genre) == 0) {
        printf("[Error] Genre cannot be empty.\n");
        return;
    }

    /* Set initial status as available */
    newBook.status = 0;           /* 0 = available */
    newBook.borrowedByUserID = -1;

    /* Add to global array */
    g_books[g_bookCount] = newBook;
    g_bookCount++;

    printf("[Success] Book added with ID %d.\n", newBook.id);

    /* Display the new book with ASCII cover */
    printf("\n--- Book Added ---\n");
    displayBookCover(&newBook);
}

/**
 * @brief Displays all books in the library
 *
 * Lists all books with their details and availability status.
 */
static void viewAllBooks(void) {
    printf("\n=== All Books (%d total) ===\n", g_bookCount);

    if (g_bookCount == 0) {
        printf("[Info] No books in the library.\n");
        return;
    }

    for (int i = 0; i < g_bookCount; i++) {
        displayBookCover(&g_books[i]);
    }
}

/**
 * @brief Updates an existing book's information
 *
 * Allows modification of title, author, or genre.
 */
static void updateBook(void) {
    int bookID;
    int bookIndex;
    int choice;
    char input[100];
    struct Book* book;

    printf("\n=== Update Book ===\n");

    if (g_bookCount == 0) {
        printf("[Info] No books to update.\n");
        return;
    }

    /* Show all books */
    printf("\n--- Book List ---\n");
    for (int i = 0; i < g_bookCount; i++) {
        printf("[ID: %d] %s by %s\n",
               g_books[i].id, g_books[i].title, g_books[i].author);
    }

    /* Get book ID */
    printf("\nEnter Book ID to update (0 to cancel): ");
    readString(input, sizeof(input));
    bookID = atoi(input);

    if (bookID == 0) {
        printf("[Info] Update cancelled.\n");
        return;
    }

    /* Find book */
    bookIndex = findBookByID(bookID);

    if (bookIndex == -1) {
        printf("[Error] Book not found.\n");
        return;
    }

    book = &g_books[bookIndex];

    /* Show current info */
    printf("\n--- Current Book Info ---\n");
    printf("1. Title: %s\n", book->title);
    printf("2. Author: %s\n", book->author);
    printf("3. Genre: %s\n", book->genre);
    printf("0. Cancel\n");

    printf("\nSelect field to update: ");
    readString(input, sizeof(input));

    if (!isdigit(input[0])) {
        printf("[Error] Please enter a number.\n");
        return;
    }

    choice = atoi(input);

    switch (choice) {
        case 1:
            printf("Enter new title: ");
            readString(input, sizeof(input));
            if (strlen(input) > 0) {
                strcpy(book->title, input);
                printf("[Success] Title updated.\n");
            }
            break;
        case 2:
            printf("Enter new author: ");
            readString(input, sizeof(input));
            if (strlen(input) > 0) {
                strcpy(book->author, input);
                printf("[Success] Author updated.\n");
            }
            break;
        case 3:
            printf("Enter new genre: ");
            readString(input, sizeof(input));
            if (strlen(input) > 0) {
                strcpy(book->genre, input);
                printf("[Success] Genre updated.\n");
            }
            break;
        case 0:
            printf("[Info] Update cancelled.\n");
            break;
        default:
            printf("[Error] Invalid selection.\n");
    }
}

/**
 * @brief Deletes a book from the library
 *
 * Removes book from the array by shifting elements.
 * Cannot delete if book is currently borrowed.
 */
static void deleteBook(void) {
    int bookID;
    int bookIndex;
    char input[20];
    char confirm[10];

    printf("\n=== Delete Book ===\n");

    if (g_bookCount == 0) {
        printf("[Info] No books to delete.\n");
        return;
    }

    /* Show all books */
    printf("\n--- Book List ---\n");
    for (int i = 0; i < g_bookCount; i++) {
        printf("[ID: %d] %s (%s)\n",
               g_books[i].id, g_books[i].title,
               g_books[i].status == 0 ? "Available" : "Borrowed");
    }

    /* Get book ID */
    printf("\nEnter Book ID to delete (0 to cancel): ");
    readString(input, sizeof(input));
    bookID = atoi(input);

    if (bookID == 0) {
        printf("[Info] Delete cancelled.\n");
        return;
    }

    /* Find book */
    bookIndex = findBookByID(bookID);

    if (bookIndex == -1) {
        printf("[Error] Book not found.\n");
        return;
    }

    /* Check if book is borrowed */
    if (g_books[bookIndex].status == 1) {
        printf("[Error] Cannot delete a borrowed book. Please wait for return.\n");
        return;
    }

    /* Confirm deletion */
    printf("Are you sure you want to delete '%s'? (y/n): ",
           g_books[bookIndex].title);
    readString(confirm, sizeof(confirm));

    if (confirm[0] != 'y' && confirm[0] != 'Y') {
        printf("[Info] Delete cancelled.\n");
        return;
    }

    /* Delete by shifting array elements */
    for (int i = bookIndex; i < g_bookCount - 1; i++) {
        g_books[i] = g_books[i + 1];
    }
    g_bookCount--;

    printf("[Success] Book deleted.\n");
}

/**
 * @brief Manages book CRUD operations
 *
 * Provides submenu for Add, View, Update, Delete operations.
 */
void manageBooks(void) {
    int choice;
    char input[10];

    while (1) {
        printf("\n=== Book Management ===\n");
        printf("1. Add Book\n");
        printf("2. View All Books\n");
        printf("3. Update Book\n");
        printf("4. Delete Book\n");
        printf("0. Back\n");
        printf("Select: ");

        readString(input, sizeof(input));

        if (!isdigit(input[0])) {
            printf("[Error] Please enter a number.\n");
            continue;
        }

        choice = atoi(input);

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                viewAllBooks();
                break;
            case 3:
                updateBook();
                break;
            case 4:
                deleteBook();
                break;
            case 0:
                return;
            default:
                printf("[Error] Invalid selection.\n");
        }
    }
}

/**
 * @brief Displays all registered users
 *
 * Lists all users with their details.
 */
static void viewAllUsers(void) {
    printf("\n=== All Users (%d total) ===\n", g_userCount);

    if (g_userCount == 0) {
        printf("[Info] No registered users.\n");
        return;
    }

    printf("\n%-6s %-20s %-20s %-10s\n",
           "ID", "Username", "Name", "Borrowed");
    printf("------------------------------------------------------\n");

    for (int i = 0; i < g_userCount; i++) {
        printf("%-6d %-20s %-20s %d/%d\n",
               g_users[i].userID,
               g_users[i].username,
               g_users[i].name,
               g_users[i].borrowedCount,
               MAX_BORROW);
    }
}

/**
 * @brief Updates a user's information
 *
 * Allows modification of username, password, or name.
 */
static void updateUser(void) {
    int userID;
    int userIndex;
    int choice;
    char input[100];
    struct User* user;

    printf("\n=== Update User ===\n");

    if (g_userCount == 0) {
        printf("[Info] No users to update.\n");
        return;
    }

    /* Show all users */
    viewAllUsers();

    /* Get user ID */
    printf("\nEnter User ID to update (0 to cancel): ");
    readString(input, sizeof(input));
    userID = atoi(input);

    if (userID == 0) {
        printf("[Info] Update cancelled.\n");
        return;
    }

    /* Find user */
    userIndex = findUserByID(userID);

    if (userIndex == -1) {
        printf("[Error] User not found.\n");
        return;
    }

    user = &g_users[userIndex];

    /* Show current info */
    printf("\n--- Current User Info ---\n");
    printf("1. Username: %s\n", user->username);
    printf("2. Password: ****\n");
    printf("3. Name: %s\n", user->name);
    printf("0. Cancel\n");

    printf("\nSelect field to update: ");
    readString(input, sizeof(input));

    if (!isdigit(input[0])) {
        printf("[Error] Please enter a number.\n");
        return;
    }

    choice = atoi(input);

    switch (choice) {
        case 1:
            printf("Enter new username: ");
            readString(input, sizeof(input));
            if (strlen(input) > 0) {
                /* Check for duplicate username */
                int duplicate = 0;
                for (int i = 0; i < g_userCount; i++) {
                    if (i != userIndex &&
                        strcmp(g_users[i].username, input) == 0) {
                        duplicate = 1;
                        break;
                    }
                }
                if (duplicate) {
                    printf("[Error] Username already exists.\n");
                } else {
                    strcpy(user->username, input);
                    printf("[Success] Username updated.\n");
                }
            }
            break;
        case 2:
            printf("Enter new password: ");
            readString(input, sizeof(input));
            if (strlen(input) > 0) {
                strcpy(user->password, input);
                printf("[Success] Password updated.\n");
            }
            break;
        case 3:
            printf("Enter new name: ");
            readString(input, sizeof(input));
            if (strlen(input) > 0) {
                strcpy(user->name, input);
                printf("[Success] Name updated.\n");
            }
            break;
        case 0:
            printf("[Info] Update cancelled.\n");
            break;
        default:
            printf("[Error] Invalid selection.\n");
    }
}

/**
 * @brief Deletes a user from the system
 *
 * Removes user from the array by shifting elements.
 * Also updates any books borrowed by this user.
 */
static void deleteUser(void) {
    int userID;
    int userIndex;
    char input[20];
    char confirm[10];
    struct User* user;

    printf("\n=== Delete User ===\n");

    if (g_userCount == 0) {
        printf("[Info] No users to delete.\n");
        return;
    }

    /* Show all users */
    viewAllUsers();

    /* Get user ID */
    printf("\nEnter User ID to delete (0 to cancel): ");
    readString(input, sizeof(input));
    userID = atoi(input);

    if (userID == 0) {
        printf("[Info] Delete cancelled.\n");
        return;
    }

    /* Find user */
    userIndex = findUserByID(userID);

    if (userIndex == -1) {
        printf("[Error] User not found.\n");
        return;
    }

    user = &g_users[userIndex];

    /* Check if user has borrowed books */
    if (user->borrowedCount > 0) {
        printf("[Warning] This user has %d borrowed book(s).\n",
               user->borrowedCount);
        printf("Deleting will mark those books as returned.\n");
    }

    /* Confirm deletion */
    printf("Are you sure you want to delete user '%s'? (y/n): ",
           user->username);
    readString(confirm, sizeof(confirm));

    if (confirm[0] != 'y' && confirm[0] != 'Y') {
        printf("[Info] Delete cancelled.\n");
        return;
    }

    /* Return all borrowed books */
    for (int i = 0; i < user->borrowedCount; i++) {
        int bookIndex = findBookByID(user->borrowedBookIDs[i]);
        if (bookIndex != -1) {
            g_books[bookIndex].status = 0;
            g_books[bookIndex].borrowedByUserID = -1;
        }
    }

    /* Delete by shifting array elements */
    for (int i = userIndex; i < g_userCount - 1; i++) {
        g_users[i] = g_users[i + 1];
    }
    g_userCount--;

    printf("[Success] User deleted.\n");
}

/**
 * @brief Manages user CRUD operations
 *
 * Provides submenu for View, Update, Delete operations.
 * Note: Users are added through signUp in user mode.
 */
void manageUsers(void) {
    int choice;
    char input[10];

    while (1) {
        printf("\n=== User Management ===\n");
        printf("1. View All Users\n");
        printf("2. Update User\n");
        printf("3. Delete User\n");
        printf("0. Back\n");
        printf("Select: ");

        readString(input, sizeof(input));

        if (!isdigit(input[0])) {
            printf("[Error] Please enter a number.\n");
            continue;
        }

        choice = atoi(input);

        switch (choice) {
            case 1:
                viewAllUsers();
                break;
            case 2:
                updateUser();
                break;
            case 3:
                deleteUser();
                break;
            case 0:
                return;
            default:
                printf("[Error] Invalid selection.\n");
        }
    }
}

/**
 * @brief Displays current loan status
 *
 * Shows all currently borrowed books with borrower information.
 * Implements advanced data cross-referencing between books and users.
 */
void viewLoanStatus(void) {
    int borrowedCount = 0;

    printf("\n=== Current Loan Status ===\n");

    printf("\n%-6s %-25s %-20s %-20s\n",
           "ID", "Book Title", "Author", "Borrowed By");
    printf("----------------------------------------------------------------------\n");

    // Search through all books for borrowed ones
    for (int i = 0; i < g_bookCount; i++) {
        if (g_books[i].status == 1) {  /* Book is borrowed */
            borrowedCount++;

            /* Cross-reference: Find the user who borrowed this book */
            int userIndex = findUserByID(g_books[i].borrowedByUserID);
            char borrowerName[MAX_NAME];

            if (userIndex != -1) {
                strcpy(borrowerName, g_users[userIndex].name);
            } else {
                strcpy(borrowerName, "Unknown");
            }

            /* Display book and borrower info */
            printf("%-6d %-25s %-20s %-20s\n",
                   g_books[i].id,
                   g_books[i].title,
                   g_books[i].author,
                   borrowerName);
        }
    }

    if (borrowedCount == 0) {
        printf("\n[Info] No books are currently borrowed.\n");
    } else {
        printf("\n[Info] Total borrowed books: %d\n", borrowedCount);
    }

    // Show summary by user
    printf("\n=== Borrowing Summary by User ===\n");
    printf("\n%-6s %-20s %-20s %-10s\n",
           "ID", "Username", "Name", "Books");
    printf("------------------------------------------------------\n");

    for (int i = 0; i < g_userCount; i++) {
        if (g_users[i].borrowedCount > 0) {
            printf("%-6d %-20s %-20s %d/%d\n",
                   g_users[i].userID,
                   g_users[i].username,
                   g_users[i].name,
                   g_users[i].borrowedCount,
                   MAX_BORROW);

            /* List borrowed books for this user */
            for (int j = 0; j < g_users[i].borrowedCount; j++) {
                int bookIndex = findBookByID(g_users[i].borrowedBookIDs[j]);
                if (bookIndex != -1) {
                    printf("       -> [%d] %s\n",
                           g_books[bookIndex].id,
                           g_books[bookIndex].title);
                }
            }
        }
    }
}
