#include <stdlib.h>
#include "sqlist.h"

#define CAPACITY_DEFAULT      32 
#define CAPACITY_LINE_1       128
#define CAPACITY_LINE_2       1024
#define CAPACITY_INCREASEMENT 1024

#define bool int
#define true 1
#define false 0

/*
 *adjust capacity of SqList, if appoint new_capacity==0 the new_capacity will be caculate autoly, otherwise it will use it directly
 */
bool reAllocate(SqList* L, const size_t capacity)
{
    SqListNode *temp;
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
    L->first=(SqListNode*)realloc(L->first, new_capacity*sizeof(SqListNode));    //relloc new memory space
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
 *clear all node in it, you must handle all data in it yourself before clear it
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
 *destroy it, you must handle all data in it yourself before clear it
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
 *return size of nodes
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
 * some error,like:can't find your node or can't insert/delete    *
 * your node.why? maybe you give an position out of range or other*
 * problems.                                                         *
 *********************************************************************/

/*
 *return first node of it
 */
SqListNode* getFirst_SqList(const SqList *L)                                                                        
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
 *return last node of it
 */
SqListNode* getLast_SqList(const SqList *L)                                                                        
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
SqListNode* getPrev_SqList(const SqList *L, const SqListNode *current)                                            
{
    if(L==NULL)    //NULL, is invalid
    { 
        return NULL;
    }    

    if(current==NULL || L->size==0 || current==L->first) //first node has no prev node
    {
        return NULL;
    }
    else
    {
        return (SqListNode*)current-1;
    }
}


/*
 *return nextElement of it
 */
SqListNode* getNext_SqList(const SqList *L, const SqListNode *current)                                            
{
    if(L==NULL)    //NULL, is invalid
    { 
        return NULL;
    }    

    if(current==NULL || L->size==0 || current >= (L->first + (L->size -1)))  //last node has no next node
    {
        return NULL;
    }
    else
    {
        return (SqListNode*)current+1;
    }
}


/*
 *get node by order
 */
SqListNode* getByOrd_SqList(const SqList *L, const size_t order)
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
 *get node by value
 */
SqListNode* getByVal_SqList(const SqList *L, const void *data, int (*compare)(const void *data1, const void *data2))
{
    int i;

    if(L==NULL)    //NULL, is invalid
    { 
        return NULL;
    }    

    if(L->size==0 || data==NULL || compare==NULL)
    {
        return NULL;
    }

    for(i=0; i<L->size; ++i)    //search from L->first
    {
        if(compare((L->first+i)->data, data)==0)    //when two value equals, stop!
        {
            return L->first+i;
        }
    }
    
    return NULL;
}    


/*
 *insert before current node
 */
SqListNode* insert_SqList(SqList *L, SqListNode *current, const void *data)
{
    SqListNode *p=NULL;                    
    size_t current_offset;

    if(L==NULL)    //NULL, is invalid
    { 
        return NULL;
    }    

    if(current==NULL || data==NULL)
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

    //move all nodes after current one step, including current
    for(p=(L->first + L->size); p!=current; --p)
    {
        *p=*(p-1);
    }
    
    p->data=(void *)data;        //const point transmit to normal
    ++(L->size);

    return p;
}


/*
 *delete current node, return data of it
 */
void* delete_SqList(SqList *L, SqListNode *current)    
{
    void *data=NULL;
    SqListNode *p=NULL;                    

    if(L==NULL || L->size==0 || current==NULL)   //NULL, is invalid
    { 
        return NULL;
    }    

    data = current->data; //save data 

    //move all nodes after current forward, excluding current
    for(p=current; p!=(L->first + (L->size - 1)); ++p)    //here need do an force type transform: from const to normal!
    {
        *p=*(p+1);
    }

    --(L->size);

    return data;
}    


/*
 *push front
 */
SqListNode* pushFront_SqList(SqList *L, const void *data)
{
    return insert_SqList(L, L->first, data);
}


/*
 *push back
 */
SqListNode* pushBack_SqList(SqList *L, const void *data)
{
    return insert_SqList(L, L->first + L->size, data);
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
 *traverse node one by one
 */
void traverse_SqList(SqList *L, TraverseAction_SqList (*handler)(void *data))
{
    SqListNode *p=NULL;
    SqListNode *previous=NULL, *current=NULL;
    TraverseAction_SqList action;

    if(L==NULL)
    {
        return;
    }

    previous = NULL;
    for(current=L->first; current!=(L->first + L->size); /*none*/)    //search from L->first
    {
        action=handler(current->data);
        switch(action)
        {
        case SQLIST_CONTINUE:    
            ++current;
            break;
        case SQLIST_DELETE_NODE:
            for(p=current; p!=(L->first + (L->size - 1)); ++p)
            {
                *p=*(p+1);
            }
            --(L->size);
            break;
        case SQLIST_STOP_TRAVERSE: 
            return;
        case SQLIST_DELETE_AND_STOP:                    
            for(p=current; p!=(L->first + (L->size - 1)); ++p)
            {
                *p=*(p+1);
            }
            --(L->size);
            return;
        default:
            return;
        }
    }
}
