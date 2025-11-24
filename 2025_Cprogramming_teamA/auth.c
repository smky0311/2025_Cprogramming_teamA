#include <stdio.h>
#include <string.h>
#include "common.h" // ��������(g_users) ����� ���� �ʼ�
#include "auth.h"

//   3 ���
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


// ���� 4(������) ���
int login() {
    char id[20]; // ID���� 20
    char pw[20]; // PW���� 20
    char buf[256]; // ���۱��� 256

    if (g_userCount <= 0) { // ����ī��Ʈ�� 0�̸�
        printf("[Auth] ȸ�������� �����ϴ�. ȸ�������� �̿����ּ���\n"); // �����޽��� ���
        return 0; // 0 ����
    }
    
    
    // TODO: ID/PW �Է¹ް� g_users�� ��
    printf("[Auth] �α��� ��� ����...\n"); // �α��� ��ɽ��� ���

    printf("ID�Է�: "); // ID�Է� ���
    // ���̵��� ���̸� üũ
    if (!fgets(buf, sizeof(buf), stdin)) { // fgets�� buf�� ������ �̻��� �޾Ƽ� NULL���� ���� -> !fgets�̹Ƿ� ���̵ǰ� ���ǹ� ����
        printf("�Է¿���\n"); // �����޽��� ���
        return 0; // 0 ���� 
    }
    // fgets�� ���ͱ��� ���ڿ��� �����Ƿ� ���Ͱ��� ���ֱ� ���� �ڵ� �߰�
    buf[strcspn(buf, "\r\n")] = '\0'; // buf���ڿ� �ȿ��� carriage return�Ǵ� line feed Ž�� �� ���ڸ��� NULL���� \0����. 
    strncpy(id, buf, sizeof(id)); // id�� ũ�⸸ŭ�� ���縦 �õ�. buf�� ������ id�� �ʰ��Ѵٸ� �ڵ�Ż��.
    id[sizeof(id) - 1] = '\0'; // id�� ������ĭ�� ������ NULL���ڿ��� �־��־� ������ ����.

    // PW �Է�
    printf("PW: "); // PW�Է� ���
    if (!fgets(buf, sizeof(buf), stdin)) { // fgets�� buf�� ������ �̻��� �޾Ƽ� NULL���� ���� -> !fgets�̹Ƿ� ���̵ǰ� ���ǹ� ����
        printf("�Է¿���\n");// �����޽��� ���
        return 0; // 0����
    }
    // fgets�� ���ͱ��� ���ڿ��� �����Ƿ� ���Ͱ��� ���ֱ� ���� �ڵ� �߰�
    buf[strcspn(buf, "\r\n")] = '\0'; // buf���ڿ� �ȿ��� carriage return�Ǵ� line feed Ž�� �� ���ڸ��� NULL���� \0����.
    strncpy(pw, buf, sizeof(pw)); // pw�� ũ�⸸ŭ�� ���縦 �õ�. buf�� ������ id�� �ʰ��Ѵٸ� �ڵ�Ż��.
    pw[sizeof(pw) - 1] = '\0'; // pw�� ������ĭ�� ������ NULL���ڿ��� �־��־� ������ ����.

    //strcmp�� �̿��� ����� �迭�� ���� ���� �Է¹��� ���� ������ ���� �α��� �����ϴ� �ڵ�
    for (int i = 0; i < g_userCount; i++) { // g_userCount 0���� �����̹Ƿ� int i = 0 �ʱ�ȭ�� ����
        if (strcmp(g_users[i].id, id) == 0) { // g_users[i].id�� ���� ���� �Է¹��� id�� ���� ������ 0������ ���ǹ�����
            if (strcmp(g_users[i].pw, pw) == 0) { // g_users[i].pw�� ���� ���� �Է¹��� pw�� ���� ������ 0������ ���ǹ�����
                printf("[%s]�α��� ����", id); // ���̵�� �Բ� �α��μ��� ���
                return 1; // 1�� ����(������)
            }
            else {
                printf("��й�ȣ�� �ùٸ��� �ʽ��ϴ�\n"); // id�� �¾����� ��й�ȣ ���ǹ����� false�ϰ�� ��� �����޽��� ���
                return 0; // 0���� 
            }
        }
    }

    printf("��ϵ� ID�� �������� �ʽ��ϴ�\n"); // id ��ü�� �˻����� ������� id �����޽��� ���
    return 0; // 0����
}