#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int coefficient, exponent;
    struct node *next;
} node;

typedef struct LinkedList {
    node *head;
} LinkedList;

void input_polynomials(LinkedList *, char msg[]);
node *create_node(int, int);
void polynomial_add_node(LinkedList *, int, int);
void insert_descending(LinkedList *, int, int);
void polynomial_view(LinkedList *);
void multiply_polynomials(LinkedList *, LinkedList *, LinkedList *);
void delete_LinkedList(LinkedList *);

int main() {
    LinkedList L1 = {NULL}, L2 = {NULL}, ans = {NULL};
    printf("            Multiplication of Two Polynomials\n");
    input_polynomials(&L1, "multiplicand");
    printf("\n");
    input_polynomials(&L2, "multiplier");
    printf("\nPolynomial Expression 1: ");
    polynomial_view(&L1);
    printf("Polynomial Expression 2: ");
    polynomial_view(&L2);

    multiply_polynomials(&ans, &L1, &L2);
    printf("Output: ");
    polynomial_view(&ans);

    delete_LinkedList(&L1);
    delete_LinkedList(&L2);
    delete_LinkedList(&ans);

    return 0;
}

void input_polynomials(LinkedList *LL, char msg[]) {
    int count, coefficient, exponent;
    printf("Enter the number of coefficients in the %s: ", msg);
    scanf("%d", &count);
    for (int i = 0; i < count; i++) {
        printf("Enter the coefficient part %d: ", i + 1);
        scanf("%d", &coefficient);
        printf("Enter the exponent part %d: ", i + 1);
        scanf("%d", &exponent);
        insert_descending(LL, coefficient, exponent);
    }
}

node *create_node(int coefficient, int exponent) {
    node *ptr = (node *)malloc(sizeof(node));
    ptr->coefficient = coefficient;
    ptr->exponent = exponent;
    ptr->next = NULL;
    return ptr;
}

void insert_descending(LinkedList *LL, int coe, int exp) {
    node *new_node = create_node(coe, exp);
    node *temp = LL->head;
    if (LL->head == NULL || LL->head->exponent < exp) {
        new_node->next = LL->head;
        LL->head = new_node;
        return;
    }
    while (temp->next) {
        if (temp->exponent > exp && (!temp->next || temp->next->exponent < exp)) {
            new_node->next = temp->next;
            temp->next = new_node;
            return;
        }
        temp = temp->next;
    }
    temp->next = new_node;
}

void polynomial_add_node(LinkedList *LL, int coe, int exp) {
    node *new_node = create_node(coe, exp);
    node *temp = LL->head;
    if (LL->head == NULL || LL->head->exponent < exp) {
        new_node->next = LL->head;
        LL->head = new_node;
        return;
    }
    while (temp) {
        if (temp->exponent == exp) {
            temp->coefficient += coe;
            free(new_node);
            return;
        }
        if (temp->exponent > exp && (!temp->next || (temp->next)->exponent < exp)) {
            new_node->next = temp->next;
            temp->next = new_node;
            return;
        }
        temp = temp->next;
    }
    temp->next = new_node;
}

void polynomial_view(LinkedList *LL) {
    node *ptr = LL->head;
    int i = 0;
    int flag = 0;
    while (ptr) {
        if (ptr->exponent != 0 && ptr->exponent != 1) {
            if (ptr->coefficient > 0 && flag == 0) {
                printf("%dx^%d", ptr->coefficient, ptr->exponent);
                flag++;
            } else if (ptr->coefficient > 0 && flag == 1)
                printf(" + %dx^%d", ptr->coefficient, ptr->exponent);
            else if (ptr->coefficient < 0 && flag == 0) {
                printf("%dx^%d", ptr->coefficient, ptr->exponent);
                flag++;
            } else if (ptr->coefficient < 0 && flag == 1)
                printf(" - %dx^%d", -ptr->coefficient, ptr->exponent);
        } else if (ptr->exponent == 0) {
            if (ptr->coefficient > 0 && flag == 0) {
                printf("%d", ptr->coefficient);
                flag++;
            } else if (ptr->coefficient > 0 && flag == 1)
                printf(" + %d", ptr->coefficient);
            else if (ptr->coefficient < 0 && flag == 0) {
                printf("%d", ptr->coefficient);
                flag++;
            } else if (ptr->coefficient < 0 && flag == 1)
                printf(" - %d", -ptr->coefficient);
        } else if (ptr->exponent == 1) {
            if (ptr->coefficient > 0 && flag == 0) {
                printf("%dx", ptr->coefficient);
                flag++;
            } else if (ptr->coefficient > 0 && flag == 1)
                printf(" + %dx", ptr->coefficient);
            else if (ptr->coefficient < 0 && flag == 0) {
                printf("%dx", ptr->coefficient);
                flag++;
            } else if (ptr->coefficient < 0 && flag == 1)
                printf(" - %dx", -ptr->coefficient);
        }
        ptr = ptr->next;
        i++;
    }
    printf("\n");
    return;
}

void multiply_polynomials(LinkedList *ans, LinkedList *L1, LinkedList *L2) {
    node *p, *q;
    int coefficient, exponent;

    p = L1->head;
    q = L2->head;

    if (!p && !q)
        return;

    if (!p)
        ans->head = q;
    else if (!q)
        ans->head = p;
    else {
        while (p) {
            while (q) {
                coefficient = p->coefficient * q->coefficient;
                exponent = p->exponent + q->exponent;
                q = q->next;
                polynomial_add_node(ans, coefficient, exponent);
            }
            q = L2->head;
            p = p->next;
        }
    }
    return;
}

void delete_LinkedList(LinkedList *LL) {
    node *temp;
    node *ptr = LL->head;
    while (ptr) {
        temp = ptr->next;
        free(ptr);
        ptr = temp;
    }
}