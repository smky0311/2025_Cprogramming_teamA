#ifndef UTILS_H
#define UTILS_H

#include "book.h"


 // UTILITY FUNCTION DECLARATIONS



 // Creates a visual representation of a book with
 // title centered inside a box frame.

void displayBookCover(struct Book* book);


 // Removes any remaining characters from stdin
 // to prevent input issues.
 
void clearInputBuffer(void);


 // Reads input using fgets and removes trailing newline.
 
void readString(char* buffer, int size);


 // Searches the global book array for a matching ID.

int findBookByID(int bookID);


 // Searches the global user array for a matching ID.

int findUserByID(int userID);


 // Finds the maximum existing book ID and returns +1.

int getNextBookID(void);


 // Finds the maximum existing user ID and returns +1.
 
int getNextUserID(void);

#endif // UTILS_H
