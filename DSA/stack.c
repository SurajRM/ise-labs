#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct stack
{
    int *items;
    unsigned capacity;
    int top;
};
typedef struct stack Stack;

void create_stack(Stack *, int);
bool is_full(Stack *);
bool is_empty(Stack *);
int peek(Stack *);
void display_items(Stack *);
void push(Stack *, int);
int pop(Stack *);

int main()
{
    Stack st;
    int capacity, choice;
    printf("Enter the size of the stack: ");
    scanf("%d", &capacity);
    create_stack(&st, capacity);
    printf("Stack of size %d created\n", capacity);
    while (true)
    {
        printf("\nSelect an operation:\n\
    1: Push\n\
    2: Pop\n\
    3: Peek\n\
    4: Check if stack is full\n\
    5: Check if stack is empty\n\
    6: Display items in stack\n\
    -1: Exit\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter the item to be pushed: ");
            int item;
            scanf("%d", &item);
            push(&st, item);
            break;
        case 2:
            printf(""); // C mandates statements after label
            int tmp = pop(&st);
            if (tmp == -100)
                printf("The stack is empty\n");
            else
                printf("Popped item is %d\n", tmp);
            break;
        case 3:
            printf("The latest item is %d\n", peek(&st));
            break;
        case 4:
            if (is_full(&st))
                printf("The stack is full\n");
            else
                printf("The stack is not full\n");
            break;
        case 5:
            if (is_empty(&st))
                printf("The stack is empty\n");
            else
                printf("The stack is not empty\n");
            break;
        case 6:
            display_items(&st);
            break;
        case -1:
            exit(0);
        default:
            printf("Invalid option\n");
            break;
        }
    }
}

void create_stack(Stack *s, int max_capcity)
{
    s->items = (int *)malloc(max_capcity * sizeof(int));
    s->top = -1;
    s->capacity = max_capcity;
}

bool is_full(Stack *s)
{
    if (s->top == s->capacity - 1)
        return true;
    return false;
}

bool is_empty(Stack *s)
{
    if (s->top == -1)
        return true;
    return false;
}

int peek(Stack *s)
{
    if (!is_empty(s))
        return s->items[s->top];
}

void display_items(Stack *s)
{
    if (is_empty(s))
        printf("STACK EMPTY\n");
    else
    {
        printf("Items: ");
        for (int i = s->top; i >= 0; i--)
        {
            printf("%d ", s->items[i]);
        }
        printf("\n");
    }
}

void push(Stack *s, int newitem)
{
    if (is_full(s))
        printf("STACK FULL\n");
    else
    {
        s->top++;
        s->items[s->top] = newitem;
    }
}

int pop(Stack *s)
{
    if (is_empty(s))
        return -100;
    else
    {
        s->top--;
        return s->items[s->top + 1];
    }
}