#include "fornecedor/fornecedor.h"
#include "cep/cep.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MAX_VALUE 5

/*
***** Trabalho feito por:
** - Pedro Henrique Alves de Azevedo
** - Wyllerson de Aquino Cavenaghi
** - Liz Almeida de Oliveira 
** - Ariel Miguel Batista da Silva
*****
*/

struct produto {
    int codigo, tipo, codForn;
    double valor;
    char desc[30], unMedida[3];
};

bool validarFornecedor(int cod) {
    struct fornecedor fornValido[MAX_VALUE] = {0};
    carregarFornecedor(fornValido);

    for (int i = 0; i < MAX_VALUE; i++) {
        if (fornValido[i].codigo == cod) {
            printf("Nome: %s\n", fornValido[i].nome);
            printf("CEP: %d\n", fornValido[i].cep);
            printf("Numero Logradouro: %d\n", fornValido[i].numLog);
            printf("Email: %s\n", fornValido[i].email);
            printf("Telefone: %d\n", fornValido[i].numTel);
            return true;
        }
    }
    return false;
}

char* unMedidas() {
    struct unMedida
    {
        char unMedida[3], medida[15];
    };

    struct unMedida unidades[3] = {
        {"LT", "Litro"},
        {"KG", "Quilograma"},
        {"MT", "Metro"}
    };

    printf("\n-- Unidades de Medida --\n");
    for (int i = 0; i < 3; i++) {
        printf("%s - %s\n", unidades[i].unMedida, unidades[i].medida);
    }

    static char op[3];
    scanf("%s", &op);
    
    strupr(op);

    for (int i = 0; i < 3; i++) {
        if (strcmp(unidades[i].unMedida, op) == 0) {
            printf("\r%s - %s\n", op, unidades[i].medida);
            return op;
        }
    }

    printf("Unidade de Medida invalida\n");
    return NULL;
}

int tipoProduto() {
    struct tipoProduto
    {
        int tipo;
        char descricao[30];
    };

    struct tipoProduto tipoProduto[5] = {
        {1, "Alimento"},
        {2, "Limpeza"},
        {3, "Higiene"},
        {4, "Saude"},
        {5, "Vestuario"}
    };

    printf("\n-- Tipos de Produtos --\n");
    for (int i = 0; i < 5; i++) {
        printf("%d - %s\n", tipoProduto[i].tipo, tipoProduto[i].descricao);
    }

    int tipo;
    scanf("%d", &tipo);

    for (int i = 0; i < 5; i++) {
        if (tipoProduto[i].tipo == tipo) {
            printf("\r%d - %s\n\n", tipo, tipoProduto[i].descricao);
            return tipo;
        }
    }

    printf("Tipo invalido\n");
    return 0;
}

int menu_produto() {
    int op;
    printf("\n-- Cadastro Produtos --\n");
    printf("1 - Incluir\n");
    printf("2 - Alterar\n");
    printf("3 - Excluir\n");
    printf("4 - Consultar\n");
    printf("5 - Limpar Tela\n");
    printf("\n");
    printf("9 - Carregar\n");
    printf("0 - Sair\n");

    scanf("%d", &op);

    return op;
}

void incluirProduto(struct produto cadastro[MAX_VALUE]) {
    for (int i = 0; i < MAX_VALUE; i++) {
        if (cadastro[i].codigo == 0) {
            printf("\n-- Incluir --\n");

            printf("Codigo do Produto: ");
            scanf("%d", &cadastro[i].codigo);

            for (int j = 0; j < i; j++) {
                if (cadastro[i].codigo == cadastro[j].codigo) {
                    printf("Codigo ja cadastrado\n");
                    cadastro[i].codigo = 0;
                    return;
                }
            }

            printf("Descricao: ");
            scanf("%s", cadastro[i].desc);

            strcpy(cadastro[i].unMedida, unMedidas());

            cadastro[i].tipo = tipoProduto();

            printf("Valor Unitario: ");
            scanf("%lf", &cadastro[i].valor);

            printf("Codigo do Fornecedor: ");
            scanf("%d", &cadastro[i].codForn);

            if (!validarFornecedor(cadastro[i].codForn)) {
                printf("Codigo de fornecedor invalido\n");
                cadastro[i].codigo = 0;
                return;
            }

            break;
        }
    }
}

void alterarProduto(struct produto cadastro[MAX_VALUE]) {
    int codigo;
    printf("\n-- Alterar --\n");
    printf("Digite o codigo: ");
    scanf("%d", &codigo);

    for (int i = 0; i < MAX_VALUE; i++) {
        if (cadastro[i].codigo == codigo) {
            printf("Codigo Encontrado!\n");
            printf("Codigo do Produto: ");
            scanf("%d", &cadastro[i].codigo);

            for (int j = 0; j < i; j++) {
                if (cadastro[i].codigo == cadastro[j].codigo) {
                    printf("Codigo ja cadastrado\n");
                    cadastro[i].codigo = 0;
                    return;
                }
            }

            printf("Descricao: ");
            scanf("%s", &cadastro[i].desc);

            strcpy(cadastro[i].unMedida, unMedidas());

            cadastro[i].tipo = tipoProduto();

            printf("Valor Unitario: ");
            scanf("%lf", &cadastro[i].valor);

            printf("Codigo do Fornecedor: ");
            scanf("%d", &cadastro[i].codForn);

            if (!validarFornecedor(cadastro[i].codForn)) {
                printf("Codigo de fornecedor invalido\n");
                cadastro[i].codigo = 0;
                return;
            }

            return;
        }
    }
    printf("Codigo nao encontrado.\n");
}

void excluirProduto(struct produto cadastro[MAX_VALUE]) {
    int codigo;
    printf("\n-- Excluir --\n");
    printf("Digite o codigo: ");
    scanf("%d", &codigo);

    for (int i = 0; i < MAX_VALUE; i++) {
        if (cadastro[i].codigo == codigo) {
            printf("Codigo Encontrado!\n");
            cadastro[i].codigo = 0;
            strcpy(cadastro[i].desc, "");
            strcpy(cadastro[i].unMedida, "");
            cadastro[i].tipo = 0;
            cadastro[i].valor = 0;
            cadastro[i].codForn = 0;
            printf("Cadastro excluido\n");
            return;
        }
    }
    printf("Codigo nao encontrado.\n");
}

void consultarProduto(struct produto cadastro[MAX_VALUE]) {
    int codigo;
    printf("\n-- Consultar --\n");
    printf("Digite o codigo ou 0 para ver todos: ");
    scanf("%d", &codigo);

    if (codigo == 0) {
        for (int i = 0; i < MAX_VALUE; i++) {
            if (cadastro[i].codigo != 0) {
                printf("\nCodigo Produto: %d\n", cadastro[i].codigo);
                printf("Descricao: %s\n", cadastro[i].desc);
                printf("Unidade Medida: %s\n", cadastro[i].unMedida);
                printf("Tipo Produto: %d\n", cadastro[i].tipo);
                printf("Valor Unitario: %.2f\n", cadastro[i].valor);
                printf("Codigo Fornecedor: %d\n", cadastro[i].codForn);
            }
        }
    } else {
        for (int i = 0; i < MAX_VALUE; i++) {
            if (cadastro[i].codigo == codigo) {
                printf("\nCodigo Produto: %d\n", cadastro[i].codigo);
                printf("Descricao: %s\n", cadastro[i].desc);
                printf("Unidade Medida: %s\n", cadastro[i].unMedida);
                printf("Tipo Produto: %d\n", cadastro[i].tipo);
                printf("Valor Unitario: %.2f\n", cadastro[i].valor);
                printf("Codigo Fornecedor: %d\n", cadastro[i].codForn);
                return;
            }
        }
        printf("Codigo nao encontrado.\n");
    }
}

void salvarProduto(struct produto cadastro[MAX_VALUE]) {
    struct stat st = {0};

    if (stat("../data", &st) == -1) {
        mkdir("../data");
    }

    FILE *arq = fopen("../data/produtos.txt", "w");

    if (arq == NULL) {
        printf("Erro ao abrir arquivo\n");
        return;
    }

    for (int i = 0; i < MAX_VALUE; i++) {
        if (cadastro[i].codigo != 0) {
            fprintf(arq, "[%d,%s,%s,%d,%.2f,%d]\n", cadastro[i].codigo, cadastro[i].desc, cadastro[i].unMedida, cadastro[i].tipo, cadastro[i].valor, cadastro[i].codForn);
        }
    }

    printf("Dados salvo com sucesso!\n");
    fclose(arq);
}

void carregarProduto(struct produto cadastro[MAX_VALUE]) {
    struct stat st = {0};

    if (stat("../data", &st) == -1) {
        mkdir("../data");
    }

    FILE *arq = fopen("../data/produtos.txt", "r");

    if (arq == NULL) {
        printf("Erro ao abrir arquivo\n");
        return;
    }

    int i = 0;
    while (i < MAX_VALUE && fscanf(arq, "[%d,%29[^,],%2[^,],%d,%lf,%d]\n", &cadastro[i].codigo, cadastro[i].desc, cadastro[i].unMedida, &cadastro[i].tipo, &cadastro[i].valor, &cadastro[i].codForn) == 6) {
        i++;
    }
    fclose(arq);
}

void produto_main() {
    struct produto produto[MAX_VALUE] = {0};
    int op;

    do {
        op = menu_produto();
        switch (op) {
            case 1:
                incluirProduto(produto);
                break;
            case 2:
                alterarProduto(produto);
                break;
            case 3:
                excluirProduto(produto);
                break;
            case 4:
                consultarProduto(produto);
                break;
            case 5:
                limparTela();
                break;
            case 9:
                carregarProduto(produto);
                printf("Dados carregados com sucesso!\n");
                break;
            case 0:
                salvarProduto(produto);
                return;
            default:
                printf("Opção inválida\n");
        }
    } while (op != 0);

    salvarProduto(produto);
}