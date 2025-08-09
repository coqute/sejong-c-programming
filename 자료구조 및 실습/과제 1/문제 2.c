#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ArrayLowToHigh(int* arr, int N)
{
	int Min = arr[0];

	for (int i = 1; i < N; i++)
	{
		if (Min > arr[i])
			Min = arr[i];
	}

	for (int i = 0; i < N; i++)
	{
		arr[i] = Min;

		Min++;
	}
}

/* �������� �����̱� ������ ù��° for������ �迭 �� ���� ���� ������
   ã�Ұ�, �ι�° for������ �迭�� ���� ���� ���� ������ �������� 1��
   ������Ű�� ����־���.
   
   �־��� ����ð��� ���� ���� ������ �迭�� ������ �κп� ���� ����̰�
   �� ��, ����ð��� (N�� ��� 2�� ������ ����� ����) O(N)�� �ȴ�.*/

int main()
{
	int N;
	int* SerialNumbers;

	scanf("%d", &N);

	SerialNumbers = malloc(sizeof(int) * N);

	for (int i = 0; i < N; i++)
	{
		scanf("%d", &SerialNumbers[i]);
	}

	ArrayLowToHigh(SerialNumbers, N);

	for (int i = 0; i < N; i++)
	{
		printf(" %d", SerialNumbers[i]);
	}

	free(SerialNumbers);

	return 0;
}