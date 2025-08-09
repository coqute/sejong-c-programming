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

NODE* getnode(int coef, int exp) // ��� ����
{
	NODE* ptr = (NODE*)malloc(sizeof(NODE));

	ptr->prev = NULL;
	ptr->next = NULL;
	ptr->coef = coef;
	ptr->exp = exp;

	return ptr;
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

	newnode = getnode(coef, exp); // ������ ���� ��찡 �ֱ� ������ ���߿� �޸� �Ҵ� �� �� �Է�

	newnode->next = ptr;
	newnode->prev = ptr->prev;
	(ptr->prev)->next = newnode;
	ptr->prev = newnode;
}

void Print(NODE* L) // L���� ����Ʈ�� ����
{
	while (L != NULL)
	{
		printf(" %d %d", L->coef, L->exp);

		L = L->next;
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

void compareAddTerm(NODE** start, NODE** cur, int coef, int exp) // ���� ���� �Էµ� ����� ���ؼ� (����� ���ٸ� ������ ���ؼ�) ���ϴ� ��ġ�� ���ο� ��� �����ϴ� �Լ�
{
	NODE* newnode = getnode(coef, exp);

	if (*start == NULL) // �ƹ� ��嵵 ���� ���
	{
		*start = newnode;
		*cur = *start;

		return;
	}

	if ((*cur)->coef < newnode->coef) // �Էµ� ����� ���� ������� ū ���
	{
		newnode->next = *cur; // ���� ����� ���� ��尡 ������ NULL�� �� (���� ��带 ���ο� ���� ����)
		(*cur)->prev = newnode;
		*start = newnode;
	}
	else if ((*cur)->coef > newnode->coef) // �Էµ� ����� ���� ������� ���� ���
	{
		while ((*cur)->next != NULL) // ���� ����� ���� ��尡 NULL�� �ƴ� ��� �ݺ�
		{
			if ((*cur)->next->coef < newnode->coef) // ���� ����� ���� ����� ����� �Էµ� ������� ���� ���, ���ο� ��带 ���� ��� ������ ����
			{										
				newnode->next = (*cur)->next;
				newnode->prev = *cur;
				(*cur)->next->prev = newnode;
				(*cur)->next = newnode;

				return;
			}

			*cur = (*cur)->next;
		}

		newnode->prev = *cur; // ���� ����� ���� ��尡 NULL�� ��� ��ũ ����
		(*cur)->next = newnode;
	}
	else // �Էµ� ����� ���� ����� ���� ���
	{
		if ((*cur)->exp > newnode->exp) // ���� ����� ������ �Էµ� �������� Ŭ ��
		{
			if ((*cur)->next != NULL) // ���� ����� ���� ��尡 NULL�� �ƴ� ���
			{
				newnode->prev = *cur;
				newnode->next = (*cur)->next;
				(*cur)->next->prev = newnode;
				(*cur)->next = newnode;

				return;
			}
			else // ���� ����� ���� ��尡 NULL�� ���
			{
				newnode->prev = *cur;
				(*cur)->next = newnode;

				return;
			}
		}

		if ((*cur)->exp < newnode->exp) // ���� ����� ������ �Էµ� �������� ���� ��
		{
			newnode->next = *cur; // ���� ����� ���� ���� ������ NULL�� �� (���� ��带 ���ο� ���� ����)
			(*cur)->prev = newnode;
			*start = newnode;
		}
	}
}

NODE* extract(NODE* H, NODE* T) // ����� �������� ������������ ������ �� ���ĵ� ���߿��Ḯ��Ʈ�� ��� ��带 ��ȯ�ϴ� �Լ�
{
	NODE* start = NULL, * cur = NULL; // ���� ���� �������� ��带 ���� ����
	NODE* ptr = H->next; // H->next ���� �����ؼ� ���� �����ִ� ptr����
	
	while (ptr != T)
	{
		compareAddTerm(&start, &cur, ptr->coef, ptr->exp);

		cur = start; // ���ϱ� ���� �������� ��� cur ���� �׻� ù ���� �����Ǳ� ������
					 // ���� �� cur ���� ����� ũ�ų�, ����� �����鼭 ������ ū ���� ������ cur ���ʿ� ��ġ�ϰ� ��
		ptr = ptr->next;
	}

	return start;
}

int main()
{
	NODE* H, * T;
	NODE* L; // ��� Ʈ���Ϸ��� ���� ���߿��Ḯ��Ʈ�� ��� ��� L
	int count, coef, exp;

	initial(&H, &T);

	scanf("%d", &count);

	for (int i = 0; i < count; i++)
	{
		scanf("%d %d", &coef, &exp);

		arrayAddTerm(H, T, coef, exp);
	}

	L = extract(H, T);

	Print(L);

	FreeMemory(H);
	FreeMemory(L);

	return 0;
}