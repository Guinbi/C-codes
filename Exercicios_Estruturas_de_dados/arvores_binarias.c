#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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

int height(TreeNode* a){
    if(a==NULL){
        return 0;
    }
    else{
        int he = height(a->left);
        int hd = height(a->right);
        if(he>hd){
            return he+1;
        }
            else{
                return hd+1;
            }
        }
    }

  int NivelCompleto(TreeNode* a, int cont, int nivel){
        if(a != NULL){

           int r = NivelCompleto(a->left, cont+1, nivel) + NivelCompleto(a->right, cont+1, nivel);

           if(r >=1){
            return 1;
           }
        }

        if(cont <= nivel){
            if(a == NULL){
            
                return 1;
               
            }
        }
            return 0;
        }
    
    

    int Acha_Nivel(TreeNode* a, int cont, int y){
    if(a != NULL){
        if(a->info == y){
        printf("\nNivel: %d", cont);
        return 1;
        }
        
        int r = Acha_Nivel(a->left, cont+1, y) + Acha_Nivel(a->right, cont+1, y);

        if(r >= 1){
        return 1;
        }
    }
    }

int order(TreeNode* a, int min, int max){
    int r = 0;
    if(a != NULL){ 
        if (a->info < min || a->info > max) return 1;
        r = order(a->left, min, a->info);
        if (r == 1) return 1;
        r = order(a->right, a->info, max);
        return r;
    }
    return 0;
}

int main(){
    int choice = 0;
    TreeNode* rootNode;
    FILE* f;

    while (choice != 9){
        printf("\n");
        printf("1- Ler uma arvore de um arquivo fornecido pelo usuario\n");
        printf("2- Imprimir a arvore (opcoes: pre-ordem; em-ordem; pos-ordem; largura)\n");
        printf("3- Verificar se um elemento x existe na arvore\n");
        printf("4- Contar o numero de elementos na arvore\n");
        printf("5- Imprimir os nos folhas da arvore\n");
        printf("6- Verificar se a arvore esta ordenada\n");
        printf("7- Verificar se uma arvore eh completa\n");
        printf("8- Imprimir o nivel ao qual o no x pertence\n");
        printf("9- Sair\n");
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
            printf("O numero de elementos da arvore eh: %d", count(rootNode));
        }

        if (choice == 5){
            printf("Os nos folhas sao: ");
            leavesNode(rootNode);
        }

        if(choice == 6){
            
            if( order(rootNode, INT_MIN, INT_MAX) == 1){
            printf("\nNao esta ordenada");
            }else{
                printf("\nEsta ordenada");
            }
        }

        if(choice == 7){
         int a = height(rootNode);
            if(  NivelCompleto(rootNode, 0, a - 2) == 1){
            printf("\nNao esta completa");
            }else{
                printf("\nEsta completa");
            }
           
        }

        if(choice == 8){
            int a;
            printf("\nO nivel de qual no voce deseja encontrar? ");
            scanf("%d", &a);
            if(Acha_Nivel(rootNode, 0, a) != 1){
                printf("\nNao esta na arvore");
            }
        }
        
    }

    return 0;
}