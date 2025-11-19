#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int chave;
    struct no* esq;
    struct no* dir;
} NoAVL;

int fatorBalanceamento(NoAVL* no) {
    return altura(no->esq) - altura(no->dir);
}

int altura(NoAVL* no) {
    if (no == NULL) { 
        return -1;
    } 

    return 1 + max(altura(no->esq), altura(no->dir));
}

int max(int a, int b) {
    if(a > b) {
        return a;
    } else {
        return b;
    }
}

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

NoAVL* rsd(NoAVL* no) {
    NoAVL* x = no->esq;
    NoAVL* y = x->dir;

    x->dir = no;
    no->esq = y;

    return x;
}

NoAVL* rse(NoAVL* no) {
    NoAVL* x = no->dir;
    NoAVL* y = x->esq;

    x->esq = no;
    no->dir = y;

    return x;
}

NoAVL* balancear(NoAVL* no) {
    int fb = fatorBalanceamento(no);

    if (fb > 1 && fatorBalanceamento(no->esq) >= 0) {
        return rsd(no);
    }

    if (fb < -1 && fatorBalanceamento(no->dir) <= 0) {
        return rse(no);
    }

    if (fb > 1 && fatorBalanceamento(no->esq) < 0) {
        no->esq = rse(no->esq);
        return rsd(no);
    }

    if (fb < -1 && fatorBalanceamento(no->dir) > 0) {
        no->dir = rsd(no->dir);
        return rsd(no);
    }

    return no;
}

NoAVL* inserir(NoAVL* raiz, int chave) {
    if(raiz == NULL) {
        return novoNo(chave);
    }

    if(chave < raiz->chave) {
        raiz->esq = inserir(raiz->esq, chave);
    } else if(chave > raiz->chave) {
        raiz->dir = inserir(raiz->dir, chave);
    } else {
        return raiz;
    }

    return balancear(raiz);
}

NoAVL* remover(NoAVL* raiz, int chave) {
    if(raiz == NULL) {
        return raiz;
    }

    if(chave < raiz->chave) {
        raiz->esq = remover(raiz->esq, chave);
    } else if(chave > raiz->chave) {
        raiz->dir = remove(raiz->dir, chave);
    } else {
        // casos
    }

    return balancear(raiz);
}

void preOrdem(NoAVL* raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->chave);
        preOrdem(raiz->esq);
        preOrdem(raiz->dir);
    }
}

void emOrdem(NoAVL* raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esq);
        printf("%d ", raiz->chave);
        emOrdem(raiz->dir);
    }
}

void posOrdem(NoAVL* raiz) {
    if (raiz != NULL) {
        posOrdem(raiz->esq);
        posOrdem(raiz->dir);
        printf("%d ", raiz->chave);
    }
}

