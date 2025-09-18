#include <stdio.h>

typedef struct{
    float valor;
    int i;
    int j;
} Pivo;

Pivo acharPivo(int m, int n, float M[m][n]){
    Pivo p;
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            if (M[i][j] != 0){
                p.valor = M[i][j];
                p.i = i;
                p.j = j;
                return p;
            }
        }
    }
}

void escalonamentoLinha(int m, int n, float M[m][n]){
    Pivo p = acharPivo(m, n, M);
    float num = M[p.i + 1][p.j];
    printf("numero embaixo do pivo: %.2f\n", num);
}

int main(){
    int m, n;
    scanf("%d %d", &m, &n);
    float M[m][n]; 

    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            scanf("%f", &M[i][j]);
        }
    }   

    escalonamentoLinha(m, n, M);

    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            printf("%.2f ", M[i][j]);
        }
        printf("\n");
    }
    return 0;
}