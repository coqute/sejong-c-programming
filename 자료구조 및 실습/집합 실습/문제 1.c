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

void AddLast(NODE** start, NODE** cur, int elem) // �Էµ� ���Ҹ� ���� ���� �����ʿ� �߰����ִ� �Լ� (�Լ� ������ �ּڰ��� �ٲ��ֱ� ���ؼ� ���������� ���)
{
	NODE* newnode = getnode(elem);

	if (*start == NULL) // ������ ������� ��� start�� cur�� �ʱ�ȭ
	{
		*start = *cur = newnode;

		return;
	}
	
	(*cur)->next = newnode; // cur�� Ȱ���Ͽ� ���� �������� ���ο� ��带 ����, ��ũ ���� �� cur�� ���ο� ��� ��ġ�� �ٲ���
	*cur = newnode;
}

NODE* Set() // ���� ũ�� N�� �Է¹ް� N ũ���� ������ ������ִ� �Լ�
{
	NODE* start = NULL, * cur = NULL;

	int N, elem;

	scanf("%d", &N);

	for (int i = 0; i < N; i++)
	{
		scanf("%d", &elem);

		AddLast(&start, &cur, elem);
	}

	return start;
}

int subset(NODE* A, NODE* B) // A�� B�� �κ��������� �Ǵ��ϴ� �Լ�
{
	while (A != NULL && B != NULL) // B�� NULL�̰ų� A�� NULL�� ������ �ݺ�
	{
		if (A->elem == B->elem) // A�� B�� ���Ұ� ���� ��� A, B ��� next�� �̵�
		{
			A = A->next;
			B = B->next;
		}
		else					// �׷��� ���� ��� B�� next�� �̵�
			B = B->next;
	}

	// A�� B�� ��� �񱳵� ���� A�� NULL���� �ƴ��� �Ǵ�

	if (A != NULL) // A�� NULL�� �ƴϸ� �̹� B�� ���ٰ� �Ǹ� ���ҵ��� �����Ʊ� ������ B�� ���Ե��� ���� ���� A�� ��ġ�� �ִ� ���� ���
		return A->elem;
	else		   // NULL�̸� A�� B�� �κ������̴ϱ� 0 ���
		return 0;
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
	NODE* A = NULL, * B = NULL;
	int result;

	A = Set();
	B = Set();

	result = subset(A, B);

	printf("%d\n", result);

	FreeMemory(A);
	FreeMemory(B);

	return 0;
}