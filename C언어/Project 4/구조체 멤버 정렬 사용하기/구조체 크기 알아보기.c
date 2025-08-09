#include <stdio.h>
#include <stddef.h>   // offsetof ��ũ�ΰ� ���ǵ� ��� ����

struct PacketHeader {
    char flags;    // 1����Ʈ
    int seq;       // 4����Ʈ
};

int main()
{
    struct PacketHeader header;

    printf("%d\n", sizeof(header.flags));           // 1: char�� 1����Ʈ
    printf("%d\n", sizeof(header.seq));             // 4: int�� 4����Ʈ
    printf("%d\n", sizeof(header));                 // 8: ����ü ��ü ũ��� 8����Ʈ
    printf("%d\n\n", sizeof(struct PacketHeader));    // 8: ����ü �̸����� ũ�� ���ϱ�

    printf("%d\n", offsetof(struct PacketHeader, flags));    // 0
    printf("%d\n", offsetof(struct PacketHeader, seq));      // 4

    return 0;
}