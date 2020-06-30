#ifndef LKLIST_H
#define LKLIST_H

#include <stddef.h>

#define bool int


typedef enum _TraverseAction_LkList
{
    LKLIST_CONTINUE,        //continue to traverse
    LKLIST_DELETE_NODE,     //delete current node
    LKLIST_STOP_TRAVERSE,   //stop traverse
    LKLIST_DELETE_AND_STOP  //delete current node and stop traverse
} TraverseAction_LkList;


typedef struct _LkListNode
{
    void   *data;               //point to data
    struct _LkListNode *prev;   //point to previous node
    struct _LkListNode *next;   //point to next node
    struct _LinkList   *owner;  //point to the list who own this node
} LkListNode;


typedef struct _LkList
{
    LkListNode guard;   //guard node, guard.next point to first node, guard.prev point to last node
    size_t     size;    //size of nodes
} LkList;


bool   init_LkList(LkList *L);              //initial it, successfully return true, failed return false
bool   clear_LkList(LkList *L);             //clear all node in it
bool   destroy_LkList(LkList *L);           //destroy it
bool   isEmpty_LkList(const LkList *L);     //is empty return true, else return false
size_t getSize_LkList(const LkList *L);     //return size of nodes

LkListNode* getFirst_LkList(const LkList *L);                           //return first node of it, return null if empty
LkListNode* getLast_LkList(const LkList *L);                            //return last node of it, return null if empty
LkListNode* getPrev_LkList(const LkList *L, const LkListNode *current); //return prevElemet of it, return null if it's already the first
LkListNode* getNext_LkList(const LkList *L, const LkListNode *current); //return nextElement of it, return null if it's already the last
LkListNode* getByOrd_LkList(const LkList *L, const size_t order);       //get node by order, return null if out of valid range
LkListNode* getByVal_LkList(const LkList *L, const void *data, int (*compare)(const void *data1, const void *data2));  //get node by value, return null if not found     

LkListNode* insert_LkList(LkList *L, LkListNode *current, const void *data); //insert before current node, return inserted node, return null if failed
void*       delete_LkList(LkList *L, LkListNode *current);                   //delete current node, return data of deleted node, return null if failed
 
LkListNode* pushFront_LkList(LkList *L, const void *data);   //push front, return inserted node, return null if failed
LkListNode* pushBack_LkList(LkList *L, const void *data);    //push back, return inserted node, return null if failed
void*       popFront_LkList(LkList *L);                      //pop front, return data of deleted node, return null if failed
void*       popBack_LkList(LkList *L);                       //pop back, return data of deleted node, return null if failed

//traverse all node one by one, and pass every data to handler function point
void traverse_LkList(LkList *L, TraverseAction_LkList (*handler)(void *data));  

#undef bool

#endif
