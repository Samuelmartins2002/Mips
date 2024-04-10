#include <stdio.h>
#include <string.h>

typedef enum {
    RT0,
    RT1,
    RT2,
    RT3,
    RT4,
    RT5,
    RT6,
    RT7,
    NUMREG
} RegistradorEnum;

typedef struct {
    char valor[8];
    RegistradorEnum regs;
} BancoRegistrador;

void escreverRegistro(BancoRegistrador *registrador, RegistradorEnum indice, char *valor);
const char* getRegistrador(RegistradorEnum regs);
void salvarRegistradores(BancoRegistrador *registrador);

int main() {
    BancoRegistrador registrador[NUMREG];

    escreverRegistro(registrador, RT0, "10");
    escreverRegistro(registrador, RT1, "20");
    escreverRegistro(registrador, RT2, "35");
    escreverRegistro(registrador, RT3, "45");

    salvarRegistradores(registrador);

    for (int i = RT0; i < NUMREG; i++) {
        printf("%s, %d, %s\n", getRegistrador(registrador[i].regs), registrador[i].regs, registrador[i].valor);
    }
    return 0;
}

void escreverRegistro(BancoRegistrador *registrador, RegistradorEnum indice, char *valor) {
    strcpy(registrador[indice].valor, valor);
    registrador[indice].regs = indice;
}

void salvarRegistradores(BancoRegistrador *registrador) {
    FILE *arquivo;
    arquivo = fopen("registradores.txt", "w");

    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo de registradores.\n");
    }

    for (int i = 0; i < NUMREG; i++) {
        fprintf(arquivo, "%s, %s\n", getRegistrador(registrador[i].regs), registrador[i].valor);
    }

    fclose(arquivo);

    printf("Registradores salvos no arquivo 'registradores.txt'.\n");
}

const char * getRegistrador(RegistradorEnum regs) {
    switch (regs) {
        case RT0:
            return "RTO";
        case RT1:
            return "RT1";
        case RT2:
            return "RT2";
        case RT3:
            return "RT3";
        case RT4:
            return "RT4";
        case RT5:
            return "RT5";
        case RT6:
            return "RT6";
        case RT7:
            return "RT7";
        default:
            return "Desconhecido";
    }
}
