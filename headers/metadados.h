#ifndef METADADOS_H
#define METADADOS_H

// Recebe um arquivo de metadados do sistema e o nome de uma tabela, e
// verifica se ela esta presente na base.
// @param char *: subpasta e nome do aquivo de metadados (sem extensão)
// @param char *: nome da tabela a ser verificada
// @param    int: 1 para sucesso, 0 para falha
int tem_tabela(char *sgdb, char *tabela);

// Dadas três sequencias de caracteres, retorna uma versão dessas cadeias
// concatenadas. Precisa ser liberado pelo usuário.
// @param char *: primeira parte
// @param char *: segunda parte
// @param char *: terceira parte
char *concatena(char *prefixo, char *meio, char *posfixo);

// Recebe um arquivo de metadados do sistema e o nome de uma tabela, e
// adiciona ela no fim do arquivo. Escreve primeiro o tamanho do nome da
// tabela (sizeof int) e depois o nome da tabela. Encerra a execução se a 
// tabela já existir no sistema.
// @param char *: subpasta e nome do aquivo de metadados (sem extensão)
// @param char *: nome da tabela a ser adicionada
void adiciona_tabela(char *sgdb, char *tabela) ;

// Recebe o nome de uma tabela, e a remove do arquivo de metadados do sistema.
// Encerra a execução se a tabela não existir no sistema.
// @param char *: nome da tabela a ser removida
void remove_tabela(char *tabela);

#endif
