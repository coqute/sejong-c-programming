#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	int height = 0;

	scanf("%d", &height);

	// ���� �Ƕ�̵带 �������� ����� ������ (���� ����, ���θ� ���� �� �� ���̿� ����.) ���̸� �������� ��ø ������ �ۼ�

	for (int i = 0; i < height; i++)
	{
		for (int j = height - 1; j >= 0; j--) /* 1) ������ �������� �ۼ��ϴµ� ������ ������ (j�� �����ϴ� ���·� ����)
											     2) ù���� ���� 4��, �� 1���̹Ƿ� ������ height - 1�� ����										
												 3) �������� ���� 0��, �� 5���̹Ƿ� �������� 0���� ����*/
		{
			if (j > i)
				printf(" ");
			else
				printf("*");
		}

		for (int j = 0; j < i; j++) // ���������� ���� �������� �ۼ��ϸ� �ȴ�.
		{
			printf("*");
		}

		printf("\n");
	}

	return 0;
}