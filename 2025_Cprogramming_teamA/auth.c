/**
 * @file auth.c
 * @brief Authentication module for user sign-up and login
 *
 * This file handles user registration (sign-up) and authentication (login).
 * It validates user input and manages the global user array.
 */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "common.h"  /* Required for global variables (g_users) */
#include "auth.h"

/**
 * @brief Registers a new user in the system
 *
 * Prompts the user to enter a new ID and password. Validates that
 * the ID is not already taken and adds the new user to the global
 * user array if successful.
 */
void signUp() {
    char id[20];    /* Array to store the new user ID (max 19 chars + null) */
    char pw[20];    /* Array to store the password */
    char buf[256];  /* Buffer for safely reading user input */

    printf("[Auth] Sign-up started...\n");

    /* Check if maximum user limit has been reached */
    if (g_userCount >= MAX_USERS) {
        printf("User limit reached. Cannot add more users.\n");
        return;
    }

    /* Prompt for new ID */
    printf("Enter new ID: ");

    /* Read ID input safely using fgets */
    if (!fgets(buf, sizeof(buf), stdin)) {
        printf("Input error.\n");
        return;
    }

    /* Remove newline character (\n or \r\n) from input */
    buf[strcspn(buf, "\r\n")] = '\0';

    /* Copy buffer to id with size limit for safety */
    strncpy(id, buf, sizeof(id));
    id[sizeof(id) - 1] = '\0';  /* Ensure null termination */

    /* Check if ID already exists in the system */
    for (int i = 0; i < g_userCount; i++) {
        if (strcmp(g_users[i].id, id) == 0) {
            printf("ID already exists. Please choose another.\n");
            return;
        }
    }

    /* Prompt for password */
    printf("Enter password: ");

    /* Read password input */
    if (!fgets(buf, sizeof(buf), stdin)) {
        printf("Input error.\n");
        return;
    }

    /* Remove newline character from password input */
    buf[strcspn(buf, "\r\n")] = '\0';

    /* Copy buffer to pw with size limit */
    strncpy(pw, buf, sizeof(pw));
    pw[sizeof(pw) - 1] = '\0';  /* Ensure null termination */

    /* Store the new ID in the global users array */
    strncpy(g_users[g_userCount].id, id, sizeof(g_users[g_userCount].id));
    g_users[g_userCount].id[sizeof(g_users[g_userCount].id) - 1] = '\0';

    /* Store the password in the global users array */
    strncpy(g_users[g_userCount].pw, pw, sizeof(g_users[g_userCount].pw));
    g_users[g_userCount].pw[sizeof(g_users[g_userCount].pw) - 1] = '\0';

    /* Increment total user count */
    g_userCount++;

    printf("Sign-up complete. User '%s' registered.\n", id);
}

/**
 * @brief Authenticates a user with ID and password
 *
 * Prompts the user to enter their ID and password, then validates
 * the credentials against the stored user data.
 *
 * @return 1 on successful login, 0 on failure
 */
int login() {
    char id[20];    /* Array to store entered ID (max 20 chars) */
    char pw[20];    /* Array to store entered password (max 20 chars) */
    char buf[256];  /* Buffer for input (256 chars) */

    /* Check if there are any registered users */
    if (g_userCount <= 0) {
        printf("[Auth] No user data found. Please sign up first.\n");
        return 0;
    }

    printf("[Auth] Login function started...\n");

    /* Prompt for ID input */
    printf("Enter ID: ");

    /* Read ID with fgets; returns NULL on buffer overflow */
    if (!fgets(buf, sizeof(buf), stdin)) {
        printf("Input error.\n");
        return 0;
    }

    /* Remove carriage return or line feed from input */
    buf[strcspn(buf, "\r\n")] = '\0';

    /* Copy input to id array with size limit; excess is truncated */
    strncpy(id, buf, sizeof(id));
    id[sizeof(id) - 1] = '\0';  /* Force null termination to prevent errors */

    /* Prompt for password input */
    printf("Enter PW: ");

    /* Read password with fgets */
    if (!fgets(buf, sizeof(buf), stdin)) {
        printf("Input error.\n");
        return 0;
    }

    /* Remove carriage return or line feed from password input */
    buf[strcspn(buf, "\r\n")] = '\0';

    /* Copy input to pw array with size limit */
    strncpy(pw, buf, sizeof(pw));
    pw[sizeof(pw) - 1] = '\0';  /* Force null termination */

    /* Compare entered credentials with stored user data */
    for (int i = 0; i < g_userCount; i++) {
        /* Check if ID matches (strcmp returns 0 on match) */
        if (strcmp(g_users[i].id, id) == 0) {
            /* ID found, now check password */
            if (strcmp(g_users[i].pw, pw) == 0) {
                printf("[%s] Login successful.\n", id);
                return 1;  /* Return 1 for success */
            }
            else {
                printf("Incorrect password.\n");
                return 0;
            }
        }
    }

    /* ID was not found in the system */
    printf("ID not found in the system.\n");
    return 0;
}
