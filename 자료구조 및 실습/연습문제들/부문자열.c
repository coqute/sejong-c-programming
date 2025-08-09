#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int substr1(char* str, char* sub)
{
	if (strstr(str, sub) != NULL)
		return strstr(str, sub) - str;
	else
		return -1;
}

int substr2(char* str, char* sub)
{
	int count = 0;
	char* cmpstr, * cmpsub; // str�� sub�� ù ���ڰ� �������� ���, �� ��ġ���� �ϳ��� ���ϴ� ������ ������ cmpstr, cmpsub�� ����ߴ�.

	if (*sub == NULL)
		return -1;

	while (*str != NULL)
	{
		if (*str == *sub)
		{
			cmpstr = str + 1;
			cmpsub = sub + 1;

			while (1)
			{
				if (*cmpsub == NULL)
					return count;
				else if (*cmpstr != *cmpsub)
					break;
				else
				{
					cmpstr++;
					cmpsub++;
				}
			}
		}

		str++;
		count++;
	}

	return -1;
}

int main()
{
	printf("%d\n", substr1("maximum", "ax"));

	printf("%d\n", substr1("over the rainbow", "rain"));

	printf("%d\n", substr2("over the rainbow", "r t"));

	printf("%d\n", substr2("bacacarcary", "car"));

	printf("%d\n", substr2("bacacarcary", "cam"));

	return 0;
}