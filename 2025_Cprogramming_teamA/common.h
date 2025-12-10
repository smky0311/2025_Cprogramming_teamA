/**
 * @file common.h
 * @brief Common definitions and declarations for the library system
 *
 * This header file contains constant definitions, structure includes,
 * and external variable declarations used across all modules.
 */

#ifndef COMMON_H
#define COMMON_H

#include "book.h"
#include "user.h"

/* ============================================
 * SYSTEM-WIDE CONSTANT DEFINITIONS
 * ============================================ */
#define MAX_BOOKS 100    /* Maximum number of books in the system */
#define MAX_USERS 50     /* Maximum number of users in the system */

/* Admin credentials for admin mode access */
#define ADMIN_ID "admin"
#define ADMIN_PW "1234"

/* Data file names for binary storage */
#define BOOKS_FILE "books.dat"
#define USERS_FILE "users.dat"

/* ============================================
 * EXTERNAL VARIABLE DECLARATIONS
 * ============================================
 * Note: Only declare with extern here.
 *       Actual definitions are in main.c
 */
extern struct Book g_books[MAX_BOOKS];   /* Global book array */
extern struct User g_users[MAX_USERS];   /* Global user array */
extern int g_bookCount;                  /* Current number of books */
extern int g_userCount;                  /* Current number of users */

/* ============================================
 * FUNCTION DECLARATIONS - Data I/O
 * ============================================ */

/**
 * @brief Loads all data (books and users) from binary files
 *
 * Called at program startup to restore saved data.
 */
void loadAllData(void);

/**
 * @brief Saves all data (books and users) to binary files
 *
 * Called before program termination to persist data.
 */
void saveAllData(void);

/**
 * @brief Loads book data from books.dat
 */
void loadBooks(void);

/**
 * @brief Saves book data to books.dat
 */
void saveBooks(void);

/**
 * @brief Loads user data from users.dat
 */
void loadUsers(void);

/**
 * @brief Saves user data to users.dat
 */
void saveUsers(void);

/* ============================================
 * FUNCTION DECLARATIONS - User Mode (user.c)
 * ============================================ */

/**
 * @brief Displays user mode main menu
 *
 * Shows options: Sign Up, Login, Exit
 */
void userMode(void);

/**
 * @brief Registers a new user in the system
 *
 * Prompts for username, password, name and validates uniqueness.
 */
void signUp(void);

/**
 * @brief Authenticates a user with credentials
 *
 * @return User ID on success, -1 on failure
 */
int login(void);

/**
 * @brief Displays user menu after login
 *
 * @param loggedInUserID The ID of the currently logged in user
 */
void userMenu(int loggedInUserID);

/**
 * @brief Searches for books by title or author
 *
 * Provides submenu for search type selection.
 */
void searchBook(void);

/**
 * @brief Borrows a book for the logged-in user
 *
 * @param loggedInUserID The ID of the user borrowing the book
 */
void loanBook(int loggedInUserID);

/**
 * @brief Returns a borrowed book
 *
 * @param loggedInUserID The ID of the user returning the book
 */
void returnBook(int loggedInUserID);

/**
 * @brief Displays user's information and borrowed books
 *
 * @param loggedInUserID The ID of the user to display info for
 */
void showMyInfo(int loggedInUserID);

/* ============================================
 * FUNCTION DECLARATIONS - Admin Mode (admin.c)
 * ============================================ */

/**
 * @brief Displays admin mode interface
 *
 * Requires admin authentication before showing admin menu.
 */
void adminMode(void);

/**
 * @brief Manages book CRUD operations
 *
 * Provides: Add, View, Update, Delete book functions.
 */
void manageBooks(void);

/**
 * @brief Manages user CRUD operations
 *
 * Provides: View, Update, Delete user functions.
 */
void manageUsers(void);

/**
 * @brief Displays current loan status
 *
 * Shows all borrowed books with borrower information.
 */
void viewLoanStatus(void);

/* ============================================
 * FUNCTION DECLARATIONS - Utilities (utils.c)
 * ============================================ */

/**
 * @brief Displays an ASCII art book cover
 *
 * @param book Pointer to the book to display
 */
void displayBookCover(struct Book* book);

/**
 * @brief Clears the input buffer
 *
 * Removes any remaining characters from stdin.
 */
void clearInputBuffer(void);

/**
 * @brief Safely reads a string from user input
 *
 * @param buffer Buffer to store the input
 * @param size Size of the buffer
 */
void readString(char* buffer, int size);

/**
 * @brief Finds a book by its ID
 *
 * @param bookID The ID to search for
 * @return Index in g_books array, or -1 if not found
 */
int findBookByID(int bookID);

/**
 * @brief Finds a user by their ID
 *
 * @param userID The ID to search for
 * @return Index in g_users array, or -1 if not found
 */
int findUserByID(int userID);

/**
 * @brief Generates the next available book ID
 *
 * @return Next available book ID
 */
int getNextBookID(void);

/**
 * @brief Generates the next available user ID
 *
 * @return Next available user ID
 */
int getNextUserID(void);

#endif /* COMMON_H */
