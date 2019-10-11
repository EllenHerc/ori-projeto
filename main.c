#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./headers/interpretador.h"
#include "./headers/auxiliares.h"
#include "./headers/comandos.h"

#define ARQUIVO 1
#define INTERATIVO 0
#define CMD_MAX 200

int modo_exec;
FILE *arquivo = NULL;

int main (int argc, char **argv)
{
    // Definindo o modo de execução
    if (argc == 2) {
        modo_exec = ARQUIVO;
        arquivo = fopen(argv[1], "r");
    }
    else {
        modo_exec = INTERATIVO;
        arquivo = stdin;
    }

    // Se conseguiu abrir o arquivo com sucesso, entra no loop de leitura
    if (arquivo != NULL) {
        char buffer[CMD_MAX];
        if (modo_exec == INTERATIVO)
            printf("> ");

        while (fgets(buffer, CMD_MAX, arquivo) != NULL) {
            char *cmd = rm_quebra_linha(buffer);
            interpreta(cmd);
            free(cmd);

            if (modo_exec == INTERATIVO)
                printf("> ");
        }

        if (modo_exec == ARQUIVO)
            fclose(arquivo);
    } 
    else {
        printf("Problemas ao abrir o arquivo\n");
        exit(EXIT_FAILURE);
    }
    
    return 0;
}
