#ifndef PARSER_H
#define PARSER_H

#include <ctype.h>
#include "../utils/intlist.h"
#include "../utils/tokenmap.h"

typedef enum {
    INTEGER = 0,
} Token;


int bypassSpace(char* str, int idx);
int findOperatorEnd(char* str, int idx);
int findTokenEnd(char* str, int idx);
int checkToken(TokenMap* map, char* str, unsigned int start, unsigned int end);


#endif