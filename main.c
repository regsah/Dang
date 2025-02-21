#include <stdio.h>
#include <math.h>
#include "utils/intlist.h"
#include "utils/tokenmap.h"

int main() {
    IntList l;
    initIntList(&l, 5);
    for(int i = 0; i < 5; ++i) intListPush(&l, pow(2, i));
    intListPop(&l);
    intListPrint(&l);

    TokenMap m;
    initTokenMap(&m, 10);
    tokenMapPut(&m, "apple", 5);
    tokenMapPut(&m, "banana", 3);
    tokenMapPut(&m, "apple", 2);
    tokenMapPrint(&m);
    
    return 0;
}