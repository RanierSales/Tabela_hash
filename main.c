#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

const char* descobre_status(int status) {
    switch (status) {
        case 0: return "em separacao!";
        case 1: return "a caminho da sua cidade!";
        case 2: return "em rota de entrega!";
        case 3: return "entregue!";
        default: return "sem status!";
    }
}

void tabela_com_pedidos(TabelaHash* tabela) {
    int i;
    const char* codigos_unicos[19] = {
        "SPMG25062101", "SPMG25062102", "SPMG25062103", "SPMG25062104", "SPMG25062105",
        "SPMG25062106", "SPMG25062107", "SPMG25062108", "SPMG25062109", "SPMG25062110",
        "SPBA25062111", "SPBA25062112", "SPBA25062113", "SPBA25062114", "SPBA25062115",
        "SPRJ25062116", "SPRJ25062117", "SPRJ25062118", "SPRJ25062119"
    };

    for (i = 0; i < 19; i++) {
        int status = i % 4;
        inserir(tabela, codigos_unicos[i], status);
    }

    const char* colisoes1[3] = {
        "SPRR25062120", "SPRR25062122", "SPRR25062123"
    };

    const char* colisoes2[3] = {
        "MGBA24062120", "MGBA24062121", "MGBA24062122"
    };

    for (i = 0; i < 3; i++) {
        inserir(tabela, colisoes1[i], i % 4);
        inserir(tabela, colisoes2[i], (i + 1) % 4);
    }
}

int main(int argc, char *argv[]) {
    TabelaHash* tabela = criar_tabela_hash();
    tabela_com_pedidos(tabela);
    carregar_tabela(tabela, "pedidos.txt");

    if (argc < 2) {
        printf("Uso:\n");
        printf("  buscar <codigo>\n");
        printf("  inserir <codigo> <status>\n");
        printf("  remover <codigo>\n");
        printf("  listar\n");
        liberar_tabela(tabela);
        return 1;
    }

    if (strcmp(argv[1], "buscar") == 0 && argc == 3) {
        int* status = buscar(tabela, argv[2]);
        if (status)
            printf("Status do pedido %s: %s\n", argv[2], descobre_status(*status));
        else
            printf("Pedido %s nao encontrado!\n", argv[2]);
    }
    else if (strcmp(argv[1], "inserir") == 0 && argc == 4) {
        int status = atoi(argv[3]);
        inserir(tabela, argv[2], status);
        printf("Pedido %s inserido/atualizado com status %d\n", argv[2], status);
    }
    else if (strcmp(argv[1], "remover") == 0 && argc == 3) {
        remover(tabela, argv[2]);
        printf("Pedido %s removido\n", argv[2]);
    }
    else if (strcmp(argv[1], "listar") == 0) {
        imprimir_tabela(tabela);
    }
    else {
        printf("Comando invalido ou argumentos insuficientes.\n");
    }

    salvar_tabela(tabela, "pedidos.txt");
    liberar_tabela(tabela);
    return 0;
}
