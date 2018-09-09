
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
    T->bucket=(HashTableElement**)malloc(sizeof(HashTableElement*)*bucket_size);

    int i;
    for(i=0; i<bucket_size; ++i)
    {
        T->bucket[i]=NULL;  //all bucket has no element when init
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
        if(T->bucket[i]!=NULL)
        {
            HashTableElement *previous=NULL, *current=NULL;
            for(current=T->bucket[i]; current!=NULL; /*none*/)
            {
                previous=current;
                current=current->next;
                free(previous->key);  //key is copyed when set element, so it should be free by this library
                free(previous);
            }
            T->bucket[i]=NULL;
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

    clear_HashTable(T); //first free elements
    free(T->bucket);    //then free bucket

    T->bucket=NULL;
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
    if(T->bucket[index]!=NULL)  //search the key mapped bucket by strcmp
    {
        for(current=T->bucket[index]; current!=NULL; current=current->next)
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
    if(T->bucket[index]!=NULL)
    {
        for(current=T->bucket[index]; current!=NULL; current=current->next)
        {
            if(strcmp(K, current->key)==0)
            {
                break;
            }
        }
    }

    if(current!=NULL)  //key is exist, so change it's value directly
    {
        current->valuePoint=valuePoint;
        return current;
    }
    else               //create new HashTableElement
    {
        HashTableElement *E=(HashTableElement*)malloc(sizeof(HashTableElement));
        E->key=(char*)malloc(sizeof(char)*strlen(K));
        strcpy(E->key, K);          //use key copy, but not reference
        E->valuePoint=valuePoint;   
        E->next=T->bucket[index];   //put new element in the first place of key mapped bucket
        T->bucket[index]=E;         //bucket first element point to this new element
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
    if(T->bucket[index]!=NULL)
    {
        for(current=T->bucket[index]; current!=NULL; /*none*/)
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
        if(previous!=NULL)  //finded element not in the first place
        {
            previous->next=current->next;
        }
        else                //finded element is the first element of key mapped bucket
        {
            T->bucket[index]=current->next;
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
        if(T->bucket[i]!=NULL)
        {
            HashTableElement *current=NULL;
            for(current=T->bucket[i]; current!=NULL; current=current->next)
            {
                stop=handler(current);  //if handler return true, break traverse
                if(stop)
                {
                    return;
                }
            }
        }
    }
}
