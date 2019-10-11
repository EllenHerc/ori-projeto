#ifndef INTERPRETADOR_H
#define INTERPRETADOR_H

// Encerra o programa quando um erro de sintaxe acontece. Recebe um inteiro que
// representa que tipo de erro ocorreu.
// C�digos de erro:
// 1: no comando
// 2: nos argumentos (quantidade ou formata��o)
// 3: nos tipos dos argumentos
// 4: espa�os indevidos
// @param int: c�digo do erro
void erro_sintaxe(int tipo);

// Recebe uma cadeia de caracteres de um comando e o decodifica, enviando para 
// a fun��o adequada. Pode chamar erro de sintaxe caso n�o reconhe�a o comando.
// @param char *: string a ser decodificada
void interpreta(char *comando);

#endif
