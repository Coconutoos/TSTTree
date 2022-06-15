#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"

No* novoNo(char letra){
    No* novoNo = (No*) malloc(sizeof(No));
    novoNo->letra = letra;
    novoNo->ehFim = 0;
    novoNo->esq = novoNo->meio = novoNo->dir = NULL;
    return novoNo;
}

void inserePalavra(No** r, char* str){
    if(*r == NULL)
        *r = novoNo(*str);
    if((*str) < (*r)->letra)
        inserePalavra(&((*r)->esq), str);
    else{
        if ((*str) > (*r)->letra)
            inserePalavra(&((*r)->dir), str);
        else{
            if (*(str+1))
                inserePalavra(&((*r)->meio), str+1);
            else
                (*r)->ehFim = 1;
        }
    }
}

void imprimeDicionarioAux(No* r, char* palavra, int n){
    if(r == NULL)
        return;

    imprimeDicionarioAux(r->esq, palavra, n);

    palavra[n] = r->letra;
    if(r->ehFim){
        palavra[n+1] = '\0';
        printf("%s\n", palavra);
    }

    imprimeDicionarioAux(r->meio, palavra, n+1);
    imprimeDicionarioAux(r->dir, palavra, n);
}

void imprimeDicionario(No* r){
    char palavra[50];
    imprimeDicionarioAux(r, palavra, 0);
}

void imprimePalavraAux(No* r, char* inicioPalavra, char* fimPalavra, int n, int* limite){
    if(r == NULL || *limite <= 0)
        return;

    imprimePalavraAux(r->esq, inicioPalavra, fimPalavra, n, limite);

    fimPalavra[n] = r->letra;
    if(r->ehFim){
        (*limite)--;
        fimPalavra[n+1] = '\0';
        printf("%s%s\n", inicioPalavra, fimPalavra);
    }

    imprimePalavraAux(r->meio, inicioPalavra, fimPalavra, n+1, limite);
    imprimePalavraAux(r->dir, inicioPalavra, fimPalavra, n, limite);
}

void imprimePalavra(No* r, char* inicioPalavra, int f){
    char fimPalavra[50];
    int limite = 10-f;
    imprimePalavraAux(r, inicioPalavra, fimPalavra, 0, &limite);
}

void consultarPalavra(No *r, char* str, char* palavra){
    if(r == NULL)
        return;
    if(*str < (r)->letra)
        consultarPalavra(r->esq, str, palavra);
    else{
        if(*str > (r)->letra)
            consultarPalavra(r->dir, str, palavra);
        else{
            if(*(str+1) == '\0'){
                if(r->ehFim)printf("%s\n", palavra);
                imprimePalavra(r->meio, palavra, r->ehFim);
                return;
            }
            consultarPalavra(r->meio, str+1, palavra);
        }
    }
}

int contaFilhos(No *node){
    return (node->esq != NULL) + (node->meio != NULL) + (node->dir != NULL);
}

No* removePalavra(No* r, char* palavra){
    if(r == NULL)
        return NULL;

    int filhos = contaFilhos(r);

    if(*palavra < r->letra)
        r->esq = removePalavra(r->esq, palavra);

    else {
        if ( *palavra > r->letra)
            r->dir = removePalavra(r->dir, palavra);

        else{
            if (*(palavra + 1))
                r->meio = removePalavra(r->meio, palavra + 1);

            else{
                if (r->ehFim == 1){
                    if (filhos > 0)
                        r->ehFim = 0;

                    else{
                        free(r);
                        return NULL;
                    }
                }
            }
        }
    }

    if (filhos != contaFilhos(r) && filhos == 1 && r->ehFim == 0){
        free(r);
        return NULL;
    }

    return r;
}
