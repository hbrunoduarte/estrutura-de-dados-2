#include <stdio.h>
#include <stdlib.h>

#define ALFABETO 26

typedef struct no {
    struct no* filhos[ALFABETO];
    int fimDePalavra;
} NoTrie;

typedef struct arvore {
    NoTrie* raiz;
} ArvoreTrie;

NoTrie* novoNo() {
    NoTrie* no = malloc(sizeof(NoTrie));

    if(!no) {
        perror("Falha ao alocar nó da Trie");
        exit(1);
    }

    no->fimDePalavra = 0;

    for(int i = 0; i < ALFABETO; i++) {
        no->filhos[i] = NULL;
    }

    return no;
}

ArvoreTrie* criaTrie() {
    ArvoreTrie* T = malloc(sizeof(ArvoreTrie));

    if(!T) {
        perror("Falha ao alocar Árvore Trie");
        exit(1);
    }

    T->raiz = novoNo();

    return T;
}

void inserirPalavra(ArvoreTrie* T, const char* palavra) {
    NoTrie* aux = T->raiz;

    for(int i = 0; palavra[i] != '\0'; i++) {
        int indice = palavra[i] - 'a'; // transforma em indice (0 - 25)

        if(aux->filhos[indice] != NULL) {
            aux->filhos[indice] = novoNo();
        }

        aux = aux->filhos[indice];
    }

    aux->fimDePalavra = 1;
}

int buscarPalavra(ArvoreTrie* T, const char* palavra) {
    NoTrie* aux = T->raiz;

    for(int i = 0; palavra[i] != '\0'; i++) {
        int indice = palavra[i] - 'a';

        if(aux->filhos[i] == NULL) {
            return 0;
        }

        aux = aux->filhos[indice];
    }
    
    return aux->fimDePalavra;
}

int temFilhos(NoTrie* no) {
    for(int i = 0; i < ALFABETO; i++) {
        if(no->filhos[i] != NULL) {
            return 1;
        }
    }
    return 0;
}

int removeAux(NoTrie* no, const char* palavra, int profundidade, int tamanho) {
    if(profundidade == tamanho) {

        if(no->fimDePalavra == 0) {
            return 0;
        }

        no->fimDePalavra = 0;

        return !temFilhos(no);
    }

    int indice = palavra[profundidade] - 'a';

    if(no->filhos[indice] == NULL) {
        return 0;
    }

    int deveApagarFilho = 
        removeAux(no->filhos[indice], palavra, profundidade + 1, tamanho);

    if(deveApagarFilho) {
        free(no->filhos[indice]);
        no->filhos[indice] = NULL;

        return !no->fimDePalavra && !temFilhos(no);
    }

    return 0;
}

int removerPalavra(ArvoreTrie* T, const char* palavra) {
    int tamanho = 0;
    while(palavra[tamanho] != '\0') {
        tamanho++;
    }

    return removeAux(T->raiz, palavra, 0, tamanho);
}

void liberaNo(NoTrie* no) {
    for(int i = 0; i < ALFABETO; i++) {
        if(no->filhos[i] != NULL) {
            liberaNo(no->filhos[i]);
        }
    }

    free(no);
}

void liberaTrie(ArvoreTrie* T) {
    liberaNo(T->raiz);
    free(T);
}