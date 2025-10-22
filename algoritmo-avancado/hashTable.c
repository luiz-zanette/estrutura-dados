#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Tabela Hash com Tratamento de Colisões por Encadeamento -> se estiver ocupado, cria uma lista ligada
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// Estruturas de nó da lista ligada por encadeamento (na colisão, os elementos são armazenados em uma lista ligada)
typedef struct Nodo {
    char chave[50];
    struct Nodo* proximo;
} Nodo;

// Vetor de ponteiros para início da lista
Nodo* tabela_chaining[TABLE_SIZE];

// Função hash simples (soma dos valores ASCII e gera módulo pelo tamanho da tabela)
int funcao_hash(const char* chave) {
    int soma = 0;
    for (int i = 0; chave[i] != '\0'; i++) {
        soma += chave[i];
    }
    return soma % TABLE_SIZE;
}

// Inserção em encadeamento
void inserir_chaining(const char* valor) {
    int indice = funcao_hash(valor);
    Nodo* novo_nodo = (Nodo*)malloc(sizeof(Nodo));
    strcpy(novo_nodo->chave, valor);
    novo_nodo->proximo = tabela_chaining[indice];
    tabela_chaining[indice] = novo_nodo;
}

// Busca em encadeamento na lista ligada
Nodo* buscar_chaining(const char* valor) {
    int indice = funcao_hash(valor);
    Nodo* atual = tabela_chaining[indice];
    while (atual != NULL) {
        if (strcmp(atual->chave, valor) == 0) {
            return atual; // Encontrado
        }
        atual = atual->proximo;
    }
    return NULL; // Não encontrado
}

// Remoção com encadeamento
void remover_chaining(const char* valor) {
    int indice = funcao_hash(valor);
    Nodo* atual = tabela_chaining[indice];
    Nodo* anterior = NULL;
    while (atual != NULL) {
        if (strcmp(atual->chave, valor) == 0) {
            if (anterior == NULL) {
                tabela_chaining[indice] = atual->proximo; // Remover o primeiro nodo
            } else {
                anterior->proximo = atual->proximo; // Pular o nodo removido
            }
            free(atual);
            printf("Elemento '%s' removido com sucesso.\n", valor); 
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    printf("Elemento '%s' não encontrado para remoção.\n", valor);
}

// Visualização da tabela hash com encadeamento
void mostrar_chaining() {
    printf("Tabela Hash (Encadeamento):\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("Índice %d:", i);
        Nodo* atual = tabela_chaining[i];
        while (atual != NULL) {
            printf(" -> %s", atual->chave);
            atual = atual->proximo;
        }
        printf("NULL\n");
    }
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Tabela Hash com Endereçamento Aberto (Sondagem Linear) -> se estiver ocupado, vai para o próximo
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// Estrutura da tabela hash com sondagem linear
typedef struct {
    char chave[50];
    int ocupado; // 0 = livre, 1 = ocupado
} Entrada;

Entrada tabela_linear[TABLE_SIZE];

// Inserção com sondagem linear
void inserir_linear(const char* valor) {
    int indice = funcao_hash(valor);
    for (int i = 0; i < TABLE_SIZE; i++) {
        int posicao = (indice + i) % TABLE_SIZE;
        if (tabela_linear[posicao].ocupado == 0 || tabela_linear[posicao].ocupado == 2) {
            strcpy(tabela_linear[posicao].chave, valor);
            tabela_linear[posicao].ocupado = 1; // Marca como ocupado
            return;
        }
    }
    printf("Tabela Hash cheia, não foi possível inserir '%s'.\n", valor);
}

// Busca com sondagem linear
int buscar_linear(const char* valor) {
    int indice = funcao_hash(valor);
    for (int i = 0; i < TABLE_SIZE; i++) {
        int posicao = (indice + i) % TABLE_SIZE;
        if (tabela_linear[posicao].ocupado == 0) { 
            return -1; // Não encontrado
        }
        if (tabela_linear[posicao].ocupado == 1 && strcmp(tabela_linear[posicao].chave, valor) == 0) {
            return posicao; // Encontrado
        }
    }
    return -1; // Não encontrado
}

// Remoção com sondagem linear
void remover_linear(const char* valor) {
    int posicao = buscar_linear(valor);
    if (posicao == -1) {
        printf("Elemento '%s' não encontrado para remoção.\n", valor);
        return;
    }
    tabela_linear[posicao].ocupado = 2; // Marca como removido
    printf("Elemento '%s' removido com sucesso.\n", valor);
}

// Visualização da tabela hash com sondagem linear
void mostrar_linear() {
    printf("Tabela Hash (Sondagem Linear):\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (tabela_linear[i].ocupado == 1) {
            printf("Índice %d: %s\n", i, tabela_linear[i].chave);
        } else if (tabela_linear[i].ocupado == -1) {
            printf("Índice %d: LIVRE\n", i);
        } else {
            printf("Índice %d: REMOVIDO\n", i);
        }
    }
}

// ********** Função main para demonstração **********
int main() {
    // Inicialização das tabelas hash
    for (int i = 0; i < TABLE_SIZE; i++) {
        tabela_chaining[i] = NULL;
        tabela_linear[i].ocupado = 0; // Marca como livre
    }

    // Inserção de elementos para exemplo
    const char* palavras[] = {
        "apple", "banana", "grape", "orange", "melon",
        "kiwi", "peach", "plum", "pear", "mango"
    };
    int n = sizeof(palavras) / sizeof(palavras[0]);

    // Inserção nas tabelas
    for (int i = 0; i < n; i++) {
        inserir_chaining(palavras[i]);
        inserir_linear(palavras[i]);
    }

    // Visiualização das tabelas
    mostrar_chaining();
    printf("\n");
    mostrar_linear();
    printf("\n");

    // Busca de um elemento
    printf("Buscando 'orange' na tabela com encadeamento: %s\n",
           buscar_chaining("orange") ? "Encontrado" : "Não Encontrado");
    printf("Buscando 'orange' na tabela com sondagem linear: %s\n",
           buscar_linear("orange") != -1 ? "Encontrado" : "Não Encontrado");
    printf("\n");
    printf("Buscando 'strawberry' na tabela com encadeamento: %s\n",
           buscar_chaining("strawberry") ? "Encontrado" : "Não Encontrado");
    printf("Buscando 'strawberry' na tabela com sondagem linear: %s\n",
           buscar_linear("strawberry") != -1 ? "Encontrado" : "Não Encontrado");
    printf("\n");

    // Remoção de um elemento
    remover_chaining("banana");
    remover_linear("banana");
    printf("\n");
    remover_chaining("strawberry");
    remover_linear("strawberry");
    printf("\n");

    // Visiualização das tabelas após remoção
    mostrar_chaining();
    printf("\n");
    mostrar_linear();   

    // Liberar memória alocada na tabela com encadeamento
    for (int i = 0; i < TABLE_SIZE; i++) {
        Nodo* atual = tabela_chaining[i];
        while (atual != NULL) {
            Nodo* temp = atual;
            atual = atual->proximo;
            free(temp);
        }
    }

    return 0;
}