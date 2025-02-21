#include "lexlist.h"

LexPair createLexPair(char* meaning, int value) {
    LexPair emptyPair = {NULL, -1};

    LexPair p;
    p.meaning = (char*)malloc(strlen(meaning) + 1);

    if (p.meaning != NULL) {
        strcpy(p.meaning, meaning);
        p.value = value;
        return p;
    }
    else return emptyPair;
}

void deletePair(LexPair* p) {
    if (p != NULL && p->meaning != NULL)
    free(p->meaning);
}

void initLexList(LexList* l, size_t size) {
    l->list = malloc(size * sizeof(LexPair));

    if(l->list == NULL) {
        printf("[LOG][List] MEMORY ALLOCATION FAILURE\n");
        l->list_errno = LEX_LIST_ERR_ALLOC;
        return;
    }

    l->size = size;
    l->used = 0;
    l->list_errno = 0;
}

void lexListPush(LexList* l, LexPair element) {
    if(l == NULL) {
        printf("[LOG][List] PUSHED TO NULL POINTER\n");
        return;
    }

    if(l->used >= l->size) {
        LexPair* temp = realloc(l->list, l->size * 2 * sizeof(LexPair));
        if(temp == NULL) {
            printf("[LOG][List] MEMORY ALLOCATION FAILURE\n");
            l->list_errno = LEX_LIST_ERR_ALLOC;
            return;
        }
        l->list = temp;
        l->size *= 2;  
    }

    l->list[l->used] = element;
    l->used += 1;

    return;
}

LexPair lexListPop(LexList* l) {
    LexPair emptyPair = {NULL, -1}; 

    if(l == NULL || l->list == NULL || l->used == 0) {
        printf("[LOG][List] STACK UNDERFOW\n");
        l->list_errno = LEX_LIST_ERR_UNDERFLOW;
        return emptyPair;
    }

    if(l->used < l->size/3) {
        LexPair* temp = realloc(l->list, l->used * sizeof(LexPair));
        if(temp == NULL) {
            printf("[LOG][List] MEMORY ALLOCATION FAILURE\n");
            l->list_errno = LEX_LIST_ERR_ALLOC;
            return emptyPair;
        }
        l->list = temp;
        l->size = l->used;
    }

    LexPair temp = l->list[l->used - 1];
    l->used -= 1;
    return temp;
}

void lexListDestroy(LexList* l) {
    if (l != NULL && l->list != NULL) {
        free(l->list);
        l->list = NULL;
        l->size = 0;
        l->used = 0;
    }
}

void lexListPrint(LexList* l) {
    printf("[ ");
    for(int idx=0; idx < l->used; ++idx) {
        printf("%s : %i", l->list[idx].meaning, l->list[idx].value);
        if(idx != l->used - 1) printf(", ");
    }
    printf(" ]\n");
}