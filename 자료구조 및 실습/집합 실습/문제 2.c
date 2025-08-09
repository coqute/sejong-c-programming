#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct NODE {
	int elem;
	struct NODE* next;
} NODE;

NODE* getnode(int elem)
{
	NODE* ptr = (NODE*)malloc(sizeof(NODE));

	ptr->elem = elem;
	ptr->next = NULL;

	return ptr;
}

void AddLast(NODE** cur, int elem) // �Էµ� ���Ҹ� ���� ���� �����ʿ� �߰����ִ� �Լ� (�Լ� ������ �ּڰ��� �ٲ��ֱ� ���ؼ� ���������� ���)
{
	NODE* newnode = getnode(elem);

	(*cur)->next = newnode; // cur�� Ȱ���Ͽ� ���� �������� ���ο� ��带 ����, ��ũ ���� �� cur�� ���ο� ��� ��ġ�� �ٲ���
	*cur = newnode;
}

NODE* Set() // ���� ũ�� N�� �Է¹ް� N ũ���� ������ ������ִ� �Լ�
{
	NODE* H = getnode(0), * cur = H;

	int N, elem;

	scanf("%d", &N);

	for (int i = 0; i < N; i++)
	{
		scanf("%d", &elem);

		AddLast(&cur, elem);
	}

	return H;
}

NODE* Union(NODE* A_H, NODE* B_H) // �������� ����� ��ȯ�ϴ� �Լ�
{
	NODE* H = getnode(0), * cur = H;

	while (A_H != NULL && B_H != NULL) // �� �� �ϳ��� NULL�� �Ǹ� ����
	{
		if (A_H->elem < B_H->elem) // A�� ������ AddLast�ϰ� A�� next �̵�
		{
			AddLast(&cur, A_H->elem);

			A_H = A_H->next;
		}
		else if (A_H->elem > B_H->elem) // B�� ������ AddLast�ϰ� B�� next �̵�
		{
			AddLast(&cur, B_H->elem);

			B_H = B_H->next;
		}
		else							// ������ AddLast�ϰ� �Ѵ� next �̵�
		{
			AddLast(&cur, A_H->elem);

			A_H = A_H->next;
			B_H = B_H->next;
		}
	}

	// ���� A Ȥ�� B�� ������ AddLast ���ְ� ����

	while (A_H != NULL)
	{
		AddLast(&cur, A_H->elem);

		A_H = A_H->next;
	}

	while (B_H != NULL)
	{
		AddLast(&cur, B_H->elem);

		B_H = B_H->next;
	}

	return H;
}

NODE* Intersect(NODE* A_H, NODE* B_H) // �������� ����� ��ȯ�ϴ� �Լ�
{
	NODE* H = getnode(0), * cur = H;

	while (A_H != NULL && B_H != NULL) // �� �� �ϳ��� NULL�� �Ǹ� ����
	{
		if (A_H->elem < B_H->elem) // A�� ������ A�� next�� �̵�
			A_H = A_H->next;
		else if (A_H->elem > B_H->elem) // B�� ������ B�� next�� �̵�
			B_H = B_H->next;
		else							// ������ AddLast�ϰ� �Ѵ� next�� �̵�
		{
			AddLast(&cur, A_H->elem);

			A_H = A_H->next;
			B_H = B_H->next;
		}
	}

	return H;
}

void Print_Result(NODE* H) // �������̸� 0, �ƴϸ� ���� ��ü�� ����ϴ� �Լ�
{
	if (H->next == NULL)
		printf("0\n");
	else
	{
		while (H->next != NULL)
		{
			H = H->next;

			printf(" %d", H->elem);
		}

		printf("\n");
	}
}

void FreeMemory(NODE* L) // �޸� ���� �Լ�
{
	NODE* ptr = L, * tmp;

	while (ptr != NULL)
	{
		tmp = ptr;

		ptr = ptr->next;

		free(tmp);
	}
}

int main()
{
	NODE* A_H, * B_H;
	NODE* ptr;

	A_H = Set();
	B_H = Set();

	ptr = Union(A_H->next, B_H->next);

	Print_Result(ptr);
	FreeMemory(ptr);

	ptr = Intersect(A_H->next, B_H->next);

	Print_Result(ptr);
	FreeMemory(ptr);

	FreeMemory(A_H);
	FreeMemory(B_H);

	return 0;
}