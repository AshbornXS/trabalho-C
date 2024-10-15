#ifndef FORNECEDOR_H
#define FORNECEDOR_H

#include <stdbool.h>

#define MAX_VALUE 5

struct fornecedor {
    int codigo, cep, numLog, numTel;
    char nome[50], email[50];
};

bool validarFornecedor(int cod);
void incluirFornecedor(struct fornecedor cadastro[MAX_VALUE]);
void alterarFornecedor(struct fornecedor cadastro[MAX_VALUE]);
void excluirFornecedor(struct fornecedor cadastro[MAX_VALUE]);
void consultarFornecedor(struct fornecedor cadastro[MAX_VALUE]);

void salvarFornecedor(struct fornecedor cadastro[MAX_VALUE]);
void carregarFornecedor(struct fornecedor cadastro[MAX_VALUE]);

void fornecedor_main();

#endif // FORNECEDOR_H