#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Professor {
    int matricula;
    char nome[100];
    int salario;
} Professor;

typedef struct Aluno {
    int matricula;
    char nome[100];
    char curso[100];
    int ano_ingresso;
} Aluno;

typedef struct Pessoa {
    int tipo;
    void* pessoa;
    struct Pessoa* next;
} Pessoa;

Pessoa* insert_person(Pessoa* head, void* new_person, int tipo){
    Pessoa* new = malloc(sizeof(Pessoa));
    new->next = head;
    new->pessoa = new_person;
    new->tipo = tipo;
    return new;
}

void print_list(Pessoa* head){
    while (head != NULL){
        if (head->tipo == 2){
            Aluno* a = (Aluno*) head->pessoa;
            printf("\nMatricula: %d", a->matricula);
            printf("\nAno: %d", a->ano_ingresso);
            printf("\n");
        }
        if (head->tipo == 1){
            Professor* p = (Professor*) head->pessoa;
            printf("\nMatricula: %d", p->matricula);
            printf("\nSalario: %d", p->salario);
            printf("\n");
        }
        head = head->next;
    }
}

Pessoa* remove_person(Pessoa* head, int mat){
    Pessoa* current = head;
    Pessoa* prev = NULL;

    while (head != NULL){
        int current_mat = -1;

        if (current->tipo == 1)
            current_mat = ((Professor*) current->pessoa)->matricula;
        else if (current_mat == 2)
            current_mat = ((Aluno*) current->pessoa)->matricula;
        
        if (current_mat == mat){
            Pessoa* to_remove = current;
            if(prev == NULL){
                head = current->next;
            }
            else {
                prev->next = current->next;
            }
            current = current->next;
            free(to_remove->pessoa);
            free(to_remove);
            return head;
        }
        prev = current;
        current = current->next;
    }
    return head;
}

void search(Pessoa* head, int mat){
    while (head != NULL){
        if (head->tipo == 2){
            Aluno* a = (Aluno*) head->pessoa;
            if (a->matricula == mat){
                printf("\nMatricula: %d", a->matricula);
                printf("\nAno: %d", a->ano_ingresso);
                printf("\n");
            }
        }
        if (head->tipo == 1){
            Professor* a = (Professor*) head->pessoa;
            if (a->matricula == mat){
                printf("\nMatricula: %d", a->matricula);
                printf("\nSalario: %d", a->salario);
                printf("\n");
            }
        }
        head = head->next;
    }
}

// Decidi fazer essa sem iterar.
int course_count(Pessoa* head, char* course){
    if (head == NULL){
        return 0;
    }
    int count = 0;
    if (head->tipo == 2){
        Aluno* a = (Aluno*) head->pessoa;
        if (strcmp(a->curso, course) == 0){
            count = 1;
        }
    }
    return count + course_count(head->next, course);
}

// A função supõe que nenhum professor tenha salário negativo,
// por isso 'max' começa como 0.
void greater_wage(Pessoa* head){
    int max = 0;
    Pessoa* head_copy = head;
    while (head_copy != NULL){
        if (head_copy->tipo == 1){
            Professor* a = (Professor*) head_copy->pessoa;
            if (a->salario > max){
                max = a->salario;
            }
        }
        head_copy = head_copy->next;
    }
    head_copy = head;
    while (head_copy != NULL){
        if (head_copy->tipo == 1){
            Professor* a = (Professor*) head_copy->pessoa;
            if (a->salario == max){
                printf("- Professor(a) %s \n", a->nome);
            }
        }
        head_copy = head_copy->next;
    }
}

int main(){
    int choice = 0;
    Pessoa* head = malloc(sizeof(Pessoa));
    
    head->tipo = 0;
    head->next = NULL;
    head->pessoa = NULL;

    while (choice != 6){
        printf("\n1 - Inserir uma pessoa na lista");
        printf("\n2 - Remover uma pessoa pela matrícula");
        printf("\n3 - Buscar uma pessoa pela matrícula");
        printf("\n4 - Contar o numero de alunos em um determinado curso");
        printf("\n5 - Imprimir os professores de maior salário");
        printf("\n6 - Sair");
        printf("\n");
        scanf("%d", &choice);

        if (choice == 1){
            int n;
            printf("Quem voce quer inserir?\n1) Professor\n2) Aluno\n");
            scanf("%d", &n);

            if (n == 1){
                Professor* prof = malloc(sizeof(Professor));

                printf("Escreva matricula, nome e salario: ");
                int matricula;
                char nome[100];
                int salario;
                scanf("%d %s %d", &matricula, nome, &salario);

                prof->matricula = matricula;
                prof->salario = salario;
                strcpy(prof->nome, nome);

                head = insert_person(head, prof, 1);
            } else if (n == 2){
                Aluno* aluno = malloc(sizeof(Aluno));

                printf("Escreva matricula, nome, curso e ano: ");
                int matricula;
                char nome[100];
                char curso[100];
                int ano_ingresso;
                scanf("%d %s %s %d", &matricula, nome, curso, &ano_ingresso);

                aluno->matricula = matricula;
                aluno->ano_ingresso = ano_ingresso;
                strcpy(aluno->nome, nome);
                strcpy(aluno->curso, curso);

                head = insert_person(head, aluno, 2);
            }
        }

        if (choice == 2){
            printf("Digite a matricula que voce quer remover: ");
            int mat;
            scanf("%d", &mat);
            head = remove_person(head, mat);
        }
        
        if (choice == 3){
            int mat;
            printf("Digite a matricula que será buscada: ");
            scanf("%d", &mat);
            search(head, mat);
        }

        if (choice == 4){
            printf("Qual o curso voce quer procurar?\n");
            char course[100];
            scanf("%s", course);
            printf("A contagem de alunos eh: %d", course_count(head, course));
        }

        if (choice == 5){
            printf("Professores com maior salario: \n");
            greater_wage(head);
        }
    }
    return 0;
}