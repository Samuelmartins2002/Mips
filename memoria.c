#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char instrucao[17];
} Memoria;

void carregarMemoria(char *nomeArquivo, Memoria *mem, int *count);

int main() {
    Memoria mem[256];
    int count = 0;

    carregarMemoria("instrucoes.txt", mem, &count);

    for (int i = 0; i < count; i++) {
        printf("%s\n", mem[i].instrucao);
    }

    return 0;
}

void carregarMemoria(char *nomeArquivo, Memoria *mem, int *count) {
    FILE *arquivo;
    arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    while (fscanf(arquivo, "%16s", mem[*count].instrucao) != EOF && *count < 100) {
        (*count)++;
    }

    fclose(arquivo);
}
