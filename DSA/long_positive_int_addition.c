#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int digit;
    struct node *next;
} node;

typedef struct CircularLL {
    node *head;
} CircularLL;

void input_long_int(CircularLL *);
node *create_node(int);
void insert_end(CircularLL *, int);
void insert_start(CircularLL *, int);
void long_int_view(CircularLL *);
void add_long_int(CircularLL *, CircularLL *, CircularLL *);
void delete_CircularLL(CircularLL *);

int main() {
    return 0;
}

void input_long_int(CircularLL *LL) {
    int num, digit;
    float num2;
    while (1) {
        printf("Enter a positive integer addend: ");
        scanf("%f", &num2);
        num = (int)num2;

        if (num != num2 || num2 < 0) {
            printf("Invalid input\n");
            continue;
        }
        break;
    }
    while(num) {
        digit = num % 10;
        num /= 10;
        insert_end(LL, digit);
    }
}