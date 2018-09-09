
#include <stdlib.h>
#include <string.h>
#include "../include/hashtable.h"

#define bool int
#define true 1
#define false 0

bool init_HashTable(HashTable *T, size_t bucket_size)
{
    if(T==NULL)
    {
        return false;
    }

    T->bucket_size=bucket_size;
    T->size=0;
    T->table=(HashTableElement**)malloc(sizeof(HashTableElement*)*bucket_size);

    int i;
    for(i=0; i<bucket_size; ++i)
    {
        T->table[i]=NULL;
    }
    return true;
}

bool clear_HashTable(HashTable *T)
{
    if(T==NULL)
    {
        return false;
    }

    int i;
    for(i=0; i<T->bucket_size; ++i)
    {
        if(T->table[i]!=NULL)
        {
            HashTableElement *previous=NULL, *current=NULL;
            for(current=T->table[i]; current!=NULL; /*none*/)
            {
                previous=current;
                current=current->next;
                free(previous->key);
                free(previous);
            }
            T->table[i]=NULL;
        }
    }
    T->size=0;
    return true;
}

bool destroy_HashTable(HashTable *T)
{
    if(T==NULL)
    {
        return false;
    }

    int i;
    for(i=0; i<T->bucket_size; ++i)
    {
        if(T->table[i]!=NULL)
        {
            HashTableElement *previous=NULL, *current=NULL;
            for(current=T->table[i]; current!=NULL; /*none*/)
            {
                previous=current;
                current=current->next;
                free(previous->key);
                free(previous);
            }
            T->table[i]=NULL;
        }
    }
    free(T->table);

    T->table=NULL;
    T->bucket_size=0;
    T->size=0;

    return true;
}

bool isEmpty_HashTable(const HashTable *T)
{
    if(T==NULL)
    {
        return false;
    }

    return T->size == 0 ? true : false;
}

size_t getSize_HashTable(const HashTable *T)
{
    if(T==NULL)
    {
        return false;
    }

    return T->size;
}

size_t BKDRHash(const char *S)
{
    size_t hash=0;
    size_t c;
    while(c=(size_t)*S++)
    {
        hash = hash*131 + c;   
        //equal to hash = hash << 7 + hash << 1 + hash + c;
    }
}

HashTableElement* get_HashTable(const HashTable *T, const char *K)
{
    if(T==NULL || K==NULL)
    {
        return false;
    }

    size_t index = BKDRHash(K) % T->bucket_size;
    HashTableElement *current=NULL;
    if(T->table[index]!=NULL)
    {
        for(current=T->table[index]; current!=NULL; current=current->next)
        {
            if(strcmp(K, current->key)==0)
            {
                break;
            }
        }
    }
    return current;
}

HashTableElement* set_HashTable(HashTable *T, const char *K, void *valuePoint)
{
    if(T==NULL || K==NULL)
    {
        return false;
    }

    size_t index = BKDRHash(K) % T->bucket_size;
    HashTableElement *current=NULL;
    if(T->table[index]!=NULL)
    {
        for(current=T->table[index]; current!=NULL; current=current->next)
        {
            if(strcmp(K, current->key)==0)
            {
                break;
            }
        }
    }

    if(current!=NULL)
    {
        current->valuePoint=valuePoint;
        return current;
    }
    else
    {
        HashTableElement *E=(HashTableElement*)malloc(sizeof(HashTableElement));
        E->key=(char*)malloc(sizeof(char)*strlen(K));
        strcpy(E->key, K);
        E->valuePoint=valuePoint;
        E->next=T->table[index];
        T->table[index]=E;
        ++(T->size);
        return E;
    }
}

void* delete_HashTable(HashTable *T, const char *K)
{
    if(T==NULL || K==NULL)
    {
        return false;
    }

    size_t index = BKDRHash(K) % T->bucket_size;
    HashTableElement *previous=NULL, *current=NULL;
    if(T->table[index]!=NULL)
    {
        for(current=T->table[index]; current!=NULL; /*none*/)
        {
            if(strcmp(K, current->key)==0)
            {
                break;
            }
            previous=current;
            current=current->next;
        }
    }

    if(current!=NULL)
    {
        void *valuePoint=current->valuePoint;
        if(previous!=NULL)
        {
            previous->next=current->next;
        }
        else
        {
            T->table[index]=current->next;
        }
        --(T->size);
        return valuePoint;
    }
    else
    {
        return NULL;
    }
}

void traverse_HashTable(HashTable *T, bool (*handler)(const HashTableElement*))
{
    if(T==NULL)
    {
        return;
    }

    int i;
    bool stop;
    for(i=0; i<T->bucket_size; ++i)
    {
        if(T->table[i]!=NULL)
        {
            HashTableElement *current=NULL;
            for(current=T->table[i]; current!=NULL; current=current->next)
            {
                stop=handler(current);
                if(stop)
                {
                    return;
                }
            }
        }
    }
}