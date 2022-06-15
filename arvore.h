#ifndef ARVORE_H
#define ARVORE_H

typedef struct No{
    char letra;
    int ehFim;
    struct No *esq, *meio, *dir;
} No;

No* novoNo(char letra);

void inserePalavra(No** r, char* str);

void imprimeDicionario(No* r);

void consultarPalavra(No *r, char* str, char* palavra);

No* removePalavra(No* r, char* palavra);

#endif //ARVORE_H