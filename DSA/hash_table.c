#include <stdlib.h>
#include <stdio.h>

typedef struct hash_table {
    int *arr;
    int capacity;
} hash_table;

hash_table *create_hash_table(int);

void display(hash_table *);

int main() {
    return 0;
}

hash_table *create_hash_table(int capacity) {
    hash_table *ht = (hash_table *) malloc(sizeof(hash_table));
    ht->capacity = capacity;
    ht->arr = (int *) malloc(capacity * sizeof(int));
    for (int i = 0; i < ht->capacity; i++)
        ht->arr[i] = -1;
    return ht;
}

void display(hash_table *ht) {
    for (int i = 0; i < ht->capacity; i++)
        printf("%d ", ht->arr[i]);
}
