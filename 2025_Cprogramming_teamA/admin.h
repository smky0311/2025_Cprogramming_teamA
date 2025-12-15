
 // This file declares admin-related functions for the
 // library management system.
 

#ifndef ADMIN_H
#define ADMIN_H


 // Requires admin authentication before showing admin menu.
 
void adminMode(void);


 // Provides: Add, View, Update, Delete book functions.
 
void manageBooks(void);


 // Provides: View, Update, Delete user functions.
 
void manageUsers(void);


 // Shows all borrowed books with borrower information.
 // Implements advanced data cross-referencing.
 
void viewLoanStatus(void);

#endif // ADMIN_H
