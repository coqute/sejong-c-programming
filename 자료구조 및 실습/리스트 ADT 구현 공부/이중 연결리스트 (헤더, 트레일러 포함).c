#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct NODE {
	struct NODE* prev, * next;
	char Alpabet;
}NODE, *NODE_PTR, **NODE_DPTR;

NODE_PTR getnode(char Alpabet)
{
	NODE_PTR ptr;
	
	ptr = (NODE_PTR)malloc(sizeof(NODE));

	ptr->prev = NULL;
	ptr->next = NULL;
	ptr->Alpabet = Alpabet;

	return ptr;
}

void initial(NODE_DPTR H, NODE_DPTR T)
{
	*H = getnode('0');
	*T = getnode('0');

	(*H)->next = *T;
	(*T)->prev = *H;

	(*H)->Alpabet = (*H)->Alpabet - 48; // ASCII �ڵ带 ����ؼ� ����� Ʈ���Ϸ��� ��� Alpabet�� ����� ����(����� Ʈ���Ϸ��� ������)�� Ȱ��
	(*T)->Alpabet = (*T)->Alpabet - 48;
}

NODE_PTR MoveNextNode(NODE_PTR H, int Rank) // ������� �����ؼ� next�� ��� �̵��Ͽ� ��带 ��ȯ
{
	NODE_PTR ptr = H;

	for (int i = 0; i < Rank; i++)
		ptr = ptr->next;

	return ptr;
}

NODE_PTR MovePrevNode(NODE_PTR T, int Rank) // Ʈ���Ϸ����� �����ؼ� prev�� ��� �̵��Ͽ� ��带 ��ȯ
{
	NODE_PTR ptr = T;

	for (int i = 0; i < (T->Alpabet + 1) - Rank; i++) // (��ü ��� ���� + 1) - ���ϴ� ��ġ = Ʈ���Ϸ��� ���� �̵� Ƚ��
		ptr = ptr->prev;							  // add : �߰��ϰ� ���� ��ġ ���� ���� �̵�, delete : �����ϰ� ���� ��ġ ���� �̵�

	return ptr;
}

NODE_PTR isHalf(NODE_PTR H, NODE_PTR T, int Rank, int RankRange) // Rank�� ���� �������� �̻����� Ȯ�����ִ� �Լ�
{
	if (Rank <= RankRange / 2)		// ���� ���� ������ �߰��� ��� ��� Ȱ��
		return MoveNextNode(H, Rank);
	else							// ���� �̻� ������ �߰��� ��� Ʈ���Ϸ� Ȱ��
		return MovePrevNode(T, Rank);
}

void Add(NODE_PTR H, NODE_PTR T, int Rank, char Alpabet) // ���صǴ� ���(ptr) ������ ��� ����
{
	NODE_PTR ptr;
	NODE_PTR newnode;

	if (Rank < 1 || Rank > (H->Alpabet) + 1)
		printf("invalid position\n");
	else
	{
		ptr = isHalf(H, T, Rank, (H->Alpabet) + 1);

		newnode = getnode(Alpabet);

		newnode->next = ptr;
		newnode->prev = ptr->prev;
		(ptr->prev)->next = newnode;
		ptr->prev = newnode;

		(H->Alpabet)++;
		(T->Alpabet)++;
	}
}

void Delete(NODE_PTR H, NODE_PTR T, int Rank)
{
	NODE_PTR ptr;

	if (Rank < 1 || Rank > (H->Alpabet))
		printf("invalid position\n");
	else
	{
		ptr = isHalf(H, T, Rank, H->Alpabet);

		(ptr->prev)->next = ptr->next;
		(ptr->next)->prev = ptr->prev;

		free(ptr);

		(H->Alpabet)--;
		(T->Alpabet)--;
	}
}

char Get(NODE_PTR H, NODE_PTR T, int Rank)
{
	NODE_PTR ptr;

	if (Rank < 1 || Rank > (H->Alpabet))
		printf("invalid position\n");
	else
	{
		ptr = isHalf(H, T, Rank, H->Alpabet);

		printf("%c\n", ptr->Alpabet);

		return ptr->Alpabet;
	}
}

void Set(NODE_PTR H, NODE_PTR T, int Rank, char Alpabet)
{
	NODE_PTR ptr;

	if (Rank < 1 || Rank > (H->Alpabet))
		printf("invalid position\n");
	else
	{
		ptr = isHalf(H, T, Rank, H->Alpabet);

		ptr->Alpabet = Alpabet;
	}
}

void Print(NODE_PTR H, NODE_PTR T)
{
	NODE_PTR ptr = H->next;

	while (ptr != T)
	{
		printf("%c", ptr->Alpabet);

		ptr = ptr->next;
	}

	printf("\n");
}

void FreeMemory(NODE_PTR H) //�޸� ���� �Լ� 
{
	NODE_PTR ptr = H, tmp;

	while (ptr != NULL)
	{
		tmp = ptr;

		ptr = ptr->next;

		free(tmp);
	}
}

void TotalFunction()
{
	NODE_PTR H, T;
	int N, Rank;
	char Type, Alpabet;

	initial(&H, &T);

	scanf("%d", &N);

	for (int i = 0; i < N; i++)
	{
		getchar();

		scanf("%c", &Type);

		if (Type == 'A')
		{
			scanf("%d %c", &Rank, &Alpabet);

			Add(H, T, Rank, Alpabet);
		}
		else if (Type == 'D')
		{
			scanf("%d", &Rank);

			Delete(H, T, Rank);
		}
		else if (Type == 'G')
		{
			scanf("%d", &Rank);

			Alpabet = Get(H, T, Rank);
		}
		else if (Type == 'P')
		{
			Print(H, T);
		}
		else
			printf("invalid type\n");
	}

	FreeMemory(H);
}

int main()
{
	TotalFunction();

	return 0;
}