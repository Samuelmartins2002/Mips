#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mips.h"

int main(){
    Memoria mem[256];
    int *count = malloc(sizeof(int));
    char *registrador=malloc(sizeof(int));
  

    *count = 0;

    carregarMemoria("instrucoes.txt", mem, count);
    
    pc(mem, count, registrador);

  }
