#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Line {
	int fromIndex, toIndex;
} Line;
typedef struct Incidence {
	int lIndex;
	struct Incidence* next;
} Incidence;
typedef struct Vertex {
	char name;
	int inDegree;
	Incidence* outLine, * inLine;
} Vertex;
typedef struct Queue {
	int* vIndexArr;
	int front, rear;
} Queue;
typedef struct Graph {
	Vertex* vertices;
	Line* lines;
} Graph;

// ǥ���Է����κ��� ����׷��� ������ �о� �鿩 �׷��� G�� ����
void buildGraph();
// vName ���� i�� G�� ��������Ʈ�� �����ϰ� i�� ���������� �ʱ�ȭ
void insertVertex(char vName, int i);
// uName ���� u�� ��������, wName ���� w�� �������� �ϴ� ���Ⱓ�� i��, G�� ��������Ʈ, u�� ���Ⱓ������Ʈ, �׸��� w�� ���԰�������Ʈ�� ���� �����ϰ� w�� ���������� ����
void insertDirectedEdge(char uName, char wName, int i);
// vName�� �ش��ϴ� ������ �ε����� ã�� ��ȯ
int index(char vName);
// (��������Ʈ�� ������)H�� ù ��� ��ġ�� ���� i�� ���ҷ� �ϴ� ��带 ����
void addFirst(Incidence* H, int i);
// G�κ��� ��������� ���ϰų� �������Ŭ�� �������� ����
void topologicalSort();

// Q�� ��� ������ True, �ƴϸ� False�� ��ȯ
bool isEmpty();
// v�� Q�� ����
void enqueue(int vIndex);
// Q�κ��� ������ �����Ͽ� ��ȯ
int dequeue();

void freeMemory();

Graph G;
int n, m;
int* in, * topOrder;
Queue Q;

int main() {
	
	buildGraph();

	topologicalSort();

	if (topOrder[0] == 0)
		printf("0");
	else
		for (int i = 1; i <= n; i++) {
			printf("%c", G.vertices[topOrder[i]].name);
			if (i != n)
				printf(" ");
		}
	printf("\n");

	freeMemory();

	return 0;
}

// ǥ���Է����κ��� ����׷��� ������ �о� �鿩 �׷��� G�� ����
void buildGraph() {
	char vName, uName, wName;

	scanf("%d", &n);
	getchar();

	G.vertices = (Vertex*)malloc(sizeof(Vertex) * n);

	for (int i = 0; i < n; i++) {
		scanf(" %c", &vName);
		insertVertex(vName, i);
	}

	scanf("%d", &m);
	getchar();

	G.lines = (Line*)malloc(sizeof(Line) * m);

	for (int i = 0; i < m; i++) {
		scanf("%c %c", &uName, &wName);
		getchar();
		insertDirectedEdge(uName, wName, i);
	}
}
// vName ���� i�� G�� ��������Ʈ�� �����ϰ� i�� ���������� �ʱ�ȭ
void insertVertex(char vName, int i) {
	(G.vertices + i)->name = vName;

	(G.vertices + i)->inLine = (Incidence*)malloc(sizeof(Incidence));
	(G.vertices + i)->inLine->next = NULL;

	(G.vertices + i)->outLine = (Incidence*)malloc(sizeof(Incidence));
	(G.vertices + i)->outLine->next = NULL;

	(G.vertices + i)->inDegree = 0;
}
// uName ���� u�� ��������, wName ���� w�� �������� �ϴ� ���Ⱓ�� i��, G�� ��������Ʈ, u�� ���Ⱓ������Ʈ, �׸��� w�� ���԰�������Ʈ�� ���� �����ϰ� w�� ���������� ����
void insertDirectedEdge(char uName, char wName, int i) {
	int u, w;

	u = index(uName);
	w = index(wName);

	(G.lines + i)->fromIndex = u;
	(G.lines + i)->toIndex = w;

	addFirst(G.vertices[u].outLine, i);
	addFirst(G.vertices[w].inLine, i);

	(G.vertices + w)->inDegree++;
}
// vName�� �ش��ϴ� ������ �ε����� ã�� ��ȯ
int index(char vName) {
	for (int i = 0; i < n; i++) {
		if (G.vertices[i].name == vName)
			return i;
	}
}
// (��������Ʈ�� ������)H�� ù ��� ��ġ�� ���� i�� ���ҷ� �ϴ� ��带 ����
void addFirst(Incidence* H, int i) {
	Incidence* node = (Incidence*)malloc(sizeof(Incidence));

	node->lIndex = i;
	node->next = H->next;
	H->next = node;
}
// G�κ��� ��������� ���ϰų� �������Ŭ�� �������� ����
void topologicalSort() {
	int t, u, w;

	Q.vIndexArr = (int*)malloc(sizeof(int) * n);

	in = (int*)malloc(sizeof(int) * n);
	topOrder = (int*)malloc(sizeof(int) * (n + 1));

	for (int i = 0; i < n; i++) {
		in[i] = G.vertices[i].inDegree;
		if (in[i] == 0)
			enqueue(i);
	}

	t = 1;

	while (!isEmpty()) {
		u = dequeue();
		topOrder[t] = u;
		t++;

		for (Incidence* ptr = G.vertices[u].outLine->next; ptr != NULL; ptr = ptr->next) {
			w = G.lines[ptr->lIndex].toIndex;
			in[w] -= 1;
			if (in[w] == 0)
				enqueue(w);
		}
	}

	if (t <= n)
		topOrder[0] = 0;
	else
		topOrder[0] = 1;
}

// Q�� ��� ������ True, �ƴϸ� False�� ��ȯ
bool isEmpty() {
	if (Q.front == Q.rear)
		return true;
	else
		return false;
}
// v�� Q�� ����
void enqueue(int vIndex) {
	Q.rear = (Q.rear + 1) % n;
	Q.vIndexArr[Q.rear] = vIndex;
}
// Q�κ��� ������ �����Ͽ� ��ȯ
int dequeue() {
	Q.front = (Q.front + 1) % n;
	return Q.vIndexArr[Q.front];
}

void freeMemory() {
	Incidence* tmp, * ptr;
	
	for (int i = 0; i < n; i++) {
		tmp = (G.vertices + i)->inLine;
		do {
			ptr = tmp->next;
			free(tmp);
			tmp = ptr;
		} while (ptr != NULL);

		tmp = (G.vertices + i)->outLine;
		do {
			ptr = tmp->next;
			free(tmp);
			tmp = ptr;
		} while (ptr != NULL);
	}

	free(G.vertices);
	free(G.lines);
	free(Q.vIndexArr);
	free(in);
	free(topOrder);
}