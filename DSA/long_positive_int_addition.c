#include <stdio.h>
#include <stdlib.h>


typedef struct node {
    int digit;
    struct node *next;
} node;


typedef struct CircularLL {
    node *head;
} CircularLL;


void input_long_int(CircularLL *, char msg[]);
node *create_node(int);
void insert_end(CircularLL *, int);
void insert_start(CircularLL *, int);
void long_int_view(CircularLL *);
void add_long_int(CircularLL *, CircularLL *, CircularLL *);
void delete_CircularLL(CircularLL *);

int main() {
    return 0;
}