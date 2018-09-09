
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
    HashTableElement **table;
    size_t bucket_size;
    size_t size;
} HashTable;

bool init_HashTable(HashTable *, size_t);
bool clear_HashTable(HashTable *);
bool destroy_HashTable(HashTable *);
bool isEmpty_HashTable(const HashTable *);
size_t getSize_HashTable(const HashTable *);

HashTableElement* get_HashTable(const HashTable *, const char *);
HashTableElement* set_HashTable(HashTable *, const char *, void *);
void* delete_HashTable(HashTable *, const char *);

void traverse_HashTable(HashTable *, bool (*)(const HashTableElement*));

#undef bool

#endif