#include <stdio.h>
#include <math.h>
#include "utils/intlist.h"
#include "utils/tokenmap.h"
#include "utils/lexlist.h"
#include "src/lexer.h"

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

    LexList ll;
    initLexList(&ll, 5);
    lexListPush(&ll, createLexPair("deneme", 5));
    lexListPush(&ll, createLexPair("hoo", 5));
    lexListPush(&ll, createLexPair("koo", 5));
    lexListPop(&ll);

    lexListPrint(&ll);

    printf("%i \n", findTokenEnd("deneme ooho", 0));
    printf("%i \n", findTokenEnd("deneme 123", 7));
    printf("%i \n", findTokenEnd("deneme.deneme", 0));
    printf("%i \n", findTokenEnd("deneme.-deneme", 6));
    printf("%i \n", findTokenEnd("deneme_1.deneme", 6));
    printf("%i \n", findTokenEnd(">=1.deneme", 0));


    
    return 0;
}