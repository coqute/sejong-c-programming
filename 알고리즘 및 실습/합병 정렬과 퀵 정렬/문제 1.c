#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct NODE {
	int num;
	struct NODE* next;
}NODE;

NODE* getNode(int num);
NODE* makeNode(int n);
void mergeSort(NODE** L, int n);
NODE* merge(NODE* L1, NODE* L2);
void partition(NODE* L, int k, NODE** L1, NODE** L2);
void print(NODE* L);
void freeMemory(NODE* L);

int main() {
	NODE* L = NULL;
	int n;

	scanf("%d", &n);
	
	L = makeNode(n);

	mergeSort(&L, n);

	print(L);

	freeMemory(L);

	return 0;
}

NODE* getNode(int num) {
	NODE* new_node = (NODE*)malloc(sizeof(NODE));

	new_node->num = num;
	new_node->next = NULL;

	return new_node;
}

NODE* makeNode(int n) {
	NODE* L = NULL, * new_node;
	int num;

	for (int i = 0; i < n; i++) {
		scanf("%d", &num);

		new_node = getNode(num);
		new_node->next = L;
		L = new_node;
	}

	return L;
}

void mergeSort(NODE** L, int n) {
	NODE* L1, * L2;
	
	if (*L == NULL || (*L)->next == NULL)
		return;

	partition(*L, n / 2, &L1, &L2);
	mergeSort(&L1, n / 2);
	mergeSort(&L2, n - (n / 2));
	*L = merge(L1, L2);
}

NODE* merge(NODE* L1, NODE* L2) {
	NODE* result = NULL;
	NODE* ptr;

	// ���� ����Ʈ�� ���ٸ� �ٸ� �� ����Ʈ�� ��ȯ
	if (L1 == NULL)
		return L2;
	else if (L2 == NULL)
		return L1;

	// ���� ��带 result
	if (L1->num <= L2->num) {
		result = L1;

		L1 = L1->next; // ������ ���� ���� ���� �̵�
	}
	else {
		result = L2;

		L2 = L2->next; // ������ ���� ���� ���� �̵�
	}

	// ������ �ϱ� ���� ������
	ptr = result;

	while (L1 != NULL && L2 != NULL) {

		// ���� ���� ����
		if (L1->num <= L2->num) {
			ptr->next = L1;  // ���� ���� ptr->next
			L1 = L1->next;    // ������ ���� ���� ���� �̵�
			ptr = ptr->next;    // ptr�� ���� ���� �̵�
		}
		else {
			ptr->next = L2;  // ���� ���� ptr->next
			L2 = L2->next;    // ������ ���� ���� ���� �̵�
			ptr = ptr->next;    // ptr�� ���� ���� �̵�
		}
	}

	// ���� L1�� ���� ���ٸ�, ptr->next�� L2�� ����
	// ���� L2�� ���� ���ٸ�, ptr->next�� L1�� ����
	if (L1 == NULL)
		ptr->next = L2;
	else
		ptr->next = L1;

	return result;
}

void partition(NODE* L, int k, NODE** L1, NODE** L2) {
	*L1 = L;
	
	// k��° ������ �̵�
	for (int i = 0; i < k - 1; i++)
		L = L->next;

	*L2 = L->next;
	L->next = NULL;
}

void print(NODE* L) {
	while (L != NULL) {
		printf(" %d", L->num);

		L = L->next;
	}

	printf("\n");
}

void freeMemory(NODE* L) {
	NODE* ptr;
	
	while (L != NULL) {
		ptr = L;
		L = L->next;

		free(ptr);
	}
}