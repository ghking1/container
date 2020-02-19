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

    pHead->value_point=NULL;
    pHead->prev=NULL;
    pHead->next=pend;
    pEnd->value_point=NULL;
    pEnd->prev=pHead;
    pEnd->next=NULL;

    L->head=pHead;
    L->end=pend;
    L->size=0;

    return true;
}


/*
 *clear all element in it, you must handle all value_point in it yourself before clear it
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
    L->end->prev=L->head;   //head and last point to head
    L->size=0;
    return true;
}


/*
 *destroy it, you must handle all value_point in it yourself before clear it
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
 *return prevElemet of it
 */
LkListElement* getPrev_LkList(const LkList *L, const LkListElement *current)
{
    if(L==NULL)    //NULL, is invalid
    { 
        return NULL;
    }    

    if(current==NULL || L->size==0 || current==L->head->next)    //head element has no prev element
    {
        return L->end;
    }
    else
    {
        return current->prev;
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

    if(current==NULL || L->size==0 || current==L->end->prev)    //last element has no next element
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
LkListElement* getByVal_LkList(const LkList *L, const void *value_point, int (*compare)(const void *value_point1, const void *value_point2))
{
    LkListElement *p=NULL;

    if(L==NULL)    //NULL, is invalid
    { 
        return NULL;
    }    

    if(L->size==0 || value_point==NULL || compare==NULL)
    {
        return L->end;
    }

    for(p=L->head->next; p!=L->end; p=p->next)       //find from first element
    {
        if(compare(p->value_point, value_point)==0)    //equals then stop
        {
            break;
        }
    }

    return p;
}    


/*
 *insert before current element
 */
LkListElement* insert_LkList(LkList *L, const LkListElement *current, const void *value_point)
{
    LkListElement *p = NULL;

    if(L==NULL )    //NULL, is invalid
    { 
        return NULL;
    }    
    
    if(current==NULL || value_point==NULL)
    {
        return L->end;
    }

    p=(LkListElement *)malloc(sizeof(LkListElement));
    if(p==NULL)
    {
        exit(ALLOCATE_MEMORY_ERROR);
    }
    
    p->value_point=(void*)value_point;    //point to value
    p->next=(LkListElement*)current;    //change points
    p->prev=current->prev;
    LkListElement *cur=(LkListElement *)current;    //const point transmit to normal point
    cur->prev->next=p;
    cur->prev=p;
    
    ++(L->size);

    return p;
}                            


/*
 *delete current element, return value_point of it
 */
void* delete_LkList(LkList *L, const LkListElement *current)
{
    void *value_point=current->value_point;    //save value_point

    if(L==NULL || current==NULL)   //NULL, is invalid
    { 
        return NULL;
    }    

    LkListElement *cur=(LkListElement *)current;    //const point transmit to normal point
    cur->prev->next=current->next;        //change points
    cur->next->prev=current->prev;

    free(cur);

    --(L->size);

    return value_point;
}    


/*
 *push front
 */
LkListElement* pushFront_LkList(LkList *L, const void *value_point)                                                        
{
    return insert_LkList(L, L->head->next, value_point);
}


/*
 *push back
 */
LkListElement* pushBack_LkList(LkList *L, const void *value_point)                                                        
{
    return insert_LkList(L, L->end, value_point);
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
    return delete_LkList(L, L->end->prev);
}


/*
 *traverse element one by one
 */
void traverse_LkList(LkList *L, TraverseAction_LkList (*handler)(const void *value_point))
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
        action=handler(current->value_point);
        switch(action)
        {
        case DO_NOTHING_LKLIST:    
            previous = current;
            current = current->next;
            break;
        case DELETE_ELEMENT_LKLIST:
            current->prev->next=current->next; 
            current->next->prev=current->prev;
            --(L->size);
            free(current);
            current=previous->next;
            break;
        case STOP_TRAVERSE_LKLIST: 
            return;
        case DELETE_AND_STOP_LKLIST:                    
            current->prev->next=current->next; 
            current->next->prev=current->prev;
            --(L->size);
            free(current);
            current=previous->next;
            return;
        }
    }
}
