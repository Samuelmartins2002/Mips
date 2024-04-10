#ifndef __MIPS__
#define __MIPS__

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
    char funct[4];
    char rs[4];
    char rt[4];
    char rd[4];
    char addr[8];
    char imm[7];
} Memoria;

void tipo_R(Memoria *mem, int *count);
void tipo_I(Memoria *mem, int *count);
void tipo_J(Memoria *mem, int *count);
void dec_bi(Memoria *mem, int k, int *count);
void ula(Memoria *mem, int *count);
int bi_dec(char *mem);
void carregarMemoria(char *nomeArquivo, Memoria *mem, int *count);
void decodificarOpcode(Memoria *mem, int *count);

void carregarMemoria(char *nomeArquivo, Memoria *mem, int *count) {
    FILE *arquivo;
    arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    while (fscanf(arquivo, "%16s", mem[*count].instrucao) != EOF && *count < 100) {

        strncpy(mem[*count].opcode, mem[*count].instrucao, 4);
        mem[*count].opcode[4] = '\0';
        (*count)++;
    }

    fclose(arquivo);
    for (int i = 0; i < *count; i++) {
       printf("%s\n", mem[i].instrucao);
   }
  *count=0;
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

void dec_bi(Memoria *mem, int k, int *count){
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
			tipo_R(mem, count);
			break;
		case 4:
			printf("Tipo I addi\n");
			tipo_I(mem, count);
			break;
		case 11:
			printf("Tipo I lw\n");
			tipo_I(mem, count);
			break;
		case 15: 
			printf("Tipo I sw\n");
			tipo_I(mem, count);
			break;
		case 8:
			printf("Tipo I beq\n");
			tipo_I(mem, count);
			break;
		case 2:
			printf("Tipo J\n");
			tipo_J(mem, count);
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
	int y=bi_dec(mem[*count].value1);
	switch(n){
		case add:
			 dec_bi(mem,x+y,count);
			break;
		case sub:
			dec_bi(mem,x-y,count);
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

void tipo_R(Memoria *mem, int *count){
	for(int i=0;i<3;i++){
		mem[*count].rs[i]=mem[*count].instrucao[i+4];
		mem[*count].rt[i]=mem[*count].instrucao[i+7]; 
		mem[*count].rd[i]=mem[*count].instrucao[i+10];
		mem[*count].funct[i]=mem[*count].instrucao[i+13]; 
	}
}

void tipo_I(Memoria *mem, int *count){
        for(int i=0;i<3;i++){
                mem[*count].rs[i]=mem[*count].instrucao[i+4];
                mem[*count].rt[i]=mem[*count].instrucao[i+7]; 
        }
        for(int i=0;i<6;i++){
                mem[*count].imm[i]=mem[*count].instrucao[i+10];
        }
}

void tipo_J(Memoria *mem, int *count){
         for(int i=0;i<7;i++){ 
                mem[*count].addr[i]=mem[*count].instrucao[i+9];
        }
}

#endif


