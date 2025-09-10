#ifndef funcoes_h
#define funcoes_h

// Constantes e inclusões necessárias
#include <stdio.h>
#include <string.h>

#define MAX_LIVROS 50
#define MAX_EMPRESTIMOS 100
#define MAX_STRING 100

// Definição das structs
struct Livro {
    char nome[MAX_STRING];
    char autor[MAX_STRING];
    char editora[MAX_STRING];
    int edicao;
    int disponivel;
};

struct Emprestimo {
    int idLivro;
    char nomeUsuario[MAX_STRING];
};

// Declaração das funções
void limparBuffer();
void exibirMenu();
void cadastrarLivro(struct Livro *biblioteca, int *totalLivros);
void listarLivros(const struct Livro *biblioteca, int totalLivros);
void emprestarLivro(struct Livro *biblioteca, struct Emprestimo *emprestimos, int totalLivros, int *totalEmprestimos);
void listarEmprestimos(const struct Livro *biblioteca, const struct Emprestimo *emprestimos, int totalEmprestimos);
void liberarMemoria(struct Livro *biblioteca, struct Emprestimo *emprestimos);

#endif