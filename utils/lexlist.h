#ifndef LEXLIST_H
#define LEXLIST_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef enum {
    LEX_LIST_OK = 0,        // No error
    LEX_LIST_ERR_ALLOC,     // Memory allocation failure
    LEX_LIST_ERR_UNDERFLOW, // Attempt to remove from an empty list
    LEX_LIST_ERR_INVALID    // Invalid operation
} LexListErrorCode;

typedef struct {
    char* meaning;
    int value;
} LexPair;

typedef struct {
    LexPair* list;        
    size_t used;      
    size_t size;      
    LexListErrorCode list_errno;
} LexList;

LexPair createLexPair(char* meaning, int value);

void initLexList(LexList* l, size_t size);
void lexListPush(LexList* l, LexPair element);
LexPair lexListPop(LexList* l);
void lexListDestroy(LexList* l);
void lexListPrint(LexList* l);

#endif