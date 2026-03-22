#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int info;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

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

TreeNode* printTreePre(TreeNode* node){
    if (node != NULL){
        printf("%d ", node->info);
        printTreePre(node->left);
        printTreePre(node->right);
    }
}

TreeNode* printTreeIn(TreeNode* node){
    if (node != NULL){
        printTreeIn(node->left);
        printf("%d ", node->info);
        printTreeIn(node->right);
    }
}

TreeNode* printTreePos(TreeNode* node){
    if (node != NULL){
        printTreePos(node->left);
        printTreePos(node->right);
        printf("%d ", node->info);
    }
}

int exist(TreeNode* node, int x){
    int e;
    if (node != NULL) {
        if (node->info == x)
            return 1;
        e = exist(node->left, x);
        if (e == 1) return e;
        e = exist(node->right, x);
        return e;
    }
    return 0;
}

int count(TreeNode* node){
    if (node != NULL){
        return 1 + count(node->left) + count(node->right);
    }
    return 0;
}

void leavesNode(TreeNode* node){
    if (node != NULL){
        if (node->left == NULL && node->right == NULL) {
            printf("%d ", node->info);
        }
        leavesNode(node->left);
        leavesNode(node->right);
    }
}

int main(){
    int choice = 0;
    TreeNode* rootNode;
    FILE* f;

    while (choice != 6){
        printf("\n");
        printf("1- Ler uma arvore de um arquivo fornecido pelo usuario\n");
        printf("2- Imprimir a arvore (opções: pre-ordem; em-ordem; e pos-ordem)\n");
        printf("3- Verificar se um elemento x existe na arvore\n");
        printf("4- Contar o numero de elementos na arvore\n");
        printf("5- Imprimir os nos folhas da árvore\n");
        printf("6- Sair\n");
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
                printf("Digite a ordem em que voce quer imprimir: ");
                
                scanf("%d", &choice2);

                if (choice2 == 1) printTreePre(rootNode);
                if (choice2 == 2) printTreeIn(rootNode);
                if (choice2 == 3) printTreePos(rootNode);
                
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
            printf("O numero de elementos da arvore eh: %d", count(rootNode));
        }

        if (choice == 5){
            printf("Os nos folhas sao: ");
            leavesNode(rootNode);
        }
    }

    return 0;
}