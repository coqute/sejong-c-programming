#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Incidence {
	struct Line* line;
	struct Incidence* next;
} Incidence;
typedef struct Vertex {
	Incidence* incidence;
	int label;
	int num;
	struct Vertex* next;
} Vertex;
typedef struct Line {
	Vertex* first, * second;
	int label;
	struct Line* next;
} Line;

// ���� �ϳ��� ���� ��ȯ (���� �����嵵 ������ �̸� ����)
Vertex* getVertex(int num);
// ���� ����Ʈ�� ���� ��, ����������� vertexL�� ��ȯ
Vertex* initVertexList(int n);
// ���� �ϳ��� ���� ��ȯ
Line* getLine(Vertex* vertexL, int firstNum, int secondNum);
// ���� ����Ʈ�� ����������� lineL�� ��ȯ
Line* initLineList(Vertex* vertexL, int m);
// Incidence �ϳ��� ���� ��ȯ
Incidence* getIncidence(Line* linePtr);
// ���� �������� ���ڸ� ������� ��ȸ�ϸ� ���Ͽ� ������������ Incidence�� �ٿ���
void addToProperPosition(Line* linePtr, int type);
// Ư�� ������ ������ �ִ� ����(������) �� ������ �ڿ� �� ���� �����͸� ������ Incedence �ϳ��� �̾���
void addIncidence(Line* lineL);
// ���� ����Ʈ�� ��ȸ�ϸ� addIncidence()�� ����
void initIncidence(Line* lineL);

// Ư�� ������ ������ ������ �����͸� ��ȯ (��ȣ�� ���� �������� ����)
Vertex* opposite(Vertex* vPtr, Incidence* iPtr);

void DFS(Vertex* vertexL, Line* lineL, int s);
// Ư�� ������ ���ؼ� ����۾� ����
void rDFS(Vertex* vPtr);

// ��ü �׷����� �޸𸮸� ��������
void freeMemory(Vertex* vertexL, Line* lineL);

int main() {
	Vertex* vertexL;
	Line* lineL;
	int n, m, s;

	scanf("%d %d %d", &n, &m, &s);

	vertexL = initVertexList(n);
	lineL = initLineList(vertexL, m);
	initIncidence(lineL);

	DFS(vertexL, lineL, s);

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
Line* getLine(Vertex* vertexL, int firstNum, int secondNum) {
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
	lPtr->next = NULL;

	return lPtr;
}
// ���� ����Ʈ�� ����������� lineL�� ��ȯ
Line* initLineList(Vertex* vertexL, int m) {
	Line* lineL = NULL;
	Line* newNode;
	int firstNum, secondNum;

	for (int i = 0; i < m; i++) {
		scanf("%d %d", &firstNum, &secondNum);

		newNode = getLine(vertexL, firstNum, secondNum);
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
// ���� �������� ���ڸ� ������� ��ȸ�ϸ� ���Ͽ� ������������ Incidence�� �ٿ���
void addToProperPosition(Line* linePtr, int type) {
	Incidence* ptr, * newNode;
	int vertexNum, oppositeNum, firstNum, secondNum;

	if (type == 1) {
		ptr = linePtr->first->incidence;
		vertexNum = linePtr->first->num;
		oppositeNum = linePtr->second->num;
	}
	else { // type == 2
		ptr = linePtr->second->incidence;
		vertexNum = linePtr->second->num;
		oppositeNum = linePtr->first->num;
	}

	newNode = getIncidence(linePtr);

	if (ptr->next == NULL) {
		newNode->next = ptr->next;
		ptr->next = newNode;
	}
	else { // ptr->next != NULL
		while (ptr->next != NULL) {
			firstNum = ptr->next->line->first->num;
			secondNum = ptr->next->line->second->num;

			if (firstNum == vertexNum) {
				if (secondNum > oppositeNum)
					break;
				else // secondNum < oppositeNum
					ptr = ptr->next;
			}
			else { // secondNum == oppositeNum
				if (firstNum > oppositeNum)
					break;
				else // firstNum < oppositeNum
					ptr = ptr->next;
			}
		}
		newNode->next = ptr->next;
		ptr->next = newNode;
	}
}
// Ư�� ������ ������ �ִ� ����(������) �� ������ �ڿ� (������������) �� ���� �����͸� ������ Incedence �ϳ��� �߰���
void addIncidence(Line* linePtr) {
	if (linePtr->first->num == linePtr->second->num)
		addToProperPosition(linePtr, 1);
	else {
		addToProperPosition(linePtr, 1);
		addToProperPosition(linePtr, 2);
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
void DFS(Vertex* vertexL, Line* lineL, int s) {
	Vertex* vPtr = vertexL;
	Line* lPtr = lineL;
	Vertex* w;

	while (vPtr != NULL) {
		vPtr->label = 0; // Fresh
		vPtr = vPtr->next;
	}
	while (lPtr != NULL) {
		lPtr->label = 0; // Fresh
		lPtr = lPtr->next;
	}

	// ��ȣ�� s�� ������ ã��
	vPtr = vertexL;
	while (vPtr != NULL) {
		if (vPtr->num == s)
			break;
		vPtr = vPtr->next;
	}

	if (vPtr->label == 0)
		rDFS(vPtr);
}
// Ư�� ������ ���ؼ� ����۾� ����
void rDFS(Vertex* vPtr) {
	Incidence* iPtr = vPtr->incidence->next;
	Vertex* w;

	vPtr->label = 1; // Visited
	printf("%d\n", vPtr->num);
	while (iPtr != NULL) {
		if (iPtr->line->label == 0) {
			w = opposite(vPtr, iPtr);
			if (w->label == 0) {
				iPtr->line->label = 1; // Tree
				rDFS(w);
			}
			else
				iPtr->line->label = 2; // Back
		}
		iPtr = iPtr->next;
	}
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