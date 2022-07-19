#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "tst_tree.h"

Node* newNode(char ch){
    Node* aux = (Node*) malloc(sizeof(Node));
    aux->ch = ch;
    aux->isEnd = 0;
    aux->left = aux->mid = aux->right = NULL;
    return aux;
}

Node* insertWord(Node* r, char* str){
  if(r == NULL)
		r = newNode(*str);

	if(r->ch == *str){
		if(*(str+1))
			r->mid = insertWord(r->mid, str+1);
		else
			r->isEnd=1;
	}
	else{
		if(r->ch > *str)
			r->left = insertWord(r->left, str);
		else
			r->right = insertWord(r->right, str);
	}

	return r;
}

void printDictionaryAux(Node* r, char* word, int n){
    if(r == NULL)
        return;

    printDictionaryAux(r->left, word, n);

    word[n] = r->ch;
    if(r->isEnd){
        word[n+1] = '\0';
        printf("%s\n", word);
    }

    printDictionaryAux(r->mid, word, n+1);
    printDictionaryAux(r->right, word, n);
}

void printDictionary(Node* r){
    char word[50];
    printDictionaryAux(r, word, 0);
}

void printVet(char words[][50], int j){
    int i;
    for(i=0; i<j-1; i++)
        printf("%s, ", words[i]);
    printf("%s\n", words[i]);
}

void printWordAux(Node* r, char words[][50], char* end, int n, int t, int* i){
    if(r == NULL || *i >=10)
        return;

    printWordAux(r->left, words, end, n, t, i);

    end[n] = r->ch;
    if(r->isEnd){
        end[n+1] = '\0';
        strcpy(words[*i]+t, end);
        (*i)++;
    }

    printWordAux(r->mid, words, end, n+1, t, i);
    printWordAux(r->right, words, end, n, t, i);
}

void printWord(Node* r, char words[][50], int t, int i){
    char end[50];
    printWordAux(r, words, end, 0, t, &i);
    printVet(words, i);
}

void addToVet(char words[][50], char str[]){
    int i;
    for(i=0; i<10; i++)
        strcpy(words[i], str);
}

void searchWord(Node *r, char* str, char* word){
    if(r == NULL)
        return;
    if(*str < (r)->ch)
        searchWord(r->left, str, word);
    else{
        if(*str > (r)->ch)
            searchWord(r->right, str, word);
        else{
            if(*(str+1) == '\0'){
                char words[10][50];
                addToVet(words, word);
                printWord(r->mid, words, strlen(word),r->isEnd);
                return;
            }
            searchWord(r->mid, str+1, word);
        }
    }
}

int countChild(Node *node){
    return (node->left != NULL) + (node->mid != NULL) + (node->right != NULL);
}

Node* removeWord(Node* r, char* word){
    if(r == NULL)
        return NULL;

    int childs = countChild(r);

    if(*word < r->ch)
        r->left = removeWord(r->left, word);

    else {
        if ( *word > r->ch)
            r->right = removeWord(r->right, word);
        else{
            if (*(word + 1))
                r->mid = removeWord(r->mid, word + 1);
            else{
                if (r->isEnd == 1){
                    if (childs > 0)
                        r->isEnd = 0;
                    else{
                        free(r);
                        return NULL;
                    }
                }
            }
        }
    }

    if (childs != countChild(r) && childs == 1 && r->isEnd == 0){
        free(r);
        return NULL;
    }

    return r;
}

void validateDif(char str[], char word[], int dif){
	int i, d;

	d = abs(strlen(str) - strlen(word));

	for(i=0; str[i] && word[i]; i++)
		if(str[i] != word[i]) d++;

	if(d <= dif)
		printf("%s\n", word);
}

void printSimilarsAux(Node* r, char *str, char *word, int dif, int n){
    if(r == NULL)
        return;

    printSimilarsAux(r->left, str, word, dif, n);

    word[n] = r->ch;
    if(r->isEnd){
        word[n+1] = '\0';
				validateDif(str, word, dif);
    }

    printSimilarsAux(r->mid, str, word, dif, n+1);
    printSimilarsAux(r->right, str, word, dif, n);
}

void printSimilars(Node* r, char *str, int dif){
    char word[50];
    printSimilarsAux(r, str, word, dif, 0);
}
