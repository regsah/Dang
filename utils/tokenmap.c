#include "tokenmap.h"

void initTokenMap(TokenMap* map, size_t size) {
    map->array = (TokenNode*)malloc(size * sizeof(TokenNode));
    if(map->array == NULL) {
        printf("[LOG][Map] MEMORY ALLOCATION FAILURE\n");
        map->map_errno = MAP_ERR_ALLOC;
        return;
    }

    for(unsigned int idx = 0; idx < size; ++idx) {
        map->array[idx].key = NULL;
        map->array[idx].val = 0;
        map->array[idx].next = NULL;
    }

    map->size = size;
    map->map_errno = MAP_OK;
}

unsigned int FNVHash(char* str, unsigned int length) {
    const unsigned int fnv_prime = 0x01000193;
    unsigned int hash = 0x811C9DC5;
    for(unsigned int i = 0; i < length; str++, i++) {
        hash *= fnv_prime;
        hash ^= (*str);
    }

    return hash;
}

unsigned int tokenMapGetIndex(char* key, size_t size) {
    return FNVHash(key, strlen(key)) % size;
}

void tokenMapPut(TokenMap* map, char* key, int val) {
    if(map == NULL) {
        printf("[LOG][Map] PUT TO NULL POINTER\n");
        return;
    }
    if (key == NULL) {
        printf("[LOG][Map] HASHED NULL STRING\n");
        map->map_errno = MAP_ERR_INVALID;
        return;
    }

    unsigned int index = tokenMapGetIndex(key, map->size);

    TokenNode* node = &map->array[index];
    if(node->key == NULL) {
        node->key = (char*) malloc((strlen(key) + 1) * sizeof(char));
        strcpy(node->key, key);
        node->val = val;
        return;
    }


    while(node->next && node->key != NULL && strcmp(node->key, key) != 0) {
        node = node->next;
    }

    if(node->key != NULL && strcmp(node->key, key) == 0) node->val = val;
    else {
        node->next = (TokenNode*) malloc(sizeof(TokenNode));
        if(node->next == NULL)
        {
            printf("[LOG][Map] MEMORY ALLOCATION FAILURE\n");   
            map->map_errno = MAP_ERR_ALLOC;
            return;
        }
        node = node->next;

        node->key = (char*)malloc((strlen(key) + 1) * sizeof(char));
        if(node->key == NULL) {
            printf("[LOG][Map] MEMORY ALLOCATION FAILURE\n");   
            map->map_errno = MAP_ERR_ALLOC;
            return;
        }
    
        strcpy(node->key, key);
        node->val = val;
        node->next = NULL;
    }
}

int tokenMapGet(TokenMap* map, char* key) {
    if(map == NULL) {
        printf("[LOG][Map] PUT TO NULL POINTER\n");
        return -1;
    }
    if (key == NULL) {
        printf("[LOG][Map] HASHED NULL STRING\n");
        map->map_errno = MAP_ERR_INVALID;
        return -1;
    }

    unsigned int index = tokenMapGetIndex(key, map->size);

    TokenNode* node = &map->array[index];
    while(node != NULL && node->key != NULL && strcmp(node->key, key) != 0) {
        node = node->next;
    }

    if(node != NULL && node->key != NULL) return node->val;
    return -1;
}

void destroyTokenNodeChain(TokenNode* node) {
    if(node->key != NULL) {
        free(node->key);
        node->key == NULL;
    }

    TokenNode* current = node->next;
    while(current != NULL) {
        TokenNode* next = current->next;
        free(current->key);
        free(node);
        current = next;
    }
    current->next = NULL;
}

void tokenMapDestroy(TokenMap* map) {
    if(map == NULL) return;

    for(unsigned int idx = 0; idx < map->size; ++idx) {
        destroyTokenNodeChain(&map->array[idx]);
    }

    free(map->array);
    free(map);
    map = NULL;
}

void tokenMapPrint(TokenMap* map) {
    printf("{ ");
    for(unsigned int idx=0; idx < map->size; ++idx) {
        TokenNode* node = &map->array[idx];
        int emptyCheck = 0;
        while(node != NULL && node->key != NULL) {
            emptyCheck = 1;
            printf("%s: %u", (node->key), node->val);
            if(node->next != NULL) printf(", ");
            node = node->next;
        }
        if(idx != map->size - 1 && emptyCheck) printf(", ");
    }
    printf(" }\n");
}

