#include "funcoes.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// MÓDULO INVENTARIO - PARTE 1
// Realiza operações de adicionar, remover e listar produtos em um inventário
// Trabalha inicialmente com array estático
// Aloca toda a memória necessária uma vez ao declarar o array

// Definição de constante
#define MAX_STR_LEN 50 // Tamanho máximo para strings
#define MAX_PRODUTOS 10 // Número máximo de produtos no inventário

// Declaração principal
int main () {
    // Cria as variáveis para as listas aqui na função main
    // e as inicializa corretamente.
    ListaEstatica invEstatica;
    ListaEncadeada invEncadeada = NULL;
    int opcao;

    // Inicializa a lista estática uma única vez
    // As funções iniciarListaEstatica e iniciarListaEncadeada estão no seu arquivo funcoes.c
    iniciarListaEstatica(&invEstatica);

    do {
        printf("\n--- Manipulacao de Listas ---\n");
        printf("1. Lista Estatica\n");
        printf("2. Lista Encadeada\n");
        printf("0. Sair do programa\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        // Limpar o buffer do teclado
        while(getchar() != '\n'); 

        switch (opcao) {
            case 1: 
                // Passa o endereco da lista estatica para o menu
                menuListaEstatica(&invEstatica);
                break;

            case 2:
                // Passa o endereco da lista encadeada para o menu
                menuListaEncadeada(&invEncadeada);
                break;

            case 0:
                // Boa prática: libera a memória da lista encadeada antes de sair
                liberarListaEncadeada(&invEncadeada);
                printf("Saindo, ate mais!\n");
                break;

            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }

    } while (opcao != 0);

    return 0;
}