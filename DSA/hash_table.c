#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define STRING_SIZE 128

typedef struct item {
    int key;
    char string[STRING_SIZE];
} item;

typedef struct hash_table {
    item **arr;
    int capacity;
} hash_table;

hash_table *create_hash_table(int);

item *create_item(int, char string[]);

int hash(int, int);

void insert(hash_table *, int, char string[]);

bool search(hash_table *, int);

item delete(hash_table *, int);

void display(hash_table *);

item dummy_item = {-1, "\0"};

int main() {
    return 0;
}

hash_table *create_hash_table(int capacity) {
    hash_table *ht = (hash_table *) malloc(sizeof(hash_table));
    ht->capacity = capacity;
    ht->arr = (item **) malloc(capacity * sizeof(item *));
    for (int i = 0; i < ht->capacity; i++)
        ht->arr[i] = NULL;
    return ht;
}

void display(hash_table *ht) {
    bool empty = true;
    for (int i = 0; i < ht->capacity; i++) {
        if (ht->arr[i] && ht->arr[i]->key != -1) {
            empty = false;
            printf("%d: %s\n", ht->arr[i]->key, ht->arr[i]->string);
        }
    }
    if (empty)
        printf("Hash table is empty\n");
}

int hash(int key, int size) {
    if (key < 0) {
        printf("\033[1;31merror: Key unhashable\033[0m\n");
        return -1;
    }
    return (key % size);
}

void insert(hash_table *ht, int key, char string[STRING_SIZE]) {
    int index = hash(key, ht->capacity);
    int i = index;

    while (ht->arr[i]) {
        if (ht->arr[i]->key == key) {
            strcpy(ht->arr[i]->string, string);
            return;
        }
        i = (i + 1) % ht->capacity;
        if (i == index) {
            printf("\033[1;31merror: Hash Table is full\033[0m\n");
            return;
        }
    }

    ht->arr[i] = create_item(key, string);
}

item *create_item(int key, char string[STRING_SIZE]) {
    item *new_item = (item *) malloc(sizeof(item));
    new_item->key = key;
    strcpy(new_item->string, string);
    return new_item;
}

item delete(hash_table *ht, int key) {
    int index = hash(key, ht->capacity);
    int i = index;
    item result = dummy_item;

    while (ht->arr[i]) {
        if (ht->arr[i]->key == key) {
            result = *(ht->arr[i]);
            free(ht->arr[i]);
            ht->arr[i] = &dummy_item;
            return result;
        }
        i = (i + 1) % ht->capacity;
        if (i == index)
            break;
    }

    printf("\033[1;31merror: Key not found\033[0m\n");
    return result;
}

bool search(hash_table *ht, int key) {
    int index = hash(key, ht->capacity);
    int i = index;

    while (ht->arr[i]) {
        if (ht->arr[i]->key == key) {
            printf("%d: %s\n", ht->arr[i]->key, ht->arr[i]->string);
            return true;
        }
        i = (i + 1) % ht->capacity;
        if (i == index)
            break;
    }

    printf("\033[1;31merror: Key not found\033[0m\n");
    return false;
}
