#ifndef APP_H
#define APP_H
#include <stdio.h>
#include "tst_tree.h"
#include "stdlib.h"

typedef enum {CONSULTAR = 1, IMPRIMIR, STOPWORDS, SEMELHANTES, SAIR} option;

//Printa o menu com as opcoes possiveis
//Pre-condicao: Nenhuma
//Pos-condicao: O menu eh printado na tela
void printMenu();

// Le a opcao do teclado e verifica se eh valida, retorna a opcao selecionada
//Pre-condicao: Nenhuma
//Pos-condicao: A opcao selecionada eh retornada
option getOption();

// Le o nome de arquivo do teclado ate um arquivo ser encontrado, retorna o ponteiro para a stream
//Pre-condicao: Uma stream para arquivo, um arquivo valido para entrada
//Pos-condicao: O ponteiro para a stream eh retornada
FILE* openFile();

// Insere as palavras do dicionario na arvore
//Pre-condicao: Um ponteiro para Node, um arquivo valido para entrada
//Pos-condicao: Um ponteiro para Node contendo as palavras do dicionario eh retornado
Node* readDictionaryFile();

// Remove as palavras do arquivo da arvore
//Pre-condicao: Um ponteiro para Node, um arquivo valido para entrada
//Pos-condicao: Um pontiero para Node com as palavras removidas eh retornado
Node* readStopWordsFile(Node* r);

void similars(Node* r);

// Gerencia a execucao do programa, inicializa o dicionario na arvore e controla o fluxo do menu
//Pre-condicao: Nenhuma
//Pos-condicao: Nenhuma
void runApp();

#endif