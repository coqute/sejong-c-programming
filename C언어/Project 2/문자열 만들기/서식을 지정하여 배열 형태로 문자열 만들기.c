#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	char s1[20];
	char s2[30];

	sprintf(s1, "Hello, %s", "world!");

	printf("%s\n", s1);

	// ����, ����, �Ǽ��� ���ڿ��� ����
	sprintf(s2, "%c %d %f %e", 'a', 10, 3.2f, 1.123456e-21f);

	printf("%s\n", s2);

	return 0;
}