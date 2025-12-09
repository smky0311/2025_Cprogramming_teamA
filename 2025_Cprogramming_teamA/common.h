/**
 * @file common.h
 * @brief Common definitions and declarations for the library system
 *
 * This header file contains constant definitions, structure declarations,
 * and external variable declarations used across all modules.
 */

#pragma once  /* Prevent multiple header inclusion */

/* ============================================
 * 1. CONSTANT DEFINITIONS
 * ============================================ */
#define MAX_BOOKS 100  /* Maximum number of books in the system */
#define MAX_USERS 50   /* Maximum number of users in the system */

/* ============================================
 * 2. STRUCTURE DEFINITIONS
 * ============================================ */

/**
 * @brief Structure representing a book in the library
 */
typedef struct {
    char title[100];   /* Book title (max 99 chars + null) */
    char id[20];       /* Book ID/ISBN */
    int available;     /* Availability status: 1 = available, 0 = borrowed */
    char author[30];   /* Author name */
} Book;

/**
 * @brief Structure representing a user in the system
 */
typedef struct {
    char id[20];  /* User ID (max 19 chars + null) */
    char pw[20];  /* User password (max 19 chars + null) */
} User;

/* ============================================
 * 3. EXTERNAL VARIABLE DECLARATIONS
 * ============================================
 * Note: Only declare with extern here.
 *       Do NOT initialize (= {0}) in header files.
 *       Actual definitions are in main.c
 */
extern Book g_books[MAX_BOOKS];  /* Global book array */
extern User g_users[MAX_USERS];  /* Global user array */
extern int g_bookCount;          /* Current number of books */
extern int g_userCount;          /* Current number of users */
