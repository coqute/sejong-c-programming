#include <stdio.h>

int main()
{
	int* numPtr = 0x100; // �����Ϳ� 0x100�� ���� ����

	printf("%d\n", *numPtr); // 0x100�� �߸��� �޸� �ּ��̹Ƿ� ���� ����

	numPtr = 0x00CCFC2C; // ������ �����ϴ� �޸� �ּҶ�� ������ �� ����

	return 0;
}