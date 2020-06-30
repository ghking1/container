#include <stdio.h>
#include <assert.h>
#include "../src/hashtable.h"

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
    HashTableNode *p=NULL;

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
        assert(*(int*)p->data == value_arr[i]);
    }
    p=set_HashTable(&t, "1", &a);
    assert(p==NULL);
    assert(getSize_HashTable(&t)==10);

    //get
    for(i=0; i<10; ++i)
    {
        sprintf(key_temp,"%d",i+1); //transform int to string
        p=get_HashTable(&t, key_temp);
        assert(*(int*)p->data == value_arr[i]);
    }
    p=get_HashTable(&t, "zero");
    assert(p==NULL);
    assert(getSize_HashTable(&t)==10);

    //delete
    for(i=0; i<10; ++i)
    {
        sprintf(key_temp,"%d",i+1); //transform int to string
        v=del_HashTable(&t, key_temp);
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
        assert(*(int*)p->data == a);
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

static TraverseAction_HashTable handler(char* key, void *value_point)
{
    switch((*(int*)value_point-1)%5 + 1)
    {
        case 1:
            return HASHTABLE_DELETE_NODE;
        case 2:
            return HASHTABLE_CONTINUE;
        case 3:
            return HASHTABLE_DELETE_NODE;
        case 4:
            return HASHTABLE_CONTINUE;
        case 5:
            return HASHTABLE_DELETE_NODE;
        defalut:
            assert(false);
    }
}

//traverse
static void test_case_1()
{
    HashTable t;
    char key_temp[32];
    int value_arr[10]={1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int i=0;
    HashTableNode *p=NULL;

    //init
    init_HashTable(&t, 3);

    //set
    for(i=0; i<10; ++i)
    {
        sprintf(key_temp,"%d",i+1); //transform int to string
        p=set_HashTable(&t, key_temp, &value_arr[i]);
        assert(*(int*)p->data == value_arr[i]);
    }
    assert(getSize_HashTable(&t) == 10);

    //traverse
    traverse_HashTable(&t, handler);
    assert(getSize_HashTable(&t) == 4);

    //destroy
    destroy_HashTable(&t);
}

void test_main_hashtable()
{
    test_case_0();
    test_case_1();
    return;
}
