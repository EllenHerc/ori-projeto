#ifndef COMANDOS_H
#define COMANDOS_H

// Encerra a interpretac�a~o e termina a execuc�a~o do programa.
void EB();

// Lista o nome de todas as tabelas existentes na base.
void LT();

// Busca em tabela os registros que satisfac�am o crite�rio busca. Os modos de
// opera��o s�o unico ou todos.
// @param char  : N (todos) ou U (primeiro)
// @param char *: em qual tabela deve-se procurar
// @param char *: o que deve ser procurado, no formado CAMPO:NOME
void BR(char modo, char *tabela, char *busca);

// Cria um �ndice estruturado em �rvore ou usando hashing para certa tabela,
// usando chave como chave de busca. Atualiza os metadados.
// @param char  : A (�rvore) ou H (hashing)
// @param char *: em qual tabela deve-se criar o �ndice
// @param char *: chave de busca
void CI(char modo, char* tabela, char* chave);

// Cria um arquivo vazio associado ao nome tabela e o registra como ativo na 
// base, sendo campos uma lista de especificac�o~es dos campos que formara~o o 
// arquivo.
// @param char *: string que cont�m o nome da tabela a ser criada
// @param char *: cont�m o tipo e nome dos campos da tabela no formato 
// tipo:nome, onde cada par � separado por ;
void CT(char *tabela, char *campos);

// Insere o registro no arquivo de tabela, usando a poli�tica de inserc�a~o
// adequada.
// @param char *: tabela na qual deve-se realizar a opera��o
// @param char *: dados do registro a ser adicionado, separados por ;
void IR(char *tabela, char *registro);

// Remove o i�ndice relativo a` chave, atualizando os metadados e apagando as 
// estruturas envolvidas.
// @param char *: tabela na qual deve-se realizar a opera��o
// @param char *: identificador do �ndice a ser apagado
void RI(char *tabela, char *chave);

// Gera novamente o i�ndice de tabela referente a` chave, partindo do zero.
// @param char *: tabela na qual deve-se realizar a opera��o
// @param char *: identificador do �ndice a ser gerado
void GI(char *tabela, char *chave);

// Apaga o arquivo relativo a tabela e remove seus metadados da base, bem como 
// estruturas associadas.
// @param char *: tabela na qual deve-se realizar a opera��o 
void RT(char *tabela);

// Apresenta um resumo dos metadados da tabela indicada: arquivos, campos e 
// i�ndices existentes.
// @param char *: tabela na qual deve-se realizar a opera��o
void AT(char *tabela);

// Apresenta na tela os valores dos registros retornados pela u�ltima busca.
// @param char *: tabela na qual deve-se realizar a opera��o
void AR(char *tabela);

// Remove, segundo a poli�tica de remoc�a~o da tabela, todos os registros da
// �ltima busca realizada.
// @param char *: tabela na qual deve-se realizar a opera��o
void RR(char *tabela);

#endif
