#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void leitor();
int tam();
void print();

typedef struct{
        char **instrucao;
}dados;
dados inf;

int main(){
	dados *pointer = &inf;
        inf.instrucao=NULL;
        leitor();
	print();
        return 0;
}

void  leitor(){
        inf.instrucao=malloc((tam())*sizeof(char*));
	for(int i=0;i<(tam());i++){
		inf.instrucao[i]=malloc(17*sizeof(char));
	}
        char *vet;
	int k=0;
        vet=malloc(17*sizeof(char));
        FILE *instrucao1;
        instrucao1 = fopen("instrucoes.txt", "rt");
        while(fgets(vet,17,instrucao1)!=NULL){
                inf.instrucao[k]=vet;
		k++;
        }
	fclose(instrucao1);
}

int tam(){
	char c, letra = '\n';
	int count=0;
	FILE *instrucao1;
        instrucao1 = fopen("instrucoes.txt", "rt");
	while(fread(&c,sizeof(char),1,instrucao1)){
		if(c==letra){
			count++;
		}
	}
        fclose(instrucao1);
	return(count);
}

void print(){
	for(int i=0;i<(tam());i++){
		printf("%s", inf.instrucao[i]);
	}
}
