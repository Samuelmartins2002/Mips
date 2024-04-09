#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    char instrucao[17];
    char opcode[5];
} Memoria;

int bi_dec(char mem[17]);
void carregarMemoria(char *nomeArquivo, Memoria *mem, int *count);
void decodificarOpCode(Memoria *mem, int count);

int main() {
    Memoria mem[256];
    int count = 0;

    carregarMemoria("instrucoes.txt", mem, &count);
    decodificarOpcode(mem, count);
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

        strncpy(mem[*count].opcode, mem[*count].instrucao, 4);
        mem[*count].opcode[4] = '\0';
        (*count)++;
    }

    fclose(arquivo);
    for (int i = 0; i < *count; i++) {
       printf("%s\n", mem[i].instrucao);
   }
}

int bi_dec(char mem[17]){
	char vet[17];
	strcpy(vet,mem);
	int i=strlen(vet);
	int value,deci=0,k=0;
	for(int j=i;j>0;j--){
		if(vet[j-1]=='0'){
			value=0;
		}
		else{
			value=1;
		}
	deci=deci+value*(pow(2,k));
	k++;
	}
	return(deci);
}

void decodificarOpcode(Memoria *mem, int count) {
	int n;
	n=bi_dec(mem[count].opcode);
	switch(n){
		case 0:
			printf("Tipo R\n");
			break;
		case 4:
			printf("Tipo I addi\n");
			break;
		case 11:
			printf("Tipo I lw\n");
			break;
		case 15: 
			printf("Tipo I sw\n");
			break;
		case 8:
			printf("Tipo I beq\n");
			break;
		case 2:
			printf("Tipo J\n");
			break;
		default:
			printf("Instrução inválida\n");
			break;
	}
}
