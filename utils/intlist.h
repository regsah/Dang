#ifndef INTLIST_H
#define INTLIST_H

#include <stdlib.h>
#include <stdio.h>

typedef enum {
    LIST_OK = 0,        // No error
    LIST_ERR_ALLOC,     // Memory allocation failure
    LIST_ERR_UNDERFLOW, // Attempt to remove from an empty list
    LIST_ERR_INVALID    // Invalid operation
} IntListErrorCode;

typedef struct {
    int* list;        
    size_t used;      
    size_t size;      
    IntListErrorCode list_errno;
} IntList;

void initIntList(IntList* l, size_t size);
void pushIntList(IntList* l, int element);
int popIntList(IntList* l);
void destroyIntList(IntList* l);
void printIntList(IntList* l);

#endif