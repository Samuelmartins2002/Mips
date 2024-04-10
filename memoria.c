#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    char instrucao[17];
    char opcode[5];
    char controle[4];
    char value[9];
    char value1[9];
    char resul[9];
} Memoria;

void dec_bi(Memoria *mem, int k, int *count);
void ula(Memoria *mem, int *count);
int bi_dec(char *mem);
void carregarMemoria(char *nomeArquivo, Memoria *mem, int *count);
void decodificarOpcode(Memoria *mem, int *count);

int main() {
    Memoria mem[256];
    int count = 0;

    carregarMemoria("instrucoes.txt", mem, &count);
    decodificarOpcode(mem, &count);
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

int bi_dec(char *mem){
	int i=strlen(mem);
	int value,deci=0,k=0;
	for(int j=i;j>0;j--){
		if(mem[j-1]=='0'){
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

void deci_bi(Memoria *mem, int k, int *count){
	int t=0;
	for(int i=0;i<8;i++){
		mem[*count].resul[i]='0';
	}
	while(k!=0){
		if(k%2==1){
			mem[*count].resul[8-t]='1';
		}
		else{
			mem[*count].resul[8-t]='1';	
		}
		t++;
		k=k/2;
	}
}

void decodificarOpcode(Memoria *mem, int *count) {
	int n;
	n=bi_dec(mem[*count].opcode);
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

void ula(Memoria *mem, int *count){
	enum comando{add=0,sub=2,or=4,and=5};
	enum comando n=bi_dec(mem[*count].controle);
        int x=bi_dec(mem[*count].value);
	int y=bi_dec(mem[*count].value);
	switch(n){
		case add:
			 deci_bi(mem,x+y,count);
			break;
		case sub:
			deci_bi(mem,x-y,count);
			break;
		case and:
        		for(int j=0;j<8;j++){
                		if(mem[*count].value[j]==mem[*count].value1[j] && mem[*count].value[j]=='1'){
					mem[*count].resul[j]='1';
                        	}
				else{
					mem[*count].resul[j]='0';
				}
			}
			break;
                case or:
			for(int j=0;j<8;j++){
                                if(mem[*count].value1[j]=='1' || mem[*count].value[j]=='1'){
                                        mem[*count].resul[j]='1';
                                }
                                else{
                                        mem[*count].resul[j]='0';
                                }
                        }
                        break;
		}
}
