#include <stdio.h>
#include "common.h" // 전역변수(g_users) 사용을 위해 필수
#include "user.h"

// 팀원 1이 아래 세 함수 담당
void loadUsers() {
    // TODO: users.dat 파일 읽어서 g_users에 채우기
    printf("[System] 회원 데이터를 로드했습니다.\n");
}

void saveUsers() {
    // TODO: g_users 내용을 users.dat에 저장하기
    printf("[System] 회원 데이터를 저장했습니다.\n");
}

void manageUsers() {
    // TODO: 회원 목록 출력 구현
    printf("[Admin] 회원 관리 메뉴 진입...\n");
}