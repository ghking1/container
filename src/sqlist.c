#include <stdlib.h>
#include "../include/sqlist.h"

#define CAPACITY_DEFAULT 32 
#define CAPACITY_LINE_1  128
#define CAPACITY_LINE_2  1024
#define CAPACITY_INCREASEMENT 1024

#define bool int
#define true 1
#define false 0

/*
 *adjust capacity of SqList, if appoint new_capacity==0 the new_capacity will be caculate autoly, otherwise it will use it directly
 */
bool reAllocate(SqList* L, const size_t capacity)
{
    SqListElement *temp;
    size_t new_capacity=capacity;

    if(L==NULL)    //L==NULL, is invalid
    {
        return false;   
    }    

    if(new_capacity==0)                              //if appoint new_capacity==0 the new_capacity will be caculate autoly
    {
        if(L->capacity ==0)                         //use CAPACITY_DEFAULT originally
        {
            new_capacity=CAPACITY_DEFAULT;
        }
        else if(L->capacity < CAPACITY_LINE_1)      //increase with 4 times
        {
            new_capacity=4*L->capacity;
        }
        else if(L->capacity < CAPACITY_LINE_2)      //increase with 2 times
        {
            new_capacity=L->capacity+L->capacity;
        }
        else                                        //increase stacically with CAPACITY_INCREASEMENT
        {
            new_capacity=L->capacity+CAPACITY_INCREASEMENT;
        }
    }
    
    temp = L->first;
    L->first=(SqListElement*)realloc(L->first, new_capacity*sizeof(SqListElement));    //relloc new memory space
    if(L->first == NULL)    //if realloc failed
    {
        L->first = temp;    //reset first point
        return false;
    }            

    L->capacity=new_capacity;   //set new capacity
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
 *set new size of space
 */
bool setCapacity_SqList(SqList *L, const size_t capacity)
{
    size_t new_capacity = capacity;

    if(L==NULL || new_capacity<L->size)    //L==NULL is invalid, new_capacity < size may cause lost of data
    {
        return false;
    }    

    if(new_capacity==L->capacity)     //new_capacity==oldCapacity, needn't reallocate
    {
        return true;
    }

    if(reAllocate(L, new_capacity))   //if reAllocate successfully return true
    {
        return true;
    }
    else
    {
        return false;
    }
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

    return (L->first + (L->size -1));
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

    if(current==NULL || L->size==0 || current >= (L->first + (L->size -1)))  //last element has no next element
    {
        return NULL;
    }
    else
    {
        return (SqListElement*)current+1;
    }
}


/*
 *get element by order
 */
SqListElement* getByOrd_SqList(const SqList *L, const size_t order)
{
    if(L==NULL)    //L==NULL, is invalid
    {
        return NULL;
    }    

    if(L->size==0 || order<=0 || order>L->size)    //order is not in range
    {
        return NULL;
    }
    else
    {
        return L->first + (order-1);
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

    if(L->size==0 || value_point==NULL || compare==NULL)
    {
        return NULL;
    }

    for(i=0; i<L->size; ++i)    //search from L->first
    {
        if(compare((L->first+i)->value_point, value_point)==0)    //when two value equals, stop!
        {
            return L->first+i;
        }
    }
    
    return NULL;
}    


/*
 *insert before current element
 */
SqListElement* insert_SqList(SqList *L, SqListElement *current, const void *value_point)
{
    SqListElement *p=NULL;                    
    size_t current_offset;

    if(L==NULL)    //NULL, is invalid
    { 
        return NULL;
    }    

    if(current==NULL || value_point==NULL)
    {
        return NULL;
    }
    
    if(L->size == L->capacity)    //free space is not enough
    {
        current_offset = current - L->first;
        if(reAllocate(L, 0))
        {
            //current point should be relocated after realloc
            current = L->first + current_offset;
        }
        else
        {
            return NULL;
        }
    }

    //move all elements after current one step, including current
    for(p=(L->first + L->size); p!=current; --p)
    {
        *p=*(p-1);
    }
    
    p->value_point=(void *)value_point;        //const point transmit to normal
    ++(L->size);

    return p;
}


/*
 *delete current element, return value_point of it
 */
void* delete_SqList(SqList *L, SqListElement *current)    
{
    void *value_point=NULL;
    SqListElement *p=NULL;                    

    if(L==NULL || L->size==0 || current==NULL)   //NULL, is invalid
    { 
        return NULL;
    }    

    value_point = current->value_point; //save value_point 

    //move all elements after current forward, excluding current
    for(p=current; p!=(L->first + (L->size - 1)); ++p)    //here need do an force type transform: from const to normal!
    {
        *p=*(p+1);
    }

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
    return insert_SqList(L, L->first + L->size, value_point);
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
    return delete_SqList(L, L->first + (L->size - 1));
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
    for(current=L->first; current!=(L->first + L->size); /*none*/)    //search from L->first
    {
        action=handler(current->value_point);
        switch(action)
        {
        case DO_NOTHING_SQLIST:    
            ++current;
            break;
        case DELETE_ELEMENT_SQLIST:
            for(p=current; p!=(L->first + (L->size - 1)); ++p)
            {
                *p=*(p+1);
            }
            --(L->size);
            break;
        case STOP_TRAVERSE_SQLIST: 
            return;
        case DELETE_AND_STOP_SQLIST:                    
            for(p=current; p!=(L->first + (L->size - 1)); ++p)
            {
                *p=*(p+1);
            }
            --(L->size);
            return;
        }
    }
}
