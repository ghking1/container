#include <stdlib.h>
#include "../include/hashtable.h"

#define bool int
#define true 1
#define false 0

/*
 *bucket_size must >=1
 */
bool init_HashTable(HashTable *T, const size_t bucket_size)
{
    int i;

    if(T==NULL || bucket_size<1)
    {
        return false;
    }

    T->bucket_size=bucket_size;
    T->size=0;
    T->bucket=(HashTableElement**)malloc(sizeof(HashTableElement*)*bucket_size);

    for(i=0; i<bucket_size; ++i)
    {
        T->bucket[i]=NULL;  //all bucket has no element when init
    }
    return true;
}


/*
 *clear all element in hashtable, you must handle all value_point in it yourself before clear it
 */
bool clear_HashTable(HashTable *T)
{
    int i;

    if(T==NULL)
    {
        return false;
    }

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


/*
 *destroy hashtable, you must handle all value_point in it yourself before clear it
 */
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


/*
 *return true if it is empty
 */
bool isEmpty_HashTable(const HashTable *T)
{
    if(T==NULL)
    {
        return false;
    }

    return T->size == 0 ? true : false;
}


/*
 *return size of it
 */
size_t getSize_HashTable(const HashTable *T)
{
    if(T==NULL)
    {
        return false;
    }

    return T->size;
}


/*
 *caculate str hash 
 */
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


/*
 *get hashelement by key
 */
HashTableElement* get_HashTable(const HashTable *T, const char *K)
{
    size_t index = BKDRHash(K) % T->bucket_size;
    HashTableElement *current=NULL;

    if(T==NULL || K==NULL)
    {
        return false;
    }

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


/*
 *set hashvalue by key
 */
HashTableElement* set_HashTable(HashTable *T, const char *K, void *value_point)
{
    size_t index = BKDRHash(K) % T->bucket_size;
    HashTableElement *current = NULL;
    HashTableElement *E = NULL;

    if(T==NULL || K==NULL)
    {
        return false;
    }

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
        current->value_point=value_point;
        return current;
    }
    else               //create new HashTableElement
    {
        E=(HashTableElement*)malloc(sizeof(HashTableElement));
        E->key=(char*)malloc(sizeof(char)*strlen(K));
        strcpy(E->key, K);          //use key copy, but not reference
        E->value_point=value_point;   
        E->next=T->bucket[index];   //put new element in the first place of key mapped bucket
        T->bucket[index]=E;         //bucket first element point to this new element
        ++(T->size);
        return E;
    }
}


/*
 *delete hashelement by key
 */
void* delete_HashTable(HashTable *T, const char *K)
{
    size_t index = BKDRHash(K) % T->bucket_size;
    HashTableElement *previous=NULL, *current=NULL;
    void *value_point = NULL;

    if(T==NULL || K==NULL)
    {
        return false;
    }

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
        value_point=current->value_point;
        if(previous!=NULL)  //finded element not in the first place
        {
            previous->next=current->next;
        }
        else                //finded element is the first element of key mapped bucket
        {
            T->bucket[index]=current->next;
        }
        --(T->size);
        free(current);
        return value_point;
    }
    else
    {
        return NULL;
    }
}


/*
 *traverse hashelement one by one, but element order is not same to insert order
 */
void traverse_HashTable(HashTable *T, TraverseAction_HashTable (*handler)(const void *value_point))
{
    int i;
    TraverseAction_HashTable action;
    HashTableElement *previous=NULL, *current=NULL;

    if(T==NULL)
    {
        return;
    }

    for(i=0; i<T->bucket_size; ++i)
    {
        if(T->bucket[i]!=NULL)
        {
            previous = NULL;
            for(current=T->bucket[i]; current!=NULL; /*none*/)
            {
                action=handler(current->value_point);
                switch(action)
                {
                case DO_NOTHING_HASHTABLE:    
                    previous = current;
                    current = current->next;
                    break;
                case DELETE_ELEMENT_HASHTABLE:
                    if(previous!=NULL)  //current element not in the first place
                    {
                        previous->next=current->next;
                        free(current);
                        current = previous->next;
                    }
                    else                //finded element is the first element of key mapped bucket
                    {
                        T->bucket[i]=current->next;
                        free(current);
                        current = T->bucket[i];
                    }
                    --(T->size);
                    break;
                case STOP_TRAVERSE_HASHTABLE: 
                    return;
                case DELETE_AND_STOP_HASHTABLE:                    
                    if(previous!=NULL)  //current element not in the first place
                    {
                        previous->next=current->next;
                        free(current);
                        current = previous->next;
                    }
                    else                //finded element is the first element of key mapped bucket
                    {
                        T->bucket[i]=current->next;
                        free(current);
                        current = T->bucket[i];
                    }
                    --(T->size);
                    return;
                }
            }
        }
    }
}
