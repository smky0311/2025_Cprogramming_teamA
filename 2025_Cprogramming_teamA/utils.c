#define _CRT_SECURE_NO_WARNINGS  

#include <stdio.h>
#include <string.h>
#include "common.h"
#include "utils.h"

// Book cover display constants
#define COVER_WIDTH 24    // Width of the ASCII book cover
#define MAX_LINE_LEN 20   // Maximum characters per line in cover


 // Reads and discards all characters until newline or EOF.
void clearInputBuffer(void) {
    int c;
    // Read characters until newline or end of file
    while ((c = getchar()) != '\n' && c != EOF);
}


 // Uses fgets for safe input and removes the trailing newline.
 // Handles buffer overflow by clearing remaining input.
 
void readString(char* buffer, int size) {
    if (fgets(buffer, size, stdin) != NULL) {
        // Find and remove newline character
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        } else {
            // Input was longer than buffer, clear remaining
            clearInputBuffer();
        }
    }
}


 // Performs linear search through the global book array.
 
int findBookByID(int bookID) {
    for (int i = 0; i < g_bookCount; i++) {
        if (g_books[i].id == bookID) {
            return i;  // Return index if found
        }
    }
    return -1;  // Not found
}

 // Performs linear search through the global user array.

int findUserByID(int userID) {
    for (int i = 0; i < g_userCount; i++) {
        if (g_users[i].userID == userID) {
            return i;  // Return index if found
        }
    }
    return -1;  // Not found
}


 // Scans all existing books to find the maximum ID,
 // then returns that value plus one.
 
int getNextBookID(void) {
    int maxID = 0;
    for (int i = 0; i < g_bookCount; i++) {
        if (g_books[i].id > maxID) {
            maxID = g_books[i].id;
        }
    }
    return maxID + 1;
}


 // Scans all existing users to find the maximum ID,
 // then returns that value plus one.

int getNextUserID(void) {
    int maxID = 0;
    for (int i = 0; i < g_userCount; i++) {
        if (g_users[i].userID > maxID) {
            maxID = g_users[i].userID;
        }
    }
    return maxID + 1;
}


 // Calculates padding to center the text within the cover width.
 
static void printCenteredLine(const char* text, int width) {
    int textLen = (int)strlen(text);  /* Cast to int to avoid C4267 warning */
    int padding;

    // Truncate if text is too long
    if (textLen > width) {
        textLen = width;
    }

    // Calculate left padding for centering
    padding = (width - textLen) / 2;

    printf("|");

    // Print left padding
    for (int i = 0; i < padding; i++) {
        printf(" ");
    }

    // Print text (truncated if necessary)
    for (int i = 0; i < textLen; i++) {
        printf("%c", text[i]);
    }

    // Print right padding
    for (int i = 0; i < width - padding - textLen; i++) {
        printf(" ");
    }

    printf("|\n");
}

/*
 *
 * Example output:
 *   |----------------------|
 *   |                      |
 *   |    Sunday Morning    |
 *   |      Breakfast       |
 *   |                      |
 *   |______________________|
 *    [ID: 101] Available
 *
 */

void displayBookCover(struct Book* book) {
    char line1[MAX_LINE_LEN + 1] = "";
    char line2[MAX_LINE_LEN + 1] = "";
    int titleLen;
    int innerWidth = COVER_WIDTH - 2;  // Width inside the borders

    if (book == NULL) {
        printf("[Error] Invalid book pointer.\n");
        return;
    }

    titleLen = (int)strlen(book->title);  // Cast to int to avoid C4267 warning

    // Split title into two lines if necessary
    if (titleLen <= MAX_LINE_LEN) {
        // Title fits in one line
        strncpy(line1, book->title, MAX_LINE_LEN);
        line1[MAX_LINE_LEN] = '\0';
    } else {
        // Need to split title into two lines
        // Find a good split point
        int splitPoint = MAX_LINE_LEN;
        for (int i = MAX_LINE_LEN; i > MAX_LINE_LEN / 2; i--) {
            if (book->title[i] == ' ') {
                splitPoint = i;
                break;
            }
        }

        // Copy first part
        strncpy(line1, book->title, splitPoint);
        line1[splitPoint] = '\0';

        // Copy second part
        if (book->title[splitPoint] == ' ') {
            splitPoint++;
        }
        strncpy(line2, book->title + splitPoint, MAX_LINE_LEN);
        line2[MAX_LINE_LEN] = '\0';
    }

    // Print top border
    printf("  |");
    for (int i = 0; i < innerWidth; i++) {
        printf("-");
    }
    printf("|\n");

    // Print empty line
    printf("  ");
    printCenteredLine("", innerWidth);

    // Print title line 1
    printf("  ");
    printCenteredLine(line1, innerWidth);

    // Print title line 2 if exists
    if (strlen(line2) > 0) {
        printf("  ");
        printCenteredLine(line2, innerWidth);
    }

    // Print author
    printf("  ");
    printCenteredLine(book->author, innerWidth);

    // Print empty line
    printf("  ");
    printCenteredLine("", innerWidth);

    // Print bottom border
    printf("  |");
    for (int i = 0; i < innerWidth; i++) {
        printf("_");
    }
    printf("|\n");

    // Print book info below the cover
    printf("   [ID: %d] %s\n", book->id,
           book->status == 0 ? "Available" : "Borrowed");
    printf("   Genre: %s\n", book->genre);
    printf("\n");
}
