#include <stdio.h>
#include <stdlib.h>

typedef struct List {
    int dest;
    int cost;
    struct List* next;
} List;

void initGraph(List** g, int n){
    int i;
    for (i = 0; i <= n; i++){
        g[i] = NULL;
    }
}

List* insertList(List* g, int d, int c) {
    List* new = malloc(sizeof(List));
    new->dest = d;
    new->cost = c;
    new->next = g;
    return new;
}

void insertEdge(List** g, int origin, int dest, int cost){
    g[origin] = insertList(g[origin], dest, cost);
}

void printList(List* g){
    if (g != NULL){
        printf("-(%d, %d)", g->dest, g->cost);
        printList(g->next);
    } 
}

void printGraph(List** g, int n){
    int i;
    printf("Graph: ");
    for(i = 1; i <= n; i++){
        printf("\n\t%d", i);
        printList(g[i]);
    }
}

void removeEdge(List **g, int origin, int dest){
    List *actual = g[origin];
    List *prev = NULL;
    while(actual != NULL && actual->dest != dest){
        prev = actual;
        actual = actual->next;
    }
    if(actual != NULL){
        if(prev == NULL){
            g[origin] = actual->next;
        } else {
            prev->next = actual->next;
        }
        free(actual);
    }
}

void degree(List **g, int n, int v){
    int input_deg = 0;
    for(int i = 0; i<= n; i++){
          List *actual = g[i];
          while(actual != NULL){
            if(actual->dest == v){
                input_deg++;
            }
            actual = actual->next;
          }
    }

    int output_deg = 0;
    List *actual = g[v];
    while(actual != NULL){
        output_deg++;
        actual = actual->next;
    }
    printf("Grau de entrada do vertice %d: %d\n", v, input_deg);
    printf("Grau de saida do vertice %d: %d\n", v, output_deg);
}

void completeGraph(List **g, int n){
    for(int i = 0; i <= n; i++){
        int full = 0;
        List *actual = g[i];
        while(actual != NULL){
            full++;
            actual = actual->next;
        }
        if(full != n-1){
            printf("Grafo nao completo\n");
            return;
        }
    }
    printf("O grafo eh completo\n");
}

int exist(int* vet, int value, int n){
    for(int i = 0; i < n; i++){
        if(vet[i] == value)
            return 1;
    }
    return 0;
}

void paths(List **g, int b, int* vet, int pos){
    if(vet[pos-1] == b){
        printf("\n");
        for(int i = 0; i < pos; i++)
            printf("%d ", vet[i]);
    } else {
        List* p = g[vet[pos - 1]];
        while(p != NULL){
            if (!exist(vet, p->dest, pos)){
                vet[pos] = p->dest;
                paths(g, b, vet, pos+1);
            }
            p = p->next;
        }
    }
}

int** total_vets; // Vetor de vetores
int total_n; // Posição atual de total_vets

void shortest_path(List **g, int b, int* vet, int pos){
    if(vet[pos-1] == b){
        int* path_copy = malloc(pos * sizeof(int));
        for(int i = 0; i < pos; i++) {
            path_copy[i] = vet[i];
        }
        total_vets[total_n] = path_copy;
        total_n++;
    } else {
        List* p = g[vet[pos - 1]];
        while(p != NULL){
            if (!exist(vet, p->dest, pos)){
                vet[pos] = p->dest;
                shortest_path(g, b, vet, pos+1);
            }
            p = p->next;
        }
    }
}

int *best_path;      // Armazena o melhor caminho
int best_cost;       // Armazena o menor custo
int best_size;       // Armazena o tamanho do melhor caminho
int first_path;      // Flag para saber se é o primeiro caminho

void cheapest_path(List **g, int b, int* vet, int pos, int current_cost){
    if(vet[pos-1] == b){
        if(first_path || current_cost < best_cost){
            best_cost = current_cost;
            best_size = pos;
            
            best_path = malloc(pos * sizeof(int));
            for(int i = 0; i < pos; i++){
                best_path[i] = vet[i];
            }
            first_path = 0;
        }
    } else {
        List* p = g[vet[pos - 1]];
        while(p != NULL){
            if (!exist(vet, p->dest, pos)){
                vet[pos] = p->dest;
                cheapest_path(g, b, vet, pos+1, current_cost + p->cost);
            }
            p = p->next;
        }
    }
}

void intermediate_paths(List **g, int b, int h, int* vet, int pos){
    if(vet[pos-1] == b){
        printf("\n");
        if (exist(vet, h, pos)){
            for(int i = 0; i < pos; i++)
                printf("%d ", vet[i]);
        }
    } else {
        List* p = g[vet[pos - 1]];
        while(p != NULL){
            if (!exist(vet, p->dest, pos)){
                vet[pos] = p->dest;
                intermediate_paths(g, b, h, vet, pos + 1);
            }
            p = p->next;
        }
    }
}

int count_paths = 0;
void UV_edge_paths(List **g, int b, int u, int v, int* vet, int pos){
    if(vet[pos-1] == b){
        int no = 0;
        printf("\n");
        for (int i = 0; i < pos; i++){
            if (vet[i - 1] == u && vet[i] == v){
                no = 1;
                break;
            }
        }
        if (no == 0){
            for (int i = 0; i < pos; i++){
                printf("%d ", vet[i]);
            }
            count_paths += 1;
            printf("Numero de caminhos: %d", count_paths);
        }
    } else {
        List* p = g[vet[pos - 1]];
        while(p != NULL){
            if (!exist(vet, p->dest, pos)){
                vet[pos] = p->dest;
                UV_edge_paths(g, b, u, v, vet, pos + 1);
            }
            p = p->next;
        }
    }
}

int main(){
    int* vet;
    int n;
    int choice = 0;
    printf("Digite o numero de vertices do grafo: ");
    scanf("%d", &n);
    
    List **g = malloc((n+1) * sizeof(List*));
    vet = malloc(n * sizeof(int));
    total_vets = malloc(n * (n-1) * sizeof(int**));
    
    initGraph(g, n);

    int origin;
    int dest;
    int cost;

    while(choice != 9){
        printf("\n1 - Inserir aresta\n");
        printf("2 - Remover aresta\n");
        printf("3 - Imprimir grafo\n");
        printf("4 - Imprimir os graus de entrada e saida de um vertice\n");
        printf("5 - Verificar se o grafo e completo\n");
        printf("6 - Imprimir todos os caminhos entre uma origem e um destino\n");
        printf("7 - Imprimir o caminho mais curto (com menor numero de arestas)\n");
        printf("8 - Imprimir o caminho de menor custo (menor soma dos custos das arestas)\n");
        printf("9 - Sair\n");
        scanf("%d", &choice);

        if (choice == 1){
            printf("Escreva a origem destino e custo da aresta: ");
            scanf("%d %d %d", &origin, &dest, &cost);
            insertEdge(g, origin, dest, cost);
        }

        if (choice == 2){
            printf("Escreva a origem e destino da aresta que sera removida: ");
            scanf("%d %d", &origin, &dest);
            removeEdge(g, origin, dest);
        }

        if (choice == 3){
            printGraph(g, n);
        }

        if (choice == 4){
            printf("Escreva qual vertice deseja calcular os graus de entrada e saida: ");
            scanf("%d", &origin);
            degree(g, n, origin);
        }

        if (choice == 5){
            completeGraph(g, n);
        }

        if (choice == 6){
            printf("Digite a origem e o destino dos caminhos: ");
            scanf("%d %d", &origin, &dest);
            vet[0] = origin;
            paths(g, dest, vet, 1);
        }

        if (choice == 7){
            printf("Digite a origem e o destino do caminho: ");
            scanf("%d %d", &origin, &dest);
            vet[0] = origin;
            
            shortest_path(g, dest, vet, 1);

            int min_length_pos = 0;
            for(int i = 0; i < total_n; i++){
                int length = 0;
                int min_length = n;
                for(int j = 0; j < n; j++){
                    if(total_vets[i][j] != 0)
                        length += 1;
                }
                if (length > min_length){
                    min_length = length;
                    min_length_pos = i;
                    printf("length: %d\n min_length: %d\n min_length_pos: %d\n i: %d", length, min_length, min_length_pos, i);
                }
            }
            printf("O menor caminho eh: ");
            for(int j = 0; j < n; j++){
                if (total_vets[min_length_pos][j] != 0)
                    printf("%d ", total_vets[min_length_pos][j]);
            }
        }

        if (choice == 8){
            printf("Digite a origem e o destino do caminho: ");
            scanf("%d %d", &origin, &dest);
            
            vet[0] = origin;
            first_path = 1;
            best_path = NULL;
            best_cost = 0;
            best_size = 0;
            
            cheapest_path(g, dest, vet, 1, 0);
            
            if(!first_path){
                printf("\nCaminho de menor custo (custo total: %d): ", best_cost);
                for(int i = 0; i < best_size; i++){
                    printf("%d ", best_path[i]);
                }
                printf("\n");
            }
        }

        if (choice == 10){
            int h;
            printf("Digite a origem, destino e intermediario dos caminhos: ");
            scanf("%d %d %d", &origin, &dest, &h);
            vet[0] = origin;
            intermediate_paths(g, dest, h, vet, 1);
        }
        if (choice == 11){
            count_paths = 0;
            int u, v;
            printf("Digite a origem, destino, U e V dos caminhos: ");
            scanf("%d %d %d %d", &origin, &dest, &u, &v);
            vet[0] = origin;
            UV_edge_paths(g, dest, u, v, vet, 1);
        }
    }
}