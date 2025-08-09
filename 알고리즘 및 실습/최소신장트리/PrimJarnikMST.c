#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Incidence {
	struct Line* line;
	struct Incidence* next;
} Incidence;
typedef struct Vertex {
	Incidence* incidence;
	int distance;
	int num;
	struct Line* parentLine;
	struct Vertex* next;
} Vertex;
typedef struct Line {
	Vertex* first, * second;
	int weight;
	struct Line* next;
} Line;

// ���� �ϳ��� ���� ��ȯ (���� �����嵵 ������ �̸� ����)
Vertex* getVertex(int num);
// ���� ����Ʈ�� ���� ��, ����������� vertexL�� ��ȯ
Vertex* initVertexList(int n);
// ���� �ϳ��� ���� ��ȯ
Line* getLine(Vertex* vertexL, int firstNum, int secondNum, int weight);
// ���� ����Ʈ�� ����������� lineL�� ��ȯ
Line* initLineList(Vertex* vertexL, int m);
// Incidence �ϳ��� ���� ��ȯ
Incidence* getIncidence(Line* linePtr);
// Ư�� ������ ������ �ִ� ����(������) �� ������ �ڿ� �� ���� �����͸� ������ Incedence �ϳ��� �̾���
void addIncidence(Line* lineL);
// ���� ����Ʈ�� ��ȸ�ϸ� addIncidence()�� ����
void initIncidence(Line* lineL);

// Ư�� ������ ������ ������ �����͸� ��ȯ (��ȣ�� ���� �������� ����)
Vertex* opposite(Vertex* vPtr, Incidence* iPtr);

void buildQ(Vertex* Q, Vertex* start, int n);
// ����
void upHeap(Vertex* Q, int i);
// �ٿ���
void downHeap(Vertex* Q, int size, int i);
// MST ������ �߰��Ǵ� ������ MST �ѹ��Ը� ���
void PrimJarnikMST(Vertex* vertexL, int n);

// ��ü �׷����� �޸𸮸� ��������
void freeMemory(Vertex* vertexL, Line* lineL);

int main() {
	// �׷����� ��������Ʈ ����, �켱���� ť�� ������ ����
	Vertex* vertexL;
	Line* lineL;
	int n, m;

	scanf("%d %d", &n, &m);

	vertexL = initVertexList(n);
	lineL = initLineList(vertexL, m);
	initIncidence(lineL);

	PrimJarnikMST(vertexL, n);

	freeMemory(vertexL, lineL);

	return 0;
}

// ���� �ϳ��� ���� ��ȯ (���� �����嵵 ������ �̸� ����)
Vertex* getVertex(int num) {
	Vertex* vPtr = (Vertex*)malloc(sizeof(Vertex));
	Incidence* iPtr = getIncidence(NULL);

	vPtr->incidence = iPtr;
	vPtr->num = num;
	vPtr->next = NULL;

	return vPtr;
}
// ���� ����Ʈ�� ���� ��, ����������� vertexL�� ��ȯ
Vertex* initVertexList(int n) {
	Vertex* vertexL = NULL;
	Vertex* newNode;

	for (int i = n; i >= 1; i--) {
		newNode = getVertex(i);
		newNode->next = vertexL;
		vertexL = newNode;
	}

	return vertexL;
}
// ���� �ϳ��� ���� ��ȯ
Line* getLine(Vertex* vertexL, int firstNum, int secondNum, int weight) {
	Line* lPtr = (Line*)malloc(sizeof(Line));
	Vertex* ptr = vertexL;
	int cnt = 0;

	while (ptr != NULL && cnt < 2) {
		if (ptr->num == firstNum && ptr->num == secondNum) {
			lPtr->first = ptr;
			lPtr->second = ptr;
			cnt = 2;
		}
		else if (ptr->num == firstNum) {
			lPtr->first = ptr;
			cnt++;
		}
		else if (ptr->num == secondNum) {
			lPtr->second = ptr;
			cnt++;
		}
		ptr = ptr->next;
	}
	lPtr->weight = weight;
	lPtr->next = NULL;

	return lPtr;
}
// ���� ����Ʈ�� ����������� lineL�� ��ȯ
Line* initLineList(Vertex* vertexL, int m) {
	Line* lineL = NULL;
	Line* newNode;
	int firstNum, secondNum, weight;

	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &firstNum, &secondNum, &weight);

		newNode = getLine(vertexL, firstNum, secondNum, weight);
		newNode->next = lineL;
		lineL = newNode;
	}

	return lineL;
}
// Incidence �ϳ��� ���� ��ȯ
Incidence* getIncidence(Line* linePtr) {
	Incidence* ptr = (Incidence*)malloc(sizeof(Incidence));

	ptr->line = linePtr;
	ptr->next = NULL;

	return ptr;
}
// Ư�� ������ ������ �ִ� ����(������) �� ������ �ڿ� �� ���� �����͸� ������ Incedence �ϳ��� �̾���
void addIncidence(Line* linePtr) {
	Incidence* ptr;
	Incidence* newNode;

	if (linePtr->first->num == linePtr->second->num) {
		ptr = linePtr->first->incidence;
		newNode = getIncidence(linePtr);
		newNode->next = ptr->next;
		ptr->next = newNode;
	}
	else {
		ptr = linePtr->first->incidence;
		newNode = getIncidence(linePtr);
		newNode->next = ptr->next;
		ptr->next = newNode;

		ptr = linePtr->second->incidence;
		newNode = getIncidence(linePtr);
		newNode->next = ptr->next;
		ptr->next = newNode;
	}
}
// ���� ����Ʈ�� ��ȸ�ϸ� addIncidence()�� ����
void initIncidence(Line* lineL) {
	Line* ptr = lineL;

	while (ptr != NULL) {
		addIncidence(ptr);
		ptr = ptr->next;
	}
}

// Ư�� ������ ������ ������ �����͸� ��ȯ (��ȣ�� ���� �������� ����)
Vertex* opposite(Vertex* vPtr, Incidence* iPtr) {
	int vertexNum;
	Line* lPtr;

	vertexNum = vPtr->num;
	lPtr = iPtr->line;

	if (lPtr->first->num == vertexNum)
		return lPtr->second;
	else // lPtr->second->num == vertexNum
		return lPtr->first;
}

// start�� ������ �������� distance�� ��� 10000�̱� ������ �񱳰� �ʿ���� �ٷ� ������
void buildQ(Vertex* Q, Vertex* start, int n) {
	Vertex* ptr = start;

	for (int i = 1; i <= n; i++) {
		Q[i] = *ptr;
		ptr = ptr->next;
	}
}
// ����
void upHeap(Vertex* Q, int i) {
	Vertex tmp;

	if (i == 1)
		return;

	if (Q[i / 2].distance <= Q[i].distance)
		return;

	tmp = Q[i / 2];
	Q[i / 2] = Q[i];
	Q[i] = tmp;

	upHeap(Q, i / 2);
}
// �ٿ���
void downHeap(Vertex* Q, int size, int i) {
	Vertex tmp;
	int left = i * 2, right = (i * 2) + 1;
	int smaller;

	if (left > size)
		return;

	smaller = left;
	if (right <= size && Q[right].distance < Q[smaller].distance)
		smaller = right;
	if (Q[i].distance <= Q[smaller].distance)
		return;
	tmp = Q[i];
	Q[i] = Q[smaller];
	Q[smaller] = tmp;

	downHeap(Q, size, smaller);
}
// MST ������ �߰��Ǵ� ������ MST �ѹ��Ը� ���
void PrimJarnikMST(Vertex* vertexL, int n) {
	Vertex* ptr = vertexL, * start = vertexL;
	Vertex u, tmp;
	Vertex* z;
	Vertex* Q = (Vertex*)malloc(sizeof(Vertex) * (n + 1));
	int size = n, total = 0;

	while (ptr != NULL) {
		ptr->distance = 10000;
		ptr->parentLine = NULL;
		ptr = ptr->next;
	}

	start->distance = 0;
	buildQ(Q, start, n);
	while (size != 0) {
		tmp = Q[1];
		Q[1] = Q[size];
		Q[size] = tmp;
		u = Q[size];
		size--;
		downHeap(Q, size, 1);

		for (Incidence* iPtr = u.incidence->next; iPtr != NULL; iPtr = iPtr->next) {
			z = opposite(&u, iPtr);
			for (int i = 1; i <= size; i++) {
				if (Q[i].num == z->num && iPtr->line->weight < z->distance) {
					z->distance = iPtr->line->weight;
					Q[i].distance = z->distance;
					z->parentLine = iPtr;
					Q[i].parentLine = z->parentLine;
					upHeap(Q, i);
					break;
				}
			}
		}
	}
	for (int i = n; i >= 1; i--)
		printf(" %d", Q[i].num);
	printf("\n");

	for (int i = 1; i <= n; i++)
		total += Q[i].distance;
	printf("%d\n", total);
	free(Q);
}

// ��ü �׷����� �޸𸮸� ��������
void freeMemory(Vertex* vertexL, Line* lineL) {
	Vertex* ptr = vertexL;
	Incidence* tmpI, * ptrI;
	Vertex* tmpV, * ptrV;
	Line* tmpL, * ptrL;

	tmpV = vertexL;
	tmpL = lineL;

	while (ptr != NULL) {
		tmpI = ptr->incidence;

		do {
			ptrI = tmpI->next;
			free(tmpI);
			tmpI = ptrI;
		} while (ptrI != NULL);

		ptr = ptr->next;
	}

	do {
		ptrV = tmpV->next;
		free(tmpV);
		tmpV = ptrV;
	} while (ptrV != NULL);
	do {
		ptrL = tmpL->next;
		free(tmpL);
		tmpL = ptrL;
	} while (ptrL != NULL);
}