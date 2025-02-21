#include <stdio.h>
#include <math.h>
#include "utils/intlist.h"


int main() {
    IntList l;
    initIntList(&l, 5);
    for(int i = 0; i < 5; ++i) pushIntList(&l, pow(2, i));
    printIntList(&l);
    return 0;
}