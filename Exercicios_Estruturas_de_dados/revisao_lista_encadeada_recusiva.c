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

// Soma 1 em todos os números pares da lista
int sumEven(Node* n){
    if (n != NULL) {
        if (n->info % 2 == 0)
            n->info += 1;
        sumEven(n->prox);
    }
}

// Remove um elemento X da lista
Node* removeElem(Node* n, int x){
    if (n != NULL){
        if (n->info == x){
            Node* aux = n;
            n = n->prox;
            free(aux);
        } else {
            l->prox = removeElem(n->prox, x);
        }
        return l;
    }
}

//Inserir ordenadamente usando return
Node* ordInsert(Node* n, int x){
    if (n != NULL){
        if (x > n->info){
            n->prox = ordInsert(n->prox, x);
            return n;
        }
        else {
            Node* new = malloc(sizeof(Node));
            new->info = x;
            new->prox = n;  
            return new;
        }
    } else {
        Node* new = malloc(sizeof(Node));
        new->info = x;
        new->prox = n;
        return new;
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
    n = insert(n, 2);
    n = insert(n, 3);
    n = insert(n, 4);
    n = insert(n, 4);
    n = insert(n, 5);
    n = insert(n, 7);
    printList(n);
    printf("--------\n");
    // printf("Existe um 40? %d\n", exist(n, 40));
    // printf("Soma: %d\n", totalSum(n));
    // printf("Quantos 1s tem? %d\n", count(n, 1));
    sumEven(n);
    // n = removeElem(n, 55);
    n = ordInsert(n, 10);

    printList(n);

    return 0;
}