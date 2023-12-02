#include <stdio.h>
#include <stdlib.h>

// Estrutura do nó da árvore binária
struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

// Função para criar um novo nó na árvore
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Função para inserir um nó na árvore
struct Node* insertNode(struct Node* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }

    if (value < root->data) {
        root->left = insertNode(root->left, value);
    } else if (value > root->data) {
        root->right = insertNode(root->right, value);
    }

    return root;
}

// Função para realizar busca em pré-ordem (raiz-esquerda-direita)
void preOrder(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preOrder(root->left);
        preOrder(root->right);
    }
}

// Função para realizar busca em ordem (esquerda-raiz-direita)
void inOrder(struct Node* root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%d ", root->data);
        inOrder(root->right);
    }
}

// Função para realizar busca em pós-ordem (esquerda-direita-raiz)
void postOrder(struct Node* root) {
    if (root != NULL) {
        postOrder(root->left);
        postOrder(root->right);
        printf("%d ", root->data);
    }
}

// Função para encontrar o nó com menor valor (nó mais à esquerda)
struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;

    while (current && current->left != NULL) {
        current = current->left;
    }

    return current;
}

// Função para remover um nó na árvore
struct Node* removeNode(struct Node* root, int value) {
    if (root == NULL) {
        return root;
    }

    if (value < root->data) {
        root->left = removeNode(root->left, value);
    } else if (value > root->data) {
        root->right = removeNode(root->right, value);
    } else {
        // Nó com apenas um filho ou sem filhos
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        // Nó com dois filhos: encontrar o sucessor (menor nó à direita)
        struct Node* temp = minValueNode(root->right);

        // Copiar o valor do sucessor para este nó
        root->data = temp->data;

        // Remover o sucessor
        root->right = removeNode(root->right, temp->data);
    }

    return root;
}

// Função principal (Menu de opções)
int main() {
    struct Node* root = NULL;
    int choice, value;

    do {
        printf("\n* * * MENU DE OPCOES * * *\n");
        printf("1. Incluir no\n");
        printf("2. Remover no\n");
        printf("3. Buscar pre-ordem\n");
        printf("4. Buscar em ordem\n");
        printf("5. Buscar pos-ordem\n");
        printf("0. Encerrar\n");
        printf("Opcao: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Digite o valor a ser incluido: ");
                scanf("%d", &value);
                root = insertNode(root, value);
                break;
            case 2:
                printf("Digite o valor a ser removido: ");
                scanf("%d", &value);
                root = removeNode(root, value);
                break;
            case 3:
                printf("Busca em pre-ordem: ");
                preOrder(root);
                printf("\n");
                break;
            case 4:
                printf("Busca em ordem: ");
                inOrder(root);
                printf("\n");
                break;
            case 5:
                printf("Busca em pos-ordem: ");
                postOrder(root);
                printf("\n");
                break;
            case 0:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (choice != 0);

    return 0;
}

