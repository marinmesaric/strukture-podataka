#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define ALLOC_ERR -2;
#define EXIT_SUCCESS -1;

struct _node;
typedef struct _node* Position;
typedef struct _node {
    int value;
    Position left;
    Position right;
} Node;


Position insert(Position root, int value);
Position createNode(int value);
int inorder(Position root);
int preorder(Position root);
int postorder(Position root);
int levelorder(Position root);


int main() {

    Position root = NULL;

    root = insert(root, 8);
    insert(root, 3);
    insert(root, 2);
    insert(root, 1);
    insert(root, 9);
    insert(root, 7);

    printf("in order: ");
    inOrder(root);
    printf("\npre order: ");
    preOrder(root);
    printf("\npost order: ");
    postOrder(root);
    printf("\nlevel order: ");
    levelOrder(root);
    printf("\n");

	return 0;
}


Position insert(Position root, int value) {
    if (!root) {
        return createNode(value);
    }
    if (value <= root->value)
        root->left = insert(root->left, value);
    else if (value > root->value)
        root->right = insert(root->right, value);
}


Position createNode(int value) {
    Position newNode = NULL;
    newNode = (Position)malloc(sizeof(Node));
    if (!newNode) {
        return ALLOC_ERR;
    }
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}


int inorder(Position root) {
    if (!root) return;
    inorder(root->left);
    printf("%d ", root->value);
    inorder(root->right);
    
}


int preorder(Position root) {
    if (!root) return;
    printf("%d ", root->value);
    preorder(root->left);
    preorder(root->right);
}


int postorder(Position root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->value);
}


int levelOrder(Position root) {
    if (root == NULL)
        return;

    Position queue[100] = { 0 };
    int front = 0, rear = 0;

    queue[rear++] = root;

    while (front < rear) {
        Position current = queue[front++];

        printf("%d ", current->value);

        if (current->left != NULL)
            queue[rear++] = current->left;

        if (current->right != NULL)
            queue[rear++] = current->right;
    }
    return EXIT_SUCCESS;
}