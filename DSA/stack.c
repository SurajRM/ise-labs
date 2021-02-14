#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct stack {
    int *items;
    int capacity;
    int top;
} Stack;

Stack *create_stack(int);
bool is_full(Stack *);
bool is_empty(Stack *);
int peek(Stack *);
void display_items(Stack *);
void push(Stack *, int);
int pop(Stack *);
int get_top_third_ele(Stack *);
int get_bottom_third_ele(Stack *st);
void pop_top_n_ele(Stack *, int);

int main() {
    int capacity, choice, temp, item;

    printf("Enter the size of the stack: ");
    scanf("%d", &capacity);
    if (capacity <= 0) {
        printf("Invalid input\n");
        exit(0);
    }
    Stack *st = create_stack(capacity);
    printf("Stack of size %d created\n", capacity);

    while (true) {
        printf("1: Push\n");
        printf("2: Pop\n");
        printf("3: Peek\n");
        printf("4: Check if stack is full\n");
        printf("5: Check if stack is empty\n");
        printf("6: Display items in stack\n");
        printf("7: Get the 3rd element from top of the stack\n");
        printf("8: Pop out top n elements from the stack\n");
        printf("9: Get 3rd element from bottom of the stack\n");
        printf("-1: Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the item to be pushed: ");
                scanf("%d", &item);
                push(st, item);
                break;
            case 2:
                temp = pop(st);
                if (temp == -2)
                    printf("The stack is empty\n");
                else
                    printf("Popped item is %d\n", temp);
                break;
            case 3:
                temp = peek(st);
                if (temp == -2)
                    printf("The stack is empty\n");
                else
                    printf("The latest item is %d\n", temp);
                break;
            case 4:
                if (is_full(st))
                    printf("The stack is full\n");
                else
                    printf("The stack is not full\n");
                break;
            case 5:
                if (is_empty(st))
                    printf("The stack is empty\n");
                else
                    printf("The stack is not empty\n");
                break;
            case 6:
                display_items(st);
                break;
            case 7:
                temp = get_top_third_ele(st);
                if (temp == -2)
                    printf("The top third element does not exist\n");
                else
                    printf("The third element from top of the stack is: %d\n", temp);
                break;
            case 8:
                printf("Enter number of elements to be popped from the stack: ");
                scanf("%d", &temp);
                while (temp > st->top + 1) {
                    printf("The number of elements in the stack is %d, try again: ", st->top + 1);
                    scanf("%d", &temp);
                }
                pop_top_n_ele(st, temp);
                break;
            case 9:
                temp = get_bottom_third_ele(st);
                if (temp == -2)
                    printf("The bottom third element does not exist\n");
                else
                    printf("The third element from bottom of the stack is: %d\n", temp);
                break;
            case -1:
                exit(0);
            default:
                printf("Invalid option\n");
                getchar();
                break;
        }
        printf("\n");
    }
}

Stack *create_stack(int max_capacity) {
    Stack *st = (Stack *) malloc(sizeof(Stack));
    st->items = (int *) malloc(max_capacity * sizeof(int));
    st->top = -1;
    st->capacity = max_capacity;

    return st;
}

bool is_full(Stack *s) {
    if (s->top == s->capacity - 1)
        return true;
    return false;
}

bool is_empty(Stack *s) {
    if (s->top == -1)
        return true;
    return false;
}

int peek(Stack *s) {
    if (!is_empty(s))
        return s->items[s->top];
    return -2;
}

void display_items(Stack *s) {
    if (is_empty(s))
        printf("STACK EMPTY\n");
    else {
        printf("Items: ");
        for (int i = s->top; i >= 0; i--)
            printf("%d ", s->items[i]);
        printf("\n");
    }
}

void push(Stack *s, int new_item) {
    if (is_full(s))
        printf("STACK FULL\n");
    else
        s->items[++s->top] = new_item;
}

int pop(Stack *s) {
    if (!is_empty(s))
        return s->items[--s->top + 1];
    return -2;
}

int get_top_third_ele(Stack *st) {
    Stack *temp = create_stack(3);
    int top_3rd_ele;

    if (st->top >= 2) {
        for (int i = 0; i < 3; i++)
            push(temp, pop(st));
        top_3rd_ele = peek(temp);

        for (int i = 0; i < 3; i++)
            push(st, pop(temp));

        return top_3rd_ele;
    }
    free(temp);
    return -2;
}

int get_bottom_third_ele(Stack *st) {
    Stack *temp = create_stack(st->top - 1);
    int bottom_3rd_ele;

    if (st->top >= 2) {
        for (int i = st->top; i >= 2; i--)
            push(temp, pop(st));
        bottom_3rd_ele = peek(temp);

        for (int i = temp->top; i >= 0; i--)
            push(st, pop(temp));

        return bottom_3rd_ele;
    }
    free(temp);
    return -2;
}

void pop_top_n_ele(Stack *st, int n) {
    for (int i = 0; i < n; i++)
        pop(st);

    printf("After popping %d elements\n", n);
    display_items(st);
}
