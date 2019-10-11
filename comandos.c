#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "./headers/interpretador.h"
#include "./headers/auxiliares.h"
#include "./headers/comandos.h"
#include "./headers/metadados.h"

void EB() 
{
    printf("Encerrando execução\n"),
    exit(0);
}

void LT() 
{
    FILE *arquivo = fopen("./metadados/SGDB/SGDB.dat", "ab+");
    rewind(arquivo);
    if (arquivo != NULL) 
    {
        int tam;
        char *buffer;
        
        if (fread(&tam, sizeof(tam), 1, arquivo))
        {
            printf("Listando tabelas: \n");
            do 
            {
                buffer = (char *) malloc_safe(sizeof(char) * (tam + 1));
                fread(buffer, sizeof(char), tam, arquivo);
                buffer[tam] = '\0';

                printf(" '%s'\n", buffer);

                free(buffer);
            } while (fread(&tam, sizeof(tam), 1, arquivo));
        }
        else
            printf("Não há tabelas na base de dados\n");

        fclose(arquivo);
    }
    else
    {
        printf("Erro ao abrir arquivo (tem_tabela): ./metadados/SGDB/SGDB.dat\n");
        exit(EXIT_FAILURE);
    }
}

void BR(char modo, char *tabela, char *busca) 
{
    Campo tabela_cmps;
    // Separando o nome do campo
    tabela_cmps.tipo = strtok(busca, ":");
    if (tabela_cmps.tipo == NULL || tem_espaco(tabela_cmps.tipo))
        erro_sintaxe(4);

    // Separando a chave a ser procurada
    tabela_cmps.nome = strtok(NULL, ":\n\0");
    if (tabela_cmps.nome == NULL)
        erro_sintaxe(2);
}

void CI(char modo, char* tabela, char* chave) 
{
}

void CT(char *tabela, char *campos) 
{
    Tabela tbl;
    tbl.num_campos = qtd_campos(campos);
    tbl.campos = (Campo *) malloc_safe(tbl.num_campos * sizeof(Campo));

    // Recortando 'campos' e colocando em 'tbl'
    tbl.campos[0].tipo = strtok(campos, ":");
    toupper_string(&tbl.campos[0].tipo);
    if (!tipo_valido(tbl.campos[0].tipo))
        erro_sintaxe(3);

    tbl.campos[0].nome = strtok(NULL, ":;");
    if (tem_espaco(tbl.campos[0].nome))
        erro_sintaxe(4);
	
	int i;
    for (i = 1; i < tbl.num_campos; i++) 
    {
        tbl.campos[i].tipo = strtok(NULL, " :");
        toupper_string(&tbl.campos[i].tipo);
        if (!tipo_valido(tbl.campos[i].tipo))
            erro_sintaxe(3);
        tbl.campos[i].nome = strtok(NULL, ":;");
        if (tem_espaco(tbl.campos[i].nome))
            erro_sintaxe(4);
    }

    // Adicionando tabela no banco de tabelas do sistema
    adiciona_tabela("SGDB/SGDB", tabela);

    // Criando arquivos com os metadados da tabela recém criada
    int temp;
    char *caminho = concatena("./metadados/", tabela, ".dat");
    FILE *arquivo = fopen(caminho, "wb+");

    if (arquivo != NULL)
    {
        free(caminho);

        fwrite(&tbl.num_campos, sizeof(int), 1, arquivo);
        int i;
        for (i = 0; i < tbl.num_campos; i++) 
        {
            // Escrevendo tipo do campo
            temp = strlen(tbl.campos[i].tipo);
            fwrite(&temp, sizeof(int), 1, arquivo);
            fwrite(tbl.campos[i].tipo, sizeof(char), temp, arquivo);

            // Escrevendo nome do campo
            temp = strlen(tbl.campos[i].nome);
            fwrite(&temp, sizeof(int), 1, arquivo);
            fwrite(tbl.campos[i].nome, sizeof(char), temp, arquivo);

        }
        fclose(arquivo);
    }
    else
    {
        printf("Erro ao abrir arquivo (CT): %s\n", caminho);
        exit(EXIT_FAILURE);
    }

    // Criando arquivo de tabela
    caminho = concatena("./tabelas/", tabela, ".dat");
    arquivo = fopen(caminho, "wb");
    if (arquivo != NULL)
    {
        free(caminho);
        fclose(arquivo);
    }
    else
    {
        printf("Erro ao abrir arquivo (CT): %s\n", caminho);
        exit(EXIT_FAILURE);
    }

    // Imprimindo para conferência dos dados
    // printf("COMANDO: CT\n");
    // printf("TABELA: %s\n", tabela);
    // imprimir_tabela(tbl);

    printf("Tabela '%s' adicionada com sucesso\n", tabela);

    free(tbl.campos);
}

void IR(char *tabela, char *registro) {
    int num_regs = qtd_registros(registro);
    char *tabela_regs[num_regs];

    tabela_regs[0] = strtok(registro, ";");
    int i;
    for (i = 1; i < num_regs; i++)
        tabela_regs[i] = strtok(NULL, ";");
}

void RI(char *tabela, char *chave) 
{
}

void GI(char *tabela, char *chave) 
{
}

void RT(char *tabela) 
{
    char *caminho;

    remove_tabela(tabela);
    
    caminho = concatena("./metadados/", tabela, ".dat");
    if (remove(caminho) != 0) 
    {
        printf("Erro ao excluir arquivo (RT): %s\n", caminho);
        exit(EXIT_FAILURE);
    }
    free(caminho);

    caminho = concatena("./tabelas/", tabela, ".dat");
    if (remove(caminho) != 0) 
    {
        printf("Erro ao excluir arquivo (RT): %s\n", caminho);
        exit(EXIT_FAILURE);
    }
    free(caminho);

    printf("Tabela '%s' removida com sucesso\n", tabela);
}

void AT(char *tabela) 
{
    if (!tem_tabela("SGDB/SGDB", tabela))
    {
        printf("Tabela '%s' não existe na base de dados\n", tabela);
        exit(EXIT_FAILURE);
    }
    
    char *caminho = concatena("./metadados/", tabela, ".dat");
    FILE *arquivo = fopen(caminho, "rb+");
    Tabela tbl;

    if (arquivo != NULL)
    {
        free(caminho);
        int temp;

        fread(&(tbl.num_campos), sizeof(int), 1, arquivo); // Lê o número de campos da tabela
        tbl.campos = (Campo *) malloc_safe(tbl.num_campos * sizeof(Campo));

		int i;
        for (i = 0; i < tbl.num_campos; i++) 
        {
            // Lendo o tipo do campo
            fread(&temp, sizeof(int), 1, arquivo);
            tbl.campos[i].tipo = (char *) malloc_safe( sizeof(char) * (temp + 1) );
            fread((tbl.campos)[i].tipo, sizeof(char), temp, arquivo);
            tbl.campos[i].tipo[temp] = '\0';

            // Lendo o nome do campo
            fread(&temp, sizeof(int), 1, arquivo);
            tbl.campos[i].nome = (char *) malloc_safe( sizeof(char) * (temp + 1) );
            fread(tbl.campos[i].nome, sizeof(char), temp, arquivo);
            tbl.campos[i].nome[temp] = '\0';

        }

        fclose(arquivo);
    }
    else
    {
        printf("Erro ao abrir arquivo (AT): %s\n", caminho);
        exit(EXIT_FAILURE);
    }

    printf("Mostrando informações de '%s'\n", tabela);
    imprimir_tabela(tbl);
    
    int i;
    for (i = 0; i < tbl.num_campos; i++) {
        free(tbl.campos[i].tipo);
        free(tbl.campos[i].nome);
    }
    free(tbl.campos);
}

void AR(char *tabela) 
{
}

void RR(char *tabela) 
{
}
