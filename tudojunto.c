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

void iniciarReg(int *registrador);
void verReg(int *registrador);
void pc(Memoria *mem, int *count,int *registrador);
void UC(Memoria *mem, int *count, int *registrador);
void tipo_R(Memoria *mem, int *count);
void tipo_I(Memoria *mem, int *count);
void tipo_J(Memoria *mem, int *count);
void dec_bi(char *output, int k, int *count);
int bi_dec(char *mem);
void carregarMemoria(char *nomeArquivo, Memoria *mem, int *count);
void decodificarOpcode(Memoria *mem, int *count);

int main(){
    Memoria mem[256];
    int *count = malloc(sizeof(int));
    int *registrador=malloc(8*sizeof(int));
  iniciarReg(registrador);
  verReg(registrador);


    *count = 0;

    carregarMemoria("instrucoes.txt", mem, count);

    pc(mem, count, registrador);
  verReg(registrador);

  }

void carregarMemoria(char *nomeArquivo, Memoria *mem, int *count) {
    char op[5];
    FILE *arquivo;
    arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    while (fscanf(arquivo, "%16s", mem[*count].instrucao) != EOF && *count < 6) {

        strncpy(op, mem[*count].instrucao, 4);
        mem[*count].opcode=bi_dec(op);
        decodificarOpcode(mem, count);
        (*count)++;
    }

    fclose(arquivo);
    for (int i = 0; i < *count; i++) {
       printf("\n %s\n", mem[i].instrucao);
       printf("rt %i\n", mem[i].rt);
      printf("rd %i\n", mem[i].rd);
      printf("rs %i\n", mem[i].rs);
        printf("imm %i\n", mem[i].imm);
        printf("funct %i\n", mem[i].funct);
        printf("addr %i\n", mem[i].addr);
        printf("op %i\n", mem[i].opcode);
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
  switch(mem[*count].opcode){
    case 0:
      printf("\n Tipo R %s \n", mem[*count].instrucao);
      tipo_R(mem, count);
      break;
    case 4:
      printf("\n Tipo I addi %s \n",mem[*count].instrucao);
      tipo_I(mem, count);
      break;
    case 11:
      printf("\n Tipo I lw %s \n",mem[*count].instrucao );
      tipo_I(mem, count);
      break;
    case 15: 
      printf("\n Tipo I sw %s \n",mem[*count].instrucao );
      tipo_I(mem, count);
      break;
    case 8:
      printf("\n Tipo I beq %s \n",mem[*count].instrucao );
      tipo_I(mem, count);
      break;
    case 2:
      printf("\n Tipo J %s \n", mem[*count].instrucao);
      tipo_J(mem, count);
      break;
    default:
      printf("Instrução inválida\n");
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

void pc(Memoria *mem, int *count,int *registrador){
  if(mem[*count].instrucao[0] == '\0'){
    return;
  }
  else{
    UC(mem, count,registrador);
    pc(mem,count+1,registrador);
  }
}

void UC(Memoria *mem, int *count, int *registrador){
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
      DadosRegistrador(registrador, *output, mem[*count].rd, null, 0);
      break;
 }
}

void verReg(int *registrador){
  for(int i=0;i<8;i++){
  printf("Registrador %i: %i \n",i, registrador[i]);
    }
}

void iniciarReg(int *registrador){
  for(int i=0;i<8;i++){
  registrador[i]=0;
    }
}
