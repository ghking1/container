#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

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
    T->bucket=(HashTableNode**)malloc(sizeof(HashTableNode*)*bucket_size);

    for(i=0; i<bucket_size; ++i)
    {
        T->bucket[i]=NULL;  //all bucket has no node when init
    }
    return true;
}


/*
 *clear all node in hashtable, you must handle all data in it yourself before clear it
 */
bool clear_HashTable(HashTable *T)
{
    int i;
    HashTableNode *previous=NULL, *current=NULL;

    if(T==NULL)
    {
        return false;
    }

    for(i=0; i<T->bucket_size; ++i)
    {
        if(T->bucket[i]!=NULL)
        {
            previous = NULL;
            for(current=T->bucket[i]; current!=NULL; /*none*/)
            {
                previous=current;
                current=current->next;
                free(previous->key);  //key is copyed when set node, so it should be free by this library
                free(previous);
            }
            T->bucket[i]=NULL;
        }
    }
    T->size=0;
    return true;
}


/*
 *destroy hashtable, you must handle all data in it yourself before clear it
 */
bool destroy_HashTable(HashTable *T)
{
    if(T==NULL)
    {
        return false;
    }

    clear_HashTable(T); //first free nodes
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
        //equal to hash = hash << 7 + hash << 1 + hash + c;
        hash = hash*131 + c;   
    }
    
    return hash;
}


/*
 *get hashnode by key
 */
HashTableNode* get_HashTable(const HashTable *T, const char *K)
{
    size_t index = BKDRHash(K) % T->bucket_size;
    HashTableNode *current=NULL;

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
HashTableNode* set_HashTable(HashTable *T, const char *K, const void *data)
{
    size_t index = BKDRHash(K) % T->bucket_size;
    HashTableNode *current = NULL;
    HashTableNode *E = NULL;

    if(T==NULL || K==NULL)
    {
        return NULL;
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

    if(current!=NULL)  
    {
        //key is exist, user must delete it manually first
        //because cover data directly may cause memory leak
        return NULL;
    }
    else 
    {
        //create new HashTableElement
        E=(HashTableNode*)malloc(sizeof(HashTableNode));
        E->key=(char*)malloc(sizeof(char)*strlen(K)+1);
        strcpy(E->key, K);          //use key copy, but not reference
        E->data=(void*)data;   
        E->next=T->bucket[index];   //put new node in the first place of key mapped bucket
        T->bucket[index]=E;         //bucket first node point to this new node
        ++(T->size);
        return E;
    }
}


/*
 *delete hashnode by key
 */
void* del_HashTable(HashTable *T, const char *K)
{
    size_t index = BKDRHash(K) % T->bucket_size;
    HashTableNode *previous=NULL, *current=NULL;
    void *data = NULL;

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
        data=current->data;
        if(previous!=NULL)  //finded node not in the first place
        {
            previous->next=current->next;
        }
        else                //finded node is the first node of key mapped bucket
        {
            T->bucket[index]=current->next;
        }
        free(current->key);
        free(current);
        --(T->size);
        return data;
    }
    else
    {
        return NULL;
    }
}


/*
 *traverse hashnode one by one, but node order is not same to insert order
 */
void traverse_HashTable(HashTable *T, TraverseAction_HashTable (*handler)(char* key, void *data))
{
    int i;
    TraverseAction_HashTable action;
    HashTableNode *previous=NULL, *current=NULL;

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
                action=handler(current->key, current->data);
                switch(action)
                {
                case HASHTABLE_CONTINUE:    
                    previous = current;
                    current = current->next;
                    break;
                case HASHTABLE_DELETE_NODE:
                    if(previous!=NULL)  //current node not in the first place
                    {
                        previous->next=current->next;
                        free(current->key);
                        free(current);
                        current = previous->next;
                    }
                    else                //finded node is the first node of key mapped bucket
                    {
                        T->bucket[i]=current->next;
                        free(current->key);
                        free(current);
                        current = T->bucket[i];
                    }
                    --(T->size);
                    break;
                case HASHTABLE_STOP_TRAVERSE: 
                    return;
                case HASHTABLE_DELETE_AND_STOP:                    
                    if(previous!=NULL)  //current node not in the first place
                    {
                        previous->next=current->next;
                        free(current->key);
                        free(current);
                        current = previous->next;
                    }
                    else                //finded node is the first node of key mapped bucket
                    {
                        T->bucket[i]=current->next;
                        free(current->key);
                        free(current);
                        current = T->bucket[i];
                    }
                    --(T->size);
                    return;
                default:
                    return;
                }
            }
        }
    }
}
