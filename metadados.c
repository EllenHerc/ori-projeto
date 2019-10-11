#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "./headers/interpretador.h"
#include "./headers/auxiliares.h"
#include "./headers/comandos.h"
#include "./headers/metadados.h"

int tem_tabela(char *sgdb, char *tabela) 
{
    int tam = 0;
    int achou_tabela = 0;
    char *buffer;
    char *caminho = concatena("./metadados/", sgdb, ".dat");
    FILE *arquivo = fopen(caminho, "ab+");

    if (arquivo != NULL) 
    {
        free(caminho);
        rewind(arquivo);
        while (!achou_tabela && fread(&tam, sizeof(tam), 1, arquivo)) 
        {
            buffer = (char *) malloc_safe(sizeof(char) * (tam + 1));
            fread(buffer, sizeof(char), tam, arquivo);
            buffer[tam] = '\0';
            if (strcmp(buffer, tabela) == 0)
                achou_tabela = 1;

            free(buffer);
        }
        fclose(arquivo);
    }
    else
    {
        printf("Erro ao abrir arquivo (tem_tabela): %s\n", caminho);
        exit(EXIT_FAILURE);
    }

    return achou_tabela;
}

char *concatena(char *prefixo, char *meio, char *posfixo) 
{
    int offset = 0;
    int tam = strlen(prefixo) + strlen(meio) + strlen(posfixo) + 1;
    char *dest = malloc_safe(sizeof(char) * tam);

	int i;
    for (i = 0; i < strlen(prefixo); i++)
    {
        dest[i] = prefixo[i];
    } 

    offset = strlen(prefixo);

    for (i = 0; i < strlen(meio); i++)
    {
        dest[offset + i]  = meio[i];
    }
    offset += strlen(meio);


    for (i = 0; i < strlen(posfixo); i++)
    {
        dest[offset + i]  = posfixo[i];
    }
    dest[tam - 1]  = '\0';

    return dest;
}

void adiciona_tabela(char *sgdb, char *tabela) 
{   
    if (!tem_tabela(sgdb, tabela)) 
    {
        FILE *arquivo;
        int tam = strlen(tabela);
        char *caminho = NULL;

        caminho = concatena("./metadados/", sgdb, ".dat");
        arquivo = fopen(caminho, "ab+");

        if (arquivo != NULL) 
        {
            free(caminho);

            fwrite(&tam, sizeof(tam), 1, arquivo);
            fwrite(tabela, sizeof(char), tam, arquivo);
            fclose(arquivo);
        }
        else 
        {
            printf("Erro ao abrir arquivo (adiciona_tabela): %s\n", caminho);
            exit(EXIT_FAILURE);
        }
    }
    else 
    {
        printf("Tabela '%s' já existe na base de dados\n", tabela);
        exit(EXIT_FAILURE);
    }
}

void remove_tabela(char *tabela)
{
    if (tem_tabela("SGDB/SGDB", tabela)) 
    {
    	int verifica = 0;
        FILE *arquivo;
        int tam;
        char *buffer;
        char *caminho = concatena("./metadados", "/SGDB/SGDB", ".dat");

        arquivo = fopen(caminho, "rb+");
        if (arquivo != NULL) 
        {            

            while (fread(&tam, sizeof(tam), 1, arquivo)) 
            {
                buffer = (char *) malloc_safe(sizeof(char) * (tam + 1));

                fread(buffer, sizeof(char), tam, arquivo);
                buffer[tam] = '\0';

                if (strcmp(buffer, tabela)!=0)
                {
                	verifica = 1;
                    adiciona_tabela("SGDB/temp", buffer);
                }

                free(buffer);
            }
            fclose(arquivo);
        
			remove("./metadados/SGDB/SGDB.dat");	
			rename("./metadados/SGDB/temp.dat", "./metadados/SGDB/SGDB.dat");
            
            
        }
        else 
        {
            printf("Erro ao abrir arquivo (adiciona_tabela): %s\n", caminho);
            exit(EXIT_FAILURE);
        }
    }
    else 
    {
        printf("Tabela '%s' não existe na base de dados\n", tabela);
        exit(EXIT_FAILURE);
    }
}
