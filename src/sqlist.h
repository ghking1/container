#ifndef SQLIST_H
#define SQLIST_H

#include <stddef.h>

#define bool int


typedef enum _TraverseAction_SqList
{
    SQLIST_CONTINUE,        //do nothing for current node
    SQLIST_DELETE_NODE,     //delete current node node
    SQLIST_STOP_TRAVERSE,   //stop traverse
    SQLIST_DELETE_AND_STOP  //delete current node and stop traverse
} TraverseAction_SqList;


typedef struct _SqListNode
{
    void *data;         //point to data
} SqListNode;


typedef struct _SqList
{
    SqListNode *first;  //point to the first node
    size_t size;        //size of list 
    size_t capacity;    //size of space
} SqList;


bool   setCapacity_SqList(SqList *L, const size_t capacity);  //set size of space
size_t getCapacity_SqList(const SqList *L);                   //return size of space

bool   init_SqList(SqList *L);               //initial it, successfully return true, failed return false
bool   clear_SqList(SqList *L);              //clear all node in it
bool   destroy_SqList(SqList *L);            //destroy it
bool   isEmpty_SqList(const SqList *L);      //is empty return true, else return false
size_t getSize_SqList(const SqList *L);      //return size of nodes

SqListNode* getFirst_SqList(const SqList *L);                            //return first node of it, return null if empty
SqListNode* getLast_SqList(const SqList *L);                             //return last node of it, return null if empty
SqListNode* getPrev_SqList(const SqList *L, const SqListNode *current);  //return prevElemet of it, return null if it's already the first
SqListNode* getNext_SqList(const SqList *L, const SqListNode *current);  //return nextElement of it, return null if it's already the last
SqListNode* getByOrd_SqList(const SqList *L, const size_t order);        //get node by order, return null if out of valid range
SqListNode* getByVal_SqList(const SqList *L, const void *data, int (*compare)(const void *data1, const void *data2));  //get node by value, return null if not found  

SqListNode* insert_SqList(SqList *L, SqListNode *current, const void *data2);  //insert before current node, return inserted node, return null if failed
void*       delete_SqList(SqList *L, SqListNode *current);                     //delete current node, return data of deleted node, return null if failed

SqListNode* pushFront_SqList(SqList *L, const void *data); //push front, return inserted node, return null if failed
SqListNode* pushBack_SqList(SqList *L, const void *data);  //push back, return inserted node, return null if failed
void*       popFront_SqList(SqList *L);                    //pop front, return data of deleted node, return null if failed
void*       popBack_SqList(SqList *L);                     //pop back, return data of deleted node, return null if failed

//traverse all node one by one, and pass every data to handler function point
void traverse_SqList(SqList *L, TraverseAction_SqList (*handler)(void *data));  

#undef bool

#endif
