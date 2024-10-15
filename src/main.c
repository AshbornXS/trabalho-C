#include "fornecedor/fornecedor.h"
#include "produto/produto.h"
#include "cep/cep.h"
#include <stdio.h>
#include <stdlib.h>

void main() {
    int escolha;

    do {
        system("cls");
        printf("-- Escolha o Modulo --\n");
        printf("1 - CEP\n");
        printf("2 - Fornecedor\n");
        printf("3 - Produto\n");
        printf("\n0 - Sair\n");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                cep_main();
                break;
            case 2:
                fornecedor_main();
                break;
            case 3:
                produto_main();
                break;
            case 0:   
                break;
            default:
                printf("Opção inválida\n");
        }
    } while (escolha != 0);

    return;
}