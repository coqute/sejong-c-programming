#include <stdio.h>

int add(int a, int b)
{
    return a + b;
}

int sub(int a, int b)
{
    return a - b;
}

struct Calc {
    int (*fp[2])(int, int); // ([1]�� ��� : �Լ� �����͸� ����� ������ ����), ([2]�� ��� : �Լ� ������ �迭)
};

int executer(int (*fp)(int, int), int a, int b)
{
    return fp(a, b); // [4] fp(a, b)�� ���� �Լ��� ȣ���ϱ� ������ int�� ��ȯ��, int�� �Ű����� �� ���� �Լ� �����͸� ���� �� �ֵ��� �Ѵ�.
}

int (*getFunc(struct Calc *c, int index))(int, int) // [3] �Լ� �ȿ����� ����ü ������ c, ���� index�� �Ű������� ����Ѵ�.
                                                    // fp[index] : int�� ��ȯ��, int�� �Ű����� �� ���� �Լ� �����͸� ��ȯ
{
    return c->fp[index]; // [2] ����ü ������ c�� ����ü ��� fp�� index�� �Ű������� ����.
                         // ����, ����ü ������ c�� ��� fp�� �ε����� �����Ͽ� ��Ҹ� ��ȯ�ϱ� ������ ����ü Calc�� ��� fp�� �Լ� ������ �迭�̴�.
}

int main()
{
    struct Calc c = { { add, sub } }; // [1] ����ü Calc�� ������ �� add, sub�� �޸� �ּҸ� ���� ��, �Լ� �����͸� ����� ������ �ִ�.

    printf("%d\n", executer(getFunc(&c, 0), 10, 20)); // ���� ���ʿ� �ִ� getFunc �Լ����� ���캻��.
    printf("%d\n", executer(getFunc(&c, 1), 10, 20)); // �� ���� executer �Լ��� ���캻��.

    return 0;
}