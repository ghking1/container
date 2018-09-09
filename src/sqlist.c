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
bool reAllocate(SqList* L, size_t newCapacity)
{
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
    
    size_t size=(L->end)-(L->begin);                //caculate size and save it
    L->begin=(void *)realloc(L->begin, newCapacity*sizeof(SqListElement));    //relloc new memory space
    if(L->begin == NULL)     //if relloc failed exit
    {
        exit(ALLOCATE_MEMORY_ERROR);
    }            

    L->end=L->begin + size;    //set new end point
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

    L->begin    = NULL;  //initial SqList
    L->end      = NULL;
    L->capacity = 0;
    
    reAllocate(L, 0);    //allocate space for it originally

    return true;
}


/*
 *clear all element in it
 */
bool clear_SqList(SqList *L)                
{
    if(L==NULL)    //L==NULL, is invalid
    {
        return false;
    }    

    L->end=L->begin;    //reset SqList

    return true;
}


bool destroy_SqList(SqList *L)
{
    if(L==NULL)    //L==NULL, is invalid
    {
        return false;
    }    

    free(L->begin);    //free memory
    
    L->begin=NULL;     //set SqList uninitialed
    L->end=NULL;
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
        return false;
    }    

    return (L->end)-(L->begin)==0 ? true : false;
}


/*
 *set new size of space
 */
bool setCapacity_SqList(SqList *L, size_t newCapacity)
{
    if(L==NULL || newCapacity<(L->end)-(L->begin))    //L==NULL is invalid, newCapacity < size may cause lost of data
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

    return (L->end)-(L->begin);
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
 *return begin element of it
 */
SqListElement* getBegin_SqList(const SqList *L)                                                                        
{
    if(L==NULL)    //L==NULL, is invalid
    {
        return NULL;
    }    

    return L->begin;    
}


/*
 *return end element of it
 */
SqListElement* getEnd_SqList(const SqList *L)                                                                        
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
SqListElement* getPrior_SqList(const SqList *L, const SqListElement *current)                                            
{
    if(L==NULL)    //NULL, is invalid
       { 
        return NULL;
    }    

    if(current==NULL || (L->end)-(L->begin)==0 || current==L->begin)        //begin element has no prior element
    {
        return L->end;
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

    if(current==NULL || (L->end)-(L->begin)==0 || current==L->end-1)        //end element has no next element
    {
        return L->end;
    }
    else
    {
        return (SqListElement*)current+1;
    }
}


/*
 *get element by number
 */
SqListElement* getByNum_SqList(const SqList *L, size_t number)
{
    if(L==NULL)    //L==NULL, is invalid
    {
        return NULL;
    }    

    if((L->end)-(L->begin)==0 || number<=0 || number>(L->end)-(L->begin))    //number is not in range
    {
        return L->end;
    }
    else
    {
        return L->begin+(number-1);
    }
}    


/*
 *get element by value
 */
SqListElement* getByVal_SqList(const SqList *L, const void *valuePoint, int (*compare)(const void*, const void*))
{
    if(L==NULL)    //NULL, is invalid
       { 
        return NULL;
    }    

    if((L->end)-(L->begin)==0 || valuePoint==NULL || compare==NULL)
    {
        return L->end;
    }

    SqListElement *p=NULL;
    for(p=L->begin ; p!=L->end; ++p)    //search from L->begin
    {
        if(compare(p->valuePoint, valuePoint)==0)    //when two value equals, stop!
        {
            break;
        }
    }
    
    return p;
}    


/*
 *insert before current element
 */
SqListElement* insert_SqList(SqList *L, const SqListElement *current, const void *valuePoint)
{
    if(L==NULL)    //NULL, is invalid
       { 
        return NULL;
    }    

    if(current==NULL || valuePoint==NULL)
    {
        return L->end;
    }
    
    if((L->end)-(L->begin) == L->capacity)    //free space is not enough
    {
        if(!reAllocate(L, 0))
        {
            return NULL;
        }
    }
    
    SqListElement *p=NULL;                    //move all elements after current back, including current
    for(p=L->end; p!=current; --p)
    {
        *p=*(p-1);
    }
    
    p->valuePoint=(void *)valuePoint;        //const point transmit to normal

    ++(L->end);    //refresh L's member
    return p;
}


/*
 *delete current element, return valuePoint of it
 */
void * delete_SqList(SqList *L, const SqListElement *current)    
{
    if(L==NULL || (L->end)-(L->begin)==0 || current==NULL)   //NULL, is invalid
       { 
        return NULL;
    }    

    void *valuePoint=current->valuePoint;    //save valuePoint 

    SqListElement *p=NULL;                    //move all elements after current forward, excluding current
    for(p=(SqListElement*)current; p!=L->end-1; ++p)    //here need do an force type transform: from const to normal!
    {
        *p=*(p+1);
    }

    --(L->end);    //refresh L's member
    return valuePoint;
}    


/*
 *push front
 */
SqListElement* pushFront_SqList(SqList *L, const void *valuePoint)
{
    return insert_SqList(L, L->begin, valuePoint);
}


/*
 *push back
 */
SqListElement* pushBack_SqList(SqList *L, const void *valuePoint)
{
    return insert_SqList(L, L->end, valuePoint);
}


/*
 *pop front
 */
void * popFront_SqList(SqList *L)
{
    return delete_SqList(L, L->begin);
}


/*
 *pop back
 */
void * popBack_SqList(SqList *L)
{
    return delete_SqList(L, L->end-1);
}
