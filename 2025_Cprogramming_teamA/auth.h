/**
 * @file auth.h
 * @brief Header file for authentication module
 *
 * Declares functions for user registration and login.
 */

#pragma once

/**
 * @brief Registers a new user in the system
 *
 * Prompts for ID and password, validates the ID is unique,
 * and adds the new user to the global user array.
 */
void signUp();

/**
 * @brief Authenticates a user with ID and password
 *
 * @return 1 on successful login, 0 on failure
 */
int login();
