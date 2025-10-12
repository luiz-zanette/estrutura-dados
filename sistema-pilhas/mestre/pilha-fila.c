#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50

// Estrutura para os dados da pessoa
typedef struct {
    char nome[30];
    int idade;
} Pessoa;

// Estrutura da Fila
typedef struct {
    Pessoa dados[MAX];
    int inicio, fim;
} Fila;

// Estrutura da Pilha
typedef struct {
    Pessoa dados[MAX];
    int topo;
} Pilha;

// --- Funções da Fila ---

// Inicializa a fila
void inicializarFila(Fila *f) {
    f->inicio = 0;
    // O 'fim' deve começar em -1 para indicar que a fila está vazia.
    f->fim = -1;
}

// Verifica se a fila está vazia
int filaVazia(Fila *f) {
    // A fila está vazia quando o 'fim' é menor que o 'inicio'.
    return f->fim < f->inicio;
}

// Insere um elemento na fila
void inserir(Fila *f, Pessoa info) {
    // Verifique se há espaço antes de inserir
    if (f->fim == MAX - 1) {
        printf("Erro: A fila está cheia.\n");
        return;
    }
    // Incrementa o 'fim' e insere o dado.
    f->fim++;
    f->dados[f->fim] = info;
    printf("Pessoa %s, Idade: %d adicionada à fila.\n", info.nome, info.idade);
}

// Remove um elemento da fila
Pessoa remover(Fila *f) {
    // Verifique se a fila está vazia antes de remover
    if (filaVazia(f)) {
        printf("Erro: A fila está vazia.\n");
        Pessoa pessoaVazia = {"", 0};
        return pessoaVazia;
    }
    // A remoção acontece no 'inicio' e depois incrementamos 'inicio'.
    return f->dados[f->inicio++];
}

// Exibe os elementos da fila
void exibirFila(Fila *f) {
    if (filaVazia(f)) {
        printf("A fila está vazia.\n");
        return;
    }
    // O loop deve ir do 'inicio' até o 'fim'
    for (int i = f->inicio; i <= f->fim; i++) {
        printf("Nome: %s, Idade: %d\n", f->dados[i].nome, f->dados[i].idade);
    }
}

// --- Funções da Pilha ---

// Inicializa a pilha
void inicializarPilha(Pilha *p) {
    // O 'topo' deve começar em -1 para indicar que a pilha está vazia.
    p->topo = -1;
}

// Verifica se a pilha está vazia
int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

// Insere um elemento na pilha (push)
void push(Pilha *p, Pessoa pessoaTopo) {
   // Verifique se há espaço antes de inserir
   if (p->topo == MAX - 1) {
       printf("Erro: A pilha está cheia.\n");
       return;
   }
   // O 'push' deve incrementar o topo E depois inserir o dado.
   p->dados[++p->topo] = pessoaTopo;
}

// Remove um elemento da pilha (pop)
Pessoa pop(Pilha *p) {
    // Verifique se a pilha está vazia antes de remover
    if (pilhaVazia(p)) {
        printf("Erro: A pilha está vazia.\n");
        Pessoa pessoaVazia = {"", 0};
        return pessoaVazia;
    }
    // A remoção acontece no 'topo' e depois decrementamos 'topo'.
    return p->dados[p->topo--];
}

// --- Função Principal ---
int main() {
    Fila filaOriginal, filaReversa;
    Pilha auxiliar;

    inicializarFila(&filaOriginal);
    inicializarFila(&filaReversa);
    inicializarPilha(&auxiliar);

    Pessoa novaPessoa[] = {
        {"Ana", 25},
        {"Bruno", 30},
        {"Carla", 22},
        {"Daniel", 28},
        {"Eva", 35}
    };

    printf("--- Adicionando pessoas à fila original ---\n");
    for (int i = 0; i < 5; i++) {
        inserir(&filaOriginal, novaPessoa[i]);
    }

    printf("\n--- Fila Original ---\n");
    exibirFila(&filaOriginal);

    // Passo 1: Remover todos os elementos da fila e empurrá-los para a pilha
    printf("\n--- Movendo da fila para a pilha ---\n");
    while (!filaVazia(&filaOriginal)) {
        push(&auxiliar, remover(&filaOriginal));
    }

    // Passo 2: Remover todos os elementos da pilha e inseri-los na nova fila
    printf("\n--- Movendo da pilha para a fila reversa ---\n");
    while (!pilhaVazia(&auxiliar)) {
        inserir(&filaReversa, pop(&auxiliar));
    }

    printf("\n--- Fila Reversa ---\n");
    exibirFila(&filaReversa);

    return 0;
}