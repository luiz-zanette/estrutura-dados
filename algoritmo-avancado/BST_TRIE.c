#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Definição da estrutura do nó da árvore binária
typedef struct No {
    char valor [50]; //Máximo de caracteres
    struct No* esquerda; //Ponteiro para filho esquerdo
    struct No* direita; //Ponteiro para filho direito
} No;

// Função para criar um novo nó com alocação dinâmica
No* criarNo(const char* valor) {
    No* novoNo = (No*)malloc(sizeof(No)); // Aloca memória para o novo nó
    if (!novoNo) {
        printf("Erro ao alocar memória\n");
        exit(1); // Sai do programa em caso de erro
    }
    strcpy(novoNo->valor, valor); // Copia o valor para o nó
    novoNo->esquerda = NULL; // Inicializa o filho esquerdo como NULL
    novoNo->direita = NULL; // Inicializa o filho direito como NULL
    return novoNo; // Retorna o novo nó criado
}

// Função para inserir um novo valor na árvore binária de forma recursiva
No* inserir(No* raiz, const char* valor) {
    if (raiz == NULL) {
        return criarNo(valor); // Se a raiz for NULL, cria um novo nó
    }
    if (strcmp(valor, raiz->valor) < 0) {
        raiz->esquerda = inserir(raiz->esquerda, valor); // Insere na subárvore esquerda
    } else if (strcmp(valor, raiz->valor) > 0) {
        raiz->direita = inserir(raiz->direita, valor); // Insere na subárvore direita
    }
    return raiz; // Retorna a raiz da árvore
}

// Função pré ordem para buscar valores na árvore binária
void preOrdem(No* raiz) {
    if (raiz != NULL) {
        printf("%s ", raiz->valor); // Visita e exibe o nó atual
        preOrdem(raiz->esquerda); // Visita a subárvore esquerda
        preOrdem(raiz->direita); // Visita a subárvore direita
    }
}

// Função Em Ordem para buscar valores na árvore binária
void emOrdem(No* raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esquerda); // Visita a subárvore esquerda
        printf("%s ", raiz->valor); // Visita e exibe o nó atual
        emOrdem(raiz->direita); // Visita a subárvore direita
    }
}

// Função Pós Ordem para buscar valores na árvore binária
void posOrdem(No* raiz) {
    if (raiz != NULL) {
        posOrdem(raiz->esquerda); // Visita a subárvore esquerda
        posOrdem(raiz->direita); // Visita a subárvore direita
        printf("%s ", raiz->valor); // Visita e exibe o nó atual
    }
}

// Função para liberar a memória alocada para a árvore binária
void liberar(No* raiz) {
    if (raiz != NULL) {
        liberar(raiz->esquerda); // Libera a subárvore esquerda
        liberar(raiz->direita); // Libera a subárvore direita
        free(raiz); // Libera o nó atual
    }
}

// Função main para testar a implementação da árvore binária
int main() {
   setlocale(LC_ALL, "pt_BR.UTF-8"); // Configura o locale para suportar caracteres acentuados

    No* raiz = NULL; // Inicializa a raiz da árvore como NULL

    // Inserção de valores na árvore binária
    raiz = inserir(raiz, "Hall de entrada");
    inserir(raiz, "Sala de estar");
    inserir(raiz, "Biblioteca");
    inserir(raiz, "Quarto");
    
    // Exibição dos valores em diferentes ordens
    printf("Pré Ordem: ");
    preOrdem(raiz);
    printf("\n");

    printf("Em Ordem: ");
    emOrdem(raiz);
    printf("\n");

    printf("Pós Ordem: ");
    posOrdem(raiz);
    printf("\n");

    // Liberação da memória alocada para a árvore
    liberar(raiz);
    return 0;
}