#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Árvore AVL sem o fator de balanceamento
typedef struct TreeNode {
    int info;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;


// ---------- Código copiado do trabalho anterior -------------------
TreeNode* ReadTree(FILE *f) {
    char c;
    int n;

    fscanf(f,"%c",&c);		
    fscanf(f,"%d",&n);

    if (n == -1) {				
        fscanf(f,"%c",&c);
        return NULL;
    }
    else {
        TreeNode* node = malloc(sizeof(TreeNode));
        
        node->info = n;
        node->left = ReadTree(f);
        node->right = ReadTree(f);

        fscanf(f,"%c",&c);
        
        return node;
    }
}

void printTreePre(TreeNode* node){
    if (node != NULL){
        printf("%d ", node->info);
        printTreePre(node->left);
        printTreePre(node->right);
    }
}

void printTreeIn(TreeNode* node){
    if (node != NULL){
        printTreeIn(node->left);
        printf("%d ", node->info);
        printTreeIn(node->right);
    }
}

void printTreePos(TreeNode* node){
    if (node != NULL){
        printTreePos(node->left);
        printTreePos(node->right);
        printf("%d ", node->info);
    }
}

void printLevel(TreeNode* a, int cont, int nivel) {
   if (a != NULL) {
      if (cont == nivel)
         printf("%d ", a->info);
      else {
         printLevel(a->left, cont+1, nivel); 
         printLevel(a->right, cont+1, nivel); 
      }
   }
}

void printTreeWidth(TreeNode* node, int h){
    for(int i = 0; i < h; i++){
        printLevel(node, 0, i);
        printf("\n");
    }
}

int exist(TreeNode* node, int x){
    int e;
    if (node != NULL) {
        if (node->info == x) return 1;
        if(node->info > x)
            return exist(node->left, x);
        else
            return exist(node->right, x);
    }
    return 0;
}

int levelOf(TreeNode* node, int count, int x){
    if (node != NULL){
        if (node->info == x){
           return count; 
        }
        else if (node->info > x) {
            return levelOf(node->left, count+1, x);
        }
        else {
            return levelOf(node->right, count+1, x);
        }
    }
    return -1;
}

void printLessThen(TreeNode* node, int x){
    // Mudei o estilo das chaves pra ficar mais legível
    if (node != NULL)
    {
        if (node->info < x && node->left == NULL && node->right == NULL)
        {
            printf("%d ", node->info);
        } 
        else if (node->info >= x) 
        {
            printLessThen(node->left, x);
        } 
        else if (node->info < x)
        {
            printLessThen(node->left, x);
            printLessThen(node->right, x);
        }
    }
}

int height(TreeNode* node){
    if (node == NULL) return 0;
    else {
        int hL = height(node->left);
        int hR = height(node->right);
        if (hL >= hR) 
            return hL + 1;
        else 
            return hR + 1;
    }
}

// --------------- Novo Código ----------------------

// Rotação simples para a direita
TreeNode* simple_right_rotation(TreeNode* p){
    TreeNode* b = p->left;
    p->left = b->right;
    b->right = p;
    return b;
}

// Rotação simples para a esquerda
TreeNode* simple_left_rotation(TreeNode* p){
    TreeNode* b = p->right;
    p->right = b->left;
    b->left = p;
    return b;
}

// Rotação dupla para a direita
TreeNode* double_right_rotation(TreeNode* p){
    p->left = simple_left_rotation(p->left);
    p = simple_right_rotation(p);
    return p;
}

// Rotação dupla para a esquerda
TreeNode* double_left_rotation(TreeNode* p){
    p->right = simple_right_rotation(p->right);
    p = simple_left_rotation(p);
    return p;
}

// Rotação geral para a esquerda
TreeNode* rotation_to_left(TreeNode* node){
    if (node != NULL){
        int hL = height(node->left);
        int hR = height(node->right);

        if (hR - hL < -1) {
            hL = height(node->left->left);
            hR = height(node->left->right);

            if (hL > hR)
                node = double_left_rotation(node);
            else
                node = simple_left_rotation(node);
        }

        return node;
    }
}

// Rotação geral para a direita
TreeNode* rotation_to_right(TreeNode* node){
    if (node != NULL){
        int hL = height(node->left);
        int hR = height(node->right);

        if (hR - hL < -1) {
            hL = height(node->left->left);
            hR = height(node->left->right);

            if (hL > hR)
                node = simple_right_rotation(node);
            else
                node = double_right_rotation(node);
        }

        return node;
    }
}

// Insere um nó
TreeNode* insertNode(TreeNode* node, int x){
    if (node != NULL){
        if (x <= node->info) {
            node->left = insertNode(node->left, x);
            node = rotation_to_right(node);
        }
        else {
            node->right = insertNode(node->right, x);
            node = rotation_to_left(node);
        }
        return node;
    } 
    else {
        TreeNode* new_node = malloc(sizeof(TreeNode));
        new_node->info = x;
        new_node->left = NULL;
        new_node->right = NULL;
        return new_node;
    }
}

// Remove um nó
TreeNode* removeElem(TreeNode* node, int x){
    if (node != NULL){
        if (x < node->info){
            node->left = removeElem(node->left, x);
            node = rotation_to_left(node);
        }
        else if (x > node->info){
            node->right = removeElem(node->right, x);
            node = rotation_to_right(node);
        }
        else if (x == node->info){
            if (node->left == NULL && node->right == NULL){
                free(node);
                return NULL;
            }
            if (node->right == NULL) {
                TreeNode* childL = node->left;
                free(node);
                return childL;
            }
            else if (node->left == NULL){
                TreeNode* childR = node->right;
                free(node);
                return childR;
            }
            else {
                TreeNode* aux = node->left;
                while(aux->right != NULL){
                    aux = aux->right;
                }
                node->info = aux->info;
                node->left = removeElem(node->left, aux->info);
                node = rotation_to_left(node);
            }
        }
        return node;
    }
}


int main(){
    int choice = 0;
    TreeNode* rootNode;
    FILE* f;

    while (choice != 8){
        printf("\n");
        printf("1- Ler uma arvore de um arquivo fornecido pelo usuario\n");
        printf("2- Imprimir a arvore (opcoes: pre-ordem; em-ordem; pos-ordem; largura)\n");
        printf("3- Verificar se um elemento x existe na arvore\n");
        printf("4- Imprimir o nivel de um noh x\n");
        printf("5- Imprimir as folhas menores que um valor x\n");
        printf("6- Inserir um nó x na árvore\n");
        printf("7- Remover um nó x da árvore\n");
        printf("8- Sair\n");
        printf("\n");
        printf("Escolha uma opcao: ");

        scanf("%d", &choice);
        
        if(choice == 1){
            printf("Digite o nome do arquivo: ");

            char fileName[100];
            scanf("%s", fileName);

            f = fopen(fileName, "r");
            if (f == NULL){
                printf("O arquivo nao existe\n");
            }
            rootNode = ReadTree(f);
            printf("Arvore lida\n");
        }

        if (choice == 2){
            if (rootNode == NULL){
                printf("A arvore nao existe\n");
            } else {
                int choice2;
                printf("1 - pre-ordem\n");
                printf("2 - em-ordem\n");
                printf("3 - pos-ordem\n");
                printf("4 - largura\n");
                printf("Digite a ordem em que voce quer imprimir: ");
                
                scanf("%d", &choice2);

                if (choice2 == 1) printTreePre(rootNode);
                if (choice2 == 2) printTreeIn(rootNode);
                if (choice2 == 3) printTreePos(rootNode);
                if (choice2 == 4) printTreeWidth(rootNode, height(rootNode));
            }
        }

        if (choice == 3) {
            int elem;
            printf("Escolha o elemento que voce quer achar na arvore: ");
            scanf("%d", &elem);
            
            if (exist(rootNode, elem) == 1){
                printf("O elemento %d existe na arvore\n", elem);
            } else {
                printf("O elemento %d nao existe na arvore\n", elem);
            }
        }

        if (choice == 4){
            int elem;
            printf("Escolha o elemento que voce quer o nivel na arvore: ");
            scanf("%d", &elem);

            int result = levelOf(rootNode, 0, elem);
            if (result != -1)
                printf("O nivel desse elemento eh: %d\n", result);
            else 
                printf("Esse elemento não existe\n");
        }

        if (choice == 5){
            int elem;
            printf("Escolha o elemento que voce quer que as folhas sejam menores: ");
            scanf("%d", &elem);

            printf("Os nos folhas sao: ");
            printLessThen(rootNode, elem);
        }

        if(choice == 6){
            int elem;
            printf("Escolha o elemento que voce quer inserir na arvore: ");
            scanf("%d", &elem);
            rootNode = insertNode(rootNode, elem);
        }

        if(choice == 7){
            int elem;
            printf("Escolha o elemento que voce deseja remover: ");
            scanf("%d", &elem);
            rootNode = removeElem(rootNode, elem);
        }
    }
    return 0;
}