#ifndef PRODUTO_H
#define PRODUTO_H

#include <stdbool.h>

#define MAX_VALUE 5

struct produto {
    int codigo, tipo, codForn;
    float valor;
    char desc[30], unMedida[2];
};

void incluirProduto(struct produto cadastro[MAX_VALUE]);
void alterarProduto(struct produto cadastro[MAX_VALUE]);
void excluirProduto(struct produto cadastro[MAX_VALUE]);
void consultarProduto(struct produto cadastro[MAX_VALUE]);
void consultarFornecedores();
void salvarProduto(struct produto cadastro[MAX_VALUE]);
void carregarProduto(struct produto cadastro[MAX_VALUE]);

void produto_main();

#endif // PRODUTO_H