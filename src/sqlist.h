#ifndef SQLIST_H
#define SQLIST_H

#include <stddef.h>

#define bool int

typedef struct _SqListElement
{
    void *value_point;
} SqListElement;

typedef struct _SqList
{
    SqListElement *first;  //point to the first element
    size_t size;           //size of list 
    size_t capacity;       //size of space
} SqList;

typedef enum _TraverseAction_SqList
{
    DO_NOTHING_SQLIST,      //do nothing for current element
    DELETE_ELEMENT_SQLIST,  //delete current element node
    STOP_TRAVERSE_SQLIST,   //stop traverse
    DELETE_AND_STOP_SQLIST  //delete current element and stop traverse

} TraverseAction_SqList;

bool setCapacity_SqList(SqList *L, const size_t capacity);  //set size of space
size_t getCapacity_SqList(const SqList *L);  //return size of space

bool init_SqList(SqList *L);                 //initial it, successfully return true, failed return false
bool clear_SqList(SqList *L);                //clear all element in it
bool destroy_SqList(SqList *L);              //destroy it
bool isEmpty_SqList(const SqList *L);        //is empty return true, else return false
size_t getSize_SqList(const SqList *L);      //return size of elements

SqListElement* getFirst_SqList(const SqList *L);                               //return first element of it, return null if empty
SqListElement* getLast_SqList(const SqList *L);                                //return last element of it, return null if empty
SqListElement* getPrev_SqList(const SqList *L, const SqListElement *current);  //return prevElemet of it, return null if it's already the first
SqListElement* getNext_SqList(const SqList *L, const SqListElement *current);  //return nextElement of it, return null if it's already the last
SqListElement* getByOrd_SqList(const SqList *L, const size_t order);           //get element by order, return null if out of valid range
SqListElement* getByVal_SqList(const SqList *L, const void *value_point, int (*compare)(const void *value_point1, const void *value_point2));  //get element by value, return null if not found  

SqListElement* insert_SqList(SqList *L, SqListElement *current, const void *value_point2);  //insert before current element, return inserted element, return null if failed
void* delete_SqList(SqList *L, SqListElement *current);       //delete current element, return value_point of deleted element, return null if failed

SqListElement* pushFront_SqList(SqList *L, const void *value_point); //push front, return inserted element, return null if failed
SqListElement* pushBack_SqList(SqList *L, const void *value_point);  //push back, return inserted element, return null if failed
void* popFront_SqList(SqList *L);                                    //pop front, return value_point of deleted element, return null if failed
void* popBack_SqList(SqList *L);                                     //pop back, return value_point of deleted element, return null if failed

//traverse all element one by one, and pass every value_point to handler function point
void traverse_SqList(SqList *L, TraverseAction_SqList (*handler)(void *value_point));  

#undef bool

#endif
