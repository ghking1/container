#include <stdlib.h>
#include "lklist.h"

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

    L->guard.data  = NULL;
    L->guard.next  = &L->guard;
    L->guard.prev  = &L->guard;
    L->guard.owner = L;

    L->size=0;

    return true;
}


/*
 *clear all node in it, you must handle all data in it yourself before clear it
 */
bool clear_LkList(LkList *L)                
{
    LkListNode *previous=NULL, *current=NULL;//release all node excluding head and tail

    if(L==NULL)    //L==NULL, is invalid
    { 
        return false;
    }    

    for(current=L->guard.next; current!=&L->guard; /*none*/)
    {
        previous=current;
        current=current->next;
        free(previous);
    }
    
    L->guard.next  = &L->guard; //head point's next point pointed to NULL
    L->guard.prev  = &L->guard; //head and last point to head
    L->size=0;

    return true;
}


/*
 *destroy it, you must handle all data in it yourself before clear it
 */
bool destroy_LkList(LkList *L)                
{
    if(L==NULL)    //L==NULL, is invalid
    { 
        return false;
    }    

    clear_LkList(L); //first free all node

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
 *return size of nodes
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
 * some error,like:can't find your node or can't insert/delete    *
 * your node.why? maybe you give an position out of range or other*
 * problems.                                                         *
 *********************************************************************/

/*
 *return first node of it
 */
LkListNode* getFirst_LkList(const LkList *L)                                                                        
{
    if(L==NULL)    //L==NULL, is invalid
    { 
        return NULL;
    }    

    if(L->size == 0)
    {
        return NULL;
    }

    return L->guard.next;
}


/*
 *return last node of it
 */
LkListNode* getLast_LkList(const LkList *L)
{
    if(L==NULL)    //L==NULL, is invalid
    { 
        return NULL;
    }    

    if(L->size == 0)
    {
        return NULL;
    }

    return L->guard.prev;
}    


/*
 *return prevElemet of it
 */
LkListNode* getPrev_LkList(const LkList *L, const LkListNode *current)
{
    if(L==NULL)    //NULL, is invalid
    { 
        return NULL;
    }    

    if(current==NULL || L->size==0 || current==L->guard.next)    //head node has no prev node
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
LkListNode* getNext_LkList(const LkList *L, const LkListNode *current)                                            
{
    if(L==NULL)    //NULL, is invalid
    { 
        return NULL;
    }    

    if(current==NULL || L->size==0 || current==L->guard.prev)    //last node has no next node
    {
        return NULL;
    }
    else
    {
        return current->next;
    }
}


/*
 *get node by order
 */
LkListNode* getByOrd_LkList(const LkList *L, const size_t order)                                                    
{
    LkListNode *p=NULL; 
    size_t i=0;

    if(L==NULL)    //L==NULL is invalid or order is not in range
    { 
        return NULL;
    }    

    if(L->size==0 || order<=0 || order>L->size)
    {
        return NULL;
    }

    p=&L->guard;
    while(i<order)
    {
        p=p->next;
        ++i;
    }

    return p;
}


/*
 *get node by value
 */
LkListNode* getByVal_LkList(const LkList *L, const void *data, int (*compare)(const void *data1, const void *data2))
{
    LkListNode *p=NULL;

    if(L==NULL)    //NULL, is invalid
    { 
        return NULL;
    }    

    if(L->size==0 || data==NULL || compare==NULL)
    {
        return NULL;
    }

    for(p=L->guard.next; p!=&L->guard; p=p->next)       //find from first node
    {
        if(compare(p->data, data)==0)    //equal then stop
        {
            break;
        }
    }

    return p==&L->guard ? NULL : p;
}    


/*
 *insert before current node
 */
LkListNode* insert_LkList(LkList *L, LkListNode *current, const void *data)
{
    LkListNode *p = NULL;

    if(L==NULL )    //NULL, is invalid
    { 
        return NULL;
    }    
    
    if(current==NULL || data==NULL)
    {
        return NULL;
    }

    p=(LkListNode *)malloc(sizeof(LkListNode));
    if(p==NULL)
    {
        return NULL;
    }
    
    p->data=(void*)data;  //point to value

    p->next=current;    //change points
    p->prev=current->prev;
    current->prev->next=p;
    current->prev=p;
    
    ++(L->size);

    return p;
}                            


/*
 *delete current node, return data of it
 */
void* delete_LkList(LkList *L, LkListNode *current)
{
    void *data=NULL;    

    if(L==NULL || L->size==0 || current==NULL)   //NULL, is invalid
    { 
        return NULL;
    }    

    data = current->data; //save data

    current->prev->next=current->next; //change points
    current->next->prev=current->prev;

    free(current);

    --(L->size);

    return data;
}    


/*
 *push front
 */
LkListNode* pushFront_LkList(LkList *L, const void *data)                                                        
{
    return insert_LkList(L, L->guard.next, data);
}


/*
 *push back
 */
LkListNode* pushBack_LkList(LkList *L, const void *data)                                                        
{
    return insert_LkList(L, &L->guard, data);
}


/*
 *pop front
 */
void* popFront_LkList(LkList *L)    
{    
    return delete_LkList(L, L->guard.next);
}


/*
 *pop back
 */
void* popBack_LkList(LkList *L)                                                                                        
{
    return delete_LkList(L, L->guard.prev);
}


/*
 *traverse node one by one
 */
void traverse_LkList(LkList *L, TraverseAction_LkList (*handler)(void *data))
{
    LkListNode *previous=NULL, *current=NULL;
    TraverseAction_LkList action;

    if(L==NULL)
    {
        return;
    }

    previous = &L->guard;
    for(current=L->guard.next; current!=&L->guard; /*none*/)  //find from first node
    {
        action=handler(current->data);
        switch(action)
        {
        case LKLIST_CONTINUE:    
            previous = current;
            current = current->next;
            break;
        case LKLIST_DELETE_NODE:
            current->prev->next=current->next; 
            current->next->prev=current->prev;
            --(L->size);
            free(current);
            current=previous->next;
            break;
        case LKLIST_STOP_TRAVERSE: 
            return;
        case LKLIST_DELETE_AND_STOP:                    
            current->prev->next=current->next; 
            current->next->prev=current->prev;
            --(L->size);
            free(current);
            current=previous->next;
            return;
        default:
            return;
        }
    }
}
