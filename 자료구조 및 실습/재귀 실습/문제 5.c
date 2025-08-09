#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void Hanoi(int n, char from, char aux, char to)
{
	if (n == 1)
	{
		printf("%c %c\n", from, to);
		return;
	}
	
	Hanoi(n - 1, from, to, aux); // �� �Ʒ� ������ ������ n - 1���� ������ ��� ���� -> ���� ����
	
	printf("%c %c\n", from, to); // ��� ���� -> ��ǥ ����
	
	Hanoi(n - 1, aux, from, to); // n - 1���� ������ ���� ���� -> ��ǥ ����

	return;
}

int main()
{
	int N;

	scanf("%d", &N);

	Hanoi(N, 'A', 'B', 'C');

	return 0;
}