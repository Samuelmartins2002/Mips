#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void leitor();
void tipo_inst(char *dados);

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
        if(instrucao1!=NULL){
        fgets(vet,17,instrucao1);
		tipo_inst(vet);
}        
}
void tipo_inst(char *dados){
        inf.instrucao=dados;
        char vet1[4];
        char r[]="010",i[]="001",j[]="000";
        for(int i=0;i<3;i++){
                vet1[i]=inf.instrucao[i];
        }
	printf("%s", vet1);
        if(strcmp(vet1,r)==0){
        printf("\nTipo R");
        }
        if(strcmp(vet1,i)==0){
        printf("\nTipo I");
        }
        if(strcmp(vet1,j)==0){
        printf("\nTipo J");
        }
        else{
        printf("\nTipo de instrução inválida");
        }
}

