#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int valor;
    int altura;
    struct no* esq;
    struct no* dir;
} NoAVL;

NoAVL* novoNo() {
    NoAVL* no = malloc(sizeof(NoAVL));

    if(!no) {
        perror("Falha ao alocar nó da AVL");
        exit(1);
    }
}
