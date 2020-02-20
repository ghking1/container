#include <stdio.h>
#include <assert.h>
#include "../include/lklist.h"

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
    LkList l;
    int arr[5]={3, 2, 1, 5, 4};
    int i=0, a=0, b=6;
    void *v=NULL;
    LkListElement *p=NULL;

    //init
    init_LkList(&l);
    assert(l.size == 0);
    assert(l.head != NULL);
    assert(l.tail!= NULL);
    assert(l.head->next == l.tail);
    assert(l.tail->prev == l.head);

    //insert, list value should be [1-> 2 -> 3 -> 4 -> 5]
    p=insert_LkList(&l, l.tail, &arr[0]);
    assert(*(int*)p->value_point == arr[0]);
    p=insert_LkList(&l, p, &arr[1]);
    assert(*(int*)p->value_point == arr[1]);
    p=insert_LkList(&l, p, &arr[2]);
    assert(*(int*)p->value_point == arr[2]);
    p=insert_LkList(&l, l.tail, &arr[3]);
    assert(*(int*)p->value_point == arr[3]);
    p=insert_LkList(&l, p, &arr[4]);
    assert(*(int*)p->value_point == arr[4]);

    assert(getSize_LkList(&l)==5);

    //getByOrd
    for(i=0; i<5; ++i)
    {
        p=getByOrd_LkList(&l, i+1);
        assert(*(int*)p->value_point == i+1);
    }
    p=getByOrd_LkList(&l, 0);
    assert(p==NULL);
    p=getByOrd_LkList(&l, 6);
    assert(p==NULL);

    //getByVal
    for(i=0; i<5; ++i)
    {
        p=getByVal_LkList(&l, &arr[i], compare);
        assert(*(int*)p->value_point == arr[i]);
    }
    p=getByVal_LkList(&l, &a, compare);  //a==0
    assert(p==NULL);
    p=getByVal_LkList(&l, &b, compare);  //b==6
    assert(p==NULL);

    //delete
    p=getByVal_LkList(&l, &arr[0], compare);
    v=delete_LkList(&l, p);
    assert(*(int*)v == arr[0]);
    p=getByVal_LkList(&l, &arr[1], compare);
    v=delete_LkList(&l, p);
    assert(*(int*)v == arr[1]);
    p=getByVal_LkList(&l, &arr[2], compare);
    v=delete_LkList(&l, p);
    assert(*(int*)v == arr[2]);
    p=getByVal_LkList(&l, &arr[3], compare);
    v=delete_LkList(&l, p);
    assert(*(int*)v == arr[3]);
    p=getByVal_LkList(&l, &arr[4], compare);
    v=delete_LkList(&l, p);
    assert(*(int*)v == arr[4]);

    assert(isEmpty_LkList(&l)==true);

    //clear
    for(i=0; i<1024; ++i)
    {
        p=insert_LkList(&l, l.tail, &a);
        assert(*(int*)p->value_point == a);
    }
    assert(getSize_LkList(&l)==1024);
    clear_LkList(&l);
    assert(isEmpty_LkList(&l)==true);

    //destroy
    destroy_LkList(&l);
    assert(l.size == 0);
    assert(l.head == NULL);
    assert(l.tail == NULL);

    return;
}

//pushBack, getFirst, getNext, popBack
static void test_case_1()
{
    LkList l;
    int arr[5]={1, 2, 3, 4, 5};
    int i=0;
    void *v=NULL;
    LkListElement *p=NULL;

    //init
    init_LkList(&l);

    //pushBack, list value should be [1-> 2 -> 3 -> 4 -> 5]
    for(i=0; i<5; ++i)
    {
        p=pushBack_LkList(&l, &arr[i]);
        assert(*(int*)p->value_point == arr[i]);
    }
    assert(getSize_LkList(&l) == 5);

    //getFirst, getNext
    for(i=0, p=getFirst_LkList(&l); p!=NULL; ++i, p=getNext_LkList(&l, p))
    {
        assert(*(int*)p->value_point == arr[i]);
    }
    assert(i == 5);

    //popBack
    for(i=4; i>-1; --i)
    {
        v=popBack_LkList(&l);
        assert(*(int*)v == arr[i]);
    }
    v=popBack_LkList(&l);
    assert(v==NULL);
    assert(isEmpty_LkList(&l)==true);

    //destroy
    destroy_LkList(&l);

    return;
}

//pushFront, getLast, getPrev, popFront
static void test_case_2()
{
    LkList l;
    int arr[5]={5, 4, 3, 2, 1};
    int i=0;
    void *v=NULL;
    LkListElement *p=NULL;

    //init
    init_LkList(&l);

    //pushFront, list value should be [1-> 2 -> 3 -> 4 -> 5]
    for(i=0; i<5; ++i)
    {
        p=pushFront_LkList(&l, &arr[i]);
        assert(*(int*)p->value_point == arr[i]);
    }
    assert(getSize_LkList(&l) == 5);

    //getLast, getPrev
    for(i=0, p=getLast_LkList(&l); p!=NULL; ++i, p=getPrev_LkList(&l, p))
    {
        assert(*(int*)p->value_point == arr[i]);
    }
    assert(i == 5);

    //popFront
    for(i=4; i>-1; --i)
    {
        v=popFront_LkList(&l);
        assert(*(int*)v == arr[i]);
    }
    v=popFront_LkList(&l);
    assert(v==NULL);
    assert(isEmpty_LkList(&l)==true);

    //destroy
    destroy_LkList(&l);

    return;
}

static TraverseAction_LkList handler(void *value_point)
{
    switch(*(int*)value_point)
    {
        case 1:
            return DELETE_ELEMENT_LKLIST;
        case 2:
            return DO_NOTHING_LKLIST;
        case 3:
            return DELETE_ELEMENT_LKLIST;
        case 4:
            return DO_NOTHING_LKLIST;
        case 5:
            return DELETE_ELEMENT_LKLIST;
        defalut:
            assert(false);
    }
}

//traverse
static void test_case_3()
{
    LkList l;
    int arr[5]={1, 2, 3, 4, 5};
    int i=0;
    LkListElement *p=NULL;

    //init
    init_LkList(&l);

    //pushBack, list value should be [1-> 2 -> 3 -> 4 -> 5]
    for(i=0; i<5; ++i)
    {
        p=pushBack_LkList(&l, &arr[i]);
        assert(*(int*)p->value_point == arr[i]);
    }
    assert(getSize_LkList(&l) == 5);

    //traverse
    traverse_LkList(&l, handler);
    assert(getSize_LkList(&l) == 2);

    p=getByVal_LkList(&l, &arr[0], compare);
    assert(p==NULL);

    p=getByVal_LkList(&l, &arr[1], compare);
    assert(*(int*)p->value_point == arr[1]);

    p=getByVal_LkList(&l, &arr[2], compare);
    assert(p==NULL);

    p=getByVal_LkList(&l, &arr[3], compare);
    assert(*(int*)p->value_point == arr[3]);

    p=getByVal_LkList(&l, &arr[4], compare);
    assert(p==NULL);

    //destroy
    destroy_LkList(&l);
}

void test_main_lklist()
{
    test_case_0();  
    test_case_1();  
    test_case_2();  
    test_case_3();  
    return;
}
