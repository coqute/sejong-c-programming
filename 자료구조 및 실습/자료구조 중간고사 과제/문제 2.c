#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct NODE { // ���� ���, ���� ����, ����&���� ��带 ����Ű�� ��ũ�� ������ ��� ����ü ����
	int coef, exp;
	struct NODE* prev, * next;
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

void arrayAddTerm(NODE* H, NODE* T, int coef, int exp) // �ԷµǴ� ����� exp ���� ���� ��忡 �ִ� exp ���� ���ϸ� next�� ���ư��� ���ϴ� ��ġ�� ��带 �����ϴ� �Լ�
{
	NODE* ptr = H->next; // ������� ���� ���� ������ next���� ���ϱ� ���� ���� ����
	NODE* newnode;

	while (exp <= ptr->exp && ptr != T) // ptr�� ������ �Էµ� ������ ���ؼ� ptr�� �ִ� Ʈ���Ϸ��� ���� �ʴ� ������ �̵���Ŵ
	{
		if (exp == ptr->exp) // ������ ���� ��� ����� ����
		{
			ptr->coef = ptr->coef + coef;

			if (ptr->coef == 0) // ������ �� ����� 0�� �Ǹ� ����� ��ũ�� �����ϰ� �޸� ����
			{
				(ptr->prev)->next = ptr->next;
				(ptr->next)->prev = ptr->prev;

				free(ptr);
			}
			
			return; // ������ ������ �� ������ �ʿ䰡 ���� ������ ����
		}
			
		ptr = ptr->next;
	}

	newnode = (NODE*)malloc(sizeof(NODE)); // ������ ���� ��찡 �ֱ� ������ ���߿� �޸� �Ҵ� �� �� �Է�

	newnode->coef = coef;
	newnode->exp = exp;

	newnode->next = ptr;
	newnode->prev = ptr->prev;
	(ptr->prev)->next = newnode;
	ptr->prev = newnode;
}

void Print(NODE* H, NODE* T) // ��� next���� ����Ʈ�� ����
{
	NODE* ptr = H->next;

	while (ptr != T)
	{
		printf(" %d %d", ptr->coef, ptr->exp);

		ptr = ptr->next;
	}

	printf("\n");
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
	NODE* H, * T;
	int count, coef, exp;

	initial(&H, &T);

	scanf("%d", &count);

	for (int i = 0; i < count; i++)
	{
		scanf("%d %d", &coef, &exp);

		arrayAddTerm(H, T, coef, exp);
	}

	Print(H, T);

	FreeMemory(H);

	return 0;
}