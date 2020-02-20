#include <stdio.h>

extern void test_hashtable();
extern void test_lklist();
extern void test_sqlist();

int main()
{
    test_lklist();
    //test_sqlist();
    //test_hashtable();

    printf("\nall test finished successfully!\n");

    return 0;
}
