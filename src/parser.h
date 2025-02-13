#ifndef PARSER_H
#define PARSER_H


#include <ctype.h>
#include "../utils/intlist.h"
#include "../utils/hashmap.h"

typedef enum {
    SELECT = 0,

} Token;


void tokenize(IntList* l);

int bypassSpace(char* str, int idx);
int checkToken(TokenMap* map, char* str, unsigned int start, unsigned int end);



#endif