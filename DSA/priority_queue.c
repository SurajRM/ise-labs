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
    int capacity, choice, temp;

    printf("\t\tPriority queue using heaps\n");
    printf("Enter the size of the queue: ");
    scanf("%d", &capacity);
    if (capacity <= 0) {
        printf("error: capacity is not positive integer\n");
        return 0;
    }

    Heap *hp = create_heap(capacity);

    while (true) {
        printf("\n1: Insert\n2: Delete\n3: Display queue\n4: Pop max\n5: Display max\n-1: Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter an integer: ");
                scanf("%d", &temp);
                insert(hp, temp);
                print_queue(hp);
                break;
            case 2:
                printf("Enter the index of the element to be deleted: ");
                scanf("%d", &temp);
                delete(hp, temp);
                print_queue(hp);
                break;
            case 3:
                print_queue(hp);
                break;
            case 4:
                temp = pop_max(hp);
                if (temp != -1)
                    printf("Max: %d\n", temp);
                break;
            case 5:
                temp = get_max(hp);
                if (temp != -1)
                    printf("Max: %d\n", temp);
                break;
            case -1:
                exit(0);
            default:
                printf("error: invalid choice\n");
        }
    }
}

void print_queue(Heap *hp) {
    if (is_empty(hp)) {
        printf("Queue empty\n");
        return;
    }
    printf("Queue: ");
    for (int i = 0; i <= hp->size; i++) {
        printf("%d ", hp->arr[i]);
    }
    printf("\n");
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
        printf("insertion failed: heap full\n");
        return false;
    }
    hp->arr[++(hp->size)] = value;
    shift_up(hp, hp->size);
    return true;
}

int pop_max(Heap *hp) {
    if (is_empty(hp)) {
        printf("error: queue empty\n");
        return -1;
    }
    int max = hp->arr[0];
    hp->arr[0] = hp->arr[hp->size--];
    shift_down(hp, 0);
    return max;
}

bool delete(Heap *hp, int index) {
    if (is_empty(hp)) {
        printf("deletion failed: heap empty\n");
        return false;
    }
    if (index < 0 || index > hp->size) {
        printf("deletion failed: index out of range\n");
        return false;
    }
    hp->arr[index] = get_max(hp) + 1;
    shift_up(hp, index);
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
