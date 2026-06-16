#include "fila.h"
#include <stdio.h>
#include <stdlib.h>

#define QUEUE_SIZE 200

struct Fila{
    int data[QUEUE_SIZE];
    int n;         
    int begin;          
    int end;  
};

Fila* init_queue(){
    Fila* Q = malloc(sizeof(Fila));
    Q->n = 0;
    Q->begin = Q->end = 0;
    return Q;
}

void destroy_queue(Fila* Q) {
    free(Q);
}

void remove_elem(Fila* Q){
    printf("\nElemento removido: %d\n", Q->data[Q->begin]);
    Q->n--;
    Q->begin = (Q->begin+1) % QUEUE_SIZE;
}

void insert_elem(Fila* Q, int x){
    Q->data[Q->end] = x;
    Q->n++;
    Q->end = (Q->end+1) % QUEUE_SIZE;
}

void print_queue(Fila* Q){
    int count = 0;
    int i = Q->begin;
    while (count < Q->n){
        printf("%d ", Q->data[i]);
        i = (i + 1) % QUEUE_SIZE;
        count += 1;
    }
}

