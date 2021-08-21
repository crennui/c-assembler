#include <string.h>
#include "hash_table.h"
#include <stdlib.h>



unsigned int hash (const char* key) {
    unsigned long int hash = 0; 
    size_t i = 0; 

    while (key[i] != '\0'){
        /*
        I looked at one of the java decompiled hash functions on string 
        and used the same logic. 31 was chosen because he's an odd prime number.  
        */
        hash = hash * 31 + key[i]; 
        i++;
    }
    return hash; 
}

unsigned int getBucketIndex (const char* key){
    return hash(key) % BUCKETS_IN_TABLE;  
}


Entry_p newEntry(const char* key, void * value, Entry_p next){
    Entry_p entry = malloc(sizeof(struct Entry));
    if (entry == NULL){return NULL;}
    entry -> key = malloc(sizeof(char)* strlen(key)+1);
    if (entry -> key == NULL){ free(entry); return NULL;}
    strcpy(entry -> key, key); 
    entry -> value = value; 
    entry -> next = next;
    return entry; 
}

void freeEntry(Entry_p entry){
    if (entry != NULL){
        free(entry -> key);
        free(entry);
    }
}

HashTable_p newHashTable(){
    HashTable_p table = malloc(sizeof(struct HashTable));
    size_t i;

    if (table == NULL){ return NULL;}

    for (i=0; i < BUCKETS_IN_TABLE; i++) {
        table -> buckets[i] = NULL;
    }
    return table; 
}


int put (HashTable_p table, const char* key, void * value){
    void* currentValue = get(table, key);
    Entry_p last;
    unsigned int index;

    if (currentValue != NULL){
        removeEntry(table, key); 
    }
    
    index = getBucketIndex(key); 
    if (table -> buckets[index] == NULL){
        table -> buckets[index] = newEntry(key, value, NULL);
    } else{
        last = table -> buckets[index];
        while (last -> next != NULL){ last = last -> next; }
        last -> next = newEntry(key, value, NULL);
    }
    return 0; 
}


void* get(HashTable_p table, const char* key){
    unsigned int index = getBucketIndex(key);
    Entry_p value = table -> buckets[index];
    while(value != NULL || value -> next != NULL){
        if (strcmp(value -> key, key) == 0){
            return value; 
        }
        value = value -> next; 
    }
    return value;   
}

int removeEntry(HashTable_p table, const char* key){
unsigned int index = getBucketIndex(key);
    Entry_p value = table -> buckets[index];
    Entry_p tmpValue; 

    if (value == NULL){ return -1; }

    if (strcmp(value -> key, key) == 0){
        table -> buckets[index] = value->next;
        value -> next = NULL; 
        freeEntry(value);
        return 0;
    }

    while(value -> next != NULL){
        if (strcmp(value -> next -> key , key) == 0){
            tmpValue = value -> next; 
            value -> next = value->next->next; 
            tmpValue->next = NULL;
            freeEntry(tmpValue);            
            return 0; 
        }
        value = value -> next; 
    }
    return -1;    
}