#include <stdio.h>
#include <string.h>
#include "common.h" // 전역변수(g_users) 사용을 위해 필수
#include "auth.h"

// 팀원 3 담당
void signUp() {
    // TODO: ID 중복체크 및 g_users에 신규 회원 추가
    printf("[Auth] 회원가입 기능 실행...\n");
}

// 팀원 4 담당
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
    if (!fgets(buf, sizeof(buf), stdin)) { // 버퍼 오버플로우를 막기위해 fgets를 사용 입력받은값이 buf의 사이즈인 256이 넘어가면
        printf("입력오류"); // 에러메시지 출력
        return 0; // 0 리턴 
    }


    // 임시로 항상 로그인 성공(1) 리턴
    return 1;
}