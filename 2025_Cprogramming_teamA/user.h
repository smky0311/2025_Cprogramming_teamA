/**
 * @file user.h
 * @brief Header file for User structure definition
 *
 * This file defines the User structure and related constants
 * for the library management system.
 */

#ifndef USER_H
#define USER_H

/* ============================================
 * CONSTANT DEFINITIONS FOR USER
 * ============================================ */
#define MAX_USERNAME 50   /* Maximum length of username (login ID) */
#define MAX_PASSWORD 50   /* Maximum length of password */
#define MAX_NAME 30       /* Maximum length of user's real name */
#define MAX_BORROW 5      /* Maximum number of books a user can borrow */

/* ============================================
 * USER STRUCTURE DEFINITION
 * ============================================ */

/**
 * @brief Structure representing a user in the system
 *
 * Contains all information about a single user including
 * authentication credentials and borrowing information.
 */
struct User {
    int userID;                        /* Unique user ID (auto-generated) */
    char username[MAX_USERNAME];       /* Login ID */
    char password[MAX_PASSWORD];       /* Login password */
    char name[MAX_NAME];               /* User's real name */
    int borrowedBookIDs[MAX_BORROW];   /* Array of borrowed book IDs */
    int borrowedCount;                 /* Current number of borrowed books */
};

#endif /* USER_H */
