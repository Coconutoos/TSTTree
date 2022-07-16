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

void printWordAux(Node* r, char* beginning, char* end, int n, int* limit){
    if(r == NULL || *limit <= 0)
        return;

    printWordAux(r->left, beginning, end, n, limit);

    end[n] = r->ch;
    if(r->isEnd){
        (*limit)--;
        end[n+1] = '\0';
        printf("%s%s\n", beginning, end);
    }

    printWordAux(r->mid, beginning, end, n+1, limit);
    printWordAux(r->right, beginning, end, n, limit);
}

void printWord(Node* r, char* beginning, int f){
    char end[50];
    int limit = 10-f;
    printWordAux(r, beginning, end, 0, &limit);
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
                if(r->isEnd) printf("%s\n", word);
                printWord(r->mid, word, r->isEnd);
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