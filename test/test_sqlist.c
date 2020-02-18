#include <stdio.h>
#include "../include/sqlist.h"

int sqlist_compare(const void*a, const void*b)
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

int test_sqlist()
{
    SqList l;
    init_SqList(&l);
    int a=1, b=2, c=3;
    pushBack_SqList(&l, &a);
    pushBack_SqList(&l, &b);
    pushBack_SqList(&l, &c);

    SqListElement *p=getBegin_SqList(&l);

    while(p!=l.end)
    {
        printf("%d\n", *(int*)p->valuePoint);
        p=getNext_SqList(&l, p);
    }

    clear_SqList(&l);

    pushFront_SqList(&l, &a);
    pushFront_SqList(&l, &b);
    pushFront_SqList(&l, &c);
    popBack_SqList(&l);
    popFront_SqList(&l);

    p=getEnd_SqList(&l);
    p=getPrior_SqList(&l, p);
    while(p!=l.end)
    {
        printf("%d\n", *(int*)p->valuePoint);
        p=getPrior_SqList(&l, p);
    }
    
    pushFront_SqList(&l, &a);

    p=getByNum_SqList(&l, 2);
    printf("%d\n", *(int*)p->valuePoint);

    p=getByVal_SqList(&l, &a, sqlist_compare);
    printf("%d\n", *(int*)p->valuePoint);


    destroy_SqList(&l);

    return 0;
}
