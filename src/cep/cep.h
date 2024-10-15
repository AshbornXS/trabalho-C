#ifndef CEP_H
#define CEP_H

#include <stdbool.h>

#define MAX_VALUE 5

struct cep {
    int cep;
    char logradouro[50], bairro[50], cidade[50], estado[3];
};

void limparTela();

bool exibirEstado(char uf[3]);
void incluirCep(struct cep cadastro[MAX_VALUE]);
void alterarCep(struct cep cadastro[MAX_VALUE]);
void excluirCep(struct cep cadastro[MAX_VALUE]);
void consultarCep(struct cep cadastro[MAX_VALUE]);
void salvarCep(struct cep cadastro[MAX_VALUE]);
void carregarCep(struct cep cadastro[MAX_VALUE]);

void cep_main();

#endif // CEP_H