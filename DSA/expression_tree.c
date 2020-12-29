#include <stdio.h>
#include <stdbool.h>

#define CAPACITY 200

typedef struct stack {
    char items[CAPACITY];
    int top;
} stack;

typedef struct node {
    char data;
    struct node *left_node;
    struct node *right_node;
} node;

int precedence(char);

bool is_operator(char);

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