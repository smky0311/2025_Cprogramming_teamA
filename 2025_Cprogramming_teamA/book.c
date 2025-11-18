#include <stdio.h>
#include "common.h" // 전역변수(g_books) 사용을 위해 필수
#include "book.h"

void loadBooks() {
    // TODO: books.dat 파일 읽어서 g_books에 채우기
    printf("[System] 도서 데이터를 로드했습니다.\n");
}

void saveBooks() {
    // TODO: g_books 내용을 books.dat에 저장하기
    printf("[System] 도서 데이터를 저장했습니다.\n");
}

void manageBooks() {
    // TODO: 도서 추가, 목록 출력 메뉴 구현
    printf("[Admin] 도서 관리 메뉴 진입...\n");
}