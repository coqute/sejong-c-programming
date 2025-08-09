/* �Լ��� ���ڷ� ���� arr�� �Ȱ��� ũ���� tmp�� �����. �� ���� arr�� ��� �� �ּڰ��� ã�Ƽ� Min�� �����Ѵ�.
   �׷����� for���� �����µ� �Է��� �������� �����̱� ������ ��Ģ�� �����Ѵ�.
   � ���� ������������ ���ĵ� �� �־���� ��ġ�� (�ڱ��ڽ� - Min)�̶�� ���̴�. ���� ���ڸ�
   arr = {10, 8, 7, 6, 9}, Min = 6 : ������������ �������� �� 10�� �־���� ��ġ(= 10 - 6 = 4), 8�� �־���� ��ġ(= 8 - 6 = 2).....
   �� ��Ģ�� �̿��ؼ� tmp[arr[i] - Min] = arr[i]�� ���ش�.
   ���������δ� tmp�� �ִ� ���ĵ� ������ arr�� �������ְ� tmp�� �޸𸮸� �������ش�.
   �̷��� �Ǹ� (N�� ��� 3�� ����� ����) ����ð��� O(N)�� �ȴ�.*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void ArrayLowToHigh(int* arr, int N)
{
	int* tmp = malloc(sizeof(int) * N); 
	int Min = arr[0];
	int i;

	for (i = 1; i < N; i++) 
	{
		if (Min > arr[i])
			Min = arr[i];
	}

	for (i = 0; i < N; i++)
	{
		tmp[arr[i] - Min] = arr[i];
	}								

	for (i = 0; i < N; i++)
	{
		arr[i] = tmp[i];
	}

	free(tmp);
}

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