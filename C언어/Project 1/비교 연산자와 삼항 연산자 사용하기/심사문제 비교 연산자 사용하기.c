#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	char c1 = 0;

	scanf("%c", &c1);

	if (c1 != 'k')
		printf("��\n");
	else if (c1 == 'k')
		printf("����\n");

	if (c1 > 'h')
		printf("��\n");
	else
		printf("����\n");

	if (c1 <= 'o')
		printf("��\n");
	else
		printf("����\n");

	return 0;
}