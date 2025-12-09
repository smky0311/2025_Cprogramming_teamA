/**
 * @file user.c
 * @brief User management module for the library system
 *
 * This file handles loading, saving, and managing user data.
 * It provides functionality for persisting user information
 * and viewing user lists (admin feature).
 */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "common.h"  /* Required for global variables (g_users) */
#include "user.h"

/**
 * @brief Loads user data from the data file
 *
 * Reads user information from 'users.dat' file into the global
 * g_users array. If the file doesn't exist, starts with empty data.
 *
 * TODO: Implement file reading logic similar to loadBooks()
 */
void loadUsers() {
    printf("[System] User data loaded.\n");
}

/**
 * @brief Saves user data to the data file
 *
 * Writes all user information from the global g_users array
 * to 'users.dat' file for persistent storage.
 *
 * TODO: Implement file writing logic similar to saveBooks()
 */
void saveUsers() {
    printf("[System] User data saved.\n");
}

/**
 * @brief Displays the user management menu for administrators
 *
 * Provides options to view and manage registered users.
 * This is an admin-only feature.
 *
 * TODO: Implement user listing and management options
 */
void manageUsers() {
    printf("[Admin] Entering user management menu...\n");
}
