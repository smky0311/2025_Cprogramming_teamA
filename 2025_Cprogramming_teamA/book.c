#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>    // strcspn 사용을 위해 추가
#include "common.h"
#include "book.h"

void loadBooks() {
    FILE* fp = fopen("books.dat", "rb");
    if (fp == NULL) {
        printf("[System] books.dat 파일이 없습니다. 새로 시작합니다.\n");
        g_bookCount = 0;
        return;
    }

    fread(g_books, sizeof(Book), MAX_BOOKS, fp);
    fclose(fp);

    // id[0]이 '\0'이면 빈 칸
    g_bookCount = 0;
    while (g_bookCount < MAX_BOOKS && g_books[g_bookCount].id[0] != '\0')
        g_bookCount++;

    printf("[System] 도서 %d권 로드 완료!\n", g_bookCount);
}

void saveBooks() {
    FILE* fp = fopen("books.dat", "wb");
    if (fp == NULL) {
        printf("[Error] 저장 실패!\n");
        return;
    }
    fwrite(g_books, sizeof(Book), MAX_BOOKS, fp);
    fclose(fp);
    printf("[System] 도서 데이터 저장 완료!\n");
}

void manageBooks() {
    int ch;
    while (1) {
        printf("\n=== 도서 관리 (관리자) ===\n");
        printf("1. 도서 추가\n2. 도서 목록\n0. 돌아가기\n선택: ");
        if (scanf("%d", &ch) != 1) {
            printf("[Error] 입력 오류! 숫자를 입력하세요.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');  // scanf 후 버퍼 비우기

        if (ch == 1) {
            if (g_bookCount >= MAX_BOOKS) {
                printf("더 이상 추가 불가!\n");
                continue;
            }
            Book* b = &g_books[g_bookCount];

            printf("ID: ");
            fgets(b->id, sizeof(b->id), stdin);
            b->id[strcspn(b->id, "\n")] = '\0';

            printf("제목: ");
            fgets(b->title, sizeof(b->title), stdin);
            b->title[strcspn(b->title, "\n")] = '\0';

            printf("저자: ");
            fgets(b->author, sizeof(b->author), stdin);
            b->author[strcspn(b->author, "\n")] = '\0';

            b->available = 1;
            g_bookCount++;
            printf("추가 완료! 현재 %d권\n", g_bookCount);
        }
        else if (ch == 2) {
            printf("\n도서 목록 (%d권)\n", g_bookCount);
            for (int i = 0; i < g_bookCount; i++) {
                printf("%s | %s | %s | %s\n",
                    g_books[i].id,
                    g_books[i].title,
                    g_books[i].author,
                    g_books[i].available ? "Available" : "Checked Out");
            }
        }
        else if (ch == 0) {
            break;
        }
    }
}