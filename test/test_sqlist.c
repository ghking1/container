#include <stdio.h>
#include <assert.h>
#include "../src/sqlist.h"

#define bool int
#define true 1
#define false 0

static int compare(const void*a, const void*b)
{
    if(*(int*)a == *(int*)b)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

//init, clear, destroy, insert, delete, getByOrd, getByVal
static void test_case_0()
{
    SqList l;
    int arr[5]={3, 2, 1, 5, 4};
    int i=0, a=0, b=6;
    void *v=NULL;
    SqListNode *p=NULL;

    //init
    init_SqList(&l);
    assert(l.size == 0);
    assert(l.first != NULL);
    assert(l.capacity == 32);

    //insert, list value should be [1-> 2 -> 3 -> 4 -> 5]
    p=insert_SqList(&l, l.first+l.size, &arr[0]);
    assert(*(int*)p->data == arr[0]);
    p=insert_SqList(&l, p, &arr[1]);
    assert(*(int*)p->data == arr[1]);
    p=insert_SqList(&l, p, &arr[2]);
    assert(*(int*)p->data == arr[2]);
    p=insert_SqList(&l, l.first+l.size, &arr[3]);
    assert(*(int*)p->data == arr[3]);
    p=insert_SqList(&l, p, &arr[4]);
    assert(*(int*)p->data == arr[4]);

    assert(getSize_SqList(&l)==5);
    assert(l.capacity==32);

    //getByOrd
    for(i=0; i<5; ++i)
    {
        p=getByOrd_SqList(&l, i+1);
        assert(*(int*)p->data == i+1);
    }
    p=getByOrd_SqList(&l, 0);
    assert(p==NULL);
    p=getByOrd_SqList(&l, 6);
    assert(p==NULL);

    //getByVal
    for(i=0; i<5; ++i)
    {
        p=getByVal_SqList(&l, &arr[i], compare);
        assert(*(int*)p->data == arr[i]);
    }
    p=getByVal_SqList(&l, &a, compare);  //a==0
    assert(p==NULL);
    p=getByVal_SqList(&l, &b, compare);  //b==6
    assert(p==NULL);

    //delete
    p=getByVal_SqList(&l, &arr[0], compare);
    v=delete_SqList(&l, p);
    assert(*(int*)v == arr[0]);
    p=getByVal_SqList(&l, &arr[1], compare);
    v=delete_SqList(&l, p);
    assert(*(int*)v == arr[1]);
    p=getByVal_SqList(&l, &arr[2], compare);
    v=delete_SqList(&l, p);
    assert(*(int*)v == arr[2]);
    p=getByVal_SqList(&l, &arr[3], compare);
    v=delete_SqList(&l, p);
    assert(*(int*)v == arr[3]);
    p=getByVal_SqList(&l, &arr[4], compare);
    v=delete_SqList(&l, p);
    assert(*(int*)v == arr[4]);

    assert(isEmpty_SqList(&l)==true);
    assert(l.capacity==32);

    //clear
    for(i=0; i<1024; ++i)
    {
        p=insert_SqList(&l, l.first+l.size, &a);
        assert(*(int*)p->data == a);
    }
    assert(getSize_SqList(&l)==1024);
    assert(l.capacity==1024);
    clear_SqList(&l);
    assert(isEmpty_SqList(&l)==true);
    assert(l.capacity==1024);

    //destroy
    destroy_SqList(&l);
    assert(l.first == NULL);
    assert(l.size == 0);
    assert(l.capacity==0);

    return;
}

//pushBack, getFirst, getNext, popBack
static void test_case_1()
{
    SqList l;
    int arr[5]={1, 2, 3, 4, 5};
    int i=0;
    void *v=NULL;
    SqListNode *p=NULL;

    //init
    init_SqList(&l);

    //pushBack, list value should be [1-> 2 -> 3 -> 4 -> 5]
    for(i=0; i<5; ++i)
    {
        p=pushBack_SqList(&l, &arr[i]);
        assert(*(int*)p->data == arr[i]);
    }
    assert(getSize_SqList(&l) == 5);

    //getFirst, getNext
    for(i=0, p=getFirst_SqList(&l); p!=NULL; ++i, p=getNext_SqList(&l, p))
    {
        assert(*(int*)p->data == arr[i]);
    }
    assert(i == 5);

    //popBack
    for(i=4; i>-1; --i)
    {
        v=popBack_SqList(&l);
        assert(*(int*)v == arr[i]);
    }
    v=popBack_SqList(&l);
    assert(v==NULL);
    assert(isEmpty_SqList(&l)==true);

    //destroy
    destroy_SqList(&l);

    return;
}

//pushFront, getLast, getPrev, popFront
static void test_case_2()
{
    SqList l;
    int arr[5]={5, 4, 3, 2, 1};
    int i=0;
    void *v=NULL;
    SqListNode *p=NULL;

    //init
    init_SqList(&l);

    //pushFront, list value should be [1-> 2 -> 3 -> 4 -> 5]
    for(i=0; i<5; ++i)
    {
        p=pushFront_SqList(&l, &arr[i]);
        assert(*(int*)p->data == arr[i]);
    }
    assert(getSize_SqList(&l) == 5);

    //getLast, getPrev
    for(i=0, p=getLast_SqList(&l); p!=NULL; ++i, p=getPrev_SqList(&l, p))
    {
        assert(*(int*)p->data == arr[i]);
    }
    assert(i == 5);

    //popFront
    for(i=4; i>-1; --i)
    {
        v=popFront_SqList(&l);
        assert(*(int*)v == arr[i]);
    }
    v=popFront_SqList(&l);
    assert(v==NULL);
    assert(isEmpty_SqList(&l)==true);

    //destroy
    destroy_SqList(&l);

    return;
}

static TraverseAction_SqList handler(void *value_point)
{
    switch(*(int*)value_point)
    {
        case 1:
            return SQLIST_DELETE_NODE;
        case 2:
            return SQLIST_CONTINUE;
        case 3:
            return SQLIST_DELETE_NODE;
        case 4:
            return SQLIST_CONTINUE;
        case 5:
            return SQLIST_DELETE_NODE;
        defalut:
            assert(false);
    }
}

//traverse
static void test_case_3()
{
    SqList l;
    int arr[5]={1, 2, 3, 4, 5};
    int i=0;
    SqListNode *p=NULL;

    //init
    init_SqList(&l);

    //pushBack, list value should be [1-> 2 -> 3 -> 4 -> 5]
    for(i=0; i<5; ++i)
    {
        p=pushBack_SqList(&l, &arr[i]);
        assert(*(int*)p->data == arr[i]);
    }
    assert(getSize_SqList(&l) == 5);

    //traverse
    traverse_SqList(&l, handler);
    assert(getSize_SqList(&l) == 2);

    p=getByVal_SqList(&l, &arr[0], compare);
    assert(p==NULL);

    p=getByVal_SqList(&l, &arr[1], compare);
    assert(*(int*)p->data == arr[1]);

    p=getByVal_SqList(&l, &arr[2], compare);
    assert(p==NULL);

    p=getByVal_SqList(&l, &arr[3], compare);
    assert(*(int*)p->data == arr[3]);

    p=getByVal_SqList(&l, &arr[4], compare);
    assert(p==NULL);

    //destroy
    destroy_SqList(&l);
}

void test_main_sqlist()
{
    test_case_0();  
    test_case_1();  
    test_case_2();  
    test_case_3();  
    return;
}
