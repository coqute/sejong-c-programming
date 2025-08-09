#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct NODE {
	int key;
	struct NODE* lChild, * parent, * rChild;
} NODE;

void findElement(NODE* root, int k);	// Ʈ���� ��ȸ�Ͽ� Ű �� k�� ���� ����(Ű)�� ��� or (���ٸ�) X ���
void insertItem(NODE* root, int k);		// Ű �� k�� ���� ��带 ����
NODE* treeSearch(NODE* node, int k);	// Ű �� k�� ���� ���� ��� ��ȯ or (���ٸ�) �� ��ġ�� �ܺ� ��� ��ȯ
void removeElement(NODE** root, int k);	// Ű �� k�� ���� ��带 ���� �� Ű ��ȯ
void preOrderPrint(NODE* node);			// ��Ʈ���� ������ȸ �μ�

void init(NODE** root);
NODE* getNode(int k);
bool isExternal(NODE* w);
bool isInternal(NODE* w);
NODE* inOrderSucc(NODE* w);
NODE* sibling(NODE* w);
void expandExternal(NODE* z, int key);
void reduceExternal(NODE** root, NODE* z);

void freeMemory(NODE* node); // ������ȸ �޸� ����

int main() {
	NODE* root;
	char type;
	int key;

	init(&root);

	do {
		scanf("%c", &type);

		switch (type) {
		case 'i':
			scanf("%d", &key);
			getchar();
			insertItem(root, key);
			break;
		case 'd':
			scanf("%d", &key);
			getchar();
			removeElement(&root, key);
			break;
		case 's':
			scanf("%d", &key);
			getchar();
			findElement(root, key);
			break;
		case 'p':
			preOrderPrint(root);
			printf("\n");
			break;
		}
	} while (type != 'q');
	
	freeMemory(root);

	return 0;
}

void findElement(NODE* root, int k) {
	NODE* w = treeSearch(root, k);

	if (isInternal(w))
		printf("%d\n", w->key);
	else
		printf("X\n");
}

void insertItem(NODE* root, int k) {
	NODE* w = treeSearch(root, k);

	if (isInternal(w))
		return;
	else
 		expandExternal(w, k);
}

NODE* treeSearch(NODE* node, int k) {
	if (isExternal(node))
		return node;

	if (node->key == k)
		return node;
	else if (node->key > k)
		return treeSearch(node->lChild, k);
	else
		return treeSearch(node->rChild, k);
}

void removeElement(NODE** root, int k) {
	NODE* y, * z;
	int e;
	
	NODE* w = treeSearch(*root, k);

	if (isExternal(w)) {
		printf("X\n");
		return;
	}
	
	e = w->key;
	z = w->lChild;

	if (isInternal(z))
		z = w->rChild;
	
	if (isExternal(z))
		reduceExternal(root, z);
	else {
		y = inOrderSucc(w);
		z = y->lChild;
		
		w->key = y->key;
		reduceExternal(root, z);
	}

	printf("%d\n", e);
}

void preOrderPrint(NODE* node) {
	if (isExternal(node))
		return;

	printf(" %d", node->key);
	preOrderPrint(node->lChild);
	preOrderPrint(node->rChild);
}

void init(NODE** root) {
	NODE* external_node = getNode(0);

	*root = external_node;
}

NODE* getNode(int k) {
	NODE* new_node = (NODE*)malloc(sizeof(NODE));

	new_node->key = k;
	new_node->parent = NULL;
	new_node->lChild = NULL;
	new_node->rChild = NULL;

	return new_node;
}

bool isExternal(NODE* w) {
	if (w->lChild == NULL && w->rChild == NULL)
		return true;
	else
		return false;
}

bool isInternal(NODE* w) {
	if (w->lChild != NULL || w->rChild != NULL)
		return true;
	else
		return false;
}

NODE* sibling(NODE* w) {
	if (w->parent == NULL)
		return NULL;

	if (w->parent->lChild == w)
		return w->parent->rChild;
	else
		return w->parent->lChild;
}

NODE* inOrderSucc(NODE* w) {
	w = w->rChild;

	if (isExternal(w))
		return NULL;
	
	while (isInternal(w->lChild))
		w = w->lChild;
	return w;
}

void expandExternal(NODE* z, int key) {
	NODE* lChild = getNode(0);
	NODE* rChild = getNode(0);

	z->key = key;
	z->lChild = lChild;
	z->rChild = rChild;

	lChild->parent = z;
	rChild->parent = z;
}

void reduceExternal(NODE** root, NODE* z) {
	NODE* w = z->parent, * zs = sibling(z);
	NODE* g;

	if (w->parent == NULL) {
		*root = zs;
		zs->parent = NULL;
	}
	else {
		g = w->parent;
		zs->parent = g;
		if (w == g->lChild)
			g->lChild = zs;
		else
			g->rChild = zs;
	}

	free(z);
	free(w);
}

void freeMemory(NODE* node) {
	if (isExternal(node))
		return;

	freeMemory(node->lChild);
	freeMemory(node->rChild);
	free(node);
}