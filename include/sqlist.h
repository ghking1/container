#ifndef SQLIST_H
#define SQLIST_H

#include <stddef.h>

#define bool int

typedef struct _SqListElement
{
    void *valuePoint;
} SqListElement;

typedef struct _SqList
{
    SqListElement *begin;  //point to the first element
    SqListElement *end;    //point to the end, but not last element
    size_t capacity;       //size of space
} SqList;

typedef enum _TraverseAction_SqList
{
    DO_NOTHING_SQLIST,      //do nothing for current element
    DELETE_ELEMENT_SQLIST,  //delete current element node
    STOP_TRAVERSE_SQLIST,   //stop traverse
    DELETE_AND_STOP_SQLIST  //delete current element and stop traverse

} TraverseAction_SqList;

bool setCapacity_SqList(SqList *L, const size_t newCapacity);  //set size of space
size_t getCapacity_SqList(const SqList *L);  //return size of space

bool init_SqList(SqList *L);                 //initial it, successfully return true, failed return false
bool clear_SqList(SqList *L);                //clear all element in it
bool destroy_SqList(SqList *L);              //destroy it
bool isEmpty_SqList(const SqList *L);        //is empty return true, else return false
size_t getSize_SqList(const SqList *L);      //return size of elements

SqListElement* getBegin_SqList(const SqList *L);                                //return first element of it
SqListElement* getEnd_SqList(const SqList *L);                                  //return last element of it
SqListElement* getPrior_SqList(const SqList *L, const SqListElement *current);  //return priorElemet of it
SqListElement* getNext_SqList(const SqList *L, const SqListElement *current);   //return nextElement of it
SqListElement* getByNum_SqList(const SqList *L, const size_t number);           //get element by number
SqListElement* getByVal_SqList(const SqList *L, const void *valuePoint, int (*compare)(const void *valuePoint1, const void *valuePoint2));  //get element by value    

SqListElement* insert_SqList(SqList *L, const SqListElement *current, const void *valuePoint2);  //insert before current element
void* delete_SqList(SqList *L, const SqListElement *current);       //delete current element, return valuePobool of it

SqListElement* pushFront_SqList(SqList *L, const void *valuePoint); //push front
SqListElement* pushBack_SqList(SqList *L, const void *valuePoint);  //push back
void* popFront_SqList(SqList *L);                                   //pop front
void* popBack_SqList(SqList *L);                                    //pop back

//traverse all element one by one
void traverse_SqList(SqList *L, TraverseAction_SqList (*handler)(const void *valuePoint));  

#undef bool

#endif
