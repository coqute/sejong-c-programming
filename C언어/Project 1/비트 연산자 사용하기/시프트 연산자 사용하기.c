#include <stdio.h>

int main()
{
	unsigned char num1 = 3;
	unsigned char num2 = 24;
	
	printf("%u\n", num1 << 3); // <<�� 2�� �ŵ������� ���ϱ�
	printf("%u\n", num2 >> 2); // >>�� 2�� �ŵ������� ������

	return 0;
}