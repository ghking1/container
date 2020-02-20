#include <stdlib.h>
#include "../include/lklist.h"

#define bool int
#define true 1
#define false 0

/*
 *init list, successfully return true, failed return false
 */
bool init_LkList(LkList *L)                
{
    if(L==NULL)    //L==NULL, is invalid
    { 
        return false;
    }    

    L->head = (LkListElement*)malloc(sizeof(LkListElement));  //allocate head and initial it
    L->tail = (LkListElement*)malloc(sizeof(LkListElement));  //allocate tail and initial it

    L->head->value_point=NULL;
    L->head->prev=NULL;
    L->head->next=L->tail;
    L->tail->value_point=NULL;
    L->tail->prev=L->head;
    L->tail->next=NULL;

    L->size=0;

    return true;
}


/*
 *clear all element in it, you must handle all value_point in it yourself before clear it
 */
bool clear_LkList(LkList *L)                
{
    LkListElement *previous=NULL, *current=NULL;//release all element excluding head and tail

    if(L==NULL)    //L==NULL, is invalid
    { 
        return false;
    }    

    for(current=L->head->next; current!=L->tail; /*none*/)
    {
        previous=current;
        current=current->next;
        free(previous);
    }
    
    L->head->next=L->tail;    //head point's next point pointed to NULL
    L->tail->prev=L->head;   //head and last point to head
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
    free(L->head);   //then free head and tail
    free(L->tail);

    L->head=NULL;    //set it uninitialed
    L->tail=NULL;
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
 *return first element of it
 */
LkListElement* getFirst_LkList(const LkList *L)                                                                        
{
    if(L==NULL)    //L==NULL, is invalid
    { 
        return NULL;
    }    

    if(L->size == 0)
    {
        return NULL;
    }

    return L->head->next;
}


/*
 *return last element of it
 */
LkListElement* getLast_LkList(const LkList *L)
{
    if(L==NULL)    //L==NULL, is invalid
    { 
        return NULL;
    }    

    if(L->size == 0)
    {
        return NULL;
    }

    return L->tail->prev;
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
        return NULL;
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

    if(current==NULL || L->size==0 || current==L->tail->prev)    //last element has no next element
    {
        return NULL;
    }
    else
    {
        return current->next;
    }
}


/*
 *get element by order
 */
LkListElement* getByOrd_LkList(const LkList *L, const size_t order)                                                    
{
    LkListElement *p=NULL; 
    size_t i=0;

    if(L==NULL)    //L==NULL is invalid or order is not in range
    { 
        return NULL;
    }    

    if(L->size==0 || order<=0 || order>L->size)
    {
        return NULL;
    }

    p=L->head;
    while(i<order)
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
        return NULL;
    }

    for(p=L->head->next; p!=L->tail; p=p->next)       //find from first element
    {
        if(compare(p->value_point, value_point)==0)    //equal then stop
        {
            break;
        }
    }

    return p==L->tail ? NULL : p;
}    


/*
 *insert before current element
 */
LkListElement* insert_LkList(LkList *L, LkListElement *current, const void *value_point)
{
    LkListElement *p = NULL;

    if(L==NULL )    //NULL, is invalid
    { 
        return NULL;
    }    
    
    if(current==NULL || value_point==NULL)
    {
        return NULL;
    }

    p=(LkListElement *)malloc(sizeof(LkListElement));
    if(p==NULL)
    {
        return NULL;
    }
    
    p->value_point=(void*)value_point;  //point to value

    p->next=current;    //change points
    p->prev=current->prev;
    current->prev->next=p;
    current->prev=p;
    
    ++(L->size);

    return p;
}                            


/*
 *delete current element, return value_point of it
 */
void* delete_LkList(LkList *L, LkListElement *current)
{
    void *value_point=NULL;    

    if(L==NULL || current==NULL)   //NULL, is invalid
    { 
        return NULL;
    }    

    value_point = current->value_point; //save value_point

    current->prev->next=current->next; //change points
    current->next->prev=current->prev;

    free(current);

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
    return insert_LkList(L, L->tail, value_point);
}


/*
 *pop front
 */
void* popFront_LkList(LkList *L)    
{    
    if(L->size==0)
    {
        return NULL;
    }
    return delete_LkList(L, L->head->next);
}


/*
 *pop back
 */
void* popBack_LkList(LkList *L)                                                                                        
{
    if(L->size==0)
    {
        return NULL;
    }
    return delete_LkList(L, L->tail->prev);
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
    for(current=L->head->next; current!=L->tail; /*none*/)  //find from first element
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
