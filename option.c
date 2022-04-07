#include <stdio.h>
#include <stdlib.h>
#include "option.h"
int optionChoice(){
    int option = -1;
    char line[80];
    fgets(line,80,stdin);
    option = (int)atoi(line);
    return option;
}

