#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Vertex {
	int num;
} Vertex;
typedef struct Line {
	int first, second;
	int value;
} Line;

int sum(int n);

Vertex* initVertexList(int n);
Line* initLineList(int m);
int** initMatrix(Line* arrL, int n, int m);

void inPlaceSelectionSort(int** arr, int n);
void print(Vertex* arrV, Line* arrL, int** matrix, int n, int m);
void update(Vertex* arrV, Line* arrL, int** matrix, int n, int* m);

void freeMemory(Vertex* arrV, Line* arrL, int** matrix, int n);

int main() {
	Vertex* arrV;
	Line* arrL;
	int** matrix;

	int n, m;
	n = 6; m = 8;
	
	arrV = initVertexList(n);
	arrL = initLineList(sum(n));
	matrix = initMatrix(arrL, n, m);

	char type;

	do {
		scanf("%c", &type);

		switch (type) {
		case 'a':
			print(arrV, arrL, matrix, n, m);
			break;
		case 'm':
			update(arrV, arrL, matrix, n, &m);
			break;
		}
	} while (type != 'q');

	freeMemory(arrV, arrL, matrix, n);

	return 0;
}

int sum(int n) {
	if (n == 1)
		return 1;
	else
		return n + sum(n - 1);
}

Vertex* initVertexList(int n) {
	Vertex* ptr = (Vertex*)malloc(sizeof(Vertex) * n);

	for (int i = 1; i <= n; i++)
		(ptr + i - 1)->num = i;

	return ptr;
}
Line* initLineList(int m) {
	Line* ptr = (Line*)malloc(sizeof(Line) * m);

	int lArray[8][3] = { {0, 1, 1}, {0, 2, 1}, {0, 3, 1}, {0, 5, 2}, {1, 2, 1}, {2, 4, 4}, {4, 5, 3}, {4, 4, 4} };

	for (int i = 0; i < m; i++) {
		(ptr + i)->first = lArray[i][0];
		(ptr + i)->second = lArray[i][1];
		(ptr + i)->value = lArray[i][2];
	}

	return ptr;
}
int** initMatrix(Line* arrL, int n, int m) {
	int indexF, indexS;

	int** matrix = (int**)malloc(sizeof(int*) * n);
	for (int i = 0; i < n; i++)
		matrix[i] = (int*)malloc(sizeof(int) * n);
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			matrix[i][j] = -1;
		}
	}

	for (int i = 0; i < m; i++) {
		indexF = arrL[i].first;
		indexS = arrL[i].second;

		matrix[indexF][indexS] = i;
		matrix[indexS][indexF] = i;
	}

	return matrix;
}

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
void print(Vertex* arrV, Line* arrL, int** matrix, int n, int m) {
	int num;
	int indexV;
	int cnt, index;
	int** VLarray;

	scanf("%d", &num);
	getchar();

	// Ư���� ������ ���� ���
	for (indexV = 0; indexV < n; indexV++) {
		if (arrV[indexV].num == num)
			break;
	}
	if (indexV == n) {
		printf("-1\n");
		return;
	}

	// ������ �͵��� ������ cnt�� ����
	cnt = 0;
	for (int i = 0; i < m; i++) {
		if (arrL[i].first == indexV || arrL[i].second == indexV)
			cnt++;
	}

	// cnt�� Ȱ���ؼ� ���߹迭 ����
	VLarray = (int**)malloc(sizeof(int*) * cnt);
	for (int i = 0; i < cnt; i++)
		VLarray[i] = (int*)malloc(sizeof(int) * 2);
	
	index = 0;
	for (int i = 0; i < m; i++) {
		if (arrL[i].first == indexV || arrL[i].second == indexV) {
			VLarray[index][1] = arrL[i].value;

			// first Ȥ�� second�� indexV�� ���� ��, first�� second�� �ε����� second�� first�� �ε����� ���
			if (arrL[i].first == indexV)
				VLarray[index][0] = arrV[arrL[i].second].num;
			else if (arrL[i].second == indexV)
				VLarray[index][0] = arrV[arrL[i].first].num;

			index++;
		}
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
void update(Vertex* arrV, Line* arrL, int** matrix, int n, int* m) {
	int firstNum, secondNum, w;
	int indexL, j;
	int indexV1, indexV2;
	int cnt;

	scanf("%d %d %d", &firstNum, &secondNum, &w);
	getchar();

	// firstNum Ȥ�� secondNum�� ��ȣ�� ���� ������ ���� ��츦 üũ
	cnt = 0;
	for (int i = 0; i < n; i++) {
		if (arrV[i].num == firstNum && firstNum == secondNum)
			cnt = 2;
		else if (arrV[i].num == firstNum || arrV[i].num == secondNum)
			cnt++;

		if (cnt == 2)
			break;
	}
	if (cnt != 2) {
		printf("-1\n");
		return;
	}

	// ������ �׷����̱� ������ �������� ������ �ٲ� ���� �������� ����� ��) (1, 2) == (2, 1)
	for (indexL = 0; indexL < *m; indexL++) {
		if (arrV[arrL[indexL].first].num == firstNum && arrV[arrL[indexL].second].num == secondNum)
			break;
		if (arrV[arrL[indexL].first].num == secondNum && arrV[arrL[indexL].second].num == firstNum)
			break;
	}
	
	// ã�� ������ ������ �߰�
	cnt = 0;
	if (indexL == *m && w != 0) {
		// ���� ����Ʈ�� �ε��� �� ���� �˾Ƴ��� �ٷ� ���� (cnt Ȱ��)
		for (int i = 0; i < n; i++) {
			if (arrV[i].num == firstNum) {
				indexV1 = i;
				cnt++;
			}
			if (arrV[i].num == secondNum) {
				indexV2 = i;
				cnt++;
			}
			if (cnt == 2)
				break;
		}
		// �� ����
		(arrL + indexL)->first = indexV1;
		(arrL + indexL)->second = indexV2;
		(arrL + indexL)->value = w;

		// ��� ���� ����
		matrix[indexV1][indexV2] = indexL;
		matrix[indexV2][indexV1] = indexL;
		
		*m = *m + 1;
	}
	// ã�� ������ �����ϰ� w�� 0�� �ƴϸ� ����ġ�� w�� �ٲ�
	else if (indexL != *m && w != 0)
		(arrL + indexL)->value = w;
	// ã�� ������ �����ϰ� w�� 0�̸� ������ ����
	else if (indexL != *m && w == 0) {
		*m = *m - 1;
		
		// ���� ����Ʈ �� ������ �ε����� ��� ������ -1�� �ʱ�ȭ
		matrix[arrL[*m].first][arrL[*m].second] = -1;
		matrix[arrL[*m].second][arrL[*m].first] = -1;

		// ���� ����Ʈ �� indexL �ε����� ������ ����
		// ���� indexL���� *m - 1������ ������ ���� ��� ������ ����
		for (int i = indexL; i < *m; i++) {
			j = i + 1;

			// ���� ���� (������)
			(arrL + i)->first = (arrL + j)->first;
			(arrL + i)->second = (arrL + j)->second;
			(arrL + i)->value = (arrL + j)->value;

			// ��� ����
			matrix[arrL[i].first][arrL[i].second] = i;
			matrix[arrL[i].second][arrL[i].first] = i;
		}
	}
	// ã�� ������ ���µ� ������ ���ַ��� �ϴ� ���
	else // indexL == m && w == 0
		printf("-1\n");
}

void freeMemory(Vertex* arrV, Line* arrL, int** matrix, int n) {
	free(arrV);
	free(arrL);

	for (int i = 0; i < n; i++)
		free(matrix[i]);
	free(matrix);
}