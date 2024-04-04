#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
      char **instrucao;
      int count;
} dados;

void leitor(dados *inf);
//int tam();
void print(dados *inf);

int main(){
	dados inf;
        inf.instrucao=NULL;
        inf.count=0;
        leitor(&inf);
        print(&inf);

        for (int i = 0; i < inf.count; i++) {
            free(inf.instrucao[i]);
        }
        free(inf.instrucao);

        return 0;
}

void  leitor(dados *inf){
  char cache[256];
  FILE *instrucao1 = fopen("instrucoes.txt", "rt");

        while(fgets(cache,sizeof(cache),instrucao1)!=NULL){
          inf->instrucao = realloc(inf->instrucao, (inf->count + 1) * sizeof(char *));
          inf->instrucao[inf->count] = malloc(strlen(cache) + 1);
          strcpy(inf->instrucao[inf->count], cache);
          inf->count++;
        }
	fclose(instrucao1);
}

/*int tam(){
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
}*/

void print(dados *inf){
	for(int i=0;i<inf->count;i++){
		printf("%s", inf->instrucao[i]);
	}
}
