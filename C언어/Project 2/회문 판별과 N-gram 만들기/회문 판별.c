#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	char* ptr = malloc(sizeof(char) * 30);

	scanf("%s", ptr);

	int length = strlen(ptr) - 1;

	for (int i = 0; i < strlen(ptr) / 2; i++)
	{
		if (ptr[i] == ptr[length])
			length--;
	}

	if (ptr[strlen(ptr) / 2] == ptr[length])
		printf("ȸ�� �Դϴ�.\n");
	else
		printf("ȸ���� �ƴմϴ�.\n");
	
	free(ptr);

	return 0;
}