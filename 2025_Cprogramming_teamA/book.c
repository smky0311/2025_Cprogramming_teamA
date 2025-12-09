#define _CRT_SECURE_NO_WARNINGS
// book.c
#include <stdio.h>      // printf, scanf, FILE, fopen, fclose 등 사용
#include "common.h"      // 전역 변수 g_books[], g_bookCount, MAX_BOOKS, Book 구조체 정의
#include "book.h"        // 함수 선언부 (loadBooks, saveBooks, manageBooks)

// 프로그램 시작 시 자동으로 호출 → 이전에 저장된 도서 데이터를 파일에서 읽어옴
void loadBooks() {
    FILE *fp = fopen("books.dat", "rb");        // books.dat 파일을 바이너리 읽기 모드로 열기
    if (fp == NULL) {                           // 파일이 없으면(처음 실행하거나 삭제된 경우)
        printf("[System] books.dat 파일이 없습니다. 새로 시작합니다.\n");
        g_bookCount = 0;                        // 도서 개수를 0으로 초기화
        return;                                 // 함수 종료
    }

    fread(g_books, sizeof(Book), MAX_BOOKS, fp);
    fclose(fp);

    // 실제로 몇 권이 저장돼 있는지 계산 (id가 0이면 빈 칸이라고 가정)
    g_bookCount = 0;
    while (g_bookCount < MAX_BOOKS && g_books[g_bookCount].id != 0)
        g_bookCount++;                            // id가 0이 나올 때까지 카운트 증가

    printf("[System] 도서 %d권 로드 완료!\n", g_bookCount);  // 로드 완료 메시지
}

// 프로그램 종료 직전에 자동으로 호출 → 현재 메모리의 도서 데이터를 파일에 저장
void saveBooks() {
    FILE *fp = fopen("books.dat", "wb");        // 바이너리 쓰기 모드로 파일 열기(없으면 생성)
    if (fp == NULL) {                           // 파일 열기 실패 시
        printf("[Error] 저장 실패!\n");
        return;
    }
    
    // 현재 g_books 배열 전체를 통째로 파일에 저장
    fwrite(g_books, sizeof(Book), MAX_BOOKS, fp);
    fclose(fp);                                 // 파일 닫기
    printf("[System] 도서 데이터 저장 완료!\n");
}

// 관리자 메뉴에서 3번 선택 시 호출되는 도서 관리 메뉴
void manageBooks() {
    char buf[256];
    int ch;                                     // 사용자 입력 저장할 변수
    while (1) {                                 // 0 입력할 때까지 무한 반복
        printf("\n=== 도서 관리 (관리자) ===\n");
        printf("1. 도서 추가\n2. 도서 목록\n0. 돌아가기\n선택: ");
        if (scanf("%d", &ch) != 1) {            // C6031: check scanf return value
            printf("[Error] 입력 오류! 숫자를 입력하세요.\n");
            // 입력 버퍼 비우기
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }

        // 1. 도서 추가
        if (ch == 1) {
            if (g_bookCount >= MAX_BOOKS) {     // 배열이 꽉 찼으면 더 이상 추가 불가
                printf("더 이상 추가 불가!\n");
                continue;
            }
            // 현재 비어 있는 다음 위치에 새 도서 정보 입력
            Book *b = &g_books[g_bookCount];    // 새 도서를 넣을 위치 포인터
            printf("ID: ");    fgets(b->id, sizeof(buf), stdin);       // 도서 ID 입력
            printf("제목: ");   fgets(b->title, sizeof(buf), stdin) ;     // 제목 입력
            printf("저자: ");   fgets(b->author, sizeof(buf), stdin);   // 저자 입력
            b->available = 1;                           // 대출 가능 상태로 초기화
            g_bookCount++;                              // 총 도서 수 1 증가
            printf("추가 완료! 현재 %d권\n", g_bookCount);
        }
        
        // 2. 도서 목록 출력
        else if (ch == 2) {
            printf("\n도서 목록 (%d권)\n", g_bookCount);
            for (int i = 0; i < g_bookCount; i++) {
                printf("%d | %s | %s | %s\n",
                       g_books[i].id,
                       g_books[i].title,
                       g_books[i].author,
                       g_books[i].available ? "대출가능" : "대출중");
            }
        }
        
        // 0. 돌아가기
        else if (ch == 0) {
            break;                              // while 루프 탈출 → 메인 메뉴로 복귀
        }
    }
}