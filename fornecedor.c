#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VALUE 5

/*
***** Trabalho feito por:
** - Pedro Henrique Alves de Azevedo
** - Wyllerson de Aquino Cavenaghi
** - Liz Almeida de Oliveira 
** - Ariel Miguel Batista da Silva
*****
*/

struct cep {
    int cep;
    char logradouro[50], bairro[50], cidade[50], estado[3];
};

struct fornecedor {
    int codigo, cep, numLog, numTel;
    char nome[50], email[50];
};

void carregarCep(struct cep cep[MAX_VALUE]) {
    FILE *arq = fopen("cep.txt", "r");

    if (arq == NULL) {
        printf("Erro ao abrir arquivo\n");
        return;
    }

    int i = 0;
    while (i < MAX_VALUE && fscanf(arq, "[%d,%49[^,],%49[^,],%49[^,],%2[^]]]\n", &cep[i].cep, cep[i].logradouro, cep[i].bairro, cep[i].cidade, cep[i].estado) == 5) {
        i++;
    }
    fclose(arq);
}

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

int menu() {
    int op;
    printf("\n-- Cadastro Fornecedor --\n");
    printf("1 - Incluir\n");
    printf("2 - Alterar\n");
    printf("3 - Excluir\n");
    printf("4 - Consultar\n");
    printf("5 - Consultar CEPs\n");
    printf("\n");
    printf("9 - Carregar\n");
    printf("0 - Sair\n");

    scanf("%d", &op);

    return op;
}

void incluir(struct fornecedor cadastro[MAX_VALUE]) {
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
            scanf("%s", &cadastro[i].nome);
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
            scanf("%s", &cadastro[i].email);
            printf("Telefone: ");
            scanf("%d", &cadastro[i].numTel);
            break;
        }
    }
}

void alterar(struct fornecedor cadastro[MAX_VALUE]) {
    int codigo;
    printf("\n-- Alterar --\n");
    printf("Digite o codigo: ");
    scanf("%d", &codigo);

    for (int i = 0; i < MAX_VALUE; i++) {
        if (cadastro[i].codigo == codigo) {
            printf("Codigo Encontrado!\n");
            printf("Codigo: ");
            scanf("%d", &cadastro[i].codigo);

            for (int j = 0; j < i; j++) {
                if (cadastro[i].codigo == cadastro[j].codigo) {
                    printf("Codigo ja cadastrado\n");
                    cadastro[i].codigo = codigo;
                    return;
                }
            }

            printf("Nome: ");
            scanf("%s", &cadastro[i].nome);
            printf("CEP: ");
            scanf("%d", &cadastro[i].cep);

            if (!validarCEP(cadastro[i].cep)) {
                printf("CEP invalido\n");
                cadastro[i].codigo = codigo;
                return;
            }

            printf("Numero logradouro: ");
            scanf("%d", &cadastro[i].numLog);
            printf("Email: ");
            scanf("%s", &cadastro[i].email);
            printf("Telefone: ");
            scanf("%d", &cadastro[i].numTel);
            printf("Cadastro alterado\n");
            return;
        }
    }
    printf("Codigo nao encontrado.\n");
}

void excluir(struct fornecedor cadastro[MAX_VALUE]) {
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

void consultar(struct fornecedor cadastro[MAX_VALUE]) {
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

void consultarCEP() {
    struct cep cep[MAX_VALUE] = {0};
    carregarCep(cep);

    printf("\n-- Consultar CEP --\n");

    for (int i = 0; i < MAX_VALUE; i++) {
        if (cep[i].cep != 0) {
            printf("\nCEP: %d\n", cep[i].cep);
            printf("Logradouro: %s\n", cep[i].logradouro);
            printf("Bairro: %s\n", cep[i].bairro);
            printf("Cidade: %s\n", cep[i].cidade);
            printf("Estado: %s\n", cep[i].estado);
        }
    }
}

void salvar(struct fornecedor cadastro[MAX_VALUE]) {
    FILE *arq = fopen("fornecedores.txt", "w");

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

void carregar(struct fornecedor cadastro[MAX_VALUE]) {
    FILE *arq = fopen("fornecedores.txt", "r");

    if (arq == NULL) {
        printf("Erro ao abrir arquivo\n");
        return;
    }

    int i = 0;
    while (i < MAX_VALUE && fscanf(arq, "[%d,%49[^,],%d,%d,%49[^,],%d]\n", &cadastro[i].codigo, cadastro[i].nome, &cadastro[i].cep, &cadastro[i].numLog, cadastro[i].email, &cadastro[i].numTel) == 6) {
        i++;
    }

    fclose(arq);
    printf("Dados carregados com sucesso!\n");
}

int main() {
    struct fornecedor fornecedor[MAX_VALUE] = {0};
    int op;

    do {
        op = menu();
        switch (op) {
            case 1:
                incluir(fornecedor);
                break;
            case 2:
                alterar(fornecedor);
                break;
            case 3:
                excluir(fornecedor);
                break;
            case 4:
                consultar(fornecedor);
                break;
            case 5:
                consultarCEP();
                break;
            case 9:
                carregar(fornecedor);
                break;
            case 0:
                break;
            default:
                printf("Opção inválida\n");
        }
    } while (op != 0);

    salvar(fornecedor);
}