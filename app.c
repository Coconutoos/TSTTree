#include "app.h"
#include <string.h>

void printMenu(){
  printf("1. Consultar palavra\n");
  printf("2. Imprimir Dicionario\n");
  printf("3. Carregar arquivo de StopWords\n");
  printf("4. Sair\n");
}

void getOption(option *aux){
  scanf("%u%*c", aux);
  while(*aux < CONSULTAR || *aux > SAIR){
    printf("Opcao invalida, digite novamente\n");
    scanf("%u%*c", aux);
  }
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

void lerDicionarioArquivo(No** r){
  char aux[100], buffer;
  FILE *f;
  f = openFile();
  int n;
  while(fgets(aux, 100, f)){
    n = strcspn(aux, "\n");
    aux[n] = 0;
    inserePalavra(r, aux);
  }
  fclose(f);
}

void runApp() {
    No *root;
    char search[50];
    option op;

    lerDicionarioArquivo(&root);

    printf("Dicionario Carregado!\n");

    while(1) {
        printMenu();
        getOption(&op);
        switch(op){
            case CONSULTAR:
                scanf("%s%*c", search);
                consultarPalavra(root, search, search);
                break;
            case IMPRIMIR:
                imprimeDicionario(root);
                break;
            case STOPWORDS:
                printf("Stop words\n");
                break;
            case SAIR:
                return;
        };
    }
}