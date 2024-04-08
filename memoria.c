#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char instrucao[17];
    char opcode[7];
} Memoria;

void carregarMemoria(char *nomeArquivo, Memoria *mem, int *count);
void decodificarOpCode(Memoria *mem, int count);

int main() {
    Memoria mem[256];
    int count = 0;

    carregarMemoria("instrucoes.txt", mem, &count);
    decodificarOpCode(mem, count);

    return 0;
}

void carregarMemoria(char *nomeArquivo, Memoria *mem, int *count) {
    FILE *arquivo;
    arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
// esse 16s pega 16 caracteres char
    while (fscanf(arquivo, "%16s", mem[*count].instrucao) != EOF && *count < 100) {

        strncpy(mem[*count].opcode, mem[*count].instrucao, 6);
        mem[*count].opcode[6] = '\0';
        (*count)++;
    }

    fclose(arquivo);

    for (int i = 0; i < *count; i++) {
       printf("%s\n", mem[i].instrucao);
   }
}

void decodificarOpCode(Memoria *mem, int count) {
    printf("Decodificação do OpCode:\n");

    for (int i = 0; i < count; i++) {
        printf("Instrução %d: %s OpCode = %s\n", i + 1, mem[i].instrucao, mem[i].opcode);
    }
}
