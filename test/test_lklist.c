#include <stdio.h>
#include "../include/lklist.h"

int lklist_compare(const void*a, const void*b)
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

int test_lklist()
{
    LkList l;
    init_LkList(&l);
    int a=1, b=2, c=3;
    pushBack_LkList(&l, &a);
    pushBack_LkList(&l, &b);
    pushBack_LkList(&l, &c);

    LkListElement *p=getBegin_LkList(&l);

    while(p!=l.end)
    {
        printf("%d\n", *(int*)p->valuePoint);
        p=getNext_LkList(&l, p);
    }

    clear_LkList(&l);

    pushFront_LkList(&l, &a);
    pushFront_LkList(&l, &b);
    pushFront_LkList(&l, &c);
    popBack_LkList(&l);
    popFront_LkList(&l);

    p=getEnd_LkList(&l);
    p=getPrior_LkList(&l, p);
    while(p!=l.end)
    {
        printf("%d\n", *(int*)p->valuePoint);
        p=getPrior_LkList(&l, p);
    }
    
    pushFront_LkList(&l, &a);

    p=getByNum_LkList(&l, 2);
    printf("%d\n", *(int*)p->valuePoint);

    p=getByVal_LkList(&l, &a, lklist_compare);
    printf("%d\n", *(int*)p->valuePoint);

    destroy_LkList(&l);
    
    return 0;
}
