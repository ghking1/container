#ifndef HASHTABLE_H
#define HASHTABLE_H 

#include <stddef.h>

#define bool int


typedef enum _TraverseAction_HashTable
{
    HASHTABLE_CONTINUE,         //do nothing for current node
    HASHTABLE_DELETE_NODE,      //delete current node node
    HASHTABLE_STOP_TRAVERSE,    //stop traverse
    HASHTABLE_DELETE_AND_STOP   //delete current node and stop traverse
} TraverseAction_HashTable;


typedef struct _HashTableNode
{
    char *key;                    //hash key
    void *data;                   //point to data
    struct _HashTableNode *next;  //point to next node
} HashTableNode;


typedef struct _HashTable
{
    HashTableNode **bucket;  //bucket is point to an array of (HashTableElement*)
    size_t bucket_size;      //size of bucket
    size_t size;             //size of nodes
} HashTable;


bool   init_HashTable(HashTable *T, const size_t bucket_size); //initial it, successfully return true, failed return false
bool   clear_HashTable(HashTable *T);                          //clear all node in it
bool   destroy_HashTable(HashTable *T);                        //destroy it
bool   isEmpty_HashTable(const HashTable *T);                  //is empty return true, else return false
size_t getSize_HashTable(const HashTable *T);                  //return size of nodes

HashTableNode* get_HashTable(const HashTable *T, const char *K);             //get node by key, return null if key not found
HashTableNode* set_HashTable(HashTable *T, const char *K, const void *data); //set node by key, return null if failed
void*          del_HashTable(HashTable *T, const char *K);                   //delete node by key, return null if failed

//traverse all node one by one, but node order is not same to insert order 
void traverse_HashTable(HashTable *T, TraverseAction_HashTable (*handler)(char* key, void *data));  

#undef bool

#endif