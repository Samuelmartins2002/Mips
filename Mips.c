#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mips.h"


int main() {
    Memoria mem[256];
    int *count=malloc(sizeof(int));
    *count = 0;
    carregarMemoria("instrucoes.txt", mem, count);
    decodificarOpcode(mem, count);
    return 0;
}
