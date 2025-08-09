#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct NODE {
	char elem;
	struct NODE* next;
}NODE, *NODE_PTR, **NODE_DPTR;

NODE_PTR getnode(char elem)
{
	NODE_PTR ptr = (NODE_PTR)malloc(sizeof(NODE));

	ptr->elem = elem;
	ptr->next = NULL;

	return ptr;
}

void initial(NODE_DPTR L, char elem1, NODE_DPTR S, char elem2)
{
	*L = getnode(elem1);
	*S = getnode(elem2);
}

NODE_PTR MoveNode(NODE_PTR ptr, int Rank)
{
	for (int i = 0; i < Rank; i++)
		ptr = ptr->next;

	return ptr;
}

void add(NODE_DPTR L, int Rank, char elem, int* size)
{
	NODE_PTR ptr = *L;
	NODE_PTR newnode;

	if (Rank < 0 || Rank > (*size) + 1)
		printf("invalid position\n");
	else if (Rank == 1)
	{
		newnode = getnode(elem);

		newnode->next = *L;
		*L = newnode;

		(*size)++;
	}
	else
	{
		ptr = MoveNode(*L, Rank - 2);

		newnode = getnode(elem);

		newnode->next = ptr->next;
		ptr->next = newnode;

		(*size)++;
	}
}

char ASCII(char num)
{
	return num - 48;
}

void FreeMemory(NODE_PTR L)
{
	NODE_PTR ptr = L, tmp;

	while (ptr != NULL)
	{
		tmp = ptr;

		ptr = ptr->next;

		free(tmp);
	}
}

int main()
{
	NODE_PTR L, S;
	NODE_PTR Ltmp, Stmp;
	int size1 = 1, size2 = 1;
	int before = 1; // S ���Ḯ��Ʈ���� �ϳ��� ���������� �Űܰ� ��, ������ �ִ� elem ���� ����

	initial(&L, 'O', &S, ASCII('1'));

	add(&L, 2, 'R', &size1);
	add(&L, 3, 'A', &size1);
	add(&L, 4, 'N', &size1);
	add(&L, 5, 'G', &size1);
	add(&L, 6, 'E', &size1);

	add(&S, 2, ASCII('4'), &size2);
	add(&S, 3, ASCII('5'), &size2);

	Ltmp = L;
	Stmp = S;

	while (Stmp != NULL)
	{
		Ltmp = MoveNode(Ltmp, Stmp->elem - before); // S ���Ḯ��Ʈ���� ���� ����� elem�� ���� ����� elem�� ���̸�ŭ L ���Ḯ��Ʈ�� ��带 ������

		printf(" %c", Ltmp->elem); // �ű� �� ���� ���

		before = Stmp->elem; // S ���Ḯ��Ʈ���� next�� ���� �� elem ���� before�� ����

		Stmp = Stmp->next; // S ���Ḯ��Ʈ���� ���� ���� �̵�
	}

	printf("\n");

	FreeMemory(L);
	FreeMemory(S);

	return 0;
}