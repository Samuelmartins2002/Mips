#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "mips.h"

void carregarMemoria(Memoria *mem, int *n_instrucoes) {

    FILE *arquivo;
    char *nome=malloc(sizeof(char)*51);
    printf("Qual o nome do arquivo de instruções? ");
    fgets(nome, 51, stdin);
    arquivo = fopen(nome, "r");

    if (arquivo == NULL) {
      printf("Erro ao abrir o arquivo.\n");
      return;
    }

    while (fscanf(arquivo, "%16s", mem[*n_instrucoes].instrucao) != EOF && *n_instrucoes < 256) {
		*n_instrucoes++;
  }
     
  fclose(arquivo);
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

void inverter_bits(char *imm){
  int length = strlen(imm);
  for(int i=0;i<length;i++){
    if(imm[i] == '0'){
      imm[i] = '1';
    } else if (imm[i] == '1') {
      imm[i] = '0';
    }
  }
}

int converter_imm(char *imm){
  int deci = 0;

  if(imm[0] == '1'){
    inverter_bits(imm);
    deci = bi_dec(imm) + 1;
    deci = -deci;
  } else {
    deci = bi_dec(imm);
  }
  return deci;
}

void decodificarOpcode(Memoria *mem, int *count) {//fazer recursao
	char b11_9[4];
    char b8_6[4];
    char b5_3[4];
    char b5_0[6];
    char b0_6[7];
	
   for(int i=0;i<3;i++){
    b11_9[i]=mem[*n_instrucoes].instrucao[i+9];
    b8_6[i]=mem[*n_instrucoes].instrucao[i+6];
    b5_3[i]=mem[*n_instrucoes].instrucao[i+3];
}
  
   for(int i=0;i<6;i++){
     b5_0[i]=mem[*n_instrucoes].instrucao[i];
     b0_6[i]=mem[*n_instrucoes].instrucao[i];
  }
   b0_6[6]=mem[*n_instrucoes].instrucao[6];
  
      mem[*n_instrucoes].b0_6=bi_dec(b0_6);   
      mem[*n_instrucoes].b5_0=bi_dec(b5_0);  
      mem[*n_instrucoes].b8_6=bi_dec(b8_6); 
      mem[*n_instrucoes].b5_3=bi_dec(b5_3);
      mem[*n_instrucoes].b11_9=bi_dec(b11_9);
}

void ula(int funct, int valor, int valor1, int *output, int *count){
  switch(funct){
    case 0:
    if(valor + valor1 > 127 || valor + valor1 < -128){
      printf("Estouro de bits no add.\n");
      *output=valor + valor1;
    }else{
      *output=valor + valor1;
    }
      break;
    case 2:
    if(valor - valor1 > 127 || valor - valor1 < -128){
      printf("Estouro de bits na sub.\n");
      *output=valor - valor1;
    }else{
      *output=valor - valor1;
    }
      break;
    case 5:
    if((valor & valor1) > 127 || (valor & valor1) < -128){
      printf("Estouro de bits na sub.\n");
      *output=valor & valor1;
    }else{
      *output=valor & valor1;
    }
      break;
    case 4:
    if((valor | valor1) > 127 || (valor | valor1) < -128){
      printf("Estouro de bits na sub.\n");
      *output=valor | valor1;
    }else{
      *output=valor | valor1;
    }
      break;
    }
  }

/* void tipo_R(Memoria *mem, int *count){
  char rs[4],rt[4],rd[4],funct[4];

  for(int i=0;i<3;i++){
    rs[i]=mem[*count].instrucao[i+4];
    rt[i]=mem[*count].instrucao[i+7];
    rd[i]=mem[*count].instrucao[i+10];
    funct[i]=mem[*count].instrucao[i+13];
  }
  rs[3] = '\0';
  rt[3] = '\0';
  rd[3] = '\0';
  funct[3] = '\0';
  mem[*count].rs=bi_dec(rs);
  mem[*count].rt=bi_dec(rt);
  mem[*count].rd=bi_dec(rd);
  mem[*count].funct=bi_dec(funct);
}

void tipo_I(Memoria *mem, int *count){
  char rs[4],rt[4],imm[7];
  for(int i=0;i<3;i++){
    rs[i]=mem[*count].instrucao[i+4];
    rt[i]=mem[*count].instrucao[i+7];
  }
  rs[3] = '\0';
  rt[3] = '\0';
  imm[6] = '\0';

  for(int i=0;i<6;i++){
    imm[i]=mem[*count].instrucao[i+10];
  }
  mem[*count].rs=bi_dec(rs);
  mem[*count].rt=bi_dec(rt);
  mem[*count].imm=converter_imm(imm);
}

void tipo_J(Memoria *mem, int *count){
  char addr[8];
  for(int i=0;i<7;i++){
    addr[i]=mem[*count].instrucao[i+9];
  }
  addr[7]='\0';
  mem[*count].addr=bi_dec(addr);
}
*/

void DadosRegistrador(int *registradores, int dados, int end, int *output, int chose){
  switch(chose){
    case 0:
      registradores[end]=dados;
      break;
    case 1:
      *output=registradores[end];
      break;
  }
}

/*
void UC(Memoria *mem, int *count, int *registrador, dados *m2, back *reserva){
   fback(m2, registrador, reserva, 0, count);
  int k=mem[*count].opcode;
  int *null=malloc(sizeof(int));
  int *valor=malloc(sizeof(int));
  int *valor1=malloc(sizeof(int));
  int *output=(int*)malloc(sizeof(int));
  *null=0;
  *valor=0;
  *valor1=0;
  *output=0;
  switch(k){
    case 0:
      DadosRegistrador(registrador, *null, mem[*count].rs, valor, 1);
      DadosRegistrador(registrador, *null, mem[*count].rt, valor1, 1);
      ula(mem[*count].funct, *valor, *valor1 ,output, count);
      DadosRegistrador(registrador, *output, mem[*count].rd, null, 0);
      break;
    case 4:
      DadosRegistrador(registrador, *null, mem[*count].rs, valor, 1);
      ula(*null, *valor, mem[*count].imm, output, count);
      DadosRegistrador(registrador, *output, mem[*count].rt, null, 0);
      break;
    case 2:
      (*count)=mem[*count].addr-1;
      break;
    case 8:
      DadosRegistrador(registrador, *null, mem[*count].rs, valor, 1);
      DadosRegistrador(registrador, *null, mem[*count].rt, valor1, 1);
      if(*valor1==*valor){
         (*count)=(*count)+mem[*count].imm-1;
      }
      break;
    case 11:
  *valor=m2->memoria_dados[mem[*count].rs+mem[*count].imm];
  DadosRegistrador(registrador, *valor, mem[*count].rt, null, 0);
  break;
    case 15:
      if ( (mem[*count].imm+mem[*count].rs) >= 0 && (mem[*count].imm+mem[*count].rs) < 256) {
  DadosRegistrador(registrador, *null, mem[*count].rt, valor, 1);
  m2->memoria_dados[mem[*count].rs+mem[*count].imm]=*valor;


      }
      else{
        printf("Endereço inválido.\n");
      }
  }
}
*/

void verReg(int *registrador){
  for(int i=0;i<8;i++){
    printf("\nRegistrador %i: %i \n",i, registrador[i]);
  }
}

void iniciarReg(int *registrador){
  for(int i=0;i<8;i++){
    registrador[i]=0;
  }
}

void inicializarMemoriaDados(dados *memoria2){
    for (int i = 0; i < 256; i++) {
        memoria2->memoria_dados[i] = 0;
    }
}

void vermemoriadados(dados *memoria2){
  for(int i=0;i<256;i++){
    printf("[%d]: %i\t", i, memoria2->memoria_dados[i]);
  }
}
void salvarDados(dados *memoria2) {
    FILE *arquivo;
    arquivo = fopen("dados.dat", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar.\n");
        return;
    }
    for (int i = 0; i < 256; i++) {
          fprintf(arquivo, "%d\n", memoria2->memoria_dados[i]);
    }
    fclose(arquivo);
    printf("Dados salvos com sucesso no arquivo dados.dat.\n");
}
void carregarDados(dados *memoria2) {
    FILE *arquivo;
    arquivo = fopen("dados.dat", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para carregar.\n");
        return;
    }
    for (int i = 0; i < 256; i++) {
       fscanf(arquivo, "%d\n", &memoria2->memoria_dados[i]); // Correção aqui
    }
    fclose(arquivo);
    printf("Dados carregados com sucesso do arquivo dados.dat.\n");
}

void fback(dados *memoria2 , int *registrador, back *reserva, int chose, int *count){
  if(chose == 0 ){
    reserva->memoria_dados=*memoria2;
    for(int i=0;i<8;i++){
      reserva->registradores[i]=registrador[i];
    }
    reserva->pc=*count;
  }
  else{
   *count=reserva->pc+1;
    *memoria2=reserva->memoria_dados;
    for(int i=0;i<8;i++){
      registrador[i]=reserva->registradores[i];
    }
  }
}

/*
void salvarAsm(Memoria *mem, int *n_instrucoes){

  FILE *arquivoSaida;
  arquivoSaida = fopen("instrucoes.asm", "w");

  if (arquivoSaida == NULL){
    printf("Erro ao abrir o arquivo.\n");
    return;
  }

    for (int i = 0; i < *n_instrucoes; i++) {
        switch (mem[i].opcode){
            case 0:
                switch(mem[i].funct){
                  case add:
                    fprintf(arquivoSaida, "add $%d, $%d, $%d\n", mem[i].rd, mem[i].rs, mem[i].rt);
                  break;
                  case sub:
                    fprintf(arquivoSaida, "sub $%d, $%d, $%d\n", mem[i].rd, mem[i].rs, mem[i].rt);
                  break;
                  case Or:
                    fprintf(arquivoSaida, "or $%d, $%d, $%d\n", mem[i].rd, mem[i].rs, mem[i].rt);
                  break;
                  case And:
                    fprintf(arquivoSaida, "and $%d, $%d, $%d\n", mem[i].rd, mem[i].rs, mem[i].rt);
                  break;
                  default:
                    fprintf(arquivoSaida, "instrucaoinvalida");
                  break;
                }
            break;
            case 4:
                fprintf(arquivoSaida, "addi $%d, $%d, %d\n", mem[i].rt, mem[i].rs, mem[i].imm);
            break;
            case 11:
                fprintf(arquivoSaida, "lw $%d, %d($%d)\n", mem[i].rt, mem[i].imm, mem[i].rs);
                break;
            case 15:
                fprintf(arquivoSaida, "sw $%d, %d($%d)\n", mem[i].rt, mem[i].imm, mem[i].rs);
                break;
            case 8:
                fprintf(arquivoSaida, "beq $%d, $%d, %d\n", mem[i].rt, mem[i].rs, mem[i].imm);
                break;
            case 2:
                fprintf(arquivoSaida, "j %d\n", mem[i].addr);
                break;
            default:
                break;
    }
  }
  fclose(arquivoSaida);
}

void verinstrucoes(Memoria *mem, int *count, int chose, int *n_instrucoes){
  int *count1=malloc(sizeof(int));
  *count1=0;
  if(chose==0){
  printf("\nInstrução [%i]: %s\n", *count, mem[*count].instrucao);
   switch (mem[*count].opcode){
            case 0:
                switch(mem[*count].funct){
                  case add:
                    printf("add $t%d, $t%d, $t%d\n", mem[*count].rd, mem[*count].rs, mem[*count].rt);
                  break;
                  case sub:
                    printf("sub $t%d, $t%d, $t%d\n", mem[*count].rd, mem[*count].rs, mem[*count].rt);
                  break;
                  case Or:
                    printf("or $t%d, $t%d, $t%d\n", mem[*count].rd, mem[*count].rs, mem[*count].rt);
                  break;
                  case And:
                    printf("and $t%d, $t%d, $t%d\n", mem[*count].rd, mem[*count].rs, mem[*count].rt);
                  break;
                  default:
                    printf("instrucaoinvalida");
                  break;
                }
            break;
            case 4:
                printf("addi $t%d, $t%d, %d\n", mem[*count].rt, mem[*count].rs, mem[*count].imm);
            break;
            case 11:
                printf("lw $t%d, %d($t%d)\n", mem[*count].rt, mem[*count].imm, mem[*count].rs);
                break;
            case 15:
                printf("sw $t%d, %d($t%d)\n", mem[*count].rt, mem[*count].imm, mem[*count].rs);
                break;
            case 8:
                printf("beq $t%d, $t%d, %d\n", mem[*count].rt, mem[*count].rs, mem[*count].imm);
                break;
            case 2:
                printf("j %d\n", mem[*count].addr);
                break;
            default:
                break;
    }
  }
  else{
    if(*count<*n_instrucoes){
    printf("\nInstrução [%i]: %s\n", *count, mem[*count].instrucao);
    switch (mem[*count].opcode){
            case 0:
                switch(mem[*count].funct){
                  case add:
                    printf("add $t%d, $t%d, $t%d\n", mem[*count].rd, mem[*count].rs, mem[*count].rt);
                  break;
                  case sub:
                    printf("sub $t%d, $t%d, $t%d\n", mem[*count].rd, mem[*count].rs, mem[*count].rt);
                  break;
                  case Or:
                    printf("or $t%d, $t%d, $t%d\n", mem[*count].rd, mem[*count].rs, mem[*count].rt);
                  break;
                  case And:
                    printf("and $t%d, $t%d, $t%d\n", mem[*count].rd, mem[*count].rs, mem[*count].rt);
                  break;
                  default:
                    printf("instrucaoinvalida");
                  break;
                }
            break;
            case 4:
                printf("addi $t%d, $t%d, %d\n", mem[*count].rt, mem[*count].rs, mem[*count].imm);
            break;
            case 11:
                printf("lw $t%d, %d($t%d)\n", mem[*count].rt, mem[*count].imm, mem[*count].rs);
                break;
            case 15:
                printf("sw $t%d, %d($t%d)\n", mem[*count].rt, mem[*count].imm, mem[*count].rs);
                break;
            case 8:
                printf("beq $t%d, $t%d, %d\n", mem[*count].rt, mem[*count].rs, mem[*count].imm);
                break;
            case 2:
                printf("j %d\n", mem[*count].addr);
                break;
            default:
                break;

  }
    *count1=*count+1;
    verinstrucoes(mem, count1 ,1, n_instrucoes);
    }
  free(count1);
}
}
*/

