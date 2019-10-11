#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "./headers/interpretador.h"
#include "./headers/auxiliares.h"
#include "./headers/comandos.h"

char* rm_quebra_linha(char *texto) 
{
    char *aux = NULL;
    char *txt_final = NULL;
    size_t tam_final = 0;

    aux = (char *) malloc(strlen(texto));

    if (aux != NULL) {  
		int i;  
        for (i = 0; i <= strlen(texto); i++) {
            if (texto[i] != '\n') {
                aux[tam_final++] = texto[i];
            }
        }

        txt_final = (char *) malloc(tam_final);
        if (txt_final != NULL) {
            strcpy(txt_final, aux);
            free(aux);
            return txt_final;
        }
        else
            exit(EXIT_FAILURE);
    }
    else 
        exit(EXIT_FAILURE);
}

int tem_espaco(char *texto) 
{
	int i;
    for (i = 0; i <= strlen(texto); i++) {
            if (texto[i] == ' ') {
                return 1;
            }
        }
    return 0;
}

int tipo_valido(char *texto) 
{
    return (strcmp(texto, "INT") == 0 || strcmp(texto, "FLT") == 0 
    || strcmp(texto, "STR") == 0 || strcmp(texto, "BIN") == 0);
}

void toupper_string(char **string) 
{
    int i = 0;
    while ((*string)[i] != '\0')
    {
        (*string)[i] = toupper((*string)[i]);
        i++;
    }
}

int qtd_campos(char *campos) 
{
    int aux1 = 0;
    int aux2 = 0;

	int i;
    for (i = 0; i < strlen(campos); i++)
    {
        if (campos[i] == ';')
            aux1++;
        if (campos[i] == ':')
            aux2++;
    }

    if (++aux1 != aux2)
        erro_sintaxe(2);
    return aux1;
}

int qtd_registros(char *campos) 
{
    int aux = 0;
	int i;
    for (i = 0; i < strlen(campos); i++)
    {
        if (campos[i] == ';')
            aux++;
    }
    return aux + 1;
}

void imprimir_tabela(Tabela tbl)
{
	int i;
    for (i = 0; i < tbl.num_campos; i++) {
        printf(" %s:%s\n", tbl.campos[i].tipo, tbl.campos[i].nome);
    }
}

void *malloc_safe(unsigned nbytes)
{
 void *p;
 p = malloc(nbytes);
 if (p == NULL)
 {
    printf("Não foi possível alocar memória\n");
    exit(EXIT_FAILURE);
 }
 return p;
}
