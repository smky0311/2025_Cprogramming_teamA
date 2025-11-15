#include <stdio.h>


void user_jihyung() {
	//printf("...");
}

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_USERS 100
#define MAX_BOOKS 500
#define MAX_STR 100

typedef struct {
    int id;
    char username[MAX_STR];
    char password[MAX_STR];
    int is_admin;
} User;

typedef struct {
    int id;
    char title[MAX_STR];
    char author[MAX_STR];
    int year;
    int owner_id;
} Book;

User users[MAX_USERS];
Book books[MAX_BOOKS];
int user_count = 0;
int book_count = 0;
int current_user_id = -1;

const char* USER_FILE = "users.dat";
const char* BOOK_FILE = "books.dat";

void load_data();
void save_data();
void create_default_admin();
int login();
int register_user();
void add_book();
void view_my_books();
//void view_all_books();
void edit_book();
void delete_book();
void admin_edit_book();
void admin_delete_book();
void admin_view_all_books();
int find_book_by_id(int id, int* index);
int find_user_by_name(const char* name, int* index);

int user_wyn() {
    printf("Wai Yan Naung");
    load_data();
    create_default_admin();

    int choice;
    while (1) {
        if (current_user_id == -1) {
            printf("\n=== BOOK LIBRARY SYSTEM ===\n");
            printf("1. Login\n");
            printf("2. Register\n");
            printf("3. Exit\n");
            printf("Choose: ");
            if (scanf("%d", &choice) != 1) {
                while (getchar() != '\n');
                continue;
            }

            switch (choice) {
            case 1: current_user_id = login(); break;
            case 2: current_user_id = register_user(); break;
            case 3:
                save_data();
                printf("Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice!\n");
            }
        }
        else {
            int is_admin = users[current_user_id].is_admin;
            printf("\n--- Logged in as: %s [%s] ---\n",
                users[current_user_id].username,
                is_admin ? "ADMIN" : "USER");

            if (is_admin) {
                printf("1. Add Book\n");
                printf("2. View All Books\n");
                printf("3. Edit Any Book\n");
                printf("4. Delete Any Book\n");
                printf("5. View My Books\n");
                printf("6. Logout\n");
                printf("Choose: ");
            }
            else {
                printf("1. Add Book\n");
                printf("2. View My Books\n");
                printf("3. Edit My Book\n");
                printf("4. Delete My Book\n");
                printf("5. Logout\n");
                printf("Choose: ");
            }

            if (scanf("%d", &choice) != 1) {
                while (getchar() != '\n');
                continue;
            }

            if (is_admin) {
                switch (choice) {
                case 1: add_book(); break;
                case 2: admin_view_all_books(); break;
                case 3: admin_edit_book(); break;
                case 4: admin_delete_book(); break;
                case 5: view_my_books(); break;
                case 6: current_user_id = -1; break;
                default: printf("Invalid choice!\n");
                }
            }
            else {
                switch (choice) {
                case 1: add_book(); break;
                case 2: view_my_books(); break;
                case 3: edit_book(); break;
                case 4: delete_book(); break;
                case 5: current_user_id = -1; break;
                default: printf("Invalid choice!\n");
                }
            }
        }
    }
}

void load_data() {
    FILE* uf = fopen(USER_FILE, "rb");
    if (uf) {
        fread(&user_count, sizeof(int), 1, uf);
        fread(users, sizeof(User), user_count, uf);
        fclose(uf);
    }

    FILE* bf = fopen(BOOK_FILE, "rb");
    if (bf) {
        fread(&book_count, sizeof(int), 1, bf);
        fread(books, sizeof(Book), book_count, bf);
        fclose(bf);
    }
}

void save_data() {
    FILE* uf = fopen(USER_FILE, "wb");
    if (uf) {
        fwrite(&user_count, sizeof(int), 1, uf);
        fwrite(users, sizeof(User), user_count, uf);
        fclose(uf);
    }

    FILE* bf = fopen(BOOK_FILE, "wb");
    if (bf) {
        fwrite(&book_count, sizeof(int), 1, bf);
        fwrite(books, sizeof(Book), book_count, bf);
        fclose(bf);
    }
}

void create_default_admin() {
    int i;
    if (find_user_by_name("admin", &i)) return;

    users[0].id = 0;
    strcpy(users[0].username, "admin");
    strcpy(users[0].password, "sku");
    users[0].is_admin = 1;
    user_count = 1;
}

int login() {
    char username[MAX_STR], password[MAX_STR];
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    int index;
    if (find_user_by_name(username, &index)) {
        if (strcmp(users[index].password, password) == 0) {
            printf("Login successful!\n");
            return users[index].id;
        }
    }
    printf("Invalid credentials!\n");
    return -1;
}

int register_user() {
    if (user_count >= MAX_USERS) {
        printf("User limit reached!\n");
        return -1;
    }

    char username[MAX_STR], password[MAX_STR];
    printf("New Username: ");
    scanf("%s", username);

    int i;
    if (find_user_by_name(username, &i)) {
        printf("Username already exists!\n");
        return -1;
    }

    printf("New Password: ");
    scanf("%s", password);

    users[user_count].id = user_count;
    strcpy(users[user_count].username, username);
    strcpy(users[user_count].password, password);
    users[user_count].is_admin = 0;

    printf("Registration successful! You can now login.\n");
    return user_count++;
}

void add_book() {
    if (book_count >= MAX_BOOKS) {
        printf("Book limit reached!\n");
        return;
    }

    Book b;
    b.id = book_count;
    b.owner_id = users[current_user_id].id;

    printf("Enter Book Title: ");
    scanf(" %[^\n]", b.title);
    printf("Enter Author: ");
    scanf(" %[^\n]", b.author);
    printf("Enter Year: ");
    if (scanf("%d", &b.year) != 1) {
        printf("Invalid year!\n");
        while (getchar() != '\n');
        return;
    }

    books[book_count++] = b;
    printf("Book added successfully! ID: %d\n", b.id);
}

void view_my_books() {
    int found = 0;
    printf("\n--- YOUR BOOKS ---\n");
    for (int i = 0; i < book_count; i++) {
        if (books[i].owner_id == users[current_user_id].id) {
            printf("ID: %d | Title: %s | Author: %s | Year: %d\n",
                books[i].id, books[i].title, books[i].author, books[i].year);
            found = 1;
        }
    }
    if (!found) printf("No books found.\n");
}

void admin_view_all_books() {
    printf("\n--- ALL BOOKS IN LIBRARY ---\n");
    if (book_count == 0) {
        printf("No books in library.\n");
        return;
    }
    for (int i = 0; i < book_count; i++) {
        char owner[20] = "Unknown";
        for (int j = 0; j < user_count; j++) {
            if (users[j].id == books[i].owner_id) {
                strcpy(owner, users[j].username);
                break;
            }
        }
        printf("ID: %d | Title: %s | Author: %s | Year: %d | Owner: %s\n",
            books[i].id, books[i].title, books[i].author, books[i].year, owner);
    }
}

void edit_book() {
    int id;
    printf("Enter Book ID to edit: ");
    if (scanf("%d", &id) != 1) {
        while (getchar() != '\n');
        return;
    }

    int index;
    if (!find_book_by_id(id, &index)) {
        printf("Book not found!\n");
        return;
    }
    if (books[index].owner_id != users[current_user_id].id) {
        printf("You can only edit your own books!\n");
        return;
    }

    printf("Current Title: %s → New Title: ", books[index].title);
    scanf(" %[^\n]", books[index].title);
    printf("Current Author: %s → New Author: ", books[index].author);
    scanf(" %[^\n]", books[index].author);
    printf("Current Year: %d → New Year: ", books[index].year);
    scanf("%d", &books[index].year);

    printf("Book updated!\n");
}

void delete_book() {
    int id;
    printf("Enter Book ID to delete: ");
    if (scanf("%d", &id) != 1) {
        while (getchar() != '\n');
        return;
    }

    int index;
    if (!find_book_by_id(id, &index)) {
        printf("Book not found!\n");
        return;
    }

    if (books[index].owner_id != users[current_user_id].id) {
        printf("You can only delete your own books!\n");
        return;
    }

    for (int i = index; i < book_count - 1; i++) {
        books[i] = books[i + 1];
        books[i].id = i;
    }
    book_count--;
    printf("Book deleted!\n");
}

void admin_edit_book() {
    int id;
    printf("Enter Book ID to edit (Admin): ");
    if (scanf("%d", &id) != 1) {
        while (getchar() != '\n');
        return;
    }

    int index;
    if (!find_book_by_id(id, &index)) {
        printf("Book not found!\n");
        return;
    }

    printf("Editing Book ID: %d\n", id);
    printf("New Title: ");
    scanf(" %[^\n]", books[index].title);
    printf("New Author: ");
    scanf(" %[^\n]", books[index].author);
    printf("New Year: ");
    scanf("%d", &books[index].year);

    printf("Book updated by Admin!\n");
}

void admin_delete_book() {
    int id;
    printf("Enter Book ID to delete (Admin): ");
    if (scanf("%d", &id) != 1) {
        while (getchar() != '\n');
        return;
    }

    int index;
    if (!find_book_by_id(id, &index)) {
        printf("Book not found!\n");
        return;
    }

    for (int i = index; i < book_count - 1; i++) {
        books[i] = books[i + 1];
        books[i].id = i;
    }
    book_count--;
    printf("Book deleted by Admin!\n");
}

int find_book_by_id(int id, int* index) {
    for (int i = 0; i < book_count; i++) {
        if (books[i].id == id) {
            *index = i;
            return 1;
        }
    }
    return 0;
}

int find_user_by_name(const char* name, int* index) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, name) == 0) {
            *index = i;
            return 1;
        }
    }
    return 0;
}