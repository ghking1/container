#include <stdio.h>
#include "../include/hashtable.h"

int print_hash_element(const HashTableElement *E)
{
    printf("%s:%d\n", E->key, *(int*)(E->valuePoint));
    return 0;
}

int main()
{
    HashTable t;
    init_HashTable(&t, 100);

    int a=1, b=2, c=3;
    set_HashTable(&t, "one", &a);
    set_HashTable(&t, "two", &b);
    set_HashTable(&t, "there", &c);

    HashTableElement* E1=get_HashTable(&t, "one");
    HashTableElement* E2=get_HashTable(&t, "two");
    HashTableElement* E3=get_HashTable(&t, "there");
    if(E1!=NULL)
    {
        printf("%s:%d\n", E1->key, *(int*)(E1->valuePoint));
    }
    if(E2!=NULL)
    {
        printf("%s:%d\n", E2->key, *(int*)(E2->valuePoint));
    }
    if(E3!=NULL)
    {
        printf("%s:%d\n", E3->key, *(int*)(E3->valuePoint));
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

    return 0;
}
