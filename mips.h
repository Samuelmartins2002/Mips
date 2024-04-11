#ifndef __MIPS__
#define __MIPS__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    char instrucao[17];
    char opcode[5];
    char funct[4];
    char rs[4];
    char rt[4];
    char rd[4];
    char addr[8];
    char imm[7];
} Memoria;

void UC(Memoria *mem, int *count, char **registrador);
void pc(Memoria *mem, int *count, char **registrador);
void tipo_R(Memoria *mem, int *count);
void tipo_I(Memoria *mem, int *count);
void tipo_J(Memoria *mem, int *count);
void dec_bi(char *output, int k, int *count);
void ula(char *funct, char *valor,char *valor1, char *output, int *count);
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

void dec_bi(char *output, int k, int *count){
	int t=0;
	for(int i=0;i<8;i++){
		output[i]='0';
	}
	while(k!=0){
		if(k%2==1){
			output[8-t]='1';
		}
		else{
			output[8-t]='1';	
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

void ula(char *funct, char *valor, char *valor1, char *output, int *count){
	enum comando{add=0,sub=2,or=4,and=5};
	enum comando n=bi_dec(funct);
        int x=bi_dec(valor);
	int y=bi_dec(valor1);
	switch(n){
		case add:
			 dec_bi(output,x+y,count);
			break;
		case sub:
			dec_bi(output,x-y,count);
			break;
		case and:
			for(int j=0;j<8;j++){
        			if(valor[j]==valor1[j] && valor[j]=='1'){
	        			output[j]='1';
			}
        			else{
        				output[j]='0';
				}
			}
      			break;
      		case or:
			for(int j=0;j<8;j++){
  				if(valor[j]=='1' || valor1[j]=='1'){
          				output[j]='1';
 				}
  				else{
          				output[j]='0';
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

void iniciarRegistrador(char **registrador){
  for(int i=0;i<8;i++){
    registrador[i]=*(char **)malloc(17*sizeof(char));
  }
}

void DadosRegistrador(char **registradores, char *dados, char *end, int chose, char *des){
  int k=bi_dec(end);
  switch(chose){
    case 0:
      strcpy(registradores[k],dados);
      break;
    case 1:
      strcpy(des,registradores[k]);
      break;
  }
}

void pc(Memoria *mem, int *count,char **registrador){
  decodificarOpcode(mem, count);
  UC(mem, count, registrador);
  printf("sei la 2\n");
  if(mem[*count].instrucao[0] == '\0'){
    return;
  }
  else{
    UC(mem, count,registrador);
    pc(mem,count+1,registrador);
  }
}

void UC(Memoria *mem, int *count, char **registrador){
 int k=bi_dec(mem[*count].opcode);
 char *value;
 value=(char*)malloc(17*sizeof(char));
 char *value1; 
 value1=(char*)malloc(17*sizeof(char));
 char *output;
 output=(char*)malloc(17*sizeof(char));
 char *null1;
 null1=(char*)malloc(17*sizeof(char));
for(int i=0;i<16;i++){
  null1[i]='0';
  value[i]='0';
  value1[i]='0';
}

  switch(k){
 case 0:
      DadosRegistrador(registrador, null1, mem[*count].rs, 1, value);
      DadosRegistrador(registrador, null1, mem[*count].rt, 1, value1);
      ula(mem[*count].funct, value,value1,output,count);
      DadosRegistrador(registrador, output, mem[*count].rd, 0, null1);
      break;
  case 4:
      DadosRegistrador(registrador, null1, mem[*count].rs, 1, value);
      ula(null1, value, mem[*count].imm, output, count);
      DadosRegistrador(registrador, output, mem[*count].rd, 0, null1);
      break;
 }
}

void inciarRegistrador(char **registrador){
  registrador=(char**)malloc(8*sizeof(char*));
  for(int i=0;i<16;i++){
    registrador[i]=(char*)malloc(17*sizeof(char));
    registrador[i]='0';
  }
}
#endif


