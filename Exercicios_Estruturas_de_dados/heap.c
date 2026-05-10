#include <stdio.h>
#include <math.h>

int total_elem = 0; // Total de elementos do heap

// ---------- Funções Auxiliares -------------
int leftChildIndex(int x){
    int index = (2 * x) + 1;
    if (x >= total_elem || index >= total_elem)
        return -1;
    else
        return index;
}

int rightChildIndex(int x){
    int index = (2 * x) + 2;
    if (x >= total_elem || index >= total_elem)
        return -1;
    else
        return index;
}

int parentIndex(int x){
    int index = floor((x - 1) / 2);
    if (index <= -1 || x >= total_elem) return -1;
    else return index;
}

void bubble_up(int *heap, int pos){
    if (pos == -1) return;
    int parent = parentIndex(pos);
    if (parent == -1) return;
    if (heap[parent] > heap[pos]){
        int temp = heap[parent];
        heap[parent] = heap[pos];
        heap[pos] = temp;
        bubble_up(heap, parent);
    }
}

void bubble_down(int *heap, int pos){
    if (pos != -1 && leftChildIndex(pos) != -1){
        int smallerChild = leftChildIndex(pos);
        if (smallerChild != 1 && heap[smallerChild] > heap[rightChildIndex(pos)]){
            smallerChild = heap[rightChildIndex(pos)];
        }

        if (heap[pos] > heap[smallerChild]){
            int temp = heap[pos];
            heap[pos] = heap[smallerChild];
            heap[smallerChild] = temp;
            bubble_down(heap, smallerChild);
        }
    }
}
// -----------------------------------------------

int insertElem(int *heap, int x){
    heap[total_elem] = x;
    total_elem++;

    bubble_up(heap, total_elem - 1);
}

int removeElem(int *heap){
    if (total_elem == 0)
        return -1;
    else {
        int retorno = heap[0];

        heap[0] = heap[total_elem - 1];
        total_elem--;
        bubble_down(heap, 0);

        return retorno;
    }
}

int main(){
    int choice = 0;
    int heap[100];
    
    while (choice != 4){
        printf("1 - Inserir um elemento x na heap\n");
        printf("2 - Remover um elemento\n");
        printf("3 - Imprimir heap\n");
        printf("4 - Sair\n");
        scanf("%d", &choice);
        if (choice == 1){
            int elem;
            printf("Escolha um elemento para inserir: ");
            scanf("%d", &elem);
            insertElem(heap, elem);
        }
        if (choice == 2){
            int retorno = removeElem(heap);
            if (retorno == -1)
                printf("Nao existe elementos na heap");
            else 
                printf("Você removeu o elemento %d\n", retorno);
        }
        if (choice == 3){
            for (int i = 0; i < total_elem; i++){
                printf("%d ", heap[i]);
            }
            printf("\n");
        }
    }

    return 0;
}