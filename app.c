#include "app.h"
#include <string.h>

void printMenu(){
    printf("\n ---------------------------------\n");
    printf("|1. Consultar palavra             |\n");
    printf("|2. Imprimir Dicionario           |\n");
    printf("|3. Carregar arquivo de StopWords |\n");
    printf("|4. Sair                          |\n");
    printf(" ---------------------------------\n");
}

option getOption(){
    option aux;
    scanf("%u%*c", &aux);
    while(aux < CONSULTAR || aux > SAIR){
        printf("Opcao invalida, digite novamente\n");
        scanf("%u%*c", &aux);
    }
    return aux;
}

FILE* openFile(){
    FILE* aux;
    char fn[50];
    printf("Digite o nome do arquivo dicionario: ");
    scanf("%s%*c", fn);
    aux = fopen(fn, "r");
    while(aux == NULL){
        printf("Arquivo nao encontrado, digite novamente\n");
        scanf("%s%*c", fn);
        aux = fopen(fn, "r");
    };
    return aux;
}

Node* readDictionaryFile(Node* r){
    char aux[100];
    FILE *f;
    f = openFile();

    while(fscanf(f, "%s%*c", aux) != EOF)
        r = insertWord(r, aux);

    fclose(f);
    return r;
}

Node* readStopWordsFile(Node* r){
    char aux[100];
    FILE *f;
    f = openFile();

    while(fscanf(f, "%s%*c", aux) != EOF)
        r = removeWord(r, aux);

    fclose(f);
    return r;
}

void runApp() {
    Node* root = NULL;
    char search[50];
    option op;

    root = readDictionaryFile(root);

    printf("Dicionario Carregado!\n");

    while(1){
        printMenu();
        op = getOption();
        switch(op){
            case CONSULTAR:
                scanf("%s%*c", search);
                printf("\n===================================\n");
                searchWord(root, search, search);
                printf("===================================\n");
                printf("Prefixo pesquisado: %s\n", search);
                printf("===================================\n\n");
                break;

            case IMPRIMIR:
                printf("===================================\n");
                printDictionary(root);
                printf("===================================\n\n");
                break;

            case STOPWORDS:
                root = readStopWordsFile(root);
                printf("\nStopWords executado com sucesso!\n");
                break;
            case SAIR:
                return;
        };
    }
}