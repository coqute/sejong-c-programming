#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Vertex {
	int num;
	struct Vertex* next;
} Vertex;
typedef struct Line {
	Vertex* first, * second;
	int weight;
	struct Line* next;
} Line;
typedef struct Node {
	Vertex vertex;
	struct Node* set, * next;
} Node;
typedef struct Record {
	int size;
	Node* head, * tail;
} Record;

// ���� �ϳ��� ���� ��ȯ (���� �����嵵 ������ �̸� ����)
Vertex* getVertex(int num);
// ���� ����Ʈ�� ���� ��, ����������� vertexL�� ��ȯ
Vertex* initVertexList(int n);
// ���� �ϳ��� ���� ��ȯ
Line* getLine(Vertex* vertexL, int firstNum, int secondNum, int weight);
// ���� ����Ʈ�� ����������� lineL�� ��ȯ
Line* initLineList(Vertex* vertexL, int m);

// �и����� ����
void buildSet(Record** D, Vertex* vertexL, int n);
// ���� ������ ū ���հ� ��ħ
void uvUnion(Record* smaller, Record* bigger);
// ������ �޸� ����
void freeSet(Record* D, int n);

// ���� �� ����� ������
void buildQ(Line* Q, Line* start, int m);
// �ٿ���
void downHeap(Line* Q, int size, int i);
// ť���� ��Ʈ�� �ִ� �ּҰ��� �����ؼ� u, v�� ���� ��������
void removeMin(Record* D, Line* Q, int* u, int* v, int n, int* size);

// MST ���� �� ������ ���Ը� ������� ����ϰ� �� ���Ը� ���
void KruskalMST(Vertex* vertexL, Line* lineL, int n, int m);

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

	KruskalMST(vertexL, lineL, n, m);

	freeMemory(vertexL, lineL);

	return 0;
}

// ���� �ϳ��� ���� ��ȯ (���� �����嵵 ������ �̸� ����)
Vertex* getVertex(int num) {
	Vertex* vPtr = (Vertex*)malloc(sizeof(Vertex));

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

// �и����� ����
void buildSet(Record** D, Vertex* vertexL, int n) {
	Record* rPtr = *D;
	Node* nPtr;
	Vertex* vPtr = vertexL;

	for (int i = 0; i < n; i++) {
		(rPtr + i)->size = 1;
		nPtr = (Node*)malloc(sizeof(Node));
		nPtr->vertex = *vPtr;
		nPtr->set = nPtr;
		nPtr->next = NULL;
		(rPtr + i)->head = (rPtr + i)->tail = nPtr;

		vPtr = vPtr->next;
	}
}
// ���� ������ ū ���հ� ��ħ
void uvUnion(Record* smaller, Record* bigger) {
	Node* headS = smaller->head, * tailS = smaller->tail;
	Node* headB = bigger->head, * tailB = bigger->tail;
	Node* ptr = headS;

	while (ptr != NULL) {
		ptr->set = headB;
		ptr = ptr->next;
	}
	tailB->next = headS;
	bigger->tail = tailS;
	bigger->size += smaller->size;
	smaller->head = smaller->tail = NULL;
	smaller->size = 0;
}
// ������ �޸� ����
void freeSet(Record* D, int n) {
	Node* ptr, * tmp;

	for (int i = 0; i < n; i++) {
		if (D[i].size == 0)
			continue;
		
		tmp = D[i].head;
		do {
			ptr = tmp->next;
			free(tmp);
			tmp = ptr;
		} while (ptr != NULL);
	}
}

// ���� �� ����� ������
void buildQ(Line* Q, Line* start, int m) {
	Line* ptr = start;

	for (int i = 1; i <= m; i++) {
		Q[i] = *ptr;
		ptr = ptr->next;
	}

	for (int i = m / 2; i >= 1; i--)
		downHeap(Q, m, i);
}
// �ٿ���
void downHeap(Line* Q, int size, int i) {
	Line tmp;
	int left = i * 2, right = (i * 2) + 1;
	int smaller;

	if (left > size)
		return;

	smaller = left;
	if (right <= size && Q[right].weight < Q[smaller].weight)
		smaller = right;
	if (Q[i].weight <= Q[smaller].weight)
		return;
	tmp = Q[i];
	Q[i] = Q[smaller];
	Q[smaller] = tmp;

	downHeap(Q, size, smaller);
}
// ť���� ��Ʈ�� �ִ� �ּҰ��� �����ؼ� u, v�� ���� ��������
void removeMin(Record* D, Line* Q, int* u, int* v, int n, int* size) {
	Line tmp;
	Node* ptr;
	int cnt = 0;

	tmp = Q[1];
	Q[1] = Q[*size];
	Q[*size] = tmp;

	for (int i = 0; i < n; i++) {
		if (D[i].size == 0)
			continue;
		
		ptr = D[i].head;
		while (ptr != NULL) {
			if (ptr->vertex.num == Q[*size].first->num) {
				*u = i;
				cnt++;
			}
			else if (ptr->vertex.num == Q[*size].second->num) {
				*v = i;
				cnt++;
			}
			if (cnt == 2)
				break;
			ptr = ptr->next;
		}
	}

	(*size)--;
	downHeap(Q, *size, 1);
}

// MST ���� �� ������ ���Ը� ������� ����ϰ� �� ���Ը� ���
void KruskalMST(Vertex* vertexL, Line* lineL, int n, int m) {
	Record* D = (Record*)malloc(sizeof(Record) * n);
	Line* Q = (Line*)malloc(sizeof(Line) * (m + 1));
	
	int u, v;
	int size = m;
	int totalWeight = 0;

	buildSet(&D, vertexL, n);
	buildQ(Q, lineL, m);

	while (size != 0) {
		removeMin(D, Q, &u, &v, n, &size);

		if (D[u].head != D[v].head) {
			if (D[u].size != 0 && D[u].size <= D[v].size) {
				totalWeight += Q[size + 1].weight;
				printf(" %d", Q[size + 1].weight);
				uvUnion(&D[u], &D[v]);
			}
			else if (D[v].size != 0 && D[u].size > D[v].size) {
				totalWeight += Q[size + 1].weight;
				printf(" %d", Q[size + 1].weight);
				uvUnion(&D[v], &D[u]);
			}
		}
	}
	printf("\n%d\n", totalWeight);

	freeSet(D, n);
	free(D);
	free(Q);
}

// ��ü �׷����� �޸𸮸� ��������
void freeMemory(Vertex* vertexL, Line* lineL) {
	Vertex* ptr = vertexL;
	Vertex* tmpV, * ptrV;
	Line* tmpL, * ptrL;

	tmpV = vertexL;
	tmpL = lineL;

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