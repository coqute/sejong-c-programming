#include <stdio.h>

int main()
{
	int i = 0;

	// do�� �ش��ϴ� �κ�
	printf("Hello, world! %d\n", i); // ó�� �� ���� ����
	i++;							 // ó�� �� ���� ����

	while (i < 100)
	{
		printf("Hello, world! %d\n", i);
		i++;
	}

	return 0;
}