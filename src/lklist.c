#include <stdlib.h>
#include "../include/lklist.h"

#define bool int
#define true 1
#define false 0

/*
 *initial it, successfully return true, failed return false
 */
bool init_LkList(LkList *L)                
{
    LkListElement *pHead= NULL;
    LkListElement *pend= NULL;    

    if(L==NULL)    //L==NULL, is invalid
    { 
        return false;
    }    

    pHead = (LkListElement*)malloc(sizeof(LkListElement));  //allocate head and initial it
    pEnd = (LkListElement*)malloc(sizeof(LkListElement));   //allocate end and initial it

    pHead->valuePoint=NULL;
    pHead->prior=NULL;
    pHead->next=pend;
    pEnd->valuePoint=NULL;
    pEnd->prior=pHead;
    pEnd->next=NULL;

    L->head=pHead;
    L->end=pend;
    L->size=0;

    return true;
}


/*
 *clear all element in it, you must handle all valuepoint in it yourself before clear it
 */
bool clear_LkList(LkList *L)                
{
    LkListElement *previous=NULL, *current=NULL;//release all element excluding head and end

    if(L==NULL)    //L==NULL, is invalid
    { 
        return false;
    }    

    for(current=L->head->next; current!=L->end; /*none*/)
    {
        previous=current;
        current=current->next;
        free(previous);
    }
    
    L->head->next=L->end;    //head point's next point pointed to NULL
    L->end->prior=L->head;   //head and last point to head
    L->size=0;
    return true;
}


/*
 *destroy it, you must handle all valuepoint in it yourself before clear it
 */
bool destroy_LkList(LkList *L)                
{
    if(L==NULL)    //L==NULL, is invalid
    { 
        return false;
    }    

    clear_LkList(L); //first free all element node
    free(L->head);   //then free head and end
    free(L->end);

    L->head=NULL;    //set it uninitialed
    L->end=NULL;
    L->size=0;

    return true;
}


/*
 *is empty return true, else return false
 */
bool isEmpty_LkList(const LkList *L)            
{
    if(L==NULL)    //L==NULL, is invalid
    { 
        return false;
    }    

    return L->size == 0 ? true : false;
}


/*
 *return size of elements
 */
size_t getSize_LkList(const LkList *L)            
{
    if(L==NULL)    //L==NULL, is invalid
    { 
        return 0;
    }    

    return L->size;
}


/*********************************************************************
 * all of follow points returned maybe NULL, that means encountered  *
 * some error,like:can't find your element or can't insert/delete    *
 * your element.why? maybe you give an position out of range or other*
 * problems.                                                         *
 *********************************************************************/

/*
 *return head element of it
 */
LkListElement* getBegin_LkList(const LkList *L)                                                                        
{
    if(L==NULL)    //L==NULL, is invalid
    { 
        return NULL;
    }    

    return L->head->next;
}


/*
 *return last element of it
 */
LkListElement* getEnd_LkList(const LkList *L)
{
    if(L==NULL)    //L==NULL, is invalid
    { 
        return NULL;
    }    

    return L->end;
}    


/*
 *return priorElemet of it
 */
LkListElement* getPrior_LkList(const LkList *L, const LkListElement *current)
{
    if(L==NULL)    //NULL, is invalid
       { 
        return NULL;
    }    

    if(current==NULL || L->size==0 || current==L->head->next)    //head element has no prior element
    {
        return L->end;
    }
    else
    {
        return current->prior;
    }
}    


/*
 *return nextElement of it
 */
LkListElement* getNext_LkList(const LkList *L, const LkListElement *current)                                            
{
    if(L==NULL)    //NULL, is invalid
    { 
        return NULL;
    }    

    if(current==NULL || L->size==0 || current==L->end->prior)    //last element has no next element
    {
        return L->end;
    }
    else
    {
        return current->next;
    }
}


/*
 *get element by number
 */
LkListElement* getByNum_LkList(const LkList *L, const size_t number)                                                    
{
    LkListElement *p=L->head;   //locate the element
    size_t i=0;

    if(L==NULL)    //L==NULL is invalid or number is not in range
    { 
        return NULL;
    }    

    if(L->size==0 || number<=0 || number>L->size)
    {
        return L->end;
    }

    while(i<number)
    {
        p=p->next;
        ++i;
    }

    return p;
}


/*
 *get element by value
 */
LkListElement* getByVal_LkList(const LkList *L, const void *valuePoint, int (*compare)(const void *valuePoint1, const void *valuePoint2))
{
    LkListElement *p=NULL;

    if(L==NULL)    //NULL, is invalid
    { 
        return NULL;
    }    

    if(L->size==0 || valuePoint==NULL || compare==NULL)
    {
        return L->end;
    }

    for(p=L->head->next; p!=L->end; p=p->next)       //find from first element
    {
        if(compare(p->valuePoint, valuePoint)==0)    //equals then stop
        {
            break;
        }
    }

    return p;
}    



/*
 *insert before current element
 */
LkListElement* insert_LkList(LkList *L, const LkListElement *current, const void *valuePoint)
{
    LkListElement *p = NULL;

    if(L==NULL )    //NULL, is invalid
    { 
        return NULL;
    }    
    
    if(current==NULL || valuePoint==NULL)
    {
        return L->end;
    }

    p=(LkListElement *)malloc(sizeof(LkListElement));
    if(p==NULL)
    {
        exit(ALLOCATE_MEMORY_ERROR);
    }
    
    p->valuePoint=(void*)valuePoint;    //point to value
    p->next=(LkListElement*)current;    //change points
    p->prior=current->prior;
    LkListElement *cur=(LkListElement *)current;    //const point transmit to normal point
    cur->prior->next=p;
    cur->prior=p;
    
    ++(L->size);

    return p;
}                            


/*
 *delete current element, return valuePoint of it
 */
void* delete_LkList(LkList *L, const LkListElement *current)
{
    void *valuePoint=current->valuePoint;    //save valuePoint

    if(L==NULL || current==NULL)   //NULL, is invalid
    { 
        return NULL;
    }    

    LkListElement *cur=(LkListElement *)current;    //const point transmit to normal point
    cur->prior->next=current->next;        //change points
    cur->next->prior=current->prior;

    free(cur);

    --(L->size);

    return valuePoint;
}    


/*
 *push front
 */
LkListElement* pushFront_LkList(LkList *L, const void *valuePoint)                                                        
{
    return insert_LkList(L, L->head->next, valuePoint);
}


/*
 *push back
 */
LkListElement* pushBack_LkList(LkList *L, const void *valuePoint)                                                        
{
    return insert_LkList(L, L->end, valuePoint);
}


/*
 *pop front
 */
void* popFront_LkList(LkList *L)    
{    
    return delete_LkList(L, L->head->next);
}


/*
 *pop back
 */
void* popBack_LkList(LkList *L)                                                                                        
{
    return delete_LkList(L, L->end->prior);
}


/*
 *traverse element one by one
 */
void traverse_LkList(LkList *L, TraverseAction_LkList (*handler)(const void *valuePoint))
{
    LkListElement *previous=NULL, *current=NULL;
    TraverseAction_LkList action;

    if(L==NULL)
    {
        return;
    }

    previous = L->head;
    for(current=L->head->next; current!=L->end; /*none*/)  //find from first element
    {
        action=handler(current->valuePoint);
        switch(action)
        {
        case DO_NOTHING_LKLIST:    
            previous = current;
            current = current->next;
            break;
        case DELETE_ELEMENT_LKLIST:
            current->prior->next=current->next; 
            current->next->prior=current->prior;
            --(L->size);
            free(current);
            current=previous->next;
            break;
        case STOP_TRAVERSE_LKLIST: 
            return;
        case DELETE_AND_STOP_LKLIST:                    
            current->prior->next=current->next; 
            current->next->prior=current->prior;
            --(L->size);
            free(current);
            current=previous->next;
            return;
        }
    }
}
