#include <stdio.h>
#include <string.h>
#include "common.h" // 전역변수(g_users) 사용을 위해 필수
#include "auth.h"

// 팀원 3 담당
void signUp() {
    char id[20];
    char pw[20];
    char buf[256];

    printf("[Auth] Sign-up started...\n");

    if (g_userCount >= MAX_USERS) {
        printf("User limit reached. Cannot add more users.\n");
        return;
    }

    printf("Enter new ID: ");
    if (!fgets(buf, sizeof(buf), stdin)) {
        printf("Input error.\n");
        return;
    }
    buf[strcspn(buf, "\r\n")] = '\0';
    strncpy(id, buf, sizeof(id));
    id[sizeof(id) - 1] = '\0';

    for (int i = 0; i < g_userCount; i++) {
        if (strcmp(g_users[i].id, id) == 0) {
            printf("ID already exists. Please choose another.\n");
            return;
        }
    }

    printf("Enter password: ");
    if (!fgets(buf, sizeof(buf), stdin)) {
        printf("Input error.\n");
        return;
    }
    buf[strcspn(buf, "\r\n")] = '\0';
    strncpy(pw, buf, sizeof(pw));
    pw[sizeof(pw) - 1] = '\0';

    strncpy(g_users[g_userCount].id, id, sizeof(g_users[g_userCount].id));
    g_users[g_userCount].id[sizeof(g_users[g_userCount].id) - 1] = '\0';

    strncpy(g_users[g_userCount].pw, pw, sizeof(g_users[g_userCount].pw));
    g_users[g_userCount].pw[sizeof(g_users[g_userCount].pw) - 1] = '\0';

    g_userCount++;

    printf("Sign-up complete. User '%s' registered.\n", id);
}


// 팀원 4(김지형) 담당
int login() {
    char id[20]; // ID길이 20
    char pw[20]; // PW길이 20
    char buf[256]; // 버퍼길이 256

    if (g_userCount <= 0) { // 유저카운트가 0이면
        printf("[Auth] 회원정보가 없습니다. 회원가입후 이용해주세요\n"); // 에러메시지 출력
        return 0; // 0 리턴
    }
    
    
    // TODO: ID/PW 입력받고 g_users와 비교
    printf("[Auth] 로그인 기능 실행...\n"); // 로그인 기능실행 출력

    printf("ID입력: "); // ID입력 출력
    // 아이디의 길이를 체크
    if (!fgets(buf, sizeof(buf), stdin)) { // fgets가 buf의 사이즈 이상을 받아서 NULL값을 리턴 -> !fgets이므로 참이되고 조건문 실행
        printf("입력오류\n"); // 에러메시지 출력
        return 0; // 0 리턴 
    }
    // fgets는 엔터까지 문자열로 받으므로 엔터값을 없애기 위한 코드 추가
    buf[strcspn(buf, "\r\n")] = '\0'; // buf문자열 안에서 carriage return또는 line feed 탐색 후 그자리에 NULL값인 \0대입. 
    strncpy(id, buf, sizeof(id)); // id의 크기만큼만 복사를 시도. buf의 내용이 id를 초과한다면 자동탈락.
    id[sizeof(id) - 1] = '\0'; // id의 마지막칸에 강제로 NULL문자열을 넣어주어 오류를 방지.

    // PW 입력
    printf("PW: "); // PW입력 출력
    if (!fgets(buf, sizeof(buf), stdin)) { // fgets가 buf의 사이즈 이상을 받아서 NULL값을 리턴 -> !fgets이므로 참이되고 조건문 실행
        printf("입력오류\n");// 에러메시지 출력
        return 0; // 0리턴
    }
    // fgets는 엔터까지 문자열로 받으므로 엔터값을 없애기 위한 코드 추가
    buf[strcspn(buf, "\r\n")] = '\0'; // buf문자열 안에서 carriage return또는 line feed 탐색 후 그자리에 NULL값인 \0대입.
    strncpy(pw, buf, sizeof(pw)); // pw의 크기만큼만 복사를 시도. buf의 내용이 id를 초과한다면 자동탈락.
    pw[sizeof(pw) - 1] = '\0'; // pw의 마지막칸에 강제로 NULL문자열을 넣어주어 오류를 방지.

    //strcmp를 이용해 저장된 배열의 값과 현재 입력받은 값이 같은지 비교후 로그인 실행하는 코드
    for (int i = 0; i < g_userCount; i++) { // g_userCount 0부터 시작이므로 int i = 0 초기화후 증가
        if (strcmp(g_users[i].id, id) == 0) { // g_users[i].id의 값과 현재 입력받은 id의 값이 같으면 0리턴후 조건문실행
            if (strcmp(g_users[i].pw, pw) == 0) { // g_users[i].pw의 값과 현재 입력받은 pw의 값이 같으면 0리턴후 조건문실행
                printf("[%s]로그인 성공", id); // 아이디와 함께 로그인성공 출력
                return 1; // 1을 리턴(성공용)
            }
            else {
                printf("비밀번호가 올바르지 않습니다\n"); // id는 맞았지만 비밀번호 조건문에서 false일경우 비번 에러메시지 출력
                return 0; // 0리턴 
            }
        }
    }

    printf("등록된 ID가 존재하지 않습니다\n"); // id 자체가 검색되지 않을경우 id 에러메시지 출력
    return 0; // 0리턴
}
