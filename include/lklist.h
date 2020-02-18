#ifndef LKLIST_H
#define LKLIST_H

#include <stddef.h>

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
    LkListElement *end;    //point to the end, but not last element
    size_t size;           //size of elements
} LkList;

typedef enum _TraverseAction_LkList
{
    DO_NOTHING_LKLIST,      //do nothing for current element
    DELETE_ELEMENT_LKLIST,  //delete current element node
    STOP_TRAVERSE_LKLIST,   //stop traverse
    DELETE_AND_STOP_LKLIST  //delete current element and stop traverse

} TraverseAction_LkList;

bool init_LkList(LkList *L);                //initial it, successfully return true, failed return false
bool clear_LkList(LkList *L);               //clear all element in it
bool destroy_LkList(LkList *L);             //destroy it
bool isEmpty_LkList(const LkList *L);       //is empty return true, else return false
size_t getSize_LkList(const LkList *L);     //return size of elements

LkListElement* getBegin_LkList(const LkList *L);                                //return first element of it
LkListElement* getEnd_LkList(const LkList *L);                                  //return last element of it
LkListElement* getPrior_LkList(const LkList *L, const LkListElement *current);  //return priorElemet of it
LkListElement* getNext_LkList(const LkList *L, const LkListElement *current);   //return nextElement of it
LkListElement* getByNum_LkList(const LkList *L, const size_t number);           //get element by number
LkListElement* getByVal_LkList(const LkList *L, const void *valuePoint, int (*compare)(const void *valuePoint1, const void *valuePoint2));  //get element by value    

LkListElement* insert_LkList(LkList *L, const LkListElement *current, const void *valuePoint);   //insert before current element
void* delete_LkList(LkList *L, const LkListElement *current);       //delete current element, return valuePoint of it
 
LkListElement* pushFront_LkList(LkList *L, const void *valuePoint); //push front
LkListElement* pushBack_LkList(LkList *L, const void *valuePoint);  //push back
void* popFront_LkList(LkList *L);                                   //pop front
void* popBack_LkList(LkList *L);                                    //pop back

//traverse all element one by one
void traverse_LkList(LkList *L, TraverseAction_LkList (*handler)(const void *valuePoint));  

#undef bool

#endif
