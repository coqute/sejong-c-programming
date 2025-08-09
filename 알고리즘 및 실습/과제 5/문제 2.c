#define _CRT_SECURE_NO_WARNINGS

#ifndef min
#define min(a,b)  (((a) < (b)) ? (a) : (b))
#endif

#include <stdio.h>
#include <stdlib.h>

typedef struct Vertex {
	int num;
	int distance;
	struct Vertex* next;
} Vertex;
typedef struct Line {
	Vertex* from, * to;
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

// ������� s���� �ٸ� ��� ���������� �ִܰŸ��� ���� ��ȣ�� ������������ ���
void BellmanFordShortestPaths(Vertex* vertexL, Line* lineL, int s, int n);

// ��ü �׷����� �޸𸮸� ��������
void freeMemory(Vertex* vertexL, Line* lineL);

int main() {
	Vertex* vertexL;
	Line* lineL;
	int n, m, s;

	scanf("%d %d %d", &n, &m, &s);

	vertexL = initVertexList(n);
	lineL = initLineList(vertexL, m);

	BellmanFordShortestPaths(vertexL, lineL, s, n);

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
			lPtr->from = ptr;
			lPtr->to = ptr;
			cnt = 2;
		}
		else if (ptr->num == firstNum) {
			lPtr->from = ptr;
			cnt++;
		}
		else if (ptr->num == secondNum) {
			lPtr->to = ptr;
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

// ������� s���� �ٸ� ��� ���������� �ִܰŸ��� ���� ��ȣ�� ������������ ���
void BellmanFordShortestPaths(Vertex* vertexL, Line* lineL, int s, int n) {
	Vertex* ptrV = vertexL;
	Line* ptrL;
	Vertex* u, * z;

	while (ptrV != NULL) {
		if (ptrV->num == s)
			ptrV->distance = 0;
		else // ptr->num != s
			ptrV->distance = 30000;
		ptrV = ptrV->next;
	}

	for (int i = 1; i <= n - 1; i++) {
		ptrL = lineL;
		while (ptrL != NULL) {
			u = ptrL->from;
			z = ptrL->to;
			if (u->distance != 30000) // ptrL->weight�� ���̳ʽ� ���� ��� ���� �߸��ٲ�� ������
				z->distance = min(z->distance, u->distance + ptrL->weight);
			ptrL = ptrL->next;
		}
	}

	ptrV = vertexL;
	while (ptrV != NULL) {
		if (ptrV->num != s && ptrV->distance != 30000)
			printf("%d %d\n", ptrV->num, ptrV->distance);
		ptrV = ptrV->next;
	}
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