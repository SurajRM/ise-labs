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
int parent(int);
int left_child(int);
int right_child(int);
void shift_up(Heap *, int);
void shift_down(Heap *, int);
bool delete(Heap *, int);
int get_max(Heap *);
int pop_max(Heap *);
void print_queue(Heap *);
bool is_empty(Heap *);
bool is_full(Heap *);
void swap(int *, int *);

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

bool insert(Heap *hp, int value) {
    if (is_full(hp)) {
        printf("error: heap full\n");
        return false;
    }
    hp->arr[++(hp->size)] = value;
    shift_up(hp, hp->size);
    return true;
}

int pop_max(Heap *hp) {
    int max = hp->arr[0];
    hp->arr[0] = hp->arr[hp->size--];
    shift_down(hp, 0);
    return max;
}

bool delete(Heap *hp, int position) {
    if (is_empty(hp)) {
        printf("error: heap empty\n");
        return false;
    }
    hp->arr[position] = get_max(hp) + 1;
    shift_up(hp, position);
    pop_max(hp);
    return true;
}

void shift_up(Heap *hp, int pos) {
    while (pos > 0 && hp->arr[parent(pos)] < hp->arr[pos]) {
        swap(&hp->arr[parent(pos)], &hp->arr[pos]);
        pos = parent(pos);
    }
}

void shift_down(Heap *hp, int pos) {
    int max_index = pos;

    int left_index = left_child(pos);
    if (left_index <= hp->size && hp->arr[left_index] > hp->arr[max_index])
        max_index = left_index;

    int right_index = right_child(pos);
    if (right_index <= hp->size && hp->arr[right_index] > hp->arr[max_index])
        max_index = right_index;

    if (pos != max_index) {
        swap(&hp->arr[pos], &hp->arr[max_index]);
        shift_down(hp, max_index);
    }
}

void swap(int *a, int *b) {
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}

int parent(int i) {
    return (i - 1) / 2;
}

int left_child(int i) {
    return 2 * i + 1;
}

int right_child(int i) {
    return 2 * i + 2;
}
