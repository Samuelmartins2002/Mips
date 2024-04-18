#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

enum comando{add=0,sub=2,or=4,and=5};

typedef struct {
    char instrucao[17];
    int opcode;
    int funct;
    int rs;
    int rt;
    int rd;
    int addr;
    int imm;
} Memoria;

typedef struct{
    int memoria_dados[256];
}dados;

void inicializarMemoriaDados(dados *memoria2);
void iniciarReg(int *registrador);
void verReg(int *registrador);
void pc(Memoria *mem, int *count,int *registrador, dados *m2);
void UC(Memoria *mem, int *count, int *registrador, dados *m2);
void tipo_R(Memoria *mem, int *count);
void tipo_I(Memoria *mem, int *count);
void tipo_J(Memoria *mem, int *count);
void dec_bi(char *output, int k, int *count);
int bi_dec(char *mem);
void carregarMemoria(char *nomeArquivo, Memoria *mem, int *count);
void decodificarOpcode(Memoria *mem, int *count);
void DadosRegistrador(int *registradores, int dados, int end, int *output, int chose);
void verinstrucoes(Memoria *mem, int *count);
void imprimirMemoriaDados(dados *memoria2);

int main(){
  dados *memoria2=malloc(sizeof(dados));
  Memoria mem[256];
  int *count = malloc(sizeof(int));
  int *registrador=malloc(8*sizeof(int));
  iniciarReg(registrador);
  int k=1;
  *count = 0;
  inicializarMemoriaDados(memoria2);
  carregarMemoria("instrucoes.txt", mem, count);
  while(k!=0){
    printf("\n================================\n");
    printf("             MENU\n");
    printf("================================\n");
    printf("1 - (RUN)Executar todo o arquivo\n");
    printf("2 - (STEP)Executar uma linha\n");
    printf("3 - (BACK)Voltar uma instrução\n");
    printf("4 - Ver Registradores\n");
    printf("5 - Ver instruções\n");
    printf("6 - Ver Dados\n");
    printf("7 - Sair\n");
    printf("================================\n");
    printf("Selecione: ");
    scanf("%i",&k);
    switch(k){
      case 1:
        pc(mem, count, registrador,memoria2);
        break;
      case 2:
        UC(mem, count, registrador,memoria2);
        (*count)++;
        break;
      case 3:
        (*count)--;
        UC(mem, count, registrador,memoria2);
        (*count)++;
        break;
      case 4:
        verReg(registrador);
        break;
      case 5:
        verinstrucoes(mem,count);
        break;
      case 6:
        imprimirMemoriaDados(memoria2);
        break;
      case 7:
        k=0;
        break;
      default:
        printf("Opção inválida!!!");
        break;
    }
  }
}

void carregarMemoria(char *nomeArquivo, Memoria *mem, int *count) {
    char op[5];
    FILE *arquivo;
    arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL) {
      printf("Erro ao abrir o arquivo.\n");
      return;
    }

    while (fscanf(arquivo, "%16s", mem[*count].instrucao) != EOF && *count < 256) {
      strncpy(op, mem[*count].instrucao, 4);
      mem[*count].opcode=bi_dec(op);
      decodificarOpcode(mem, count);
      (*count)++;
    }

  fclose(arquivo);
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

void decodificarOpcode(Memoria *mem, int *count) {
  switch(mem[*count].opcode){
    case 0:
      tipo_R(mem, count);
      break;
    case 4:
      tipo_I(mem, count);
      break;
    case 11:
      tipo_I(mem, count);
      break;
    case 15:
      tipo_I(mem, count);
      break;
    case 8:
      tipo_I(mem, count);
      break;
    case 2:
      tipo_J(mem, count);
      break;
  }
}

void ula(int funct, int valor, int valor1, int *output, int *count){
  enum comando{add=0,sub=2,or=4,and=5};
  enum comando n=funct;
  switch(n){
    case add:
      *output=valor+valor1;
      break;
    case sub:
      *output=valor-valor1;
      break;
    case and:
      *output=valor & valor1;
      break;
    case or:
      *output= valor | valor1;
      break;
    }
  }

void tipo_R(Memoria *mem, int *count){
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
  mem[*count].imm=bi_dec(imm);
}

void tipo_J(Memoria *mem, int *count){
  char addr[8];
  for(int i=0;i<7;i++){
    addr[i]=mem[*count].instrucao[i+9];
  }
  addr[7]='\0';
  mem[*count].addr=bi_dec(addr);
}

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

void pc(Memoria *mem, int *count,int *registrador, dados *m2){
  if(strlen(mem[*count].instrucao) == 0){
    return;
  }
  else{
    UC(mem, count, registrador,m2);
    (*count)++;
    pc(mem,count,registrador,m2);
  }
}

void UC(Memoria *mem, int *count, int *registrador, dados *m2){
  int k=mem[*count].opcode;
  int *null=malloc(sizeof(int));
  int *valor=malloc(sizeof(int));
  int *valor1=malloc(sizeof(int));
  int *output=(int*)malloc(sizeof(int));
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
      (*count)=mem[*count].addr*2-1;
      break;
    case 8:
      if(mem[*count].rs==mem[*count].rt){
         (*count)=(*count)+mem[*count].imm*2-1;
      }
      break;
    case 15:
      if ( (mem[*count].imm+mem[*count].rs)>= 0 && (mem[*count].imm+mem[*count].rs) < 256) {
        m2->memoria_dados[mem[*count].rs+mem[*count].imm]=mem[*count].rt;
      }
      else{
        printf("Endereço inválido.\n");
      }
    case 11:
      if ( (mem[*count].imm+mem[*count].rs)>= 0 && (mem[*count].imm+mem[*count].rs) < 256) {
        mem[*count].rt=m2->memoria_dados[mem[*count].rs+mem[*count].imm];
      }
      else{
        printf("Endereço inválido.\n");
      }
  }
}

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

void verinstrucoes(Memoria *mem, int *count){
  int i=0;
  while(strlen(mem[*count].instrucao) != 0){
    i++;
    printf("\n %s\n", mem[i].instrucao);
    printf("RT: %i\n", mem[i].rt);
    printf("RD: %i\n", mem[i].rd);
    printf("RS: %i\n", mem[i].rs);
    printf("imm %i\n", mem[i].imm);
    printf("funct %i\n", mem[i].funct);
    printf("addr %i\n", mem[i].addr);
    printf("op %i\n", mem[i].opcode);
  }
}

void inicializarMemoriaDados(dados *memoria2){
      for (int i = 0; i < 256; i++) {
          memoria2->memoria_dados[i] = 0;
      }
  }
void imprimirMemoriaDados(dados *memoria2) {
    printf("\nMemória de Dados:\n");
    for (int i = 0; i < 256; i += 4) {
        printf("Endereço %03d: %5d | ", i, memoria2->memoria_dados[i]);
        printf("Endereço %03d: %5d | ", i + 1, memoria2->memoria_dados[i + 1]);
        printf("Endereço %03d: %5d | ", i + 2, memoria2->memoria_dados[i + 2]);
        printf("Endereço %03d: %5d\n", i + 3, memoria2->memoria_dados[i + 3]);
    }
}
