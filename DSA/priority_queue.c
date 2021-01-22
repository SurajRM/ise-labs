#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct heap {
    int *arr;
    int size;
    int capacity;
} Heap;

Heap *create_heap(int);
bool insert(Heap *, int);
bool delete(Heap *, int);
int get_max(Heap *);
int pop_max(Heap *);
void print_queue(Heap *);
bool is_empty(Heap *);
bool is_full(Heap *);

int main() {
    return 0;
}

void print_queue(Heap *hp) {
    for (int i = 0; i < hp->size; i++) {
        printf("%d ", hp->arr[i]);
    }
}

int get_max(Heap *hp) {
    if (is_empty(hp)) {
        printf("error: queue empty\n");
        return -1;
    }
    return hp->arr[0];
}

bool is_empty(Heap *hp) {
    return hp->size == -1;
}

bool is_full(Heap *hp) {
    return hp->size == hp->capacity - 1;
}

Heap *create_heap(int capacity) {
    Heap *hp = (Heap *) malloc(sizeof(Heap));
    hp->arr = (int *) calloc(capacity, sizeof(int));
    hp->capacity = capacity;
    hp->size = -1;
    return hp;
}
