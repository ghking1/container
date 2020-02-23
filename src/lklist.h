#ifndef LKLIST_H
#define LKLIST_H

#include <stddef.h>

#define bool int

typedef struct _LkListElement
{
    void *value_point;
    struct _LkListElement *prev;
    struct _LkListElement *next;
} LkListElement;

typedef struct _LkList
{
    LkListElement *head;    //point to the head, who is before first element
    LkListElement *tail;    //point to the tail, who is after last element
    size_t size;            //size of elements
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

LkListElement* getFirst_LkList(const LkList *L);                                //return first element of it, return null if empty
LkListElement* getLast_LkList(const LkList *L);                                 //return last element of it, return null if empty
LkListElement* getPrev_LkList(const LkList *L, const LkListElement *current);   //return prevElemet of it, return null if it's already the first
LkListElement* getNext_LkList(const LkList *L, const LkListElement *current);   //return nextElement of it, return null if it's already the last
LkListElement* getByOrd_LkList(const LkList *L, const size_t order);            //get element by order, return null if out of valid range
LkListElement* getByVal_LkList(const LkList *L, const void *value_point, int (*compare)(const void *value_point1, const void *value_point2));  //get element by value, return null if not found     

LkListElement* insert_LkList(LkList *L, LkListElement *current, const void *value_point);   //insert before current element, return inserted element, return null if failed
void* delete_LkList(LkList *L, LkListElement *current);        //delete current element, return value_point of deleted element, return null if failed
 
LkListElement* pushFront_LkList(LkList *L, const void *value_point); //push front, return inserted element, return null if failed
LkListElement* pushBack_LkList(LkList *L, const void *value_point);  //push back, return inserted element, return null if failed
void* popFront_LkList(LkList *L);                                    //pop front, return value_point of deleted element, return null if failed
void* popBack_LkList(LkList *L);                                     //pop back, return value_point of deleted element, return null if failed

//traverse all element one by one, and pass every value_point to handler function point
void traverse_LkList(LkList *L, TraverseAction_LkList (*handler)(void *value_point));  

#undef bool

#endif
