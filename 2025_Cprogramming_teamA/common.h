#ifndef COMMON_H
#define COMMON_H

#include "book.h"
#include "user.h"


#define MAX_BOOKS 100    // Maximum number of books in the system
#define MAX_USERS 50     // Maximum number of users in the system

// Admin credentials for admin mode access
#define ADMIN_ID "admin"
#define ADMIN_PW "1234"

// Data file names for binary storage
#define BOOKS_FILE "books.dat"
#define USERS_FILE "users.dat"


 // Note: Only declare with extern here.
 //       Actual definitions are in main.c
 
extern struct Book g_books[MAX_BOOKS];   // Global book array
extern struct User g_users[MAX_USERS];   // Global user array
extern int g_bookCount;                  // Current number of books
extern int g_userCount;                  // Current number of users


 // Called at program startup to restore saved data.
 void loadAllData(void);


 // Called before program termination to persist data.
void saveAllData(void);
void loadBooks(void);
void saveBooks(void);
void loadUsers(void);
void saveUsers(void);


 // Shows options: Sign Up, Login, Exit
 void userMode(void);

 
 
 // Prompts for username, password, name and validates uniqueness.
void signUp(void);
int login(void);
void userMenu(int loggedInUserID);
void searchBook(void);
void loanBook(int loggedInUserID);
void returnBook(int loggedInUserID);
void showMyInfo(int loggedInUserID);


 // Requires admin authentication before showing admin menu.
void adminMode(void);


 // Provides: Add, View, Update, Delete book functions.
void manageBooks(void);


 // Provides: View, Update, Delete user functions.
void manageUsers(void);


 // Shows all borrowed books with borrower information.
void viewLoanStatus(void);
void displayBookCover(struct Book* book);


 // Removes any remaining characters from stdin.
void clearInputBuffer(void);
void readString(char* buffer, int size);
int findBookByID(int bookID);
int findUserByID(int userID);
int getNextBookID(void);
int getNextUserID(void);

#endif // COMMON_H
