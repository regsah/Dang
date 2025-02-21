#include "intlist.h"


void initIntList(IntList* l, size_t size) {
    l->list = malloc(size * sizeof(int));

    if(l->list == NULL) {
        printf("[LOG][List] MEMORY ALLOCATION FAILURE\n");
        l->list_errno = LIST_ERR_ALLOC;
        return;
    }

    l->size = size;
    l->used = 0;
    l->list_errno = 0;
}

void intListPush(IntList* l, int element) {
    if(l == NULL) {
        printf("[LOG][List] PUSHED TO NULL POINTER\n");
        return;
    }

    if(l->used >= l->size) {
        int* temp = realloc(l->list, l->size * 2 * sizeof(int));
        if(temp == NULL) {
            printf("[LOG][List] MEMORY ALLOCATION FAILURE\n");
            l->list_errno = LIST_ERR_ALLOC;
            return;
        }
        l->list = temp;
        l->size *= 2;  
    }

    l->list[l->used] = element;
    l->used += 1;

    return;
}

int intListPop(IntList* l) {
    if(l == NULL || l->list == NULL || l->used == 0) {
        printf("[LOG][List] STACK UNDERFOW\n");
        l->list_errno = LIST_ERR_UNDERFLOW;
        return -1;
    }

    if(l->used < l->size/3) {
        int* temp = realloc(l->list, l->used * sizeof(int));
        if(temp == NULL) {
            printf("[LOG][List] MEMORY ALLOCATION FAILURE\n");
            l->list_errno = LIST_ERR_ALLOC;
            return -1;
        }
        l->list = temp;
        l->size = l->used;
    }

    int temp = l->list[l->used - 1];
    l->used -= 1;
    return temp;
}

void intListDestroy(IntList* l) {
    if (l != NULL && l->list != NULL) {
        free(l->list);
        l->list = NULL;
        l->size = 0;
        l->used = 0;
    }
}

void intListPrint(IntList* l) {
    printf("[ ");
    for(int idx=0; idx < l->used; ++idx) {
        printf("%i", l->list[idx]);
        if(idx != l->used - 1) printf(", ");
    }
    printf(" ]\n");
}