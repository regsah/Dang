#include "lexer.h"

int bypassSpace(char* str, int idx)
{
    if(str == NULL) return -1;
    while(str[idx] != 0 && isspace(str[idx])) idx += 1;
    return idx;
}

int checkToken(TokenMap* map, char* str, unsigned int start, unsigned int end)
{
    if(str == NULL || end > strlen(str) || start >= end) return -1;
    
    char c = str[end];
    str[end] = '\0';

    int val = tokenMapGet(map, str+start);
    str[end] = c;
    
    return val;
}
