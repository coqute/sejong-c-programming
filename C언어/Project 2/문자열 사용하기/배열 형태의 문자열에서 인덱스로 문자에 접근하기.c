#include <stdio.h>

int main()
{
	char s1[10] = "Hello";

	s1[0] = 'A'; // �迭 ������ ���ڿ��� �ε����� �����Ͽ� ������ ������ �� �ִ�.

	printf("%s\n", s1);

	return 0;
}