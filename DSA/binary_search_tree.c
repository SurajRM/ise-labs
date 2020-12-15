#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *left_node, *right_node;
} node;

node *create_node(int);

node *insert_node(node *, int);

void preorder_traversal(node *);

void inorder_traversal(node *);

void postorder_traversal(node *);

int main() {
    return 0;
}

node *create_node(int data) {
    node *new_node = (node *) malloc(sizeof(node));
    new_node->data = data;
    new_node->left_node = NULL;
    new_node->right_node = NULL;
    return new_node;
}

node *insert_node(node *root, int data) {
    if (root == NULL) {
        root = create_node(data);
    } else if (data < root->data)
        root->left_node = insert_node(root->left_node, data);
    else
        root->right_node = insert_node(root->right_node, data);
    return root;
}

void preorder_traversal(node *root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder_traversal(root->left_node);
        preorder_traversal(root->right_node);
    }
}

void inorder_traversal(node *rename) {
    if (rename != NULL) {
        inorder_traversal(rename->left_node);
        printf("%d ", rename->data);
        inorder_traversal(rename->right_node);
    }
}

void postorder_traversal(node *root) {
    if (root != NULL) {
        postorder_traversal(root->left_node);
        postorder_traversal(root->right_node);
        printf("%d ", root->data);
    }
}