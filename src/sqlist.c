#include <stdlib.h>
#include "../include/sqlist.h"

#define CAPACITY_DEFAULT 8
#define CAPACITY_LINE_1 128
#define CAPACITY_LINE_2 1024
#define CAPACITY_INCREASEMENT 1024

#define bool int
#define true 1
#define false 0

/*
 *adjust capacity of SqList, if appoint newCapacity==0 the newCapacity will be caculate autoly, otherwise it will use it directly
 */
bool reAllocate(SqList* L, const size_t newCapacity)
{
    SqListElement *temp;

    if(L==NULL)    //L==NULL, is invalid
    {
        return false;   
    }    

    if(newCapacity==0)                              //if appoint newCapacity==0 the newCapacity will be caculate autoly
    {
        if(L->capacity ==0)                         //use CAPACITY_DEFAULT originally
        {
            newCapacity=CAPACITY_DEFAULT;
        }
        else if(L->capacity < CAPACITY_LINE_1)      //increase with 4 times
        {
            newCapacity=4*L->capacity;
        }
        else if(L->capacity < CAPACITY_LINE_2)      //increase with 2 times
        {
            newCapacity=L->capacity+L->capacity;
        }
        else                                        //increase stacically with CAPACITY_INCREASEMENT
        {
            newCapacity=L->capacity+CAPACITY_INCREASEMENT;
        }
    }
    
    temp = L->first;
    L->first=(void *)realloc(L->first, newCapacity*sizeof(SqListElement));    //relloc new memory space
    if(L->first == NULL)     //if relloc failed
    {
        L->first = temp;    //reset first point
        return false;
    }            

    L->last=L->first + (L->size-1);    //set new last point
    L->capacity=newCapacity;   //set new capacity
    return true;
}


/*
 *initial it, successfully return true, failed return false
 */
bool init_SqList(SqList *L)                
{
    if (L == NULL)  //L==NULL, is invalid
    {
        return false;
    }

    L->first = NULL;  //initial SqList
    L->last  = NULL;
    L->size     = 0;
    L->capacity = 0;
    
    return reAllocate(L, 0); //allocate space for it originally
}


/*
 *clear all element in it, you must handle all value_point in it yourself before clear it
 */
bool clear_SqList(SqList *L)                
{
    if(L==NULL)    //L==NULL, is invalid
    {
        return false;
    }    

    L->last=L->first;    //reset SqList
    L->size = 0;

    return true;
}


/*
 *destroy it, you must handle all value_point in it yourself before clear it
 */
bool destroy_SqList(SqList *L)
{
    if(L==NULL)    //L==NULL, is invalid
    {
        return false;
    }    

    free(L->first);    //free memory
    
    L->first=NULL;     //set SqList uninitialed
    L->last=NULL;
    L->size=0;
    L->capacity=0;

    return true;
}


/*
 *is empty return true, else return false
 */
bool isEmpty_SqList(const SqList *L)            
{
    if(L==NULL)    //L==NULL, is invalid
    {
        return true;
    }    

    return L->size==0 ? true : false;
}


/*
 *set new size of space
 */
bool setCapacity_SqList(SqList *L, const size_t newCapacity)
{
    if(L==NULL || newCapacity<L->size)    //L==NULL is invalid, newCapacity < size may cause lost of data
    {
        return false;
    }    

    if(newCapacity==L->capacity)     //newCapacity==oldCapacity, needn't reallocate
    {
        return true;
    }

    if(reAllocate(L, newCapacity))   //if reAllocate successfully return true
    {
        return true;
    }
    else
    {
        return false;
    }
}    


/*
 *return size of elements
 */
size_t getSize_SqList(const SqList *L)            
{
    if(L==NULL)    //L==NULL, is invalid
    {
        return 0;
    }    

    return L->size;
}


/*
 *return size of space
 */
size_t getCapacity_SqList(const SqList *L)        
{
    if(L==NULL)    //L==NULL, is invalid
    {
        return 0;
    }    

    return L->capacity;
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
SqListElement* getFirst_SqList(const SqList *L)                                                                        
{
    if(L==NULL)    //L==NULL, is invalid
    {
        return NULL;
    }    

    if(L->size==0)
    {
        return NULL;
    }

    return L->first;    
}


/*
 *return last element of it
 */
SqListElement* getLast_SqList(const SqList *L)                                                                        
{
    if(L==NULL)    //L==NULL, is invalid
    {
        return NULL;
    }    

    if(L->size==0)
    {
        return NULL;
    }

    return L->last;
}


/*
 *return prevElemet of it
 */
SqListElement* getPrev_SqList(const SqList *L, const SqListElement *current)                                            
{
    if(L==NULL)    //NULL, is invalid
    { 
        return NULL;
    }    

    if(current==NULL || L->size==0 || current==L->first) //first element has no prev element
    {
        return NULL;
    }
    else
    {
        return (SqListElement*)current-1;
    }
}


/*
 *return nextElement of it
 */
SqListElement* getNext_SqList(const SqList *L, const SqListElement *current)                                            
{
    if(L==NULL)    //NULL, is invalid
    { 
        return NULL;
    }    

    if(current==NULL || L->size==0 || current==L->last)  //last element has no next element
    {
        return NULL;
    }
    else
    {
        return (SqListElement*)current+1;
    }
}


/*
 *get element by number
 */
SqListElement* getByNum_SqList(const SqList *L, const size_t number)
{
    if(L==NULL)    //L==NULL, is invalid
    {
        return NULL;
    }    

    if(L->size==0 || number<=0 || number>L->size)    //number is not in range
    {
        return NULL;
    }
    else
    {
        return L->first+(number-1);
    }
}    


/*
 *get element by value
 */
SqListElement* getByVal_SqList(const SqList *L, const void *value_point, int (*compare)(const void *value_point1, const void *value_point2))
{
    int i;

    if(L==NULL)    //NULL, is invalid
    { 
        return NULL;
    }    

    if(size==0 || value_point==NULL || compare==NULL)
    {
        return NULL;
    }

    for(i=0; i<L->size; ++i)    //search from L->first
    {
        if(compare((L->first+i)->value_point, value_point)==0)    //when two value equals, stop!
        {
            break;
        }
    }
    
    return p;
}    


/*
 *insert before current element
 */
SqListElement* insert_SqList(SqList *L, const SqListElement *current, const void *value_point)
{
    SqListElement *p=NULL;                    

    if(L==NULL)    //NULL, is invalid
    { 
        return NULL;
    }    

    if(current==NULL || value_point==NULL)
    {
        return NULL;
    }
    
    if(size == L->capacity)    //free space is not enough
    {
        if(!reAllocate(L, 0))
        {
            return NULL;
        }
    }

    //move all elements after current back, including current
    for(p=L->last+1; p!=current; --p)
    {
        *p=*(p-1);
    }
    
    p->value_point=(void *)value_point;        //const point transmit to normal

    ++(L->last);    //refresh L's member
    ++(L->size);
    return p;
}


/*
 *delete current element, return value_point of it
 */
void* delete_SqList(SqList *L, const SqListElement *current)    
{
    void *value_point=current->value_point;    //save value_point 
    SqListElement *p=NULL;                    

    if(L==NULL || size==0 || current==NULL)   //NULL, is invalid
    { 
        return NULL;
    }    

    //move all elements after current forward, excluding current
    for(p=(SqListElement*)current; p!=L->last; ++p)    //here need do an force type transform: from const to normal!
    {
        *p=*(p+1);
    }

    --(L->last);    //refresh L's member
    --(L->size);
    return value_point;
}    


/*
 *push front
 */
SqListElement* pushFront_SqList(SqList *L, const void *value_point)
{
    return insert_SqList(L, L->first, value_point);
}


/*
 *push back
 */
SqListElement* pushBack_SqList(SqList *L, const void *value_point)
{
    return insert_SqList(L, L->last+1, value_point);
}


/*
 *pop front
 */
void* popFront_SqList(SqList *L)
{
    return delete_SqList(L, L->first);
}


/*
 *pop back
 */
void* popBack_SqList(SqList *L)
{
    return delete_SqList(L, L->last);
}


/*
 *traverse element one by one
 */
void traverse_SqList(SqList *L, TraverseAction_SqList (*handler)(const void *value_point))
{
    SqListElement *p=NULL;
    SqListElement *previous=NULL, *current=NULL;
    TraverseAction_SqList action;

    if(L==NULL)
    {
        return;
    }

    previous = NULL;
    for(current=L->first; current!=L->last+1; /*none*/)    //search from L->first
    {
        action=handler(current->value_point);
        switch(action)
        {
        case DO_NOTHING_SQLIST:    
            ++current;
            break;
        case DELETE_ELEMENT_SQLIST:
            for(p=current; p!=L->last; ++p)
            {
                *p=*(p+1);
            }
            --(L->last);    //refresh L's member
            --(L->size);
            break;
        case STOP_TRAVERSE_SQLIST: 
            return;
        case DELETE_AND_STOP_SQLIST:                    
            for(p=current; p!=L->last; ++p)
            {
                *p=*(p+1);
            }
            --(L->last);    //refresh L's member
            --(L->size);
            return;
        }
    }
}
