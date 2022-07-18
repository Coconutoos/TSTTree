#ifndef TSTTREE_H
#define TSTTREE_H

typedef struct Node{
    char ch;
    int isEnd;
    struct Node *left, *mid, *right;
} Node;


// Cria um novo no da arvore TST
//Pre-condicao: Nenhuma
//Pos-condicao: Retorna um ponteiro para o novo no
Node* newNode(char ch);


// Insere uma palavra na arvore
//Pre-condicao: Um ponteiro para node e uma palavra
//Pos-condicao: A palavra e inserida na arvore
Node* insertWord(Node* r, char* str);

// Printa todas as palavras da arvore
//Pre-condicao: Um ponteiro para Node
//Pos-condicao: Nenhuma
void printDictionary(Node* r);

// Procura uma palavra na arvore por prefixo
//Pre-condicao: Um no para Node e uma palavra a ser pesquisada
//Pos-condicao: Imprime ate 10 palavras que comecam com o prefixo dado
void searchWord(Node *r, char* str, char* word);

// Remove uma palavra da arvore
//Pre-condicao: Um no para Node
//Pos-condicao: Retorna um ponteiro para Node e remove a palavra
Node* removeWord(Node* r, char* word);

// Busca palavras que se encaixam na distancia de edicao fornecida
//Pre-condicao: Um ponteiro para Node
//Pos-condicao: Imprime as palavras na arvore que se encaixam
void printSimilars(Node* r, char *str, int dif);

#endif //TSTTREE_H