#include <stdio.h>
#include "../include/hashtable.h"

int print_hash_element(const HashTableElement *E)
{
    printf("%s:%d\n", E->key, *(int*)(E->value_point));
    return 0;
}

void test_hashtable()
{
    /*HashTable t;

    int a=1, b=2, c=3;
    HashTableElement* E1;
    HashTableElement* E2;
    HashTableElement* E3;

    //size 10
    printf("bucket size is 1:\n");
    init_HashTable(&t, 100);

    set_HashTable(&t, "one", &a);
    set_HashTable(&t, "two", &b);
    set_HashTable(&t, "there", &c);

    E1=get_HashTable(&t, "one");
    E2=get_HashTable(&t, "two");
    E3=get_HashTable(&t, "there");
    if(E1!=NULL)
    {
        printf("%s:%d\n", E1->key, *(int*)(E1->value_point));
    }
    if(E2!=NULL)
    {
        printf("%s:%d\n", E2->key, *(int*)(E2->value_point));
    }
    if(E3!=NULL)
    {
        printf("%s:%d\n", E3->key, *(int*)(E3->value_point));
    }

    delete_HashTable(&t, "two");
    traverse_HashTable(&t, print_hash_element);

    set_HashTable(&t, "two", &b);
    traverse_HashTable(&t, print_hash_element);

    set_HashTable(&t, "two", &c);
    traverse_HashTable(&t, print_hash_element);

    clear_HashTable(&t);
    traverse_HashTable(&t, print_hash_element);

    destroy_HashTable(&t);

    //size 1
    printf("bucket size is 1:\n");
    init_HashTable(&t, 1);

    set_HashTable(&t, "one", &a);
    set_HashTable(&t, "two", &b);
    set_HashTable(&t, "there", &c);

    E1=get_HashTable(&t, "one");
    E2=get_HashTable(&t, "two");
    E3=get_HashTable(&t, "there");
    if(E1!=NULL)
    {
        printf("%s:%d\n", E1->key, *(int*)(E1->value_point));
    }
    if(E2!=NULL)
    {
        printf("%s:%d\n", E2->key, *(int*)(E2->value_point));
    }
    if(E3!=NULL)
    {
        printf("%s:%d\n", E3->key, *(int*)(E3->value_point));
    }

    delete_HashTable(&t, "two");
    traverse_HashTable(&t, print_hash_element);

    set_HashTable(&t, "two", &b);
    traverse_HashTable(&t, print_hash_element);

    set_HashTable(&t, "two", &c);
    traverse_HashTable(&t, print_hash_element);

    clear_HashTable(&t);
    traverse_HashTable(&t, print_hash_element);

    destroy_HashTable(&t);

    //size 0
    printf("bucket size is 0:\n");
    if(!init_HashTable(&t, 0))
    {
        printf("init error\n");
    }

    return;*/
}
