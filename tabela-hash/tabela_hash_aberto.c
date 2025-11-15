#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int chave;
    void* valor;
} Entrada;

typedef struct {
    int total;
    int tamanho;
    Entrada** elementos;
} Hash;

int hashingDivisao(int chave, int tamanho) {
    return (chave & 0x7FFFFFFF) % tamanho;
}

int hashingMultiplicacao(int chave, int tamanho) {
    float A = 0.61803387; 
    float i = chave * A;

    i = i - (int) i;
    return (int) (tamanho * i);
}

int hashingDobra(int chave, int tamanho) {
    int k = 10;
    int parte1 = chave >> k;
    int parte2 = chave & (tamanho - 1);

    return (int) (parte1 ^ parte2);
}

Hash* criarHash(int tamanho) {
    Hash* hash = malloc(sizeof(Hash));
    
    if(!hash) {
        perror("Erro ao alocar hash");
        exit(1);
    }

    hash->tamanho = tamanho;
    hash->total = 0;
    hash->elementos = malloc(sizeof(Entrada*) * tamanho);

    for(int i = 0; i < tamanho; i++) {
        hash->elementos[i] = NULL;
    }

    return hash;
}

void liberarHash(Hash* hash) {
    if(hash == NULL) {
        return;
    }

    for(int i = 0; i < hash->tamanho; i++) {
        if(hash->elementos[i] != NULL) {
            free(hash->elementos[i]);
        }
    }
    free(hash->elementos);
    free(hash);
}

void adicionar(Hash* hash, int chave, void* valor) {
    if(hash == NULL && hash->total >= hash->tamanho) {
        return;
    }

    int indice = hashingDivisao(chave, valor);

    Entrada* entrada = malloc(sizeof(Entrada));
    entrada->chave = chave;
    entrada->valor = valor;
    hash->elementos[indice] = entrada;
    hash->total++;
}

void* buscar(Hash* hash, int chave) {
    if(hash != NULL) {
        int indice = hashingDivisao(chave, hash->tamanho);
        if(hash->elementos[indice] != NULL) {
            return hash->elementos[indice]->valor;
        }
    }
    return NULL;
}