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
    // TODO: ID/PW 입력받고 g_users와 비교
    printf("[Auth] 로그인 기능 실행...\n");

    // 임시로 항상 로그인 성공(1) 리턴
    return 1;
}