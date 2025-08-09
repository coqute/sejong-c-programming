#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int size(int N, int f, int l)
{
	if (l == -1)
		return 0;

	return (N + l - f + 1) % N;
}

int get(int* arr, int Rank, int N, int f, int l)
{
	if (Rank < 0 || Rank >= size(N, f, l))
		printf("invalid position\n");
	else
	{
		printf("%d\n", arr[(f + Rank) % N]);

		return arr[(f + Rank) % N];
	}
}

void set(int* arr, int Rank, int element, int N, int f, int l)
{
	if (Rank < 0 || Rank >= size(N, f, l))
		printf("invalid position\n");
	else
		arr[(f + Rank) % N] = element;
}

void Add(int* arr, int Rank, int element, int N, int* f, int* l)
{
	int n = size(N, *f, *l);

	if (n == N - 1)
		printf("list is full\n");
	else if (Rank < 0 || Rank > n)
		printf("invalid position\n");
	else if (Rank < n / 2)
	{
		for (int i = 0; i < Rank; i++) // 0 0 1 2 3 4 0 0 : Rank�� 1�̸� 0 1 1 2 3 4 0 0 �� �ǰ� �� ��° 1�ڸ��� ���ο� element ���� �Էµ�
		{							   // ��, f���� Rank�� �·� ���� ����

			// (*f + i - 1) % N ���� �ϸ� f = 0 �� ��, �ε����� -1�� ��찡 ���ܼ� ���� �߻�
			arr[(N + *f + i - 1) % N] = arr[(*f + i) % N];
		}

		// (*f + Rank - 1) % N ���� �ϸ� f = 0 �� ��, �ε����� -1�� ��찡 ���ܼ� ���� �߻�
		arr[(N + *f + Rank - 1) % N] = element;

		// (*f - 1) % N ���� �ϸ� f = 0 �� ��, �ε����� -1�� ��찡 ���ܼ� ���� �߻�
		*f = (N + *f - 1) % N;
	}
	else
	{
		for (int i = n - 1; i >= Rank; i--) // ���� �ε����� �ִ밪�� n - 1�̹Ƿ� arr[n - 1] ���� arr[Rank]���� ��� ���� �����ϰ� arr[Rank]�� element �� �Է�
			arr[(*f + i + 1) % N] = arr[(*f + i) % N];

		arr[(*f + Rank) % N] = element;

		*l = (*l + 1) % N;
	}
}

void Remove(int* arr, int Rank, int N, int* f, int* l)
{
	int n = size(N, *f, *l);
	
	if (n == 0)
		printf("list is empty\n");
	else if (Rank < 0 || Rank >= n)
		printf("invalid position\n");
	else
	{
		if (Rank < n / 2)
		{
			for (int i = Rank - 1; i >= 0; i--)
				arr[(*f + i + 1) % N] = arr[(*f + i) % N];
			
			arr[*f] = 0;
			*f = (*f + 1) % N;
		}
		else
		{
			for (int i = Rank + 1; i < n; i++)
				arr[(*f + i - 1) % N] = arr[(*f + i) % N];

			arr[*l] = 0;

			// (*l - 1) % N ���� �ϸ� l = 0 �� ��, �ε����� -1�� ��찡 ���ܼ� ���� �߻�
			*l = (N + *l - 1) % N;
		}
	}
}

int main()
{
	int arr[10] = { 0, };
	int N = 10, f = 0, l = -1;
	int count, Rank, element;
	char Type;

	scanf("%d", &count);

	for (int i = 0; i < count; i++)
	{
		getchar();

		scanf("%c", &Type);

		if (Type == 'A')
		{
			scanf("%d %d", &Rank, &element);

			Add(arr, Rank, element, N, &f, &l);
		}
		else if (Type == 'R')
		{
			scanf("%d", &Rank);

			Remove(arr, Rank, N, &f, &l);
		}
		else if (Type == 'G')
		{
			scanf("%d", &Rank);

			element = get(arr, Rank, N, f, l);
		}
		else if (Type == 'S')
		{
			scanf("%d %d", &Rank, &element);

			set(arr, Rank, element, N, f, l);
		}
		else
		{
			printf("invalid type\n");
			continue;
		}

		for (int i = 0; i < N; i++)
		{
			printf(" %d", arr[i]);
		}

		printf("\n");
	}

	return 0;
}