#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "mips.h"

int main(){
int *registrador=malloc(8*sizeof(int));
iniciarReg(registrador);
int *PC;
PC=(int *)malloc(sizeof(int));
*PC = 0;
Memoria mem[256];
registradorapoio *regitemp;
regitemp=(registradorapoio *)malloc(sizeof(registradorapoio));

int louD=0, EscMem=0, IREsc=0, RegDst=0, EscReg=0, MemParaReg=0, ULAFonteUP=0, ULAFonteDown=0, controleULA=0;

int *muxloaD=(int *)malloc(sizeof(int));


int *muxRegDst=(int *)malloc(sizeof(int));

int *muxMemReg=(int *)malloc(sizeof(int));

int *muxULAdown=(int *)malloc(sizeof(int));

int *muxULAup=(int *)malloc(sizeof(int));

int *muxControleULA=(int *)malloc(sizeof(int));


int *n_instrucoes = (int *)malloc(sizeof(int));

carregarMemoria(mem, n_instrucoes);

if(louD==0){
    *muxloaD=*PC;
}
else{
    *muxloaD=*regitemp->saidaULA;
}

regitemp->dadosmem=mem[*muxloaD].inst;
regitemp->instrucao=mem[*muxloaD];

///////////////////////////////

if(MemParaReg==0){
    *muxMemReg=*regitemp->saidaULA;
}
else{
    *muxMemReg=regitemp->instrucao.inst;
}

if(RegDst==0){
    *muxRegDst=mem[*PC].b8_6;
}
else{
    *muxRegDst=mem[*PC].b5_3;
}

if(EscReg==0){
	regitemp->A=registrador[mem[*PC].b11_9];
    regitemp->B=registrador[mem[*PC].b8_6];
}
else{
    registrador[*muxRegDst]=*muxMemReg;
}

//////////

if(ULAFonteUP==0){
    *muxULAup=*PC;
}
else{
    *muxULAup=regitemp->A;
}

if(ULAFonteDown==0){
    *muxULAdown=regitemp->B;
}
if(ULAFonteDown==1){
	*muxULAdown=1;
}
if(ULAFonteDown==2){
    *muxULAdown=mem[*PC].b5_0;
}

ula(mem[*PC].opcode, *muxULAup , *muxULAdown, regitemp->saidaULA, PC);

if(controleULA==0){
	*muxControleULA=*PC+1;
}

if(controleULA==1){
	*muxControleULA=*regitemp->saidaULA;
}

/////////////

if(controleULA==0){
    if(*PC>63){
	    *muxControleULA=64+mem[*PC].b0_6;
	}
	else{
	    *muxControleULA=mem[*PC].b0_6;	
    }
}

}
