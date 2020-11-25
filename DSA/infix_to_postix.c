#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

char infix_string[200], postfix_string[200];
int top;
int stack[200];

int pop();
int precedence(char);
int is_empty();
void infix_to_postfix();
int check_space(char);
void push(long int);
bool validity(int, int);
bool is_operator(char);

int main()
{
    int count, length;
    char temp;
    top = -1;
    printf("INPUT THE INFIX EXPRESSION : ");
    scanf("%s", infix_string);
    if (!validity(0, strlen(infix_string) - 1))
    {
        printf("Invalid input\n");
        exit(0);
    }
    infix_to_postfix();
    printf("\nEQUIVALENT POSTFIX EXPRESSION : %s\n", postfix_string);
    return 0;
}

void infix_to_postfix()
{
    unsigned int count, temp = 0;
    char next;
    char symbol;
    for (count = 0; count < strlen(infix_string); count++)
    {
        symbol = infix_string[count];
        if (!check_space(symbol))
        {
            switch (symbol)
            {
            case '(':
                push(symbol);
                break;
            case ')':
                while ((next = pop()) != '(')
                {
                    postfix_string[temp++] = next;
                }
                break;
            case '+':
            case '-':
            case '*':
            case '/':
            case '%':
            case '^':
                while (!is_empty() && precedence(stack[top]) >= precedence(symbol)) // Check precedence and push the higher one
                    postfix_string[temp++] = pop();
                push(symbol);
                break;
            default:
                postfix_string[temp++] = symbol;
            }
        }
    }
    while (!is_empty())
    {
        postfix_string[temp++] = pop();
    }
    postfix_string[temp] = '\0';
}

int precedence(char symbol)
{
    switch (symbol)
    {
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

int check_space(char symbol)
{
    if (symbol == '\t' || symbol == ' ')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void push(long int symbol)
{
    if (top > 20)
    {
        printf("Stack Overflow\n");
        exit(1);
    }
    top = top + 1;
    stack[top] = symbol;
}

int is_empty()
{
    if (top == -1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int pop()
{
    if (is_empty())
    {
        printf("Stack is Empty\n");
        exit(1);
    }
    return (stack[top--]);
}

bool validity(int start, int end)
{
    int len = end - start + 1;
    bool v1, v2;

    if (len == 0 || infix_string[start] == ')')
        return false;
    if (len == 1 && isalpha(infix_string[start]))
        return true;
    if (infix_string[start] == '(')
    {
        int paren = 1;
        for (int i = start + 1; i < end + 1; i++)
        {
            if (infix_string[i] == '(')
                paren++;
            else if (infix_string[i] == ')')
                paren--;
            if (paren == 0)
            {
                if (i == end)
                    return validity(start + 1, end - 1);
                else if (!is_operator(infix_string[i + 1]))
                    return false;
                else
                {
                    v1 = validity(start + 1, i - 1);
                    v2 = validity(i + 2, end);
                    break;
                }
            }
        }
        if (paren != 0)
            return false;
    }
    else
    {
        for (int i = start; i <= end; i++)
        {
            if (infix_string[i] == '(' || infix_string[i] == ')')
                return false;
            if (is_operator(infix_string[i]))
            {
                v1 = validity(start, i - 1);
                v2 = validity(i + 1, end);
                break;
            }
        }
    }
    return v1 == true && v2 == true;
}

bool is_operator(char symbol)
{
    if (symbol == '+' || symbol == '-' || symbol == '*' ||
        symbol == '/' || symbol == '%' || symbol == '^')
        return true;
    return false;
}