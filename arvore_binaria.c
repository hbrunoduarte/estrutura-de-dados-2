#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node* left;
    struct node* right;
} Node;

Node* createNode(int value) {
    Node* newNode = malloc(sizeof(Node));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

Node* insert(Node* root, int value) {
    if(root == NULL) {
        return createNode(value);
    }

    if(value < root->value) {
        root->left = insert(root->left, value);
    } else if(value > root->value) {
        root->right = insert(root->right, value);
    }
    return root;
}

Node* seek(Node* root, int value) {
    if(root == NULL || value == root->value) {
        return root;
    } else if(value < root->value) {
        return seek(root->left, value);
    } else {
        return seek(root->right, value);
    }
}

Node* findMin(Node* root) {
    while(root->left != NULL) {
        root = root->left;
    }
    return root;
}

Node* removeNode(Node* root, int value) {
    if(root == NULL) {
        return root;
    }

    if(value < root->value) {
        root->left = removeNode(root->left, value);
    } else if(value > root->value) {
        root->right = removeNode(root->right, value);
    } else {
        //achou o nodo a ser removido
        if(root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp; // retorna null (nao tem filho) ou
                         // retorna o unico filho do nodo removido
        } else if(root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }

        // caso com dois filhos
        // (vai pro no da direita e acha o valor minimo e
        // substitui o no removido pelo no de valor min)
        Node* temp = findMin(root->right);
        root->value = temp->value;
        root->right = removeNode(root->right, temp->value);
    }

    return root;
}

void inOrder(Node* root) {
    if(root != NULL) {
        inOrder(root->left);
        printf("%d ", root->value);
        inOrder(root->right);
    }
}

void preOrder(Node* root) {
    if(root != NULL) {
        printf("%d ", root->value);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void postOrder(Node* root) {
    if(root != NULL) {
        postOrder(root->left);
        postOrder(root->right);
        printf("%d ", root->value);
    }
}