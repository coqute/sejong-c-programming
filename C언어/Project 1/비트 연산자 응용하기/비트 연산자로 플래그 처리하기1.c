#include <stdio.h>

int main()
{
	unsigned char flag = 0;

	flag |= 1; // ����ũ�� ��Ʈ OR�� ���� ��° ��Ʈ�� ��
	flag |= 2; // ����ũ�� ��Ʈ OR�� �ϰ� ��° ��Ʈ�� ��
	flag |= 4; // ����ũ�� ��Ʈ OR�� ���� ��° ��Ʈ�� ��

	printf("%u\n", flag);

	if (flag & 1)
		printf("0000 0001�� ���� ����\n");
	else
		printf("0000 0001�� ���� ����\n");

	if (flag & 2)
		printf("0000 0010�� ���� ����\n");
	else
		printf("0000 0010�� ���� ����\n");

	if (flag & 4)
		printf("0000 0100�� ���� ����\n");
	else
		printf("0000 0100�� ���� ����\n");

	return 0;
}