#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define A 0.6180339887 // Constante do método da multiplicação

// Converte string para inteiro interpretando como base 256
unsigned int string_para_inteiro(const char* chave) {
    unsigned int k = 0;
    while (*chave) {
        k = k * 256 + (unsigned char)(*chave);
        chave++;
    }
    return k;
}

// Função hash usando o método da multiplicação
unsigned int funcao_hash(const char* chave) {
    unsigned int k = string_para_inteiro(chave);
    double resultado = k * A;
    double parte_fracionaria = resultado - (int)resultado;
    return (unsigned int)(TAMANHO_TABELA * parte_fracionaria);
}

// Cria e inicializa uma nova tabela hash
TabelaHash* criar_tabela_hash() {
    TabelaHash* tabela = (TabelaHash*)malloc(sizeof(TabelaHash));
    if (tabela) {
        int i;
        for (i = 0; i < TAMANHO_TABELA; i++) {
            tabela->buckets[i] = NULL;
        }
    }
    return tabela;
}

// Insere ou atualiza um par chave-valor
bool inserir(TabelaHash* tabela, const char* chave, int valor) {
    if (!tabela) return false;
    unsigned int indice = funcao_hash(chave);

    No* atual = tabela->buckets[indice];
    while (atual) {
        if (strcmp(atual->par.chave, chave) == 0) {
            atual->par.valor = valor; // Atualiza valor se chave já existir
            return true;
        }
        atual = atual->proximo;
    }

    // Chave nova, cria novo nó
    No* novo = (No*)malloc(sizeof(No));
    if (!novo) return false;
    strncpy(novo->par.chave, chave, TAM_MAX_CHAVE);
    novo->par.valor = valor;
    novo->proximo = tabela->buckets[indice];
    tabela->buckets[indice] = novo;
    return true;
}

// Busca o valor associado a uma chave
int* buscar(TabelaHash* tabela, const char* chave) {
    if (!tabela) return NULL;
    unsigned int indice = funcao_hash(chave);

    No* atual = tabela->buckets[indice];
    while (atual) {
        if (strcmp(atual->par.chave, chave) == 0) {
            return &atual->par.valor;
        }
        atual = atual->proximo;
    }
    return NULL; // Chave não encontrada
}

// Remove um par com base na chave
bool remover(TabelaHash* tabela, const char* chave) {
    if (!tabela) return false;
    unsigned int indice = funcao_hash(chave);

    No* atual = tabela->buckets[indice];
    No* anterior = NULL;

    while (atual) {
        if (strcmp(atual->par.chave, chave) == 0) {
            if (anterior) {
                anterior->proximo = atual->proximo;
            } else {
                tabela->buckets[indice] = atual->proximo;
            }
            free(atual);
            return true;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    return false; // Chave não encontrada
}

// Imprime todo o conteúdo da tabela hash
void imprimir_tabela(TabelaHash* tabela) {
    if (!tabela) return;
    int i;
    for (i = 0; i < TAMANHO_TABELA; i++) {
        No* atual = tabela->buckets[i];
        while (atual) {
            printf("Bucket %d: [%s] = %d\n", i, atual->par.chave, atual->par.valor);
            atual = atual->proximo;
        }
    }
}

// Libera toda a memória alocada pela tabela hash
void liberar_tabela(TabelaHash* tabela) {
    if (!tabela) return;
    int i;
    for (i = 0; i < TAMANHO_TABELA; i++) {
        No* atual = tabela->buckets[i];
        while (atual) {
            No* temp = atual;
            atual = atual->proximo;
            free(temp);
        }
    }
    free(tabela);
}

// salvar_tabela(tabela, "pedidos.txt");
void salvar_tabela(TabelaHash* tabela, const char* arquivo) {
    FILE* f = fopen(arquivo, "w");
    if (!f) return;
    int i;
    for (i = 0; i < TAMANHO_TABELA; i++) {
        No* atual = tabela->buckets[i];
        while (atual) {
            fprintf(f, "%s %d\n", atual->par.chave, atual->par.valor);
            atual = atual->proximo;
        }
    }
    fclose(f);
}

// carregar_tabela(tabela, "pedidos.txt");
void carregar_tabela(TabelaHash* tabela, const char* arquivo) {
    FILE* f = fopen(arquivo, "r");
    if (!f) return;
    char chave[TAM_MAX_CHAVE];
    int valor;
    while (fscanf(f, "%s %d", chave, &valor) == 2) {
        inserir(tabela, chave, valor);
    }
    fclose(f);
}
