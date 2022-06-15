#ifndef APP_H
#define APP_H
#include <stdio.h>
#include "arvore.h"
#include "stdlib.h"

typedef enum {CONSULTAR = 1, IMPRIMIR, STOPWORDS, SAIR} option;

void printMenu();

void getOption(option *aux);

void executeOption(No* root, FILE *f, int option);

FILE* openFile();

void lerDicionarioArquivo(No** r);

void runApp();


#endif