#ifndef HASHTABLE_H
#define HASHTABLE_H 

#include <stddef.h>

#define bool int

typedef struct _HashTableElement
{
    char *key;
    void *value_point;
    struct _HashTableElement *next;
} HashTableElement;

typedef struct _HashTable
{
    HashTableElement **bucket;  //bucket is point to an array of (HashTableElement*)
    size_t bucket_size;         //size of bucket
    size_t size;                //size of elements
} HashTable;

typedef enum _TraverseAction_HashTable
{
    DO_NOTHING_HASHTABLE,      //do nothing for current element
    DELETE_ELEMENT_HASHTABLE,  //delete current element node
    STOP_TRAVERSE_HASHTABLE,   //stop traverse
    DELETE_AND_STOP_HASHTABLE  //delete current element and stop traverse

} TraverseAction_HashTable;

bool init_HashTable(HashTable *T, const size_t bucket_size); //initial it, successfully return true, failed return false
bool clear_HashTable(HashTable *T);                          //clear all element in it
bool destroy_HashTable(HashTable *T);                        //destroy it
bool isEmpty_HashTable(const HashTable *T);                  //is empty return true, else return false
size_t getSize_HashTable(const HashTable *T);                //return size of elements

HashTableElement* get_HashTable(const HashTable *T, const char *K);             //get element by key
HashTableElement* set_HashTable(HashTable *T, const char *K, const void *value_point); //set element by key
void* delete_HashTable(HashTable *T, const char *K);                            //delete element by key

//traverse all element one by one, but element order is not same to insert order 
void traverse_HashTable(HashTable *T, TraverseAction_HashTable (*handler)(char* key, void *value_point));  

#undef bool

#endif