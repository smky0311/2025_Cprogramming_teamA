 /* This file defines the Book structure and related constants
 * for the library management system.
 */

#ifndef BOOK_H
#define BOOK_H

// CONSTANT DEFINITIONS FOR BOOK

#define MAX_TITLE 100    /* Maximum length of book title */
#define MAX_AUTHOR 50    /* Maximum length of author name */
#define MAX_GENRE 30     /* Maximum length of genre name */

// BOOK STRUCTURE DEFINITION

struct Book {
    int id;                      /* Unique book ID (auto-generated) */
    char title[MAX_TITLE];       /* Book title */
    char author[MAX_AUTHOR];     /* Author name */
    char genre[MAX_GENRE];       /* Book genre/category */
    int status;                  /* Borrow status: 0 = available, 1 = borrowed */
    int borrowedByUserID;        /* ID of user who borrowed (-1 if available) */
};

#endif /* BOOK_H */
