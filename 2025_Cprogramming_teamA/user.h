/**
 * @file user.h
 * @brief Header file for user management module
 *
 * Declares functions for loading, saving, and managing users.
 */

#pragma once

/**
 * @brief Loads user data from data file
 *
 * Reads users from 'users.dat' into the global g_users array.
 */
void loadUsers();

/**
 * @brief Saves user data to data file
 *
 * Writes the global g_users array to 'users.dat'.
 */
void saveUsers();

/**
 * @brief Displays user management menu for administrators
 *
 * Allows viewing and managing registered users.
 */
void manageUsers();
