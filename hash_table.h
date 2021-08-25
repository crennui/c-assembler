#ifndef HASH_TABLE
#define HASH_TABLE
#define BUCKETS_IN_TABLE 100

/*
This is a hash table implemantation I wanted to make to learn how 
hash tabels work, I look at decompiled code in java for the hash function
to make something simmilar. 

The hash table contains an array of entries and each entry is a linked list in case of collision in hash (not a perfect hash). 
*/
struct Entry {
    char * key; 
    void * value; 
    struct Entry * next; 
}; 
typedef struct Entry* Entry_p; 


struct HashTable
{
    Entry_p buckets [BUCKETS_IN_TABLE];
};
typedef struct HashTable* HashTable_p; 

/*Allocating new Hash table, returns NULL if failes*/
HashTable_p newHashTable(); 

/*Freeing all memory related to the hash table*/
void freeHashTable (HashTable_p hashTable_p);

/*Returns the void* value related to that key
  returns NULL if doesn't exist.*/
void * get(HashTable_p table, const char * key);

/*
Creates and appends new Entry with the given key value.
If key already exists it overrides the old value.  
*/
int put (HashTable_p table, const char* key, void * value);

/*
Removes a specific Entry according to it's key.  
returns 0 if succeded and -1 if key wasn't found.
*/
int removeEntry(HashTable_p table, const char* key);

#endif