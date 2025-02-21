#include "lexer.h"

int bypassSpace(char* str, int idx)
{
    if(str == NULL) return -1;
    while(str[idx] != 0 && isspace(str[idx])) idx += 1;
    return idx;
}

int findOperatorEnd(char* str, int idx)
{
    switch (str[idx])
    {
    case '+':
    case '-':
    case '/':
    case '*':
    case '.':
    case '(':
    case ')':
    case '{':
    case '}':
    case '[':
    case ']':
        return idx+1;
    case '>':
    case '<':
    case '=':
        if(str[idx+1] == '=') return idx+2;
        else return idx + 1;
    default:
        return idx;
    }
}

int findTokenEnd(char* str, int idx) {
    if(str == NULL ||idx < 0) return -1;

    int opEnd = findOperatorEnd(str, idx);
    if(opEnd != idx) return opEnd;

    while(str[idx] != 0 && ( 
        (str[idx] >= 'a' && str[idx] <= 'z') ||
        (str[idx] >= 'A' && str[idx] <= 'Z') ||
        (str[idx] >= '0' && str[idx] <= '9') ||
        (str[idx] == '_')
    )) {
        ++idx;
    }
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
