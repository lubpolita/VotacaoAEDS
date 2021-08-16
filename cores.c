#include <stdio.h>
#include "cores.h"

void corPadrao(){
    printf("\033[0m");
}

void corVermelho(){
    printf("\033[1;31m"); 
}

void corVerde(){
    printf("\033[0;32m");
}

void corCiano(){
    printf("\033[0;36m");
}