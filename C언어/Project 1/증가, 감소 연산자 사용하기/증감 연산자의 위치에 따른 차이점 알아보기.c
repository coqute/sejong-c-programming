#include<stdio.h>

int main()
{
	int num1 = 2;
	int num2 = 2;
	int num3;
	int num4;
	int num5;
	int num6;

	num3 = num1++; // num1�� ���� num3�� �Ҵ��� �� num1�� ���� 1 ������Ŵ
	num4 = num2--; // num2�� ���� num4�� �Ҵ��� �� num2�� ���� 1 ���ҽ�Ŵ

	printf("%d %d\n", num3, num4);

	num1 = 2; // 1 ������ num1�� ���� �ٽ� 2�� �ʱ�ȭ
	num2 = 2; // 1 ���ҵ� num2�� ���� �ٽ� 2�� �ʱ�ȭ

	num5 = ++num1; // num1�� ���� 1 ������Ų �� num5�� �Ҵ�
	num6 = --num2; // num2�� ���� 1 ���ҽ�Ų �� num6�� �Ҵ�

	printf("%d %d\n", num5, num6);

	return 0;
}