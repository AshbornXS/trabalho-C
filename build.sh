#!/bin/sh
# Cria a pasta bin dentro de src se não existir
mkdir -p src/bin

# Compila os arquivos fonte e gera o executável em src/bin
gcc -I src -I src/produto -I src/fornecedor -I src/cep src/main.c src/produto/produto.c src/fornecedor/fornecedor.c src/cep/cep.c -o src/bin/programa.exe

# Verifica se a compilação foi bem-sucedida
if [ $? -eq 0 ]; then
    # Muda o diretório de trabalho para src/bin
    cd src/bin
    # Executa o programa a partir de bin
    ./programa.exe
else
    echo "Compilação falhou"
fi