#ifndef FUNCOES_H
#define FUNCOES_H

// Definição das structs
typedef struct {
    char dados[10][50];
    int quantidade;
} ListaEstatica;

typedef struct No {
    char* dado;
    struct No* proximo;
} No;

typedef No* ListaEncadeada;

// Protótipos das funções da Lista Estática
void iniciarListaEstatica(ListaEstatica *lista);
void inserirListaEstatica(ListaEstatica *lista, const char *produto);
void removerListaEstatica(ListaEstatica *lista, const char *produto);
void listarListaEstatica(const ListaEstatica *lista);

// Protótipos das funções da Lista Encadeada
void iniciarListaEncadeada(ListaEncadeada *lista);
void inserirListaEncadeada(ListaEncadeada *lista, const char *produto);
void removerListaEncadeada(ListaEncadeada *lista, const char *produto);
void listarListaEncadeada(const ListaEncadeada *lista);
void liberarListaEncadeada(ListaEncadeada *lista);

// Protótipos das funções de menu
void menuListaEstatica(ListaEstatica *lista);
void menuListaEncadeada(ListaEncadeada *lista);

#endif