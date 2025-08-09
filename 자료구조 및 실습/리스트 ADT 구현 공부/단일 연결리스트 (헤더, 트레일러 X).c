#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NODE {
	struct NODE* next;
	int Element;
}NODE, *NODE_PTR, **NODE_DPTR;

void InvalidRank()
{
	printf("invalid position\n");	//�Էµ� rank�� ���� ���� ��� ���� �߻�
}

void InvalidType()
{
	printf("invalid type\n"); //�Էµ� type�� �´� �Լ��� �������� ���� ��� ���� �߻�
}

NODE_PTR getnode(int Element)
{
	NODE_PTR ptr = (NODE_PTR)malloc(sizeof(NODE));

	ptr->next = NULL;
	ptr->Element = Element;

	return ptr;
}

NODE_PTR initial(int FirstElement, int* NodeCount) // �ʱ�ȭ �Լ�
{
	NODE_PTR ptr = getnode(FirstElement);

	(*NodeCount)++; // �������� ���������� ����� ������ ��

	return ptr;
}

NODE_PTR MoveNode(NODE_PTR ptr, int Rank) // Rank��ŭ ����� ��ġ�� ���������� �̵�
{
	for (int i = 0; i < Rank; i++)
	{
		ptr = ptr->next;
	}

	return ptr;
}

void add(NODE_PTR L, int Rank, int Element, int* NodeCount) // ��� �߰� �Լ�
{
	NODE_PTR ptr = L;
	NODE_PTR newnode;
	
	if (Rank < 1 || Rank > *NodeCount) // 1 <= Rank <= NodeCount (ó���� ��� �߰��ϴ� addfirst ���� ��, Rank�� 2���� ��ȿ)
		InvalidRank();
	else // ���� add �ȿ� addfirst�� �����ϰ� �ʹٸ� else if�� Ȱ���ؼ� Rank == 1�� ��쿡 addfirst�� �����ϸ� ��
	{
		ptr = MoveNode(ptr, Rank - 2); // �߰��ؾ��� ��� ��ġ �ٷ� �� ��带 �˰� �ͱ� ������ Rank - 2 ��ŭ ������

		newnode = getnode(Element);

		newnode->next = ptr->next;
		ptr->next = newnode;

		(*NodeCount)++;
	}
}

void addfirst(NODE_DPTR L, int Element , int* NodeCount) // ���� ���Ḯ��Ʈ���� ó���� ��带 �߰��ϱ� ���ؼ��� L�� ���� �ٲ��� �ϱ� ������ add�� ����
{
	NODE_PTR newnode = getnode(Element);

	newnode->next = *L;
	*L = newnode;

	(*NodeCount)++;
}

int get(NODE_PTR L, int Rank, int NodeCount) // Rank ��ġ ����� ��Ҹ� ��ȯ�ϴ� �Լ�
{
	NODE_PTR ptr = L;

	if (Rank < 1 || Rank > NodeCount)
		InvalidRank();
	else
	{
		ptr = MoveNode(ptr, Rank - 1);

		printf("%d\n", ptr->Element);

		return ptr->Element;
	}
}

void Remove(NODE_PTR L, int Rank, int* NodeCount) // ��� ���� �Լ�
{
	NODE_PTR ptr, before;

	if (Rank < 0 || Rank > (*NodeCount))
		InvalidRank();
	else
	{
		ptr = MoveNode(L, Rank - 1);

		before = MoveNode(L, Rank - 2);
		
		before->next = ptr->next;

		free(ptr);

		(*NodeCount)--;
	}
}

void removefirst(NODE_DPTR L, int* NodeCount) // ���� ���Ḯ��Ʈ���� ó���� ��带 �����ϱ� ���ؼ��� L�� ���� �ٲ��� �ϱ� ������ remove�� ����
{
	NODE_PTR tmp = *L;
	
	*L = (*L)->next;

	free(tmp);

	(*NodeCount)--;
}

void set(NODE_PTR L, int Rank, int Element) // Rank ��ġ ��忡 Element ���� �����ϴ� �Լ�
{
	NODE_PTR ptr = L;

	ptr = MoveNode(ptr, Rank - 1);

	ptr->Element = Element;
}

void traverse(NODE_PTR L) // ��� ��带 ��ȸ�ϴ� �Լ�
{
	NODE_PTR ptr = L;

	while (ptr != NULL)
	{
		printf(" %d", ptr->Element);

		ptr = ptr->next;
	}

	printf("\n");
}

void putnode(NODE_PTR L)
{
	NODE_PTR ptr = L;
	NODE_PTR tmp;

	while (ptr != NULL)
	{
		tmp = ptr;
		ptr = ptr->next;

		free(tmp);
	}
}

void TotalFunction()
{
	NODE_PTR L;
	int NodeCount = 0; // �ϴ�, ��ü ����� ������ �Լ��� ����
	int N, Rank, Element;
	char Type[3];

	L = initial(1, &NodeCount);

	scanf("%d", &N);

	for (int i = 0; i < N; i++)
	{
		getchar();

		scanf("%s", Type);

		if (strcmp(Type, "A") == 0)
		{
			scanf("%d %d", &Rank, &Element);

			add(L, Rank, Element, &NodeCount);
		}
		else if (strcmp(Type, "AF") == 0)
		{
			scanf("%d", &Element);

			addfirst(&L, Element, &NodeCount);
		}
		else if (strcmp(Type, "G") == 0)
		{
			scanf("%d", &Rank);

			Element = get(L, Rank, NodeCount);
		}
		else if (strcmp(Type, "S") == 0)
		{
			scanf("%d %d", &Rank, &Element);

			set(L, Rank, Element);
		}
		else if (strcmp(Type, "R") == 0)
		{
			scanf("%d", &Rank);

			Remove(L, Rank, &NodeCount);
		}
		else if (strcmp(Type, "RF") == 0)
		{
			removefirst(&L, &NodeCount);
		}
		else if (strcmp(Type, "P") == 0)
		{
			traverse(L);
		}
		else
			InvalidType();
	}

	putnode(L);
}

int main()
{
	TotalFunction();

	return 0;
}