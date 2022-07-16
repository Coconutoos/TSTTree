#ifndef TSTTREE_H
#define TSTTREE_H

typedef struct Node{
    char ch;
    int isEnd;
    struct Node *left, *mid, *right;
} Node;

Node* newNode(char ch);

Node* insertWord(Node* r, char* str);

void printDictionary(Node* r);

void searchWord(Node *r, char* str, char* word);

Node* removeWord(Node* r, char* word);

void printSimilars(Node* r, char *str, int dif);

#endif //TSTTREE_H