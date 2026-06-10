#include <stdio.h>
#include <string.h>

int N = 17;

typedef struct Aluno {
    int matricula;
    char nome[50];
    char curso[50];
    int disponibilidade;
} Aluno;

int hash(int x){
    return x % N;
}

void init(char* file_name) {
    FILE* f = fopen(file_name, "wb");
    Aluno s;
    s.matricula = 0;
    s.disponibilidade = 1;
    strcpy(s.nome, "");
    strcpy(s.curso, "");
    for (int i = 0; i < N; i++){
        fwrite(%s, sizeof(Aluno), 1, f);
    }
    fclose(f);
}

int findPos(char* file_name, int mat){
    FILE* f = fopen(file_name, "rb");
    int pos = hash(mat);
    Aluno s;
    fseek(f, pos * sizeof(Aluno), SEEK_SET);
    fread(&s, sizeof(Aluno), 1, f);
    while(s.disponibilidade == 0) {
        pos = (pos + 1) % N;
        fseek(f, pos * sizeof(Aluno), SEEK_SET);
        fread(&s, sizeof(Aluno), 1, f);
    }
    fclose(f);
    return pos;
}

void insert(char* file_name, int mat, char* name, char* course){
    int pos = findPos(mat);
    FILE* f = fopen(file_name, "r+b");
    Aluno s;
    s.matricula = mat;
    s.disponibilidade = 0;
    strcpy(s.nome, name);
    strcpy(s.curso, course);
    fseek(f, pos * sizeof(Aluno), SEEK_SET);
    fwrite(&s, sizeof(Aluno), 1);
    fclose(f);
}

void search(char* file_name, int mat){
    int pos = findPos(mat);
    FILE* f = fopen(file_name, "rb");
    Aluno s;
    fseek(f, pos * sizeof(Aluno), SEEK_SET);
    fread(&s, sizeof(Aluno), 1, f);
    printf("Matricula: %s \nNome: %s \nCurso: %s", s.matricula, s.nome, s.curso);
    fclose(f);
}

void printHashTable(){
    for (int p = 0; p < N; p++) {
        search(file_name, p);
    }
}

int main() {
    int choice;
    char file_name[100] = "alunos.b"
    printf("Escolha uma opção\n");
    printf("1 - Inserir um novo aluno\n");
    printf("2 - Imprimir as informações de um determinado aluno\n");
    printf("3 - Imprimir a tabela de dispersão\n");
    printf("4 - Sair");
    init(file_name);
    scanf("%d", &choice);
    while (choice != 4){
        if (choice == 1){
            int mat;
            char name[50];
            char course[50];
            printf("Insira as informações do aluno que voce quer inserir: \n");
            printf("Matrícula: ");
            scanf("%d", &mat);
            getchar();

            printf("Nome: ");
            scanf("%s", &name);
            getchar();

            printf("Course: ");
            scanf("%s", &course);
            getchar();

            insert(file_name, mat, name, course);
            printf("Aluno inserido na posicao %d", findPos(mat));
         }
         if (choice == 2){
            printf("Insira uma matricula para consultar: ");
            int mat;
            scanf("%d", &mat);
            search(file_name, mat);
         }
         if (choice == 3){
            printHashTable();
         }
    }
    return 0;
}