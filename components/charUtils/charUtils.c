#include <stdio.h>
#include "charUtils.h"

char* truncString(char* str,int posInit, int length){

    size_t len = strlen(str);

    str  = str + posInit;
    str[length] = '\0';
    return str;


}
