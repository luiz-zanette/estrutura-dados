// ============================================================
// PRÁTICA 1 - SISTEMA DE BIBLIOTECA
//
// OBJETIVO: Implementar um sistema simples de cadastro de livros com array estático, foco em structs, entrada e saida de dados e organização básica
//
// ============================================================
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Constantes globais - define o maximo de caracteres
#define MAX_LIVROS 50
#define MAX_STRING 100

// Definição da struct Livro - formato tradicional
struct Livro {
    char nome[MAX_STRING];
    char autor[MAX_STRING];
    char editora[MAX_STRING];
    int edicao;
};

// Função para limpar o buffer do teclado
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função principal para definir caminhos e executar o programa
int main() {
    struct Livro biblioteca[MAX_LIVROS];
    int totalLivros = 0;
    int opcao;

    // Loop principal do menu
    do {
        printf("\n=== SISTEMA DE CADASTRO DE LIVROS ===\n"); // exibe o menu
        printf("\n1 - Cadastrar novo livro\n");
        printf("2 - Listar todos os livros\n");
        printf("3 - Sair\n");
        printf("--------------------------------------------\n");
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao); // Le a opção do usuário
        limparBuffer(); // Limpa o buffer do teclado

        // Processa a opção escolhida
        switch (opcao) {
            case 1: // Cadastrar novo livro
                printf("\n--- CADASTRO DE NOVO LIVRO ---\n");
                if (totalLivros < MAX_LIVROS) {
                    printf("Nome do livro: ");
                    fgets(biblioteca[totalLivros].nome, MAX_STRING, stdin);

                    printf("Autor do livro: ");
                    fgets(biblioteca[totalLivros].autor, MAX_STRING, stdin);

                    printf("Editora do livro: ");
                    fgets(biblioteca[totalLivros].editora, MAX_STRING, stdin);

                    biblioteca[totalLivros].nome[strcspn(biblioteca[totalLivros].nome, "\n")] = 0;
                    biblioteca[totalLivros].autor[strcspn(biblioteca[totalLivros].autor, "\n")] = 0;
                    biblioteca[totalLivros].editora[strcspn(biblioteca[totalLivros].editora, "\n")] = 0;

                    printf("Edicao do livro: ");
                    scanf("%d", &biblioteca[totalLivros].edicao);
                    limparBuffer(); // Limpa o buffer do teclado

                    totalLivros++;

                    printf("\nLivro cadastrado com sucesso!\n");

                 } else {
                    printf("\nCapacidade máxima de livros atingida!\n");
                    }

            case 2: // Listar todos os livros
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
                getchar(); // Espera o usuário pressionar Enter antes de continuar
                break;

            case 3: // Sair
                printf("\nSaindo do sistema. Ate logo!\n");
                break;

            default: // Opção inválida
                printf("\nOpcao invalida! Tente novamente.\n");
                printf("Pressione Enter para continuar...");
                getchar(); // Espera o usuário pressionar Enter antes de continuar
                break;
            }
        }
        
        while (opcao != 3); // Continua até o usuário escolher sair
    
        return 0;
    }