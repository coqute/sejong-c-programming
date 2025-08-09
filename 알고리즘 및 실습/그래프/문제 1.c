#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Incidence {
	struct Line* line;
	struct Incidence* next;
} Incidence;
typedef struct Vertex {
	Incidence* incidence;
	int num;
	struct Vertex* next;
} Vertex;
typedef struct Line {
	Vertex* first, * second;
	int value;
	struct Line* next;
} Line;

// ���� �ϳ��� ���� ��ȯ (���� �����嵵 ������ �̸� ����)
Vertex* getVertex(int num);
// ���� ����Ʈ�� ���� ��, ����������� vertexL�� ��ȯ
Vertex* initVertexList();
// ���� �ϳ��� ���� ��ȯ
Line* getLine(Vertex* vertexL, int firstNum, int secondNum, int value);
// ���� ����Ʈ�� ����������� lineL�� ��ȯ
Line* initLineList(Vertex* vertexL);
// Incidence �ϳ��� ���� ��ȯ
Incidence* getIncidence(Line* linePtr);
// Ư�� ������ ������ �ִ� ����(������) �� ������ �ڿ� �� ���� �����͸� ������ Incedence �ϳ��� �̾���
void addIncidence(Line* lineL);
// ���� ����Ʈ�� ��ȸ�ϸ� addIncidence()�� ����
void initIncidence(Line* lineL);
// ���� ����Ʈ �ӿ��� Ư�� ������ ���� (�� ������ ������ ������ ���� ������ ���� ����)
void removeLine(Line** lineL, Line* linePtr);

// ���ڸ� ���� �������� ����
void inPlaceSelectionSort(int** arr, int n);
// ������ ������ ��ȣ�� �����ؼ� ������������, �������� num�� ���������̶� ����� ������ ����ġ�� ��� �μ�
void printIncidence(Vertex* vertexL);
// ���� ���� ����Ʈ���� ���ϴ� ���� �߰� Ȥ��, ���� ���� ������ ���� (ã�� ������ ���� ��� -1 ��� �� ����)
void updateLine(Vertex* vertexL, Line** lineL);

// ��ü �׷����� �޸𸮸� ��������
void freeMemory(Vertex* vertexL, Line* lineL);

int main() {
	Vertex* vertexL;
	Line* lineL;
	char type;

	vertexL = initVertexList();
	lineL = initLineList(vertexL);
	initIncidence(lineL);

	do {
		scanf("%c", &type);
		switch (type) {
		case 'a':
			printIncidence(vertexL);
			break;
		case 'm':
			updateLine(vertexL, &lineL);
			break;
		}
	} while (type != 'q');

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
Vertex* initVertexList() {
	Vertex* vertexL = NULL;
	Vertex* newNode;

	for (int i = 6; i >= 1; i--) {
		newNode = getVertex(i);
		newNode->next = vertexL;
		vertexL = newNode;
	}

	return vertexL;
}
// ���� �ϳ��� ���� ��ȯ
Line* getLine(Vertex* vertexL, int firstNum, int secondNum, int value) {
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
	lPtr->value = value;
	lPtr->next = NULL;

	return lPtr;
}
// ���� ����Ʈ�� ����������� lineL�� ��ȯ
Line* initLineList(Vertex* vertexL) {
	Line* lineL = NULL;
	Line* newNode;

	int lArray[8][3] = { {1, 2, 1}, {1, 3, 1}, {1, 4, 1}, {1, 6, 2}, {2, 3, 1}, {3, 5, 4}, {5, 6, 3}, {5, 5, 4} };

	for (int i = 0; i < 8; i++) {
			newNode = getLine(vertexL, lArray[i][0], lArray[i][1], lArray[i][2]);
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
// ���� ����Ʈ �ӿ��� Ư�� ������ ���� (�� ������ ������ ������ ���� ������ ���� ����)
void removeLine(Line** lineL, Line* linePtr) {
	Line* ptrL;
	Line* prevLinePtr;
	Incidence* ptrI;
	Incidence* prevRemovePtr;
	int firstNum, secondNum;

	firstNum = linePtr->first->num;
	secondNum = linePtr->second->num;

	// ù��° ������ ���� ��, ���־� �� Incidence�� ������ ���� ����Ʈ�� ������
	ptrI = linePtr->first->incidence;
	// Ư�� Incidence ���� Incidence�� ã��
	while (ptrI->next->line != linePtr)
		ptrI = ptrI->next;
	prevRemovePtr = ptrI;

	// ��ũ ���� �� ����
	ptrI = prevRemovePtr->next;
	prevRemovePtr->next = ptrI->next;
	free(ptrI);
	
	// ������ ���� �ι�° ����
	if (firstNum != secondNum) {
		// �ι�° ������ ���� ��, ���־� �� Incidence�� ������ ���� ����Ʈ�� ������
		ptrI = linePtr->second->incidence;
		// Ư�� Incidence ���� Incidence�� ã��
		while (ptrI->next->line != linePtr)
			ptrI = ptrI->next;
		prevRemovePtr = ptrI;

		// ��ũ ���� �� ����
		ptrI = prevRemovePtr->next;
		prevRemovePtr->next = ptrI->next;
		free(ptrI);
	}

	// �����Ϸ��� ������ �� ó�� ������ ���
	if (*lineL == linePtr) {
		*lineL = (*lineL)->next;
		free(linePtr);
		return;
	}

	ptrL = *lineL;
	// Ư�� ���� ���� ������ ã�� (���� ������ ��ũ ������ ����)
	while (ptrL->next != linePtr)
		ptrL = ptrL->next;
	prevLinePtr = ptrL;

	// ��ũ ���� �� ����
	ptrL = prevLinePtr->next;
	prevLinePtr->next = ptrL->next;
	free(ptrL);
}

// ���ڸ� ���� �������� ����
void inPlaceSelectionSort(int** arr, int n) {
	int index, minLoc;
	int tmp;

	for (index = 0; index < n - 1; index++) {
		minLoc = index;
		for (int j = index + 1; j < n; j++) {
			if (arr[minLoc][0] > arr[j][0])
				minLoc = j;
		}
		for (int k = 0; k < 2; k++) {
			tmp = arr[index][k];
			arr[index][k] = arr[minLoc][k];
			arr[minLoc][k] = tmp;
		}
	}
}
// ������ ������ ��ȣ�� �����ؼ� ������������, �������� num�� ���������̶� ����� ������ ����ġ�� ��� �μ�
void printIncidence(Vertex* vertexL) {
	Vertex* ptr = vertexL;
	Incidence* ptrI, *p;
	int num, cnt = 0;
	int index = 0;
	int** VLarray;

	scanf("%d", &num);
	getchar();

	// num�� ��ȣ�� ���� ������ ã��
	while (ptr != NULL && ptr->num != num)
		ptr = ptr->next;

	// num�� ��ȣ�� ���� ������ ���� ���
	if (ptr == NULL) {
		printf("-1\n");
		return;
	}

	// p�� ptrI�� num�� ��ȣ�� ���� ���� �� ���� ����Ʈ�� ��� ���
	p = ptr->incidence->next;
	ptrI = p;

	// ���� ����Ʈ���� ��� ��带 ������ ������ ������ ������ cnt�� ����
	while (p != NULL) {
		cnt++;
		p = p->next;
	}

	VLarray = (int**)malloc(sizeof(int*) * cnt);
	for (int i = 0; i < cnt; i++)
		VLarray[i] = (int*)malloc(sizeof(int) * 2);

	index = 0;

	// ������ �迭 VLarray�� { ��� ��ȣ, ���� ����ġ }�� ���� ������ ��� ���� (Ƚ���� cnt�� ����)
	while (ptrI != NULL) {
		VLarray[index][1] = ptrI->line->value;

		if (ptrI->line->first == ptr)
			VLarray[index][0] = ptrI->line->second->num;
		else
			VLarray[index][0] = ptrI->line->first->num;

		index++;
		ptrI = ptrI->next;
	}

	// ������ �迭 ���� ��� ��ȣ���� ���ؼ� { ��� ��ȣ, ���� ����ġ }�� �� ���� ���� ��� ���ڸ� ���� �������� ����
	inPlaceSelectionSort(VLarray, cnt);

	// ���ĵ� ������ �迭�� ���
	printf(" ");
	for (int i = 0; i < cnt; i++) {
		for (int j = 0; j < 2; j++) {
			printf("%d", VLarray[i][j]);
		}
	}
	printf("\n");

	// �����Ҵ��� ������ �迭 �޸� ����
	for (int i = 0; i < cnt; i++)
		free(VLarray[i]);
	free(VLarray);
}
// ���� ����Ʈ�� ��ȸ�ؼ� ���ϴ� ���� �߰� Ȥ��, ���� ���� ������ ���� (ã�� ������ ���� ��� -1 ��� �� ����)
void updateLine(Vertex* vertexL, Line** lineL) {
	Vertex* vPtr = vertexL;
	Line* ptr = *lineL;
	Line* newNode;
	int firstNum, secondNum, w;
	int cnt = 0;

	scanf("%d %d %d", &firstNum, &secondNum, &w);
	getchar();

	// firstNum Ȥ�� secondNum�� ��ȣ�� ���� ������ ���� ��츦 üũ
	while (vPtr != NULL) {
		if (vPtr->num == firstNum && firstNum == secondNum)
			cnt = 2;
		else if (vPtr->num == firstNum || vPtr->num == secondNum)
			cnt++;

		if (cnt == 2)
			break;
		vPtr = vPtr->next;
	}
	if (vPtr == NULL) {
		printf("-1\n");
		return;
	}

	// ������ �׷����̱� ������ �������� ������ �ٲ� ���� �������� ����� ��) (1, 2) == (2, 1)
	while (ptr != NULL) {
		if ((ptr->first->num == firstNum && ptr->second->num == secondNum) || (ptr->first->num == secondNum && ptr->second->num == firstNum))
			break;
		ptr = ptr->next;
	}

	// ã�� ������ ������ �߰�
	if (ptr == NULL && w != 0) {
		newNode = getLine(vertexL, firstNum, secondNum, w);
		newNode->next = *lineL;
		*lineL = newNode;

		addIncidence(newNode);
	}
	// ã�� ������ �����ϰ� w�� 0�� �ƴϸ� ����ġ�� w�� �ٲ�
	else if (ptr != NULL && w != 0)
		ptr->value = w;
	// ã�� ������ �����ϰ� w�� 0�̸� ������ ����
	else if (ptr != NULL && w == 0)
		removeLine(lineL, ptr);
	// ã�� ������ ���µ� ������ ���ַ��� �ϴ� ���
	else // ptr == NULL && w == 0
		printf("-1\n");
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