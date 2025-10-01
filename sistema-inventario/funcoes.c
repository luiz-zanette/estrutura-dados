#include "funcoes.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// MÓDULO INVENTARIO - PARTE 1
// Realiza operações de adicionar, remover e listar produtos em um inventário
// Trabalha inicialmente com array estático
// Aloca toda a memória necessária uma vez ao declarar o array

// As definições das structs e das macros foram removidas daqui para evitar conflitos,
// pois elas já estão no arquivo "funcoes.h" e o #include já as disponibiliza.
/*
#define MAX_STR_LEN 50
#define MAX_PRODUTOS 10
typedef struct {
    char dados[MAX_PRODUTOS][MAX_STR_LEN];
    int quantidade;
} ListaEstatica; 
typedef struct No {
    char* dado;
    struct No* proximo;
} No;
typedef No* ListaEncadeada;
*/

// Protótipos das funções de menu
void menuListaEstatica(ListaEstatica *lista);
void menuListaEncadeada(ListaEncadeada *lista);

// FUNÇÕES PARA LISTA ESTÁTICA
void iniciarListaEstatica(ListaEstatica *lista) {
    lista->quantidade = 0;
    printf("Lista estática inicializada.\n");
}

void inserirListaEstatica(ListaEstatica *lista, const char *produto) {
    // Verifica se há espaço na lista
    if (lista->quantidade == 10) { // O MAX_PRODUTOS vem do .h
        printf("Erro: Inventário cheio. Não é possível adicionar mais produtos.\n");
        return;
    }
    // Adiciona o produto ao final da lista
    strncpy(lista->dados[lista->quantidade], produto, 50 - 1); // O MAX_STR_LEN vem do .h
    lista->dados[lista->quantidade][50 - 1] = '\0'; // Garantir que a string termine com nulo
    lista->quantidade++; // Incrementa a contagem de produtos
    printf("Produto '%s' adicionado ao inventário.\n", produto);
}

void removerListaEstatica(ListaEstatica *lista, const char *produto) {
    int i, posicao = -1;
    for (i = 0; i < lista->quantidade; i++) {
        if (strcmp(lista->dados[i], produto) == 0) {
            posicao = i;
            break;
        }
    }

    if (posicao == -1) {
        printf("Erro: Produto '%s' não encontrado no inventário.\n", produto);
        return;
    }

    for (i = posicao; i < lista->quantidade - 1; i++) {
        strncpy(lista->dados[i], lista->dados[i + 1], 50); // O MAX_STR_LEN vem do .h
    }
    lista->quantidade--;
    printf("Produto '%s' removido do inventário.\n", produto);
}

void listarListaEstatica(const ListaEstatica *lista) {
    if (lista->quantidade == 0) {
        printf("Inventário vazio.\n");
        return;
    }
    printf("Produtos no inventário:\n");
    for (int i = 0; i < lista->quantidade; i++) {
        printf("%s\n", lista->dados[i]);
    }
}

// FUNÇÕES PARA LISTA ENCADEADA
void iniciarListaEncadeada(ListaEncadeada *lista) {
    *lista = NULL;
    printf("Lista encadeada inicializada.\n");
}

void inserirListaEncadeada(ListaEncadeada *lista, const char *produto) {
    No* novoNo = (No*) malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("Erro: Falha na alocação de memória para o nó.\n");
        return;
    }
    novoNo->dado = (char*) malloc(strlen(produto) + 1);
    if (novoNo->dado == NULL) {
        printf("Erro: Falha na alocação de memória para o produto.\n");
        free(novoNo); 
        return;
    }
    strcpy(novoNo->dado, produto);
    novoNo->proximo = *lista;
    *lista = novoNo;
    printf("Produto '%s' adicionado ao inventário.\n", produto);
}

void removerListaEncadeada(ListaEncadeada *lista, const char *produto) {
    No *atual = *lista;
    No *anterior = NULL;
    while (atual != NULL && strcmp(atual->dado, produto) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }
    if (atual == NULL) {
        printf("Erro: Produto '%s' não encontrado no inventário.\n", produto);
        return;
    }
    if (anterior == NULL) {
        *lista = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }
    free(atual->dado);
    free(atual);
    printf("Produto '%s' removido do inventário.\n", produto);
}

void listarListaEncadeada(const ListaEncadeada *lista) {
    if (*lista == NULL) {
        printf("Inventário vazio.\n");
        return;
    }
    printf("Produtos no inventário:\n");
    No* atual = *lista;
    while (atual != NULL) {
        printf("%s\n", atual->dado);
        atual = atual->proximo;
    }
}

void liberarListaEncadeada(ListaEncadeada *lista) {
    No* atual = *lista;
    No* proximo;
    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual->dado);
        free(atual);
        atual = proximo;
    }
    *lista = NULL;
}

// Implementação do menu da lista estática
void menuListaEstatica(ListaEstatica *lista) {
    int opcao;
    char produto[50]; // Usando o valor literal, pois MAX_STR_LEN não está definido aqui
    do {
        printf("\n--- MENU - LISTA ESTATICA ---\n");
        printf("1. Inserir produto\n");
        printf("2. Remover produto\n");
        printf("3. Listar produtos\n");
        printf("0. Voltar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        while (getchar() != '\n');
        switch (opcao) {
            case 1:
                printf("Digite o nome do produto: ");
                fgets(produto, 50, stdin);
                produto[strcspn(produto, "\n")] = '\0';
                inserirListaEstatica(lista, produto);
                break;
            case 2:
                printf("Digite o nome do produto a ser removido: ");
                fgets(produto, 50, stdin);
                produto[strcspn(produto, "\n")] = '\0';
                removerListaEstatica(lista, produto);
                break;
            case 3:
                listarListaEstatica(lista);
                break;
            case 0:
                printf("Voltando ao menu principal...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    } while (opcao != 0);
}

// Implementação do menu da lista encadeada
void menuListaEncadeada(ListaEncadeada *lista) {
    int opcao;
    char produto[50];
    do {
        printf("\n--- MENU - LISTA ENCADEADA ---\n");
        printf("1. Inserir produto\n");
        printf("2. Remover produto\n");
        printf("3. Listar produtos\n");
        printf("4. Liberar lista (memória)\n");
        printf("0. Voltar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        while (getchar() != '\n');
        switch (opcao) {
            case 1:
                printf("Digite o nome do produto: ");
                fgets(produto, 50, stdin);
                produto[strcspn(produto, "\n")] = '\0';
                inserirListaEncadeada(lista, produto);
                break;
            case 2:
                printf("Digite o nome do produto a ser removido: ");
                fgets(produto, 50, stdin);
                produto[strcspn(produto, "\n")] = '\0';
                removerListaEncadeada(lista, produto);
                break;
            case 3:
                listarListaEncadeada(lista);
                break;
            case 4:
                liberarListaEncadeada(lista);
                break;
            case 0:
                printf("Voltando ao menu principal...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    } while (opcao != 0);
}