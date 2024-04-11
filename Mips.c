#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mips.h"

int main(){
    Memoria mem[256];
    int *count = malloc(sizeof(int));
    char **registrador;

    if (count == NULL) {
      printf("Memory allocation failed for count\n");
      return 1; // Return an error status
    }

    registrador = malloc(8 * sizeof(char *)); 

    if (registrador == NULL) {
      printf("Memory allocation failed for registrador\n");
      free(count); // Free the previously allocated memory
      return 1; // Return an error status
    }

    *count = 0;

    carregarMemoria("instrucoes.txt", mem, count);
    decodificarOpcode(mem, count);
    pc(mem, count, registrador);

    // Free allocated memory before returning
    free(count);
    for (int i = 0; i < 8; i++) {
      free(registrador[i]);
    }
    free(registrador);

    return 0;
  }
