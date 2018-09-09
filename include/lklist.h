#ifndef LKLIST_H
#define LKLIST_H


#include <stddef.h>
#include "container.h"

#define bool int

typedef struct _LkListElement
{
    void *valuePoint;
    struct _LkListElement *prior;
    struct _LkListElement *next;
} LkListElement;

typedef struct _LkList
{
    LkListElement *head;   //point to the head, but not first element
    LkListElement *end;    //point to the last element
    size_t size;           //size of elements
} LkList;

bool init_LkList(LkList *);                //initial it, successfully return true, failed return false
bool clear_LkList(LkList *);               //clear all element in it
bool destroy_LkList(LkList *);             //destroy it
bool isEmpty_LkList(const LkList *);       //is empty return true, else return false
size_t getSize_LkList(const LkList *);     //return size of elements

LkListElement* getBegin_LkList(const LkList *);                                                         //return first element of it
LkListElement* getEnd_LkList(const LkList *);                                                           //return last element of it
LkListElement* getPrior_LkList(const LkList *, const LkListElement *);                                  //return priorElemet of it
LkListElement* getNext_LkList(const LkList *, const LkListElement *);                                   //return nextElement of it
LkListElement* getByNum_LkList(const LkList *, size_t);                                                 //get element by number
LkListElement* getByVal_LkList(const LkList *, const void *, int (const *)(const void*, const void*));  //get element by value    

LkListElement* insert_LkList(LkList *, const LkListElement *, const void *);   //insert before current element
void * delete_LkList(LkList *, const LkListElement *);                         //delete current element, return valuePoint of it

LkListElement* pushFront_LkList(LkList *, const void*);   //push front
LkListElement* pushBack_LkList(LkList *, const void*);    //push back
void * popFront_LkList(LkList*);                          //pop front
void * popBack_LkList(LkList*);                           //pop back

#undef bool

#endif
