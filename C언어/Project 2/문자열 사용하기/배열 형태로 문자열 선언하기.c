#include <stdio.h>

int main()
{
	char s1[10] = "Hello"; // �迭�� ������ ��� ���ڿ��� �ʱ�ȭ
						   // �迭�� �̸� �����س��� ���ڿ��� ���߿� �Ҵ��� �� ����.

	printf("%s\n", s1);

	char s2[] = "Hello"; // ���ڿ��� �Ҵ��� �� �迭�� ũ�⸦ �����ϴ� ���

	printf("%s\n", s2);

	return 0;
}