<h1>연동 테스트</h1>
<h3>15일 토요일 자정까지 부탁드립니다</h3>
<h5>master branch 말고 test branch를 저희 메인으로 쓸 예정입니다(master는 최종)</h5>
본인 브랜치를 만들어서 그곳에 먼저 push해주시고, test branch로 pull request
주시면 제가 검토후 merge하겠습니다.
<h5>VS쓰시는 분들은 clone repository 하시면 되고 다른거 쓰시는분들은 git을 사용하시던 하면됩니다.</h5>
검색하면 왠만한 정보들 다 나오니까 검색해보시고 
그래도 모르는거 있으시면 카톡 주세요</br>
빨리빨리해서 기말고사 전에 저희 끝마치는거로 합시다.

</br></br></br>
<h1>2025 C프응용 팀A</h1>
<h2>도서관 도서관리 프로그램</h2>
TO-DO LIST</br>
<h3>1주 차 목표: 4명이 각자 만든 파일과 인증 모듈을 합쳤을 때,</br> '회원가입'과 '로그인'이 파일 저장/불러오기를 통해 완벽하게 동작해야함.</h3><br/><br/>


**Day 1-2:  공통 설계 (전원 참여)**

1. Tech Spec 최종 확정: book.h, user.h의 struct 정의를 모두가 동의후 확정. (이후 수정 금지)

2. main.h (공통 헤더) 생성: 전역 변수(g_books[], g_users[]), 상수, 모든 함수의 프로토타입을 정의.

3. '빈' 함수 스켈레톤 코드 작성:

모든 .c 파일 (main.c, book_io.c, user_io.c, auth.c, admin.c, user.c 등)을 생성.

main.h에 정의된 모든 '빈' 함수(예: void searchBook() {})를 각 .c 파일에 미리 다 채워 넣는다.

이 스켈레톤 코드를 *컴파일해서 오류 없이 실행 파일이 만들어지는지 확인.<br/><br/>


**Day 3-5:  핵심 모듈 4개 동시 개발 (1인 1모듈)**

<h5>[ ] 팀원 1 (Book I/O 담당):</h5>

loadBooks(): books.dat에서 g_books 배열로 데이터 로드.

saveBooks(): g_books 배열을 books.dat에 저장.

manageBooks() (Admin): '도서 추가(Create)'와 '도서 목록(Read)' 기능만 먼저 구현 (테스트 데이터 생성용).

<h5>[ ] 팀원 2 (User I/O 담당):</h5>

loadUsers(): users.dat에서 g_users 배열로 데이터 로드.

saveUsers(): g_users 배열을 users.dat에 저장.

manageUsers() (Admin): '회원 목록(Read)' 기능만 먼저 구현 (테스트 확인용).

<h5>[ ] 팀원 3 (Authentication 담당):</h5>

signUp() (회원가입): g_users 배열 순회하며 ID 중복 검사 (strcmp) 및 신규 사용자 추가.

<h5>[ ] 팀원 4 (Authentication 담당):</h5>

login() (로그인): g_users 배열 순회하며 ID/PW 일치 검사 (strcmp).

main() 함수: 메뉴 흐름 제어 (메인 메뉴, 사용자 메뉴, 관리자 메뉴 간 이동) 담당.<br/><br/>


**Day 6-7:  1차 통합 디버깅 (전원 참여)**

목표: 4명이 만든 코드를 모두 합쳐서 컴파일하고, '회원가입 -> 종료 -> 재실행 -> 로그인' 시나리오가 완벽하게 동작해야 함.

4명의 코드를 모두 합친후. (test에 merge)

통합 테스트 시나리오 수행:

프로그램 실행.

1. (팀원 1) 관리자 모드 -> 도서 3권 추가.

2. (팀원 3) 사용자 모드 -> 회원가입 (A).

3. (팀원 3) 사용자 모드 -> 회원가입 (B).

4. (팀원 2) 관리자 모드 -> 회원 목록 확인 (A, B가 보여야 함).

5. 프로그램 종료 (이때 saveBooks, saveUsers가 호출되어야 함).

6. books.dat, users.dat 파일이 생성되었는지 확인.

7. 프로그램 재실행 (이때 loadBooks, loadUsers가 호출되어야 함).

8. (팀원 4) 사용자 모드 -> A로 로그인 (성공해야 함).

9. (팀원 4) 사용자 모드 -> C로 로그인 (실패해야 함).

위 과정에서 발생하는 모든 버그를 전원이 함께 수정.
