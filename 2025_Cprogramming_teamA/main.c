// Main entry point for the Library Management System
// Handles global variables, file I/O, and the main menu loop.

#define _CRT_SECURE_NO_WARNINGS  // Disable MSVC security warnings for fopen, strcpy, etc.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "common.h"
#include "admin.h"
#include "mine.h"

// Global variable definitions (storage for externs in common.h)
struct Book g_books[MAX_BOOKS];   // Global book array storage
struct User g_users[MAX_USERS];   // Global user array storage
int g_bookCount = 0;              // Current number of books
int g_userCount = 0;              // Current number of users

// Loads book data (count + array) from binary file 'books.dat'
void loadBooks(void) {
  FILE* fp;

  // Open file in binary read mode
  fp = fopen(BOOKS_FILE, "rb");

  if (fp == NULL) {
    // File doesn't exist - start fresh
    printf("[System] %s not found. Starting with empty book database.\n",
      BOOKS_FILE);
    g_bookCount = 0;
    return;
  }

  // Read the book count first
  if (fread(&g_bookCount, sizeof(int), 1, fp) != 1) {
    printf("[Warning] Could not read book count. Starting fresh.\n");
    g_bookCount = 0;
    fclose(fp);
    return;
  }

  // Validate count
  if (g_bookCount < 0 || g_bookCount > MAX_BOOKS) {
    printf("[Warning] Invalid book count in file. Starting fresh.\n");
    g_bookCount = 0;
    fclose(fp);
    return;
  }

  // Read the book array using fread
  if (g_bookCount > 0) {
    size_t readCount = fread(g_books, sizeof(struct Book),
      g_bookCount, fp);
    if (readCount != (size_t)g_bookCount) {
      printf("[Warning] Could only read %zu of %d books.\n",
        readCount, g_bookCount);
      g_bookCount = (int)readCount;
    }
  }

  fclose(fp);
  printf("[System] Loaded %d book(s) from %s.\n", g_bookCount, BOOKS_FILE);
}

// Saves book data (count + array) to binary file 'books.dat'
void saveBooks(void) {
  FILE* fp;

  // Open file in binary write mode
  fp = fopen(BOOKS_FILE, "wb");

  if (fp == NULL) {
    printf("[Error] Could not open %s for writing.\n", BOOKS_FILE);
    return;
  }

  // Write the book count first
  fwrite(&g_bookCount, sizeof(int), 1, fp);

  // Write the book array using fwrite
  if (g_bookCount > 0) {
    fwrite(g_books, sizeof(struct Book), g_bookCount, fp);
  }

  fclose(fp);
  printf("[System] Saved %d book(s) to %s.\n", g_bookCount, BOOKS_FILE);
}

// Loads user data (count + array) from binary file 'users.dat'
void loadUsers(void) {
  FILE* fp;

  // Open file in binary read mode
  fp = fopen(USERS_FILE, "rb");

  if (fp == NULL) {
    // File doesn't exist - start fresh
    printf("[System] %s not found. Starting with empty user database.\n",
      USERS_FILE);
    g_userCount = 0;
    return;
  }

  // Read the user count first
  if (fread(&g_userCount, sizeof(int), 1, fp) != 1) {
    printf("[Warning] Could not read user count. Starting fresh.\n");
    g_userCount = 0;
    fclose(fp);
    return;
  }

  // Validate count
  if (g_userCount < 0 || g_userCount > MAX_USERS) {
    printf("[Warning] Invalid user count in file. Starting fresh.\n");
    g_userCount = 0;
    fclose(fp);
    return;
  }

  // Read the user array using fread
  if (g_userCount > 0) {
    size_t readCount = fread(g_users, sizeof(struct User),
      g_userCount, fp);
    if (readCount != (size_t)g_userCount) {
      printf("[Warning] Could only read %zu of %d users.\n",
        readCount, g_userCount);
      g_userCount = (int)readCount;
    }
  }

  fclose(fp);
  printf("[System] Loaded %d user(s) from %s.\n", g_userCount, USERS_FILE);
}

// Saves user data (count + array) to binary file 'users.dat'
void saveUsers(void) {
  FILE* fp;

  // Open file in binary write mode
  fp = fopen(USERS_FILE, "wb");

  if (fp == NULL) {
    printf("[Error] Could not open %s for writing.\n", USERS_FILE);
    return;
  }

  // Write the user count first
  fwrite(&g_userCount, sizeof(int), 1, fp);

  // Write the user array using fwrite
  if (g_userCount > 0) {
    fwrite(g_users, sizeof(struct User), g_userCount, fp);
  }

  fclose(fp);
  printf("[System] Saved %d user(s) to %s.\n", g_userCount, USERS_FILE);
}

// Loads all data (books and users) at program startup
void loadAllData(void) {
  printf("\n[System] Loading data from files...\n");
  loadBooks();
  loadUsers();
  printf("[System] Data loading complete.\n");
}

// Saves all data (books and users) before program termination
void saveAllData(void) {
  printf("\n[System] Saving data to files...\n");
  saveBooks();
  saveUsers();
  printf("[System] Data saving complete.\n");
}

// Displays the main menu options
static void showMainMenu(void) {
  printf("\n");
  printf("============================================\n");
  printf("      LIBRARY MANAGEMENT SYSTEM\n");
  printf("============================================\n");
  printf("1. User Mode\n");
  printf("2. Admin Mode\n");
  printf("3. Minesweeper Game\n");
  printf("0. Exit\n");
  printf("============================================\n");
  printf("Select: ");
}

// Main program entry point
int main(void) {
  int choice;
  char input[10];

  // Display welcome message
  printf("\n");
  printf("************************************************\n");
  printf("* Welcome to Library Management System     *\n");
  printf("* *\n");
  printf("* A C Language Project demonstrating:         *\n");
  printf("* - Structures (struct)                       *\n");
  printf("* - Binary File I/O (fread, fwrite)           *\n");
  printf("* - Pointers and Arrays                       *\n");
  printf("* - String Functions                          *\n");
  printf("************************************************\n");

  // Load existing data from files
  loadAllData();

  // Main program loop
  while (1) {
    showMainMenu();

    readString(input, sizeof(input));

    // Validate numeric input
    if (strlen(input) == 0 || !isdigit(input[0])) {
      printf("[Error] Please enter a valid number.\n");
      continue;
    }

    choice = atoi(input);

    switch (choice) {
    case 1:
      // User Mode: signup, login, borrow, return, search
      userMode();
      break;

    case 2:
      // Admin Mode: book/user management, loan status
      adminMode();
      break;

    case 3:
      // Minesweeper Game: fun bonus feature
      mineFinder();
      break;

    case 0:
      // Exit: Save data and terminate
      printf("\n[System] Preparing to exit...\n");
      saveAllData();
      printf("\n");
      printf("************************************************\n");
      printf("* Thank you for using our Library System!    *\n");
      printf("* See you again soon!              *\n");
      printf("************************************************\n");
      return 0;

    default:
      printf("[Error] Invalid selection. Please try again.\n");
    }
  }

  return 0;
}