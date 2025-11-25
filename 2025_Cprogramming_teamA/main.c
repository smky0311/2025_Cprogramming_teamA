/*
 * 파일명: main.c
 * 작성자: 
 * 설명: 프로그램 진입점 및 메인 메뉴 분기 처리함
 */

#define _CRT_SECURE_NO_WARNINGS // scanf 보안 경고 무시함
#include <stdio.h>
#include "main.h" // 프로젝트 공통 헤더 포함함

 // ---------------------------------------------------------
 // 전역 변수 메모리 할당 영역
 // main.h의 extern 선언에 대한 실체 정의함
 // ---------------------------------------------------------
Book g_books[MAX_BOOKS]; // 도서 데이터 저장할 배열 할당함
int g_book_count = 0;    // 현재 저장된 도서 개수 0으로 초기화함

int main() {
  // 1. 초기화: 프로그램 시작 시 파일에서 기존 데이터 로드함
  loadBooks();

  int menu;

  // 메인 루프 진입함 (사용자가 종료할 때까지 반복함)
  while (1) {
    printf("\n=== 메인 메뉴 (Test Ver) ===\n");
    printf("1. 관리자 모드 (도서 추가/목록)\n");
    printf("2. 저장하고 종료\n");
    printf("선택 >> ");

    scanf("%d", &menu); // 사용자로부터 메뉴 선택 입력받음

    if (menu == 1) {
      manageBooks(); // 관리자 기능 함수 호출함 (book_io.c에 정의됨)
    }
    else if (menu == 2) {
      saveBooks(); // 종료 전 메모리 데이터를 파일에 저장함
      break;       // 반복문 탈출하여 프로그램 종료함
    }
    else {
      printf("다시 입력하세요.\n"); // 예외 입력 처리함
    }
  }

  return 0; // 프로그램 정상 종료 반환함
}