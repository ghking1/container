
#ifndef HASHTABLE_H
#define HASHTABLE_H 

#include <stddef.h>
#include "container.h"

#define bool int

typedef struct _HashTableElement
{
    char *key;
    void *valuePoint;
    struct _HashTableElement *next;
} HashTableElement;

typedef struct _HashTable
{
    HashTableElement **bucket;  //bucket is point to an array of (HashTableElement*)
    size_t bucket_size;         //size of bucket
    size_t size;                //size of elements
} HashTable;

bool init_HashTable(HashTable *, size_t);       //initial it, successfully return true, failed return false
bool clear_HashTable(HashTable *);              //clear all element in it
bool destroy_HashTable(HashTable *);            //destroy it
bool isEmpty_HashTable(const HashTable *);      //is empty return true, else return false
size_t getSize_HashTable(const HashTable *);    //return size of elements

HashTableElement* get_HashTable(const HashTable *, const char *);    //get element by key
HashTableElement* set_HashTable(HashTable *, const char *, void *);  //set element by key
void* delete_HashTable(HashTable *, const char *);                   //delete element by key

//handler function receive a HashTableElement point, and return true when it want to break
void traverse_HashTable(HashTable *, bool (*)(const HashTableElement*));  //traverse element one by one, but it is not same to insert sequence

#undef bool

#endif