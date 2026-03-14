#include <stdio.h>
#include <stdlib.h>

// Nós da lista encadeada
typedef struct node {
    int info;
    struct node* prox;
} Node;

// Retorna 1 se o número existe na lista, retorna 0 se não existe
int exist(Node* n, int x){
    if (n != NULL) {
        if (n->info == x)
            return 1;
        return exist(n->prox, x);
    }
    return 0;
}

// Insere um número no final da lista
Node* insert(Node* n, int x){
    if (n == NULL) {
        n = malloc(sizeof(Node));
        n->prox = NULL;
        n->info = x;
        return n;
    } else {
        n->prox = insert(n->prox, x);
        return n;
    }
}

// Retorna a soma total dos elementos da lista
int totalSum(Node* n){
    if (n->prox == NULL){
        return n->info;
    } else {
        return totalSum(n->prox) + n->info;
    }
}

// Retorna o número de ocorrências de um número X na lista
int count(Node* n, int x){
    if (n == NULL) return 0;
    if (n->info == x){
        return count(n->prox, x) + 1;
    } else {
        return count(n->prox, x);
    }
}

int sumEven(Node** n){
    if (*n != NULL) {
        if ((*n)->info % 2 == 0)
            (*n)->info += 1;
        sumEven(&(*n)->prox);
    }
}

// Imprime a lista
void printList(Node* n){
    if (n != NULL){
        printf("%d \n", n->info);
        printList(n->prox);
    }
}

int main() {
    Node* n;
    n->prox = NULL;
    n->info = 1;

    printf("Lista:\n");
    n = insert(n, 10);
    n = insert(n, 25);
    n = insert(n, 40);

    n = insert(n, 55);
    n = insert(n, 30);
    n = insert(n, 15);
    n = insert(n, 70);
    printList(n);
    printf("--------\n");
    printf("Existe um 40? %d\n", exist(n, 40));
    printf("Soma: %d\n", totalSum(n));
    printf("Quantos 1s tem? %d\n", count(n, 1));
    sumEven(&n);
    printList(n);

    return 0;
}