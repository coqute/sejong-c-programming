#include <stdio.h>

int main()
{
	char num1 = 67;
	char num2;

	num2 = num1 >> 5;

	printf("%d\n", num2); // 2: 0000 0010: ���ڶ�� ������ ��ȣ ��Ʈ�� ���� 0���� ä�����Ƿ� 0000 0010�� ��

	return 0;
}