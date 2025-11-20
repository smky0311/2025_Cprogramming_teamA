#include <stdio.h>
#include "common.h" 
#include "book.h"
#include "user.h"
#include "auth.h"

// main.c는 최소한으로 터치
// 각각 맡은범위 위주로 코드작성하기
// 팀원1 -> user.c (함수3개)
// 팀원2 -> book.c (함수3개)
// 팀원3 -> auth.c (회원가입)
// 팀원4 -> auth.c (로그인)
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

    char choiceStr[10]; // 입력값을 받을 문자열 버퍼 선언
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

        // 1. 입력받기
        if (fgets(choiceStr, sizeof(choiceStr), stdin) == NULL) { // choiceStr값을 받아서 오버플로우돼서 NULL이 반환되면
            printf("입력 오류입니다.\n"); // 입력오류 출력
            continue; // 다음 코드 실행하지않고 초기로 컨티뉴
        }
        // 2. 개행 문자 제거 (엔터키 문자로 받는거 없애기)
        choiceStr[strcspn(choiceStr, "\r\n")] = '\0'; // r n둘중 한값이라도 들어오면 NULL로 변환 

        // 3. 빈 입력 확인 (그냥 엔터만 쳤을 때)
        if (choiceStr[0] == '\0') { // NULL값만 입력되면
            printf("아무것도 입력하지 않았습니다.\n"); // 에러메시지 출력
            continue; // 초기로 컨티뉴
        }

        // 4. 숫자인지 한 글자씩 검사
        int isNumber = 1; // "숫자가 맞다"고 가정하고 시작
        for (int i = 0; choiceStr[i] != '\0'; i++) { // choiceStr 배열 0부터 검사시작
            // isdigit: 문자가 '0'~'9' 사이면 참, 아니면 거짓
            if (!isdigit(choiceStr[i])) { // isdigit의 값이 false이면 !isdigit 즉 true이므로 조건문실행 
                isNumber = 0; // 숫자가 아닌게 발견되면
                break;        // 중단
            }
        }

        // 5. 숫자가 아니라면 에러 출력 후 처음으로
        if (isNumber == 0) { // isNumber 1로 가정하고 시작했는데 4번조건문을 거치며 0값이되면
            printf("숫자만 입력해주세요.\n"); // 에러메시지출력
            continue; // 초기로 컨티뉴
        }
        choice = atoi(choiceStr); // 문자열을 정수로 변환 fgets는 문자열을 받으므로 atoi를 이용해 정수로 변환해준다.

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
            printf("프로그램을 종료합니다.\n"); // 프로그램 종료 출력
            return 0; // 0리턴
        default: // 디폴트값
            printf("잘못된 입력입니다.\n"); // 에러메시지 출력
        }
    }
    return 0; // 0리턴
}

