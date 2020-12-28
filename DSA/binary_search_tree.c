#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int data;
    struct node *left_node, *right_node;
} node;

node *create_node(int);

node *insert_node(node *, int);

void preorder_traversal(node *);

void inorder_traversal(node *);

void postorder_traversal(node *);

void linear_representation(node *);

bool is_leaf_node(node *);

node *delete_node(node *, int);

node *min_value_node(node *);

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

void inorder_traversal(node *root) {
    if (root != NULL) {
        inorder_traversal(root->left_node);
        printf("%d ", root->data);
        inorder_traversal(root->right_node);
    }
}

void postorder_traversal(node *root) {
    if (root != NULL) {
        postorder_traversal(root->left_node);
        postorder_traversal(root->right_node);
        printf("%d ", root->data);
    }
}

bool is_leaf_node(node *root) {
    return root->left_node == NULL && root->right_node == NULL;
}

void linear_representation(node *root) {
    if (root == NULL) {
        printf("-");
        return;
    }
    if (is_leaf_node(root)) {
        printf("%d", root->data);
        return;
    }
    printf("%d(", root->data);
    linear_representation(root->left_node);
    printf(", ");
    linear_representation(root->right_node);
    printf(")");
}

node *delete_node(node *root, int key) {
    if (root == NULL)
        return root;
    if (key < root->data)
        root->left_node = delete_node(root->left_node, key);
    else if (key > root->data)
        root->right_node = delete_node(root->right_node, key);
    else {
        if (root->left_node == NULL) {
            node *temp = root->right_node;
            free(root);
            return temp;
        } else if (root->right_node == NULL) {
            node *temp = root->left_node;
            free(root);
            return temp;
        }
        node *min = min_value_node(root->right_node);
        root->data = min->data;
        root->right_node = delete_node(root->right_node, min->data);
    }
    return root;
}

node *min_value_node(node *root) {
    node *temp = root;
    while (temp && temp->left_node != NULL)
        temp = temp->left_node;

    return temp;
}