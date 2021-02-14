#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define CAPACITY 512
#define BOLD_RED "\e[1;31m"
#define RESET "\e[0m"

typedef struct node {
    char data;
    struct node *left_node, *right_node;
} node;

typedef struct stack {
    node *items[CAPACITY];
    int top;
} stack;

int precedence(char);
bool is_operator(char);
node *create_node(char);
stack *create_stack();
void preorder_traversal(node *);
void postorder_traversal(node *);
void push(stack *, node *);
node *pop(stack *);
bool is_empty(stack *);
bool is_full(stack *);
bool check_space(char symbol);
node *create_expression_tree(char expression[CAPACITY]);
bool validity(char *, int, int);

int main() {
    node *root = NULL;
    char infix[CAPACITY];

    printf("Enter an infix expression: ");
    scanf("%[^\n]s", infix);

    root = create_expression_tree(infix);

    printf("Prefix expression: ");
    preorder_traversal(root);
    printf("\nPostfix expression: ");
    postorder_traversal(root);
    printf("\n");
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

stack *create_stack() {
    stack *st = (stack *) malloc(sizeof(struct stack));
    st->top = -1;

    return st;
}

void preorder_traversal(node *root) {
    if (root != NULL) {
        printf("%c ", root->data);
        preorder_traversal(root->left_node);
        preorder_traversal(root->right_node);
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
    if (is_full(st))
        printf(BOLD_RED "error:" RESET "stack overflow\n");
    else
        st->items[++st->top] = temp;
}

node *pop(stack *st) {
    if (is_empty(st)) {
        printf(BOLD_RED "error:" RESET "stack underflow\n");
        return NULL;
    }
    return st->items[st->top--];
}

bool is_empty(stack *st) {
    return st->top == -1;
}

bool is_full(stack *st) {
    return st->top == CAPACITY - 1;
}

node *create_expression_tree(char *expression) {
    if (!validity(expression, 0, (int) strlen(expression) - 1)) {
        printf(BOLD_RED "error:" RESET "invalid expression\n");
        exit(1);
    }
    stack *tree_st = create_stack();
    stack *operator_st = create_stack();
    char symbol;
    node *new_node = NULL, *temp = NULL;
    for (int i = 0; expression[i] != '\0'; i++) {
        symbol = expression[i];
        if (check_space(symbol))
            continue;
        new_node = create_node(symbol);
        if (isalnum(symbol))
            push(tree_st, new_node);
        else {
            if (is_empty(operator_st))
                push(operator_st, new_node);
            else {
                while (!is_empty(operator_st) &&
                       precedence(operator_st->items[operator_st->top]->data) >= precedence(symbol)) {
                    temp = pop(operator_st);
                    temp->right_node = pop(tree_st);
                    temp->left_node = pop(tree_st);
                    push(tree_st, temp);
                }
                push(operator_st, new_node);
            }
        }
    }

    while (!is_empty(operator_st)) {
        temp = pop(operator_st);
        temp->right_node = pop(tree_st);
        temp->left_node = pop(tree_st);
        push(tree_st, temp);
    }
    return pop(tree_st);
}

bool check_space(char symbol) {
    return symbol == ' ';
}

bool validity(char *infix, int start, int end) {
    int len = end - start + 1, paren;

    if (len == 0 || infix[start] == ')')
        return false;
    if (len == 1 && isalpha(infix[start]))
        return true;

    if (infix[start] == '(') {
        paren = 1;
        for (int i = start + 1; i <= end; i++) {
            if (check_space(infix[i]))
                continue;
            if (infix[i] == '(')
                paren++;
            else if (infix[i] == ')')
                paren--;
            if (paren == 0) {
                if (i == end)
                    return validity(infix, start + 1, end - 1);
                else if (!is_operator(infix[i + 1]))
                    return false;
                else
                    return validity(infix, start + 1, i - 1) && validity(infix, i + 2, end);
            }
        }
        return false;
    } else {
        for (int i = start; i <= end; i++) {
            if (check_space(infix[i]))
                continue;
            if (infix[i] == '(' || infix[i] == ')')
                return false;
            if (is_operator(infix[i]))
                return validity(infix, start, i - 1) && validity(infix, i + 1, end);
        }
    }
    return true;
}