#include <stdio.h>
#include "buffer.h"

static char *buffer;

void writeBuffer(char* str){ 
    buffer = str;
}

char* readBuffer(void){
    return buffer;
}