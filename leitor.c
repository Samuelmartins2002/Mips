#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void leitor();
void tipo_inst();

typedef struct{
        char *instrucao;
}dados;
dados inf;

int main(){
        inf.instrucao=NULL;
        leitor();
        return 0;

}
void leitor(){
        inf.instrucao=malloc(17*sizeof(char));
        char *vet;
        vet=malloc(17*sizeof(char));
        FILE *instrucao1;
        instrucao1 = fopen("instrucoes.txt", "rt");
        if(instrucao1==NULL){
                return;
        }
        while(fgets(vet,17,instrucao1)!=NULL){
                tipo_inst(vet);
        }
}
void tipo_inst(char *dados){
        inf.instrucao=dados;
        char vet[4];
        vet[3]='\0';
        char r[]="010",i[]="001",j[]="000";
        for(int i=0;i<3;i++){
                vet[i]=inf.instrucao[i];
        }
        if(strcmp(vet,r)==0){
        printf("\nTipo R");
        return;
        }
        if(strcmp(vet,i)==0){
        printf("\nTipo I");
        return;
        }
        if(strcmp(vet,j)==0){
        printf("\nTipo J");
        return;
        }
        else{
        printf("\nTipo de instrução inválida");
        return;
        }
}

