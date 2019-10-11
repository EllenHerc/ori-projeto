#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "./headers/interpretador.h"
#include "./headers/auxiliares.h"
#include "./headers/comandos.h"

void erro_sintaxe(int tipo) {
    switch (tipo) {
        case 1:
            printf("Erro no comando\n");
        break;
        case 2:
            printf("Erro nos argumentos\n");
        break;
        case 3:
            printf("Erro nos tipos\n");
        break;
        case 4:
            printf("Espaço em local não permitido\n");
        break;
    }
    printf("Encerrando execução\n");
    exit(1);
}

void interpreta(char *comando) {
    // Separando o OPCODE
    char *opcode = strtok(comando, " \n");
    if (opcode == NULL)
        return;
    toupper_string(&opcode);

    // Comando que não recebem argumentos
    if (strcmp(opcode, "EB") == 0) {
        EB();
        return;
    }
    
    if (strcmp(opcode, "LT") == 0) {
        LT();
        return;
    }

    // Comandos que recebem um argumento
    // Separando o primeiro argumento
    char *arg1 = strtok(NULL, " ");
    if (arg1 == NULL)
        erro_sintaxe(2);

    if (strcmp(opcode, "RT") == 0) {
        char *tabela = arg1;
        RT(tabela);
        return;
    }

    if (strcmp(opcode, "AT") == 0) {
        char *tabela = arg1;
        AT(tabela);
        return;
    }

    if (strcmp(opcode, "AR") == 0) {
        char *tabela = arg1;
        AR(tabela);
        return;
    }

    if (strcmp(opcode, "RR") == 0) {
        char *tabela = arg1;
        RR(tabela);
        return;
    }

    // Comandos que recebem dois argumentos
    char *arg2 = strtok(NULL, "\0");
    if (arg2 == NULL)
        erro_sintaxe(2);

    if (strcmp(opcode, "CT") == 0) {
        char *tabela = arg1;
        char *campos = arg2;
        CT(tabela, campos);
        return;
    }

    if (strcmp(opcode, "IR") == 0) {
        char *tabela = arg1;
        char *registro = arg2;
        IR(tabela, registro);
        return;
    }

    if (strcmp(opcode, "RI") == 0) {
        char *tabela = arg1;
        char *chave = arg2;
        RI(tabela, chave);
        return;
    }

    if (strcmp(opcode, "GI") == 0) {
        char *tabela = arg1;
        char *chave = arg2;
        GI(tabela, chave);
        return;
    }

    // Comandos que recebem três argumentos
    // ARG2 utilizado para separar a próxima parte do código
    char *temp = strtok(arg2, " ");
    if (temp == NULL)
        erro_sintaxe(2);
    // Separando o terceiro argumento
    char *arg3 = strtok(NULL, "\0");
    if (arg3 == NULL)
        erro_sintaxe(2);

    if (strcmp(opcode, "BR") == 0) {
        char modo = toupper(arg1[0]);
        if (modo != 'N' && modo != 'U')
            erro_sintaxe(3);
        char *tabela = temp;
        char *busca = arg3;
        BR(modo, tabela, busca);
        return;
    }

    if (strcmp(opcode, "CI") == 0) {
        char modo = toupper(arg1[0]);
        if (modo != 'A' && modo != 'H')
            erro_sintaxe(3);
        char *tabela = temp;
        char *chave = arg3;
        CI(modo, tabela, chave);
        return;
    }

    erro_sintaxe(1);  
}
