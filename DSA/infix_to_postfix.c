#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LEN 512

int top;
char infix_string[MAX_LEN], postfix_string[MAX_LEN], stack[MAX_LEN];

char pop();
int precedence(char);
bool is_empty();
void infix_to_postfix();
void push(char);
bool validity(int, int);
bool is_operator(char);

int main() {
    top = -1;
    printf("\t\tInfix to postfix\n");
    printf("Input the infix expression: ");
    scanf("%s", infix_string);

    if (!validity(0, (int) strlen(infix_string) - 1)) {
        printf("Invalid infix expression\n");
        exit(0);
    }

    infix_to_postfix();
    printf("Equivalent postfix expression: %s\n", postfix_string);
    return 0;
}

void infix_to_postfix() {
    int count, temp = 0;
    char next;
    char symbol;
    for (count = 0; count < strlen(infix_string); count++) {
        symbol = infix_string[count];
        switch (symbol) {
            case '(':
                push(symbol);
                break;
            case ')':
                while ((next = pop()) != '(') {
                    postfix_string[temp++] = next;
                }
                break;
            case '+':
            case '-':
            case '*':
            case '/':
            case '%':
            case '^':
                while (!is_empty() && precedence(stack[top]) >= precedence(symbol))
                    postfix_string[temp++] = pop();
                push(symbol);
                break;
            default:
                postfix_string[temp++] = symbol;
        }
    }
    while (!is_empty()) {
        postfix_string[temp++] = pop();
    }
    postfix_string[temp] = '\0';
}

int precedence(char symbol) {
    switch (symbol) {
        case '(':
            return 0;
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

void push(char symbol) {
    if (top >= MAX_LEN) {
        printf("error: stack is full\n");
        exit(1);
    }
    stack[++top] = symbol;
}

bool is_empty() {
    if (top == -1)
        return true;
    return false;
}

char pop() {
    if (is_empty()) {
        printf("error: stack is empty\n");
        exit(1);
    }
    return (stack[top--]);
}

bool validity(int start, int end) {
    int len = end - start + 1, paren;

    if (len == 0 || infix_string[start] == ')')
        return false;
    if (len == 1 && isalpha(infix_string[start]))
        return true;

    if (infix_string[start] == '(') {
        paren = 1;
        for (int i = start + 1; i <= end; i++) {
            if (infix_string[i] == '(')
                paren++;
            else if (infix_string[i] == ')')
                paren--;
            if (paren == 0) {
                if (i == end)
                    return validity(start + 1, end - 1);
                else if (!is_operator(infix_string[i + 1]))
                    return false;
                else
                    return validity(start + 1, i - 1) && validity(i + 2, end);
            }
        }
        return false;
    } else {
        for (int i = start; i <= end; i++) {
            if (infix_string[i] == '(' || infix_string[i] == ')')
                return false;
            if (is_operator(infix_string[i]))
                return validity(start, i - 1) && validity(i + 1, end);
        }
    }
    return false;
}

bool is_operator(char symbol) {
    if (symbol == '+' || symbol == '-' || symbol == '*' ||
        symbol == '/' || symbol == '%' || symbol == '^')
        return true;
    return false;
}