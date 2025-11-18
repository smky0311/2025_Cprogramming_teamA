#include <stdio.h>
#include "common.h" 
#include "book.h"
#include "user.h"
#include "auth.h"

// main.c는 최소한으로 터치
// 각각 맡은범위 위주로 코드작성하기
// 
// [전역 변수 실제 정의]
// 프로그램 전체에서 메모리는 오직 여기서만 할당됨
Book g_books[MAX_BOOKS]; // 책 배열 참조
User g_users[MAX_USERS]; // 유저 배열 참조
int g_bookCount = 0; // 책 카운트 초기화
int g_userCount = 0; // 유저 카운트 초기화

int main() {
    // 1. 데이터 로드
    loadBooks(); // 책 데이터 로드
    loadUsers(); // 유저 데이터 로드

    int choice; // switch문용 변수선언
    int isLoggedIn = 0; // 로그인 상태체크 (0: 로그오프, 1: 로그인)

    // 2. 메인 루프
    while (1) {
        printf("\n=== 도서 관리 프로그램 ===\n");
        printf("1. 회원가입\n");
        printf("2. 로그인\n");
        printf("3. 도서 관리 (Admin)\n");
        printf("4. 회원 관리 (Admin)\n");
        printf("0. 종료\n");
        printf("선택: ");
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            signUp(); // 회원가입 함수호출
            break;
        case 2:
            isLoggedIn = login(); // 로그인 성공여부 반환
            break;
        case 3:
            manageBooks(); // 책관리 함수호출
            break;
        case 4:
            manageUsers(); // 유저관리 함수호출
            break;
        case 0:
            // 종료전 데이터저장
            saveBooks(); // 책 정보저장
            saveUsers(); // 유저 정보저장
            printf("프로그램을 종료합니다.\n");
            return 0;
        default:
            printf("잘못된 입력입니다.\n");
        }
    }
    return 0;
}