#ifndef HASH_H
#define HASH_H

#include <stdbool.h>

#define TAMANHO_TABELA 101
#define TAM_MAX_CHAVE 50

// Par chave-valor
typedef struct ParChaveValor {
    char chave[TAM_MAX_CHAVE];
    int valor;
} ParChaveValor;

// Nó da lista ligada para o tratamento de erro
typedef struct No {
    ParChaveValor par;
    struct No* proximo;
} No;

// Estrutura da tabela hash dos pedidos
typedef struct TabelaHash {
    No* buckets[TAMANHO_TABELA];
} TabelaHash;

//funções para modificarmos/consultar a tabela
TabelaHash* criar_tabela_hash();
bool inserir(TabelaHash* tabela, const char* chave, int valor);
int* buscar(TabelaHash* tabela, const char* chave);
bool remover(TabelaHash* tabela, const char* chave);
void imprimir_tabela(TabelaHash* tabela);
void liberar_tabela(TabelaHash* tabela);
void salvar_tabela(TabelaHash* tabela, const char* arquivo);
void carregar_tabela(TabelaHash* tabela, const char* arquivo);

#endif