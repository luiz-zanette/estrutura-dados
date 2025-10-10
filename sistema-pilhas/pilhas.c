#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char nome [30];
    int idade;
} Pessoa;

#define MAX 5

typedef struct {
    Pessoa itens[MAX];
    int inicio;
    int fim;
    int total;
} Fila;

void inicializaFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

int filaCheia(Fila *f) {
    return f->total == MAX;
}

int filaVazia(Fila *f) {
    return f->total == 0;
}

void inserir(Fila *f, Pessoa p) {
    if (filaCheia(f)) {
        printf("Fila cheia! Não é possível inserir dados\n");
        return;
    }
    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX;
    f->total++;
}

void remover(Fila *f, Pessoa *p) {
    if (filaVazia(f)) {
        printf("Fila vazia! Não é possível remover.\n");
        return;
    }
    *p = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
    f->total--;
    printf("Pessoa removida: %s, Idade: %d\n", p->nome, p->idade);
}

void mostrarFila(Fila *f) {
    if (filaVazia(f)) {
        printf("Fila vazia!\n");
        return;
    }
    printf("Pessoas na fila:\n");
    for (int i = 0, idx = f->inicio; i < f->total; i++, idx = (idx + 1) % MAX) {
        printf("Nome: %s, Idade: %d\n", f->itens[idx].nome, f->itens[idx].idade);
    }
}

int main() {
    Fila f;
    //Inicia fila
    inicializaFila(&f);

    //Cria pessoas
    Pessoa p1 = {"Alice", 30};
    Pessoa p2 = {"Bob", 25};
    Pessoa p3 = {"Charlie", 35};

    //Insere pessoas na fila
    inserir(&f, p1);
    inserir(&f, p2);
    inserir(&f, p3);

    //Mostra fila
    mostrarFila(&f);

    //Remove uma pessoa da fila
    Pessoa removida;
    remover(&f, &removida);

    //Mostra fila novamente
    mostrarFila(&f);

    return 0;
}