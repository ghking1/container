#include <stdio.h>

extern void test_main_hashtable();
extern void test_main_lklist();
extern void test_main_sqlist();

int main()
{
    test_main_lklist();
    test_main_sqlist();
    test_main_hashtable();

    printf("\nall test finished successfully!\n");

    return 0;
}
