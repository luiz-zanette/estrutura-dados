// ============================================================
// 
// PRÁTICA 3 - SISTEMA DE BIBLIOTECA
//
// OBJETIVO: Modularizar o código, manter codigo mais limpo, organizado
//           e facilitar a manutenção do sistema.
//
// ============================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h" // Inclui o arquivo de cabeçalho com as declarações das funções

// Função principal para definir caminhos e executar o programa
int main() {
    // Alocação dinâmica de memória para os livros e empréstimos com ponteiros
   struct Livro *biblioteca = (struct Livro *)calloc(MAX_LIVROS, sizeof(struct Livro));
   struct Emprestimo *emprestimos = (struct Emprestimo *)malloc(MAX_EMPRESTIMOS * sizeof(struct Emprestimo));

    // Verificação de erro na alocação de memória
    if (biblioteca == NULL || emprestimos == NULL) {
        printf("Erro na alocação de memória!\n");
        return 1; // Sai do programa com código de erro
    }

    int totalLivros = 0; // Contador de livros na biblioteca
    int totalEmprestimos = 0; // Contador de empréstimos realizados
    int opcao;  // Variável para armazenar a opção do menu

    do {
        exibirMenu();
        scanf("%d", &opcao);
        limparBuffer();

        switch(opcao) {
            case 1: // Cadastrar novo livro
            cadastrarLivro (biblioteca, &totalLivros);
            break;

            case 2: // Listar todos os livros
                listarLivros(biblioteca, totalLivros);
                break;

                case 3: // Emprestar livro
                emprestarLivro(biblioteca, emprestimos, totalLivros, &totalEmprestimos);
                break;

                case 4: // Listar empréstimos
                listarEmprestimos(biblioteca, emprestimos, totalEmprestimos);
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
    liberarMemoria (biblioteca, emprestimos);
    
    return 0;
}