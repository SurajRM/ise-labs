#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int exponent;
    float coefficient;
    struct node *next;
} node;

typedef struct LinkedList {
    node *head;
} LinkedList;

void input_polynomials(LinkedList *, char *msg);
node *create_node(float, int);
void polynomial_add_node(LinkedList *, float, int);
void insert_descending(LinkedList *, float, int);
void polynomial_view(LinkedList *);
void multiply_polynomials(LinkedList *, LinkedList *, LinkedList *);
void delete_LinkedList(LinkedList *);

int main() {
    LinkedList L1 = {NULL}, L2 = {NULL}, ans = {NULL};
    printf("\t\tMultiplication of Two Polynomials\n");
    input_polynomials(&L1, "multiplicand");
    printf("\n");
    input_polynomials(&L2, "multiplier");

    multiply_polynomials(&ans, &L1, &L2);

    printf("\nPolynomial Expression 1: ");
    polynomial_view(&L1);
    printf("Polynomial Expression 2: ");
    polynomial_view(&L2);
    printf("Output: ");
    polynomial_view(&ans);

    delete_LinkedList(&L1);
    delete_LinkedList(&L2);
    delete_LinkedList(&ans);

    return 0;
}

void input_polynomials(LinkedList *LL, char *msg) {
    int count, exponent;
    float count2, coefficient, exponent2;
    printf("Enter the number of coefficients in the %s: ", msg);
    scanf("%f", &count2);
    count = (int) count2;

    if ((float) count != count2 || count2 < 0) {
        printf("Invalid input\n");
        exit(0);
    }
    if (count == 0) {
        printf("Output: 0\n");
        exit(0);
    }

    for (int i = 0; i < count; i++) {
        printf("Enter the coefficient part %d: ", i + 1);
        scanf("%f", &coefficient);
        label:
        printf("Enter the exponent part %d: ", i + 1);
        scanf("%f", &exponent2);
        exponent = (int) exponent2;
        if ((float) exponent != exponent2 || exponent2 < 0) {
            printf("error: Exponents can only be non negative integers\n");
            goto label;
        }
        insert_descending(LL, coefficient, exponent);
    }
}

node *create_node(float coefficient, int exponent) {
    node *ptr = (node *) malloc(sizeof(node));
    ptr->coefficient = coefficient;
    ptr->exponent = exponent;
    ptr->next = NULL;
    return ptr;
}

void insert_descending(LinkedList *LL, float coe, int exp) {
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

void polynomial_add_node(LinkedList *LL, float coe, int exp) {
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
}

void polynomial_view(LinkedList *LL) {
    node *ptr = LL->head;
    int flag = 0;
    while (ptr) {
        if (ptr->exponent != 0 && ptr->exponent != 1) {
            if (ptr->coefficient > 0 && flag == 0) {
                printf("%0.2fx^%d", ptr->coefficient, ptr->exponent);
                flag++;
            } else if (ptr->coefficient > 0 && flag == 1)
                printf(" + %0.2fx^%d", ptr->coefficient, ptr->exponent);
            else if (ptr->coefficient < 0 && flag == 0) {
                printf("%0.2fx^%d", ptr->coefficient, ptr->exponent);
                flag++;
            } else if (ptr->coefficient < 0 && flag == 1)
                printf(" - %0.2fx^%d", -ptr->coefficient, ptr->exponent);
        } else if (ptr->exponent == 0) {
            if (ptr->coefficient > 0 && flag == 0) {
                printf("%0.2f", ptr->coefficient);
                flag++;
            } else if (ptr->coefficient > 0 && flag == 1)
                printf(" + %0.2f", ptr->coefficient);
            else if (ptr->coefficient < 0 && flag == 0) {
                printf("%0.2f", ptr->coefficient);
                flag++;
            } else if (ptr->coefficient < 0 && flag == 1)
                printf(" - %0.2f", -ptr->coefficient);
        } else if (ptr->exponent == 1) {
            if (ptr->coefficient > 0 && flag == 0) {
                printf("%0.2fx", ptr->coefficient);
                flag++;
            } else if (ptr->coefficient > 0 && flag == 1)
                printf(" + %0.2fx", ptr->coefficient);
            else if (ptr->coefficient < 0 && flag == 0) {
                printf("%0.2fx", ptr->coefficient);
                flag++;
            } else if (ptr->coefficient < 0 && flag == 1)
                printf(" - %0.2fx", -ptr->coefficient);
        }
        ptr = ptr->next;
    }
    printf("\n");
}

void multiply_polynomials(LinkedList *ans, LinkedList *L1, LinkedList *L2) {
    node *p, *q;
    int exponent;
    float coefficient;

    p = L1->head;
    q = L2->head;

    if (!p && !q)
        return;

    if (!p)
        ans->head = L2->head;
    else if (!q)
        ans->head = L1->head;
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
}

void delete_LinkedList(LinkedList *LL) {
    node *next_node;
    node *current_node = LL->head;
    while (current_node) {
        next_node = current_node->next;
        free(current_node);
        current_node = next_node;
    }
}