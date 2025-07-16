#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    char nome [20];
    int vida;
    int ataque;
    int defesa;
} Heroi;

Heroi cadastrarHerois(int indice_jogador){
    Heroi h;
    printf("----- Jogador %d -----\n", indice_jogador);
    printf("Digite o nome do heroi: ");
    
    // pega todos os caracteres do input até o "\n"
    scanf(" %[^\n]", &h.nome);

    // pega o resto da divisão por 51 (que fica entre 0 e 50)
    // soma 50
    // retornando numeros entre 50 e 100 e atribuindo à variável "vida"
    // mesma coisa para os outros atributos
    h.vida = rand() % 51 + 50;
    h.ataque = rand() % 21 + 10;
    h.defesa = rand() % 16 + 5;
    return h;
}

int realizarAtaque(int atq, int def){
    int dano = atq - def;
    if (dano <= 0){
        return 0;
    }

    return atq - def;
}

int verificarDerrota(int vida){
    if (vida <= 0){
        return 0;
    } else {
        return 1;
    }
}

int main(){
    Heroi herois[2];
    srand(time(NULL));
    for (int i = 1; i <= 2; i++){
        herois[i - 1] = cadastrarHerois(i);
    }

    printf("--- %s ---\n", herois[0].nome);
    printf("Vida: %d\n", herois[0].vida);
    printf("Ataque: %d\n", herois[0].ataque);
    printf("Defesa: %d\n", herois[0].defesa);
    
    printf("--- %s ---\n", herois[1].nome);
    printf("Vida: %d\n", herois[1].vida);
    printf("Ataque: %d\n", herois[1].ataque);
    printf("Defesa: %d\n", herois[1].defesa);

    // Calcula o dano
    int dano1, dano2;
    dano1 = realizarAtaque(herois[0].ataque, herois[1].defesa);
    dano2 = realizarAtaque(herois[1].ataque, herois[0].defesa);

    if (dano1 > 0 || dano2 > 0){
        while (verificarDerrota(herois[0].vida) == 1 && verificarDerrota(herois[1].vida) == 1){
            herois[1].vida -= dano1;
                
            if (verificarDerrota(herois[1].vida) == 0){
                break;
            }
            herois[0].vida -= dano2;
        }
    } else {
        printf("Deu empate");
        return 0;
    }

    if(herois[1].vida > 0){
        printf("O heroi %s ganhou\n", herois[1].nome);
        printf("Vida restante: %d\n", herois[1].vida);
        if (herois[1].vida > 20){
            printf("Trivial\n");
        }
    } else {
        printf("O heroi %s ganhou\n", herois[0].nome);
        printf("Vida restante: %d\n", herois[0].vida);
        if (herois[0].vida > 20){
            printf("Trivial\n");
        }
    }
    system("PAUSE");
    return 0;
}