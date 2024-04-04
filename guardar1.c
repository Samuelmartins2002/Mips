#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char instrucoes[1000][17];
    int count;
} dados;

void leitor(dados *inf);
void print(dados inf);

int main() {
    dados inf;
    inf.count = 0;

    leitor(&inf);
    print(inf);

    return 0;
}

void leitor(dados *inf) {
    char buffer[17];
    FILE *instrucao1 = fopen("instrucoes.txt", "rt");

    while (fgets(buffer, sizeof(buffer), instrucao1) != NULL && inf->count < 1000) {
        strcpy(inf->instrucoes[inf->count], buffer);
        inf->count++;
    }

    fclose(instrucao1);
}

void print(dados inf) {
    for (int i = 0; i < inf.count; i++) {
        printf("%s", inf.instrucoes[i]);
    }
}
