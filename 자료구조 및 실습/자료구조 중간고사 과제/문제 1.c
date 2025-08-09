#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct NODE { // ���� ���, ���� ����, ����&���� ��带 ����Ű�� ��ũ�� ������ ��� ����ü ����
	int coef, exp; 
	struct NODE* prev, *next;
} NODE;

void initial(NODE** H, NODE** T) // ����� Ʈ���Ϸ��� ���� �����͸� ���ڷ� �޾� NODE��ŭ �޸𸮸� �Ҵ��ϰ� ������ ��ũ�� �ʱ�ȭ
{
	*H = (NODE*)malloc(sizeof(NODE));
	*T = (NODE*)malloc(sizeof(NODE));

	(*H)->next = *T;
	(*T)->prev = *H;

	(*H)->prev = NULL;
	(*T)->next = NULL;
}

void appendTerm(NODE* T, int coef, int exp) // ����Ʈ�� �� �ڿ� �߰��ϱ� ���ؼ� Ʈ���Ϸ��� Ȱ��
{
	NODE* newnode = (NODE*)malloc(sizeof(NODE)); // newnode�� ��带 �����ϰ� coef�� exp ���� �Է�

	newnode->coef = coef;
	newnode->exp = exp;

	newnode->next = T; // ��ũ���� ������� �̾���
	newnode->prev = T->prev;
	(T->prev)->next = newnode;
	T->prev = newnode;
}

void Print(NODE* H, NODE* T) // ��� next���� ����Ʈ�� ����
{
	NODE* ptr = H->next;

	while (ptr != T) // Ʈ���Ϸ��� �����ϸ� �ݺ��� ����
	{
		printf(" %d %d", ptr->coef, ptr->exp);

		ptr = ptr->next;
	}

	printf("\n");
}

int reversePrint(NODE* H, NODE* T) // Ʈ���Ϸ��� prev���� �����ؼ� coef, exp�� ����� 
{
	if (T->prev == H) // T->prev�� ����� �����ϸ� 0�� �����ϴ� ���̽�
		return 0;
	else
	{
		printf(" %d %d", (T->prev)->coef, (T->prev)->exp); // ���ڷ� �Էµ� T ���� ����� coef, exp�� ���

		return 1 + reversePrint(H, T->prev); // ��� ���Ŀ� ��� ���� 1 + �� ���� ��带 �����ؼ� ����� ������ �����
	}
}

void FreeMemory(NODE* H) // H���� �����ؼ� NULL�� �� ������ next�� �Űܰ��� �޸𸮸� �������ִ� �Լ�
{
	NODE* tmp;

	while (H != NULL)
	{
		tmp = H;

		H = H->next;

		free(tmp);
	}
}

int main()
{
	NODE* H, *T;
	int count, coef, exp;

	initial(&H, &T);

	scanf("%d", &count);

	for (int i = 0; i < count; i++)
	{
		scanf("%d %d", &coef, &exp);

		appendTerm(T, coef, exp);
	}
	
	Print(H, T);

	count = reversePrint(H, T);

	printf("\n%d\n", count);

	FreeMemory(H);

	return 0;
}