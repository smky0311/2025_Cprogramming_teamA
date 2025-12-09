// common.h
#pragma once  // ��� �ߺ� ���� ����

// 1. ��� ����
#define MAX_BOOKS 100 // �ִ� ���� 100��
#define MAX_USERS 50 // �ִ� ���� 50��

// 2. ����ü ����
typedef struct {
    int id;          // å ID
    char title[100]; // å ����
    char author[100]; // å ����
    int available;   // 1 = ���Ⱑ��, 0 = ���
} Book;

typedef struct {
    char id[20]; // ���� ���̵�
    char pw[20]; // ���� ��й�ȣ
} User;

// 3. ���� ���� "����" (�̰������� extern ���)
// ����: ���⼭ �ʱ�ȭ(= {0})�� �ϸ� �ȵ�.
extern Book g_books[MAX_BOOKS]; // å �迭����
extern User g_users[MAX_USERS]; // ���� �迭����
extern int g_bookCount; // å �ѹ���
extern int g_userCount; // ���� �ѹ���