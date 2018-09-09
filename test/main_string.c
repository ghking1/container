#include <stdio.h>
#include <string.h>
#include "../include/string.h"

int main()
{
    char a[100];
    char b[10];

    printf("input a:");
    scanf("%s", a);
    printf("input b:");
    scanf("%s", b);

    printf("%d\n", index_BM(a, b, 1));
    printf("%d\n", index_KMP(a, b, 1));
}
