#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funcoes.h"

// Definição das funções modularizadas
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void exibirMenu() {
    printf("\n=== Sistema de Biblioteca ===\n");
    printf("1 - Adicionar Livro\n");
    printf("2 - Listar Livros\n");
    printf("3 - Emprestar Livro\n");
    printf("4 - Listar Empréstimos\n");
    printf("0 - Sair\n");
    printf("------------------------------\n");
    printf("Escolha uma opção: ");
}

void cadastrarLivro(struct Livro *biblioteca, int *totalLivros) {
    printf("\n--- CADASTRO DE NOVO LIVRO ---\n");
    if (*totalLivros < MAX_LIVROS) {
        printf("Nome do livro: ");
        fgets(biblioteca[*totalLivros].nome, MAX_STRING, stdin);

        printf("Autor do livro: ");
        fgets(biblioteca[*totalLivros].autor, MAX_STRING, stdin);

        printf("Editora do livro: ");
        fgets(biblioteca[*totalLivros].editora, MAX_STRING, stdin);

        biblioteca[*totalLivros].nome[strcspn(biblioteca[*totalLivros].nome, "\n")] = 0;
        biblioteca[*totalLivros].autor[strcspn(biblioteca[*totalLivros].autor, "\n")] = 0;
        biblioteca[*totalLivros].editora[strcspn(biblioteca[*totalLivros].editora, "\n")] = 0;
        
        printf("Edicao do livro: ");
        scanf("%d", &biblioteca[*totalLivros].edicao);
        limparBuffer();
        
        biblioteca[*totalLivros].disponivel = 1;
        
        (*totalLivros)++;
        
        printf("\nLivro cadastrado com sucesso!\n");
    } else {
        printf("\nCapacidade máxima de livros atingida!\n");
    }
}

void listarLivros(const struct Livro *biblioteca, int totalLivros) {
    printf("\n--- LISTA DE LIVROS CADASTRADOS ---\n");
    if (totalLivros == 0) {
        printf("Nenhum livro cadastrado.\n");
    } else {
        for (int i = 0; i < totalLivros; i++) {
            printf("\nLivro %d:\n", i + 1);
            printf("Nome: %s\n", biblioteca[i].nome);
            printf("Autor: %s\n", biblioteca[i].autor);
            printf("Editora: %s\n", biblioteca[i].editora);
            printf("Edicao: %d\n", biblioteca[i].edicao);
        }
    }
    printf("Pressione Enter para continuar...");
    getchar();
}

void emprestarLivro(struct Livro *biblioteca, struct Emprestimo *emprestimos, int totalLivros, int *totalEmprestimos) {
    printf("\n--- EMPRESTAR LIVRO ---\n");
    if (*totalEmprestimos >= MAX_EMPRESTIMOS) {
        printf("Limite máximo de empréstimos atingido!\n");
    } else {
        printf("Livros disponíveis para empréstimo:\n");
        int disponiveis = 0;
        for (int i = 0; i < totalLivros; i++) {
            if (biblioteca[i].disponivel) {
                printf("%d - %s\n", i + 1, biblioteca[i].nome);
                disponiveis++;
            }
        }
        if (disponiveis == 0) {
            printf("Nenhum livro disponível para empréstimo.\n");
        } else {
            printf("Escolha o número do livro para emprestar: ");
            int numLivro;
            scanf("%d", &numLivro);
            limparBuffer();

            int idLivro = numLivro - 1;

            if (idLivro >= 0 && idLivro < totalLivros && biblioteca[idLivro].disponivel) {
                printf("Nome do usuário que está solicitando o empréstimo: ");
                fgets(emprestimos[*totalEmprestimos].nomeUsuario, MAX_STRING, stdin);
                emprestimos[*totalEmprestimos].nomeUsuario[strcspn(emprestimos[*totalEmprestimos].nomeUsuario, "\n")] = 0;

                emprestimos[*totalEmprestimos].idLivro = idLivro;

                biblioteca[idLivro].disponivel = 0;
                (*totalEmprestimos)++;
                printf("Livro emprestado com sucesso!");
            } else {
                printf("Opção inválida ou livro não disponível.\n");
            }
        }
    }
    printf("Pressione Enter para continuar...");
    getchar();
}

void listarEmprestimos(const struct Livro *biblioteca, const struct Emprestimo *emprestimos, int totalEmprestimos) {
    printf("\n--- LISTA DE EMPRÉSTIMOS REALIZADOS ---\n");
    if (totalEmprestimos == 0) {
        printf("Nenhum empréstimo realizado.\n");
    } else {
        for (int i = 0; i < totalEmprestimos; i++) {
            int idLivro = emprestimos[i].idLivro;
            printf("\nEmpréstimo %d:\n", i + 1);
            printf("Livro: %s\n", biblioteca[idLivro].nome);
            printf("Usuário: %s\n", emprestimos[i].nomeUsuario);
        }
    }
    printf("Pressione Enter para continuar...");
    getchar();
}

void liberarMemoria(struct Livro *biblioteca, struct Emprestimo *emprestimos) {
    free(biblioteca);
    free(emprestimos);
    printf("Memória liberada. Programa encerrado.\n");
}