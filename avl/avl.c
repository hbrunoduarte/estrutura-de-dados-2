#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int chave;
    int altura;
    struct no* esq;
    struct no* dir;
} NoAVL;

NoAVL* novoNo(int chave) {
    NoAVL* no = malloc(sizeof(NoAVL));

    if(!no) {
        perror("Falha ao alocar nó da AVL");
        exit(1);
    }

    no->chave = chave;
    no->dir = NULL;
    no->esq = NULL;

    return no;
}
