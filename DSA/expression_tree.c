#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define CAPACITY 200

typedef struct node {
    char data;
    struct node *left_node;
    struct node *right_node;
} node;

typedef struct stack {
    node *items[CAPACITY];
    int top;
} stack;

int precedence(char);

bool is_operator(char);

node *create_node(char);

void preorder_traversal(node *);

void inorder_traversal(node *);

void postorder_traversal(node *);

void push(stack *, node *);

node *pop(stack *);

int main() {
    return 0;
}

int precedence(char symbol) {
    switch (symbol) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
        case '%':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}

bool is_operator(char symbol) {
    if (symbol == '+' || symbol == '-' || symbol == '*' ||
        symbol == '/' || symbol == '%' || symbol == '^')
        return true;
    return false;
}

node *create_node(char symbol) {
    node *new_node = (node *) malloc(sizeof(node));
    new_node->data = symbol;
    new_node->right_node = NULL;
    new_node->left_node = NULL;
    return new_node;
}

void preorder_traversal(node *root) {
    if (root != NULL) {
        printf("%c ", root->data);
        preorder_traversal(root->left_node);
        preorder_traversal(root->right_node);
    }
}

void inorder_traversal(node *root) {
    if (root != NULL) {
        inorder_traversal(root->left_node);
        printf("%c ", root->data);
        inorder_traversal(root->right_node);
    }
}

void postorder_traversal(node *root) {
    if (root != NULL) {
        postorder_traversal(root->left_node);
        postorder_traversal(root->right_node);
        printf("%c ", root->data);
    }
}

void push(stack *st, node *temp) {
    if (st->top == CAPACITY - 1)
        printf("\033[1;31merror: Stack Overflow\033[0m\n");
    else
        st->items[++(st->top)] = temp;
}

node *pop(stack *st) {
    if (st->top == -1) {
        printf("\033[1;31merror: Stack underflow\033[1;31m\n");
        return NULL;
    }
    return st->items[(st->top)--];
}