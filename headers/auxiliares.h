#ifndef AUXILIARES_H
#define AUXILIARES_H

typedef struct campo {
    char *tipo;
    char *nome;
} Campo;

typedef struct tabela {
    int num_campos;
    Campo * campos;
} Tabela;

// Recebe uma cadeia de caracteres e retorna um endereço de memória para uma versão dela
// sem quebras de linha.
// @param char *
// @ret   char*
char* rm_quebra_linha(char *texto);

// Recebe um char * e retorna 1 se existe espaços " " e 0 se não.
// @param char *
// @ret   int
int tem_espaco(char *texto);

// Recebe uma cadeia de caracteres e retorna 1 se o ela for um dentre 
// "INT", "FLT", "STR", "BIN".
// @param char *
// @ret   int
int tipo_valido(char *texto);

// Aplica a função toupper(char) para uma string, mas altera na string
// passada como parâmetro, ao invés de retornar.
// @param char *
void toupper_string(char **string);

// Recebe uma cadeia de caracteres e retorna a quantidade de argumentos 
// contidos na string. Se utiliza do número de ; encontrados e compara com
//  : para validar.
// @param char *
// @ret   int
int qtd_campos(char *campos);

// Recebe uma cadeia de caracteres e retorna a quantidade de argumentos 
// contidos na string. Se utiliza do número de ; encontrados.
// @param char *
// @ret   int
int qtd_registros(char *campos);

// Recebe um estrutura do tipo Tabela e imprime todos os pares TIPO:NOME
// @param Tabela
void imprimir_tabela(Tabela tbl);

// Implementação da função malloc() com verificação de NULL ptr
// @param unsigned
// @ret void *
void *malloc_safe(unsigned nbytes);

#endif
