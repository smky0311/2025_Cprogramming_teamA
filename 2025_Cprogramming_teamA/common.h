// common.h
#pragma once  // 헤더 중복 포함 방지

// 1. 상수 정의
#define MAX_BOOKS 100 // 최대 도서 100권
#define MAX_USERS 50 // 최대 유저 50명

// 2. 구조체 정의
typedef struct {
    char title[100]; // 책 제목
    char id[20];
    int available;
    char author[30];
    // ... 
} Book;

typedef struct {
    char id[20]; // 유저 아이디
    char pw[20]; // 유저 비밀번호
    // ... 
} User;

// 3. 전역 변수 "선언" (이곳에서만 extern 사용)
// 주의: 여기서 초기화(= {0})를 하면 안됨.
extern Book g_books[MAX_BOOKS]; // 책 배열선언
extern User g_users[MAX_USERS]; // 유저 배열선언
extern int g_bookCount; // 책 넘버링
extern int g_userCount; // 유저 넘버링