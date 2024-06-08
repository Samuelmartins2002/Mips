#ifndef MIPS_H
#define MIPS_H

enum comando{add=0, sub=2, Or=4, And=5};

typedef struct {
    char instrucao[17];
    int inst;
    int opcode;
    int b11_9;
    int b8_6;
    int b5_3;
    int b5_0;
    int b0_6;
} Memoria;

typedef struct{
    int memoria_dados[256];
}dados;

typedef struct{
  dados memoria_dados;
  int registradores[8];
  int pc;
}back;

typedef struct{
	int A;
	int B;
	int *saidaULA;
	Memoria instrucao;
	int dadosmem;
}registradorapoio;

void fback(dados *memoria2 , int *registrador, back *reserva,int chose, int *count);
void inicializarMemoriaDados(dados *memoria2);
void iniciarReg(int *registrador);
void verReg(int *registrador);
void UC(Memoria *mem, int *count, int *registrador, dados *m2, back *reserva);
void tipo_R(Memoria *mem, int *count);
void tipo_I(Memoria *mem, int *count);
void tipo_J(Memoria *mem, int *count);
void dec_bi(char *output, int k, int *count);
int bi_dec(char *mem);
int converter_imm(char *imm);
void inverter_bits(char *imm);
void carregarMemoria(Memoria *mem,int *n_instrucoes);
void decodificarOpcode(Memoria *mem, int *count);
void DadosRegistrador(int *registradores, int dados, int end, int *output, int chose);
void verinstrucoes(Memoria *mem, int *count, int chose, int *n_instrucoes);
void vermemoriadados(dados *memoria2);
void salvarAsm(Memoria *mem, int *n_instrucoes);
void salvarDados(dados *memoria2);
void carregarDados(dados *memoria2);
void ula(int funct, int valor, int valor1, int *output, int *count);

#endif
