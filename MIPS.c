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

typedef struct{
  dados memoria_dados;
  int registradores[8];
}back;

void fback(dados *memoria2 , int *registrador, back *reserva,int chose);
void inicializarMemoriaDados(dados *memoria2);
void iniciarReg(int *registrador);
void verReg(int *registrador);
void UC(Memoria *mem, int *count, int *registrador, dados *m2, back *reserva);
void tipo_R(Memoria *mem, int *count);
void tipo_I(Memoria *mem, int *count);
void tipo_J(Memoria *mem, int *count);
void dec_bi(char *output, int k, int *count);
int bi_dec(char *mem);
void carregarMemoria(char *nomeArquivo, Memoria *mem, int *count, int *n_instrucoes);
void decodificarOpcode(Memoria *mem, int *count);
void DadosRegistrador(int *registradores, int dados, int end, int *output, int chose);
void verinstrucoes(Memoria *mem, int *count, int chose, int *n_instrucoes);
void vermemoriadados(dados *memoria2);

int main(){
  back *reserva=malloc(sizeof(back));
  int *n_instrucoes = (int *)malloc(sizeof(int));
  dados *memoria2=malloc(sizeof(dados));
  Memoria mem[256];
  int *count = malloc(sizeof(int));
  int *registrador=malloc(8*sizeof(int));
  iniciarReg(registrador);
  int k=1;
  *count = 0;
  *n_instrucoes = 0;
  inicializarMemoriaDados(memoria2);
  int q=0;
  char *nome=
  malloc(sizeof(char)*51);
  printf("Qual o nome do arquivo de instruções? ");
  fgets(nome, 51, stdin);
  if (nome[strlen(nome)-1] == '\n'){
    nome[strlen(nome)-1] = '\0';
  }
  carregarMemoria(nome, mem, count, n_instrucoes);
  while(k!=8){
    printf("\n\nPC[%i]", *count);
    printf("\n================================\n");
    printf("             MENU\n");
    printf("================================\n");
    printf("1 - (RUN)Executar todo o arquivo\n");
    printf("2 - (STEP)Executar uma linha\n");
    printf("3 - (BACK)Voltar uma instrução\n");
    printf("4 - Ver Registradores\n");
    printf("5 - Ver instrução atual\n");
    printf("6 - Ver todas as instruções\n");
    printf("7 - Ver memória de dados\n");
    printf("8 - Sair\n");
    printf("================================\n");
    printf("Selecione: ");
    scanf("%i",&k);
    getchar();
    switch(k){
      case 1:
        while(*count<*n_instrucoes){
          UC(mem, count, registrador, memoria2, reserva);
          (*count)++;
        }
        break;
      case 2:
        UC(mem, count, registrador,memoria2, reserva);
        (*count)++;  
        break;
      case 3:
        fback(memoria2, registrador, reserva, 1);
        (*count)--; 
        break; 
      case 4:
        verReg(registrador);
        break;
      case 5:
        verinstrucoes(mem,count,0, n_instrucoes);
        break;
      case 6:
        verinstrucoes(mem, count,1, n_instrucoes);
        break;
      case 7:
        vermemoriadados(memoria2);
        break;
      case 8:
        break;
      default:
        printf("Opção inválida\n");
        break;
    }
  }
}

void carregarMemoria(char *nomeArquivo, Memoria *mem, int *count, int *n_instrucoes) {
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
  *n_instrucoes=*count;
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

void UC(Memoria *mem, int *count, int *registrador, dados *m2, back *reserva){
   fback(m2, registrador, reserva, 0);
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
      DadosRegistrador(registrador, *null, mem[*count].rs, valor, 1);
      DadosRegistrador(registrador, *null, mem[*count].rt, valor1, 1);
      if(*valor1==*valor){
         (*count)=(*count)+mem[*count].imm*2-1;
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

void verinstrucoes(Memoria *mem, int *count, int chose, int *n_instrucoes){
  int *count1=malloc(sizeof(int));
  *count1=0;
  if(chose==0){
  printf("\nInstrução [%i]: %s", *count, mem[*count].instrucao);
  }
  else{
    if(*count<*n_instrucoes){
    printf("\nInstrução [%i]: %s", *count, mem[*count].instrucao);
    *count1=*count+1;
    verinstrucoes(mem, count1 ,1, n_instrucoes);
    }
  }
  free(count1);
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

void fback(dados *memoria2 , int *registrador, back *reserva, int chose){
  if(chose == 0 ){
    reserva->memoria_dados=*memoria2;
    for(int i=0;i<8;i++){
      reserva->registradores[i]=registrador[i];
    }
  }
  else{
    *memoria2=reserva->memoria_dados;
    for(int i=0;i<8;i++){
      registrador[i]=reserva->registradores[i];
    }
  }
}
