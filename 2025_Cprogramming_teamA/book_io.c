/*
 * 파일명: book_io.c
 * 작성자: 김성진 (Book I/O 담당)
 * 설명: 도서 데이터의 바이너리 파일 입출력 및 관리자용 도서 관리(CRUD) 기능 구현함
 * 비고: Visual Studio 환경의 scanf_s 경고를 방지하기 위해 _CRT_SECURE_NO_WARNINGS 정의함
 */

#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <string.h>  // strcpy 등 문자열 처리를 위해 포함함
#include "main.h"    // 전역 변수(g_books) 및 구조체(Book) 정의 포함함

 // ---------------------------------------------------------
 // 1. 파일 입출력 함수 (Data Persistence)
 // 설명: 프로그램 시작과 종료 시 메모리(RAM)와 파일(HDD/SSD) 간 데이터 동기화함
 // ---------------------------------------------------------

 /*
  * 함수명: loadBooks
  * 기능: 'books.dat' 파일에서 도서 데이터를 읽어와 메모리(g_books 배열)에 적재함
  * 반환값: 없음 (전역 변수 g_book_count가 갱신됨)
  */
void loadBooks() {
  // 파일을 읽기 모드(Binary Read)로 개방함
  // "rb": 텍스트 변환 없이 구조체 데이터를 있는 그대로 읽기 위함임
  FILE* fp = fopen("books.dat", "rb");

  // 파일이 존재하지 않는 경우 (프로그램 최초 실행 시 등) 예외 처리함
  if (fp == NULL) {
    printf("[System] 저장된 도서 파일이 없습니다. 새로 시작합니다.\n");
    return;
  }

  // 파일의 내용을 구조체 배열에 한 번에 읽어옴
  // fread(저장할주소, 사이즈, 개수, 파일포인터)
  // 반환값: 실제로 읽어온 요소의 개수 -> 이를 g_book_count에 저장하여 관리함
  g_book_count = fread(g_books, sizeof(Book), MAX_BOOKS, fp);

  printf("[System] 도서 데이터 로드 완료 (총 %d권)\n", g_book_count);

  // 파일 입출력 작업 후에는 반드시 파일을 닫아 리소스를 해제함
  fclose(fp);
}

/*
 * 함수명: saveBooks
 * 기능: 현재 메모리(g_books 배열)에 있는 데이터를 'books.dat' 파일에 영구 저장함
 * 반환값: 없음
 */
void saveBooks() {
  // 파일을 쓰기 모드(Binary Write)로 개방함
  // "wb": 파일이 있으면 내용을 덮어쓰고, 없으면 새로 생성함
  FILE* fp = fopen("books.dat", "wb");

  // 디스크 공간 부족이나 권한 문제로 파일 생성 실패 시 예외 처리함
  if (fp == NULL) {
    printf("[Error] 파일 저장 실패 (권한 부족 또는 디스크 용량 부족)\n");
    return;
  }

  // 전역 배열의 데이터를 파일에 일괄 저장함
  // MAX_BOOKS(전체 크기)가 아닌 g_book_count(실제 데이터 개수)만큼만 저장하여 용량을 최적화함
  // 구조체 내부의 데이터(ID, 제목, 저자 등)가 바이너리 형태로 그대로 저장됨
  fwrite(g_books, sizeof(Book), g_book_count, fp);

  printf("[System] 도서 데이터 저장 완료 (총 %d권)\n", g_book_count);

  // 리소스 해제함
  fclose(fp);
}

// ---------------------------------------------------------
// 2. 관리자 기능 함수 (Admin Features)
// 설명: 도서 추가, 목록 조회 등 관리자 모드에서 수행하는 기능임
// ---------------------------------------------------------

/*
 * 함수명: addBook
 * 기능: 관리자로부터 도서 정보를 입력받아 배열에 추가함 (Create)
 */
void addBook() {
  // 배열의 최대 용량을 초과하지 않도록 검사함 (Overflow 방지)
  if (g_book_count >= MAX_BOOKS) {
    printf("오류: 도서 저장 공간이 가득 찼습니다. (최대 %d권)\n", MAX_BOOKS);
    return;
  }

  // 데이터가 저장될 배열의 위치를 포인터로 가리킴
  // 매번 g_books[g_book_count]를 쓰는 것보다 가독성이 좋고 효율적임
  Book* pBook = &g_books[g_book_count];

  // 내부 관리용 데이터 자동 설정함
  pBook->id = g_book_count + 1;  // ID는 1부터 순차적으로 증가함 (Auto Increment)
  pBook->status = 0;             // 0: 대출 가능 상태로 초기화함
  pBook->borrowedByUserID = -1;  // 대출자가 없음을 나타내는 값(-1) 설정함

  printf("\n[도서 추가]\n");

  // 사용자 입력 처리함
  // scanf 포맷 " %[^\n]s" 설명:
  // 1. 첫 번째 공백: 입력 버퍼에 남아있는 이전 엔터키(\n)를 제거함
  // 2. [^\n]: 엔터키가 입력되기 전까지의 모든 문자(공백 포함)를 입력받음 -> 띄어쓰기 있는 제목 입력 가능함
  printf("제목: ");
  scanf(" %[^\n]s", pBook->title);

  printf("저자: ");
  scanf(" %[^\n]s", pBook->author);

  printf("장르: ");
  scanf(" %[^\n]s", pBook->genre);

  // 책 등록이 완료되었으므로 전체 카운트를 1 증가시킴
  g_book_count++;
  printf(">> 도서 등록 완료 (ID: %d)\n", pBook->id);
}

/*
 * 함수명: viewAllBooks
 * 기능: 현재 등록된 모든 도서 목록을 테이블 형태로 출력함 (Read)
 */
void viewAllBooks() {
  printf("\n=== 전체 도서 목록 (총 %d권) ===\n", g_book_count);
  printf("ID\t상태\t제목\t\t저자\t\t장르\n");
  printf("----------------------------------------------------------\n");

  // 등록된 책의 개수만큼 반복함
  for (int i = 0; i < g_book_count; i++) {
    char statusStr[20];

    // 상태값(int)을 사용자가 이해하기 쉬운 문자열로 변환함
    if (g_books[i].status == 0) strcpy(statusStr, "대출가능");
    else strcpy(statusStr, "대출중");

    // \t(탭) 문자를 사용하여 열 간격을 맞춤
    printf("%d\t%s\t%s\t\t%s\t\t%s\n",
      g_books[i].id, statusStr, g_books[i].title, g_books[i].author, g_books[i].genre);
  }
  printf("----------------------------------------------------------\n");
}

/*
 * 함수명: manageBooks
 * 기능: 관리자 메뉴의 메인 루프 처리함 (추가/목록/종료 분기)
 */
void manageBooks() {
  int choice;

  // 종료(0)를 선택하기 전까지 무한 반복함
  while (1) {
    printf("\n[관리자] 도서 관리 메뉴\n");
    printf("1. 도서 추가 (Create)\n");
    printf("2. 도서 목록 (Read)\n");
    printf("0. 뒤로 가기\n");
    printf("선택 >> ");

    scanf("%d", &choice);

    if (choice == 0) {
      break; // 반복문 종료 -> 메인 메뉴로 복귀함
    }
    else if (choice == 1) {
      addBook(); // 도서 추가 함수 호출함
    }
    else if (choice == 2) {
      viewAllBooks(); // 도서 목록 조회 함수 호출함
    }
    else {
      printf("잘못된 입력입니다. 다시 선택해 주세요.\n");
    }
  }
}

// ---------------------------------------------------------
// 3. 사용자 기능 함수 (User Features)
// 설명: 일반 사용자가 사용하는 기능 (검색 등)
// ---------------------------------------------------------

/*
 * 함수명: searchBook
 * 기능: 도서 검색 기능 (추후 구현 예정임)
 * 비고: 현재 스켈레톤(Skeleton) 코드로 유지함
 */
void searchBook() {
  printf("[User] 검색 기능은 아직 구현되지 않았습니다.\n");
}