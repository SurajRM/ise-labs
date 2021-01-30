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
    printf("\t\tSparse matrix using doubly linked list\n");
    DoublyLL sparse_matrix = {NULL, NULL};

    input_matrix(&sparse_matrix);
    printf("Matrix:\n");
    view_matrix(&sparse_matrix);

    delete_doublyll(&sparse_matrix);
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
    LL->head->data += 1;
}

void input_matrix(DoublyLL *LL) {
    int row, column;
    float data;
    char buffer[1024];
    char *ptr;
    printf("Enter the order of the matrix: ");
    scanf("%u %u", &row, &column);
    getchar();
    if (row <= 0 || column <= 0) {
        printf("Invalid input\n");
        exit(0);
    }
    insert_node(LL, row, column, 0);
    for (int i = 0; i < row; i++) {
        printf("Enter the elements in the row %d: ", i + 1);
        fgets(buffer, 1023, stdin);
        data = strtof(buffer, &ptr);
        for (int j = 0; j < column; j++) {
            if (data != 0)
                insert_node(LL, i, j, data);
            data = strtof(ptr, &ptr);
        }
    }
}

void view_matrix(DoublyLL *LL) {
    node *temp = LL->head->next;
    int row = LL->head->row;
    int column = LL->head->column;
    printf("[");
    for (int i = 0; i < row; i++) {
        printf("[");
        for (int j = 0; j < column; j++) {
            if (temp != NULL && (temp->row == i && temp->column == j)) {
                printf("%0.2f", temp->data);
                temp = temp->next;
            } else
                printf("0");

            if (j < column - 1)
                printf(", ");
        }
        if (i < row - 1)
            printf("],\n ");
    }
    printf("]]");
}

void delete_doublyll(DoublyLL *LL) {
    node *temp = LL->head->next;
    while (temp) {
        free(temp->previous);
        temp = temp->next;
    }
}