#ifndef BOOK_H
#define BOOK_H


#define MAX_TITLE 100
#define MAX_AUTHOR 50
#define MAX_GENRE 30


typedef struct {
  int id;                  // 도서 고유 ID
  char title[MAX_TITLE];   // 도서 제목
  char author[MAX_AUTHOR]; // 저자
  char genre[MAX_GENRE];   // 장르
  int status;              // 대출 상태 (0: 대출가능, 1: 대출중)
  int borrowedByUserID;    // 대출한 사용자 ID
} Book;

#endif