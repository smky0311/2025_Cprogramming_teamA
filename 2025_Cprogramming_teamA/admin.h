/**
 * @file admin.h
 * @brief Header file for admin mode module
 *
 * This file declares admin-related functions for the
 * library management system.
 */

#ifndef ADMIN_H
#define ADMIN_H

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
 * Implements advanced data cross-referencing.
 */
void viewLoanStatus(void);

#endif /* ADMIN_H */
