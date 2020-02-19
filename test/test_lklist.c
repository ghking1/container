#include <stdio.h>
#include <assert.h>
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
    LkListElement *p;
    int arr[3]={1, 2, 3};
    int i;

    //test pushBack, getBegin, getNext
    init_LkList(&l);
    pushBack_LkList(&l, &arr[0]);
    pushBack_LkList(&l, &arr[1]);
    pushBack_LkList(&l, &arr[2]);
    for(i=0, p=getBegin_LkList(&l); p!=l.end; ++i, p=getNext_LkList(&l, p))
    {
        assert(*(int*)p->value_point == arr[i]);
    }
    clear_LkList(&l);
    assert(l->size == 0);

    //test pushFront, getEnd, getPrev
    pushFront_LkList(&l, &arr[0]);
    pushFront_LkList(&l, &arr[1]);
    pushFront_LkList(&l, &arr[2]);
    p=getEnd_LkList(&l);
    p=getPrev_LkList(&l, p);
    while(p!=l.end)
    {
        printf("%d\n", *(int*)p->value_point);
        p=getPrev_LkList(&l, p);
    }
    
    pushFront_LkList(&l, &a);

    p=getByNum_LkList(&l, 2);
    printf("%d\n", *(int*)p->value_point);

    p=getByVal_LkList(&l, &a, lklist_compare);
    printf("%d\n", *(int*)p->value_point);

    destroy_LkList(&l);
    
    return 0;
}
