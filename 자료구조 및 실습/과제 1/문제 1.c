#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void is_prime(int N)
{
	int i;				

	for (i = 2; i < N; i++)	
	{
		if (N % i == 0)		
			break;
	}

	if (i == N)				
		printf("prime\n");
	else					
		printf("composite\n");
}

/* �Ҽ��� 1�� �ڽ� ���̿� � ���ε� ������ �������� �ȵǱ� ������
   ���� i�� (1�� �ڱ� �ڽ��� ����)2���� �����ؼ� N - 1���� �����ϴ�
   for������ ���Ȱ�, ���ʿ��� �ݺ��� ���̱� ���� N�� i�� ������
   �������� ���� break�� Ȱ���ؼ� for���� �������Դ�. �� ����
   i�� N�� �������� �Ҽ��̰�(for���� break���� �ʰ� �� ����߱� ������),
   ������ ��쿡�� i�� �ռ����� �ȴ�.

   ���� �־��� ����ð��� i�� �Ҽ��� ��� for���� N - 2�� �ݺ��ϱ� ������
   O(N)�� �ȴ�.*/

int main()
{
	int n;

	scanf("%d", &n);

	is_prime(n);
	
	return 0;
}