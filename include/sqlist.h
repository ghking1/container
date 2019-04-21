#ifndef SQLIST_H
#define SQLIST_H

#include <stddef.h>
#include "container.h"

#define bool int

typedef struct _SqListElement
{
    void *valuePoint;
} SqListElement;

typedef struct _SqList
{
    SqListElement *begin;  //pobool to the first element
    SqListElement *end;    //pobool to the tail
    size_t capacity;       //size of space
} SqList;

bool setCapacity_SqList(SqList *, size_t);  //set size of space
size_t getCapacity_SqList(const SqList *);  //return size of space

bool init_SqList(SqList *);                 //initial it, successfully return true, failed return false
bool clear_SqList(SqList *);                //clear all element in it
bool destroy_SqList(SqList *);              //destroy it
bool isEmpty_SqList(const SqList *);        //is empty return true, else return false
size_t getSize_SqList(const SqList *);      //return size of elements

SqListElement* getBegin_SqList(const SqList *);                                                         //return first element of it
SqListElement* getEnd_SqList(const SqList *);                                                           //return last element of it
SqListElement* getPrior_SqList(const SqList *, const SqListElement *);                                  //return priorElemet of it
SqListElement* getNext_SqList(const SqList *, const SqListElement *);                                   //return nextElement of it
SqListElement* getByNum_SqList(const SqList *, size_t);                                                 //get element by number
SqListElement* getByVal_SqList(const SqList *, const void *, int (*)(const void*, const void*));  //get element by value    

SqListElement* insert_SqList(SqList *, const SqListElement *, const void *);  //insert before current element
void * delete_SqList(SqList *, const SqListElement *);                        //delete current element, return valuePobool of it

SqListElement* pushFront_SqList(SqList *, const void*); //push front
SqListElement* pushBack_SqList(SqList *, const void*);  //push back
void * popFront_SqList(SqList*);                        //pop front
void * popBack_SqList(SqList*);                         //pop back

#undef bool

#endif
