#ifndef TOKENMAP_H
#define TOKENMAP_H

#include <stdlib.h>
#include <stdio.h>
#include "string.h"


typedef enum {
    MAP_OK = 0,        // No error
    MAP_ERR_ALLOC,     // Memory allocation failure
    MAP_ERR_UNDERFLOW, // Attempt to remove from an empty list
    MAP_ERR_INVALID    // Invalid operation    
} TokenMapErrorCode;

typedef struct TokenNode TokenNode;
typedef struct TokenNode{
    char* key;
    int val;
    TokenNode* next;
} TokenNode;

typedef struct {
    TokenNode* array;        
    size_t size;      
    TokenMapErrorCode map_errno;
} TokenMap;


void initTokenMap(TokenMap* map, size_t size);
unsigned int FNVHash(char* str, unsigned int length);
unsigned int tokenMapGetIndex(char* key, size_t size);
void tokenMapPut(TokenMap* map, char* key, int val);
int tokenMapGet(TokenMap* map, char* key);
void tokenMapDestroy(TokenMap* map);
void tokenMapPrint(TokenMap* map);


#endif