#ifndef USER_H
#define USER_H

#define MAX_USERNAME 50
#define MAX_PASSWORD 50
#define MAX_NAME 30
#define MAX_BORROW 5 // 1인당 최대 대출 권수

struct User {
  int userID;                      // 사용자 고유 ID
  char username[MAX_USERNAME];     // 로그인 ID
  char password[MAX_PASSWORD];     // 로그인 PW
  char name[MAX_NAME];             // 사용자 이름
  int borrowedBookIDs[MAX_BORROW]; // 현재 대출 중인 도서들의 ID 목록
  int borrowedCount;               // 현재 대출한 권수
};
#endif // USER_H