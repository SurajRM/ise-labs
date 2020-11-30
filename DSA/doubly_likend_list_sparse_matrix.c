#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int row;
    int column;
    float data;
    struct node *previous;
    struct node *next;
} node;

typedef struct DoublyLL {
    node *head;
    node *tail;
} DoublyLL;

node *create_node(int, int, float);

void insert_node(DoublyLL *, int, int, float);

void input_matrix(DoublyLL *);

void view_matrix(DoublyLL *);

void delete_doublyll(DoublyLL *);

int main() {
    return 0;
}

node *create_node(int row, int column, float data) {
    node *new_node = (node *) malloc(sizeof(node));
    new_node->row = row;
    new_node->column = column;
    new_node->data = data;
    new_node->previous = NULL;
    new_node->next = NULL;
    return new_node;
}

void insert_node(DoublyLL *LL, int row, int column, float data) {
    node *new_node = create_node(row, column, data);
    if (LL->head == NULL) {
        LL->head = LL->tail = new_node;
        return;
    }
    LL->tail->next = new_node;
    new_node->previous = LL->tail;
    LL->tail = new_node;
}

