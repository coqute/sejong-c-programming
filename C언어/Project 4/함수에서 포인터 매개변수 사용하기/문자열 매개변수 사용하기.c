#include <stdio.h>

void helloString(char* s1)	// void helloString(char s1[]): �̷� ������ char �迭�� �Ű������� �����ص�
							// �迭�Ӹ� �ƴ϶� ���ڿ��̳� �޸𸮰� �Ҵ�� �����͵� ������ �� �ִ�.
{
	printf("Hello, %s\n", s1);
}

int main()
{
	helloString("world!");

	return 0;
}