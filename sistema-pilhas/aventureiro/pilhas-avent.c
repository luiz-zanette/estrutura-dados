#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 5 // Tamanho máximo da pilha

typedef struct {
    char nome[30];
    int idade;
} Pessoa;

typedef struct {
    Pessoa itens[MAX];
    int topo;
} Pilha;

void inicializarPilha(Pilha *p) {
    p->topo = -1;
}
int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}
int pilhaCheia(Pilha *p) {
    return p->topo == MAX - 1;
}

void push(Pilha *p, Pessoa novaPessoa) {
    if (pilhaCheia(p)) {
        printf("Pilha cheia! Nao é possível adicionar mais pessoas.\n");
        return;
    }
    p->topo++;
    p->itens[p->topo] = novaPessoa;
    printf("Pessoa %s, Idade: %d adicionada à pilha.\n", novaPessoa.nome, novaPessoa.idade);
}

void pop(Pilha *p, Pessoa *removida) {
    if (pilhaVazia(p)) {
        printf("Pilha vazia! Nao é possível remover pessoas.\n");
        return;
    }
    *removida = p->itens[p->topo];
    p->topo--;
    printf("Pessoa %s, Idade: %d removida da pilha.\n", removida->nome, removida->idade);
}

void peek(Pilha *p, Pessoa *topo) {
    if (pilhaVazia(p)) {
        printf("Pilha vazia! Nao há pessoas para mostrar.\n");
        return;
    }
    *topo = p->itens[p->topo];
    printf("Pessoa no topo: %s, Idade: %d\n", topo->nome, topo->idade);
}

void seek(Pilha *p) {
    if (pilhaVazia(p)) {
        printf("Pilha vazia! Nao há pessoas para mostrar.\n");
        return;
    }
    printf("Pessoas na pilha:\n");
    for (int i = p->topo; i >= 0; i--) {
        printf("%d. %s, Idade: %d\n", i + 1, p->itens[i].nome, p->itens[i].idade);
    }
}

int main () {
    Pilha p;
    inicializarPilha(&p);

    Pessoa a = {"Ana", 30};
    Pessoa b = {"Bruno", 25};
    Pessoa c = {"Carla", 28};
    
    printf("Adicionando pessoas à pilha:\n");
    push(&p, a);
    push(&p, b);
    push(&p, c);

    printf("\nMostrando a Pilha:\n");
    seek(&p);

    printf("\nRemovendo apenas uma pessoa da pilha:\n");
    Pessoa removida;
    pop(&p, &removida);

    printf("\nMostrando a Pilha:\n");
    seek(&p);

    printf("Mostando o topo da pilha:\n");
    Pessoa topo;
    peek(&p, &topo);

    return 0;
}
