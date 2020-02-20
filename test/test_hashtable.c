#include <stdio.h>
#include <assert.h>
#include "../include/hashtable.h"

#define bool int
#define true 1
#define false 0

//init, clear, destroy, set, get, delete
static void test_case_0()
{
    HashTable t;
    char key_temp[32];
    int value_arr[10]={1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int i=0, a=0;
    void *v=NULL;
    HashTableElement *p=NULL;

    //init
    init_HashTable(&t, 3);
    assert(t.bucket != NULL);
    assert(t.bucket_size==3);
    assert(t.size==0);

    //set
    for(i=0; i<10; ++i)
    {
        sprintf(key_temp,"%d",i+1); //transform int to string
        p=set_HashTable(&t, key_temp, &value_arr[i]);
        assert(*(int*)p->value_point == value_arr[i]);
    }
    p=set_HashTable(&t, "1", &a);
    assert(p==NULL);
    assert(getSize_HashTable(&t)==10);

    //get
    for(i=0; i<10; ++i)
    {
        sprintf(key_temp,"%d",i+1); //transform int to string
        p=get_HashTable(&t, key_temp);
        assert(*(int*)p->value_point == value_arr[i]);
    }
    p=get_HashTable(&t, "zero");
    assert(p==NULL);
    assert(getSize_HashTable(&t)==10);

    //delete
    for(i=0; i<10; ++i)
    {
        sprintf(key_temp,"%d",i+1); //transform int to string
        v=delete_HashTable(&t, key_temp);
        assert(*(int*)v == value_arr[i]);
    }
    v=get_HashTable(&t, "zero");
    assert(v==NULL);
    assert(isEmpty_HashTable(&t)==true);

    //clear
    for(i=0; i<1024; ++i)
    {
        sprintf(key_temp,"%d",i+1); //transform int to string
        p=set_HashTable(&t, key_temp, &a);
        assert(*(int*)p->value_point == a);
    }
    assert(getSize_HashTable(&t)==1024);
    clear_HashTable(&t);
    assert(isEmpty_HashTable(&t)==true);

    //destroy
    destroy_HashTable(&t);
    assert(t.bucket == NULL);
    assert(t.bucket_size==0);
    assert(t.size==0);

    return;
}

static void test_case_1()
{
    return;
}

void test_hashtable()
{
    test_case_0();
    test_case_1();
    return;
}
