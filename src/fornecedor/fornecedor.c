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

struct fornecedor {
    int codigo, cep, numLog, numTel;
    char nome[50], email[50];
};

bool validarCEP(int cep) {
    struct cep cepValido[MAX_VALUE] = {0};
    carregarCep(cepValido);

    for (int i = 0; i < MAX_VALUE; i++) {
        if (cepValido[i].cep == cep) {
            printf("Logradouro: %s\n", cepValido[i].logradouro);
            printf("Bairro: %s\n", cepValido[i].bairro);
            printf("Cidade: %s\n", cepValido[i].cidade);
            printf("Estado: %s\n", cepValido[i].estado);
            return true;
        }
    }
    return false;
}

int menu_fornecedor() {
    int op;
    printf("\n-- Cadastro Fornecedor --\n");
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

void incluirFornecedor(struct fornecedor cadastro[MAX_VALUE]) {
    for (int i = 0; i < MAX_VALUE; i++) {
        if (cadastro[i].codigo == 0) {
            printf("\n-- Incluir --\n");

            printf("Codigo: ");
            scanf("%d", &cadastro[i].codigo);

            for (int j = 0; j < i; j++) {
                if (cadastro[i].codigo == cadastro[j].codigo) {
                    printf("Codigo ja cadastrado\n");
                    cadastro[i].codigo = 0;
                    return;
                }
            }

            printf("Nome: ");
            scanf("%s", cadastro[i].nome);
            printf("CEP: ");
            scanf("%d", &cadastro[i].cep);

            if (!validarCEP(cadastro[i].cep)) {
                printf("CEP invalido\n");
                cadastro[i].codigo = 0;
                return;
            }

            printf("Numero logradouro: ");
            scanf("%d", &cadastro[i].numLog);
            printf("Email: ");
            scanf("%s", cadastro[i].email);
            printf("Telefone: ");
            scanf("%d", &cadastro[i].numTel);
            break;
        }
    }
}

void alterarFornecedor(struct fornecedor cadastro[MAX_VALUE]) {
    int codigo;
    printf("\n-- Alterar --\n");
    printf("Digite o codigo: ");
    scanf("%d", &codigo);

    for (int i = 0; i < MAX_VALUE; i++) {
        if (cadastro[i].codigo == codigo) {
            printf("Codigo Encontrado!\n");

            printf("Nome: ");
            scanf("%s", cadastro[i].nome);
            printf("CEP: ");
            scanf("%d", &cadastro[i].cep);

            if (!validarCEP(cadastro[i].cep)) {
                printf("CEP invalido\n");
                return;
            }

            printf("Numero logradouro: ");
            scanf("%d", &cadastro[i].numLog);
            printf("Email: ");
            scanf("%s", cadastro[i].email);
            printf("Telefone: ");
            scanf("%d", &cadastro[i].numTel);
            printf("Cadastro alterado\n");
            return;
        }
    }
    printf("Codigo nao encontrado.\n");
}

void excluirFornecedor(struct fornecedor cadastro[MAX_VALUE]) {
    int codigo;
    printf("\n-- Excluir --\n");
    printf("Digite o codigo: ");
    scanf("%d", &codigo);

    for (int i = 0; i < MAX_VALUE; i++) {
        if (cadastro[i].codigo == codigo) {
            printf("Codigo Encontrado!\n");
            cadastro[i].codigo = 0;
            cadastro[i].cep = 0;
            cadastro[i].numLog = 0;
            cadastro[i].numTel = 0;
            strcpy(cadastro[i].nome, "");
            strcpy(cadastro[i].email, "");
            printf("Cadastro excluido\n");
            return;
        }
    }
    printf("Codigo nao encontrado.\n");
}

void consultarFornecedor(struct fornecedor cadastro[MAX_VALUE]) {
    int codigo;
    printf("\n-- Consultar --\n");
    printf("Digite o codigo ou 0 para ver todos: ");
    scanf("%d", &codigo);

    if (codigo == 0) {
        for (int i = 0; i < MAX_VALUE; i++) {
            if (cadastro[i].codigo != 0) {
                printf("\nCodigo: %d\n", cadastro[i].codigo);
                printf("Nome: %s\n", cadastro[i].nome);
                printf("CEP: %d\n", cadastro[i].cep);
                printf("Numero Logradouro: %d\n", cadastro[i].numLog);
                printf("Email: %s\n", cadastro[i].email);
                printf("Telefone: %d\n", cadastro[i].numTel);
            }
        }
    } else {
        for (int i = 0; i < MAX_VALUE; i++) {
            if (cadastro[i].codigo == codigo) {
                printf("\nCodigo: %d\n", cadastro[i].codigo);
                printf("Nome: %s\n", cadastro[i].nome);
                printf("CEP: %d\n", cadastro[i].cep);
                printf("Numero Logradouro: %d\n", cadastro[i].numLog);
                printf("Email: %s\n", cadastro[i].email);
                printf("Telefone: %d\n", cadastro[i].numTel);
                return;
            }
        }
        printf("Codigo nao encontrado.\n");
    }
}

void salvarFornecedor(struct fornecedor cadastro[MAX_VALUE]) {
    struct stat st = {0};

    if (stat("../data", &st) == -1) {
        mkdir("../data");
    }
    
    FILE *arq = fopen("../data/fornecedores.txt", "w");

    if (arq == NULL) {
        printf("Erro ao abrir arquivo\n");
        return;
    }

    for (int i = 0; i < MAX_VALUE; i++) {
        if (cadastro[i].codigo != 0) {
            fprintf(arq, "[%d,%s,%d,%d,%s,%d]\n", cadastro[i].codigo, cadastro[i].nome, cadastro[i].cep, cadastro[i].numLog, cadastro[i].email, cadastro[i].numTel);
        }
    }

    printf("Dados salvo com sucesso!\n");
    fclose(arq);
}

void carregarFornecedor(struct fornecedor cadastro[MAX_VALUE]) {
    struct stat st = {0};

    if (stat("../data", &st) == -1) {
        mkdir("../data");
    }
    
    FILE *arq = fopen("../data/fornecedores.txt", "r");

    if (arq == NULL) {
        printf("Erro ao abrir arquivo\n");
        return;
    }

    int i = 0;
    while (i < MAX_VALUE && fscanf(arq, "[%d,%49[^,],%d,%d,%49[^,],%d]\n", &cadastro[i].codigo, cadastro[i].nome, &cadastro[i].cep, &cadastro[i].numLog, cadastro[i].email, &cadastro[i].numTel) == 6) {
        i++;
    }

    fclose(arq);
}

void fornecedor_main() {
    struct fornecedor fornecedor[MAX_VALUE] = {0};
    int op;

    do {
        op = menu_fornecedor();
        switch (op) {
            case 1:
                incluirFornecedor(fornecedor);
                break;
            case 2:
                alterarFornecedor(fornecedor);
                break;
            case 3:
                excluirFornecedor(fornecedor);
                break;
            case 4:
                consultarFornecedor(fornecedor);
                break;
            case 5:
                limparTela();
                break;
            case 9:
                carregarFornecedor(fornecedor);
                printf("Dados carregados com sucesso!\n");
                break;
            case 0:
                salvarFornecedor(fornecedor);
                return;
            default:
                printf("Opção inválida\n");
        }
    } while (op != 0);

    salvarFornecedor(fornecedor); // Salva os dados ao sair do loop
}