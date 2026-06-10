#include <stdio.h>
#include <stdlib.h>

void printCombinations1(char* v, int pos, int n, char* l){
    int i;
    int countE = 0;
    int countI = 0;
    if (pos == n){
        for(i = 0; i < n; i++){
            if (v[i] == 'E'){
                countE += 1;
            }
            if (v[i] == 'I'){
                countI += 1;
            }
        }
        if (countE < countI) {
            for(i = 0; i < n; i++){
                printf("%c ", v[i]);
            }
            printf("\n");
        }
    } else {
        for (i = 0; i < n; i++){
            v[pos] = l[i];
            printCombinations1(v, pos + 1, n, l);
        }
    }
}

void printCombinations2(int* v, int pos, int n, int* l){
    int i;
    int sum = 0;
    if (pos == n){
        for (i = 0; i < pos; i++){
            sum += v[i];
        }
        if (sum % 2 == 0) {
            for(i = 0; i < n; i++){
                printf("%d ", v[i]);
            }
            printf("Soma: %d \n", sum);
        }
    } else {
        for (i = 0; i < n; i++){
            v[pos] = l[i];
            printCombinations2(v, pos + 1, n, l);
        }
    }
}

void printCombinations3(char* v, int pos, int n) {
    int i;
    if (pos == n){
        for(i = 0; i < n; i++){
            printf("%d ", v[i]);
        }
        if ((v[0] && v[1]) || (v[2] && v[3])){
            printf("v");
        } else {
            printf("f");
        }
        printf("\n");
    } else {
        for (i = 0; i < 2; i++){
            v[pos] = i;
            printCombinations3(v, pos + 1, n);
        }
    }
}

int main(){
    int choice = 0;
    
    while (choice != 4){
        printf("Escolha uma opcao: \n");
        printf("1 - Todas as combinações de A, E, I, tal que total de Es seja inferior ao total de Is\n");
        printf("2 - Contar as combinações de 15,31,55 e 44 de tamanho n, cuja soma dos elementos da combinações é par\n");
        printf("3 - Imprimir as combinações de verdadeiro e falsa das variáveis A, B, C e D tal que a expressão (A ^ B) v (C ^ D) seja verdadeiro\n");
        printf("4 - Sair\n");
        scanf("%d", &choice);

        if (choice == 1){
            char* v = malloc(sizeof(char) * 3);
            char l[3] = {'A', 'E', 'I'};
            printCombinations1(v, 0, 3, l);
            free(v);
        }
        if (choice == 2){
            int n;
            scanf("%d", &n);
            int* v = malloc(sizeof(char) * n);
            int l[4] = {15, 31, 55, 44};
            printCombinations2(v, 0, n, l);
            free(v);
        }
        if (choice == 3){
            char* v = malloc(sizeof(char) * 4);
            printf("A B C D\n");
            printCombinations3(v, 0, 4);
            free(v);
        }
    }    
    return 0;
}