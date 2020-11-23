#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int digit;
    struct node *next;
} node;

typedef struct CircularLL {
    node *tail;
} CircularLL;

void input_long_int(CircularLL *);
node *create_node(int);
void insert_end(CircularLL *, int);
void insert_start(CircularLL *, int);
void long_int_view(CircularLL *);
void add_long_int(CircularLL *, CircularLL *, CircularLL *);
void delete_circularll(CircularLL *);

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
    while (num) {
        digit = num % 10;
        num /= 10;
        insert_end(LL, digit);
    }
}

node *create_node(int digit) {
    node *temp = (node *)malloc(sizeof(node));
    temp->digit = digit;
    temp->next = NULL;
    return temp;
}

void insert_end(CircularLL *LL, int digit) {
    node *new_node = create_node(digit);
    if (LL->tail == NULL) {
        LL->tail = new_node;
        new_node->next = new_node;
        return;
    }
    new_node->next = LL->tail->next;
    LL->tail->next = new_node;
    LL->tail = new_node;
}

void insert_start(CircularLL *LL, int digit) {
    node *new_node = create_node(digit);
    if (LL->tail == NULL) {
        LL->tail = new_node;
        new_node->next = new_node;
        return;
    }
    new_node->next = LL->tail->next;
    LL->tail->next = new_node;
}

void long_int_view(CircularLL *LL) {
    node *temp = LL->tail->next;
    do {
        printf("%d", temp->digit);
        temp = temp->next;
    } while (temp != LL->tail->next);
    printf("\n");
}

void add_long_int(CircularLL *ans, CircularLL *L1, CircularLL *L2) {
    int carry = 0, sum, digit;
    node *left_over, *tail_node;

    if (!L1->tail && !L2->tail)
        return;
    if (!L1->tail)
        ans = L2;
    if (!L2->tail)
        ans = L1;

    node *p = L1->tail->next;
    node *q = L2->tail->next;
    do {
        sum = p->digit + q->digit + carry;
        digit = sum % 10;
        carry = sum / 10;

        insert_start(ans, digit);
        p = p->next;
        q = q->next;
    } while (p != L1->tail->next && q != L2->tail->next);

    if (p != L1->tail->next) {
        left_over = p;
        tail_node = L1->tail;
    } else {
        left_over = q;
        tail_node = L2->tail;
    }

    while (left_over != tail_node->next) {
        sum = left_over->digit + carry;
        digit = sum % 10;
        carry = sum / 10;
        insert_start(ans, digit);
        left_over = left_over->next;
    }

    if (carry)
        insert_start(ans, carry);
}

void delete_circularll(CircularLL *LL) {
    node *next_node = NULL;
    node *current_node = LL->tail->next;
    while (current_node != LL->tail) {
        next_node = current_node->next;
        free(current_node);
        current_node = next_node;
    }
    free(current_node);
}