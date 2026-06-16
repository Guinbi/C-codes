#include "fila.h"
#include <stdio.h>

int main(){
    Fila* q = init_queue();
    int choice = 0;

    while (choice != 4){
        printf("\n");
        printf("Escolha uma opcao\n");
        printf("1 - Inserir um elemento na fila\n");
        printf("2 - Remover um elemento da fila\n");
        printf("3 - Imprimir a fila\n");
        printf("4 - Sair\n");
        scanf("%d", &choice);
        
        if(choice == 1){
            printf("Escreva o elemento que sera inserido: ");
            int n;
            scanf("%d", &n);
            insert_elem(q, n);
        }

        if (choice == 2){
            remove_elem(q);
        }

        if (choice == 3) {
            print_queue(q);
        }
    }
    destroy_queue(q);
    return 0;
}