// ============================================================
// PRÁTICA 2 - SISTEMA DE BIBLIOTECA
//
// OBJETIVO: Adicionar a funcionalidade de emprestar e devolver livros, utilizando ponteiros e manipulação de arrays;
// Trabalhar com malloc/calloc/free para alocação dinâmica de memória
//
// ============================================================

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Constantes globais - define o maximo de caracteres
#define MAX_LIVROS 50
#define MAX_EMPRESTIMOS 100 // Limite de livros emprestados
#define MAX_STRING 100

// Definição da struct Livro - formato tradicional
struct Livro {
    char nome[MAX_STRING];
    char autor[MAX_STRING];
    char editora[MAX_STRING];
    int edicao;
    int disponivel; // 1 se disponível, 0 se emprestado
};

// Nova struct para gerenciar empréstimos
struct Emprestimo {
    int idLivro; // Índice do livro na biblioteca, para saber qual foi emprestado
    char nomeUsuario[MAX_STRING];
};

// Função para limpar o buffer do teclado
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função principal para definir caminhos e executar o programa
int main() {
    // Alocação dinâmica de memória para os livros e empréstimos com ponteiros
    struct Livro *biblioteca;
    struct Emprestimo *emprestimos;

    // Uso de calloc para inicializar a memória alocada do zero
    biblioteca = (struct Livro *)calloc(MAX_LIVROS, sizeof(struct Livro));

    // Uso de malloc para alocar memória para os empréstimos
    emprestimos = (struct Emprestimo *)malloc(MAX_EMPRESTIMOS * sizeof(struct Emprestimo));

    // Verificação de erro na alocação de memória
    if (biblioteca == NULL || emprestimos == NULL) {
        printf("Erro na alocação de memória!\n");
        return 1; // Sai do programa com código de erro
    }

    int totalLivros = 0; // Contador de livros na biblioteca
    int totalEmprestimos = 0; // Contador de empréstimos realizados
    int opcao;  // Variável para armazenar a opção do menu

    do {
        printf("\n=== Sistema de Biblioteca ===\n");
        printf("1 - Adicionar Livro\n");
        printf("2 - Listar Livros\n");
        printf("3 - Emprestar Livro\n");
        printf("4 - Listar Empréstimos\n");
        printf("0 - Sair\n");
        printf("------------------------------\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        limparBuffer(); // Limpa o buffer do teclado

        switch(opcao) {
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
                    
                    biblioteca[totalLivros].disponivel = 1; // Inicializa como disponível
                    
                    totalLivros++;
                    
                    printf("\nLivro cadastrado com sucesso!\n");

                 } else {
                    printf("\nCapacidade máxima de livros atingida!\n");
                    }
                break;

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

                case 3: // Emprestar livro
                    printf("\n--- EMPRESTAR LIVRO ---\n");

                    if (totalEmprestimos >= MAX_EMPRESTIMOS) {
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

                            // Validação da escolha do usuário
                            if (idLivro >= 0 && idLivro < totalLivros && biblioteca[idLivro].disponivel) {
                                printf("Nome do usuário que está solicitando o empréstimo: ");
                                fgets(emprestimos[totalEmprestimos].nomeUsuario, MAX_STRING, stdin);
                                emprestimos[totalEmprestimos].nomeUsuario[strcspn(emprestimos[totalEmprestimos].nomeUsuario, "\n")] = 0;

                                // Registro do empréstimo
                                emprestimos[totalEmprestimos].idLivro = idLivro;

                                // Atualiza o status do livro para emprestado
                                biblioteca[idLivro].disponivel = 0;
                                totalEmprestimos++;
                                printf("Livro emprestado com sucesso!");
                            } else {
                                printf("Opção inválida ou livro não disponível.\n");
                            }
                        }
                    }
                    printf("Pressione Enter para continuar...");
                    getchar(); // Espera o usuário pressionar Enter antes de continuar
                    break;

                case 4: // Listar empréstimos
                    printf("\n--- LISTA DE EMPRÉSTIMOS ---\n");
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
                    getchar(); // Espera o usuário pressionar Enter antes de continuar
                    break;

                case 0: // Sair
                    printf("\nSaindo do sistema. Ate logo!\n");
                    break;

                default: // Opção inválida
                    printf("\nOpcao invalida! Tente novamente.\n");
                    getchar(); // Espera o usuário pressionar Enter antes de continuar
                    break;
            }
        } while (opcao != 0); // Continua até o usuário escolher sair 

    // Liberação da memória alocada
    free(biblioteca);
    free(emprestimos);
    printf("Memória liberada. Programa encerrado.\n");

    return 0;
}