#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>

#define NUM_ESTADOS 27
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

void limparTela() {
    system("cls || clear");
}

int menu_cep() {
    int op;
    printf("\n-- Cadastro --\n");
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

bool exibirEstado(char uf[3]) {
    struct Estado {
        char uf[3], estado[30];
    };

    struct Estado estados[NUM_ESTADOS] = {
        {"AC", "Acre"},
        {"AL", "Alagoas"},
        {"AP", "Amapá"},
        {"AM", "Amazonas"},
        {"BA", "Bahia"},
        {"CE", "Ceará"},
        {"DF", "Distrito Federal"},
        {"ES", "Espírito Santo"},
        {"GO", "Goiás"},
        {"MA", "Maranhão"},
        {"MT", "Mato Grosso"},
        {"MS", "Mato Grosso do Sul"},
        {"MG", "Minas Gerais"},
        {"PA", "Pará"},
        {"PB", "Paraíba"},
        {"PR", "Paraná"},
        {"PE", "Pernambuco"},
        {"PI", "Piauí"},
        {"RJ", "Rio de Janeiro"},
        {"RN", "Rio Grande do Norte"},
        {"RS", "Rio Grande do Sul"},
        {"RO", "Rondônia"},
        {"RR", "Roraima"},
        {"SC", "Santa Catarina"},
        {"SP", "São Paulo"},
        {"SE", "Sergipe"},
        {"TO", "Tocantins"}
    };

    uf = strupr(uf);

    for (int i = 0; i < NUM_ESTADOS; i++) {
        if (strcmp(estados[i].uf, uf) == 0) {
            printf("%s - %s\n", uf, estados[i].estado);
            return true;
        }
    }
    printf("Estado inexistente\n");
    return false;
}

void incluirCep(struct cep cadastro[MAX_VALUE]) {
    for (int i = 0; i < MAX_VALUE; i++) {
        if (cadastro[i].cep == 0) {
            printf("\n-- Incluir --\n");

            printf("CEP: ");
            scanf("%d", &cadastro[i].cep);

            for (int j = 0; j < i; j++) {
                if (cadastro[i].cep == cadastro[j].cep) {
                    printf("CEP ja cadastrado\n");
                    cadastro[i].cep = 0;
                    return;
                }
            }

            printf("Logradouro: ");
            scanf("%s", &cadastro[i].logradouro);

            printf("Bairro: ");
            scanf("%s", &cadastro[i].bairro);

            printf("Cidade: ");
            scanf("%s", &cadastro[i].cidade);

            printf("Estado: ");
            scanf("%s", &cadastro[i].estado);

            if (!exibirEstado(cadastro[i].estado)) {
                cadastro[i].cep = 0;
                return;
            }

            break;
        }
    }
}

void alterarCep(struct cep cadastro[MAX_VALUE]) {
    int cep;
    printf("\n-- Alterar --\n");
    printf("Digite o CEP: ");
    scanf("%d", &cep);

    for (int i = 0; i < MAX_VALUE; i++) {
        if (cadastro[i].cep == cep) {
            printf("CEP Encontrado!\n");

            printf("CEP: ");
            scanf("%d", &cadastro[i].cep);

            for (int j = 0; j < i; j++) {
                if (cadastro[i].cep == cadastro[j].cep) {
                    printf("CEP ja cadastrado\n");
                    cadastro[i].cep = cep;
                    return;
                }
            }

            printf("Logradouro: ");
            scanf("%s", &cadastro[i].logradouro);

            printf("Bairro: ");
            scanf("%s", &cadastro[i].bairro);

            printf("Cidade: ");
            scanf("%s", &cadastro[i].cidade);

            printf("Estado: ");
            scanf("%s", &cadastro[i].estado);

            if (!exibirEstado(cadastro[i].estado)) {
                cadastro[i].cep = cep;
                return;
            }

            printf("Cadastro alterado\n");
            return;
        }
    }
    printf("CEP nao encontrado.\n");
}

void excluirCep(struct cep cadastro[MAX_VALUE]) {
    int cep;
    printf("\n-- Excluir --\n");
    printf("Digite o CEP: ");
    scanf("%d", &cep);

    for (int i = 0; i < MAX_VALUE; i++) {
        if (cadastro[i].cep == cep) {
            printf("CEP Encontrado!\n");
            cadastro[i].cep = 0;
            strcpy(cadastro[i].logradouro, "");
            strcpy(cadastro[i].bairro, "");
            strcpy(cadastro[i].cidade, "");
            strcpy(cadastro[i].estado, "");
            printf("Cadastro excluido\n");
            return;
        }
    }
    printf("CEP nao encontrado.\n");
}

void consultarCep(struct cep cadastro[MAX_VALUE]) {
    int cep;
    printf("\n-- Consultar --\n");
    printf("Digite o CEP ou 0 para ver todos: ");
    scanf("%d", &cep);
    
    if (cep == 0) {
        for (int i = 0; i < MAX_VALUE; i++) {
            if (cadastro[i].cep != 0) {
                printf("\nCEP: %d\n", cadastro[i].cep);
                printf("Logradouro: %s\n", cadastro[i].logradouro);
                printf("Bairro: %s\n", cadastro[i].bairro);
                printf("Cidade: %s\n", cadastro[i].cidade);
                printf("Estado: %s\n", cadastro[i].estado);
            }
        }
    } else {
        for (int i = 0; i < MAX_VALUE; i++) {
            if (cadastro[i].cep == cep) {
                printf("\nCEP: %d\n", cadastro[i].cep);
                printf("Logradouro: %s\n", cadastro[i].logradouro);
                printf("Bairro: %s\n", cadastro[i].bairro);
                printf("Cidade: %s\n", cadastro[i].cidade);
                printf("Estado: %s\n", cadastro[i].estado);
                return;
            }
        }
        printf("CEP nao encontrado.\n");
    }
}

void salvarCep(struct cep cadastro[MAX_VALUE]) {
    struct stat st = {0};

    if (stat("../data", &st) == -1) {
        mkdir("../data");
    }
    
    FILE *arq = fopen("../data/cep.txt", "w");

    if (arq == NULL) {
        printf("Erro ao abrir arquivo\n");
        return;
    }

    for (int i = 0; i < MAX_VALUE; i++) {
        if (cadastro[i].cep != 0) {
            fprintf(arq, "[%d,%s,%s,%s,%s]\n", cadastro[i].cep, cadastro[i].logradouro, cadastro[i].bairro, cadastro[i].cidade, cadastro[i].estado);
        }
    }

    printf("Dados salvo com sucesso!\n");
    fclose(arq);
}

void carregarCep(struct cep cadastro[MAX_VALUE]) {
    struct stat st = {0};

    if (stat("../data", &st) == -1) {
        mkdir("../data");
    }
    
    FILE *arq = fopen("../data/cep.txt", "r");

    if (arq == NULL) {
        printf("Erro ao abrir arquivo\n");
        return;
    }

    int i = 0;
    while (i < MAX_VALUE && fscanf(arq, "[%d,%49[^,],%49[^,],%49[^,],%2[^]]]\n", &cadastro[i].cep, cadastro[i].logradouro, cadastro[i].bairro, cadastro[i].cidade, cadastro[i].estado) == 5) {
        i++;
    }
    fclose(arq);
}

void cep_main() {
    struct cep cadastro[MAX_VALUE] = {0};
    int op;

    do {
        op = menu_cep();
        switch (op) {
            case 1:
                incluirCep(cadastro);
                break;
            case 2:
                alterarCep(cadastro);
                break;
            case 3:
                excluirCep(cadastro);
                break;
            case 4:
                consultarCep(cadastro);
                break;
            case 5:
                limparTela();
                break;
            case 9:
                carregarCep(cadastro);
                printf("Dados carregados com sucesso!\n");
                break;
            case 0:
                salvarCep(cadastro);
                return;
            default:
                printf("Opcao invalida\n");
        }
    } while (op != 0);

    salvarCep(cadastro);
}