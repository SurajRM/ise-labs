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

bool insert(hash_table *, int, char string[]);

bool search(hash_table *, int);

item delete(hash_table *, int);

void display(hash_table *);

void print_item(item *);

item dummy_item = {-1, "\0"};

int main() {
    int size, choice, key;
    char value[STRING_SIZE];
    printf("\t\t\033[1;34mHash table with linear probing\033[0m\n");
    printf("Enter the size of the hash table: ");
    scanf("%d", &size);
    if (size <= 0) {
        printf("\033[1;31merror: size can only be positive integers\033[0m\n");
        exit(0);
    }
    hash_table *ht = create_hash_table(size);

    while (true) {
        printf("1: Insert\n2: Delete\n3: Search\n4: Display\n-1: Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the key: ");
                scanf("%d", &key);
                getchar();
                printf("Enter the value: ");
                scanf("%[^\n]s", value);
                insert(ht, key, value);
                break;
            case 2:
                printf("Enter the key: ");
                scanf("%d", &key);
                delete(ht, key);
                break;
            case 3:
                printf("Enter the key: ");
                scanf("%d", &key);
                search(ht, key);
                break;
            case 4:
                display(ht);
                break;
            case -1:
                exit(0);
            default:
                printf("\033[1;31merror: invalid option\033[0m\n");
        }
        printf("---------------------------\n");
    }
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
            print_item(ht->arr[i]);
        }
    }
    if (empty)
        printf("Hash table is empty\n");
}

int hash(int key, int size) {
    if (key < 0) {
        printf("\033[1;31merror: Key unhashable\033[0m\n");
        exit(0);
    }
    return (key % size);
}

bool insert(hash_table *ht, int key, char string[STRING_SIZE]) {
    int index = hash(key, ht->capacity);
    int i = index;

    while (ht->arr[i]) {
        if (ht->arr[i]->key == key || ht->arr[i]->key == -1) {
            if (ht->arr[i]->key == key)
                free(ht->arr[i]);
            ht->arr[i] = create_item(key, string);
            return true;
        }
        i = (i + 1) % ht->capacity;
        if (i == index) {
            printf("\033[1;31merror: Hash Table is full\033[0m\n");
            return false;
        }
    }
    ht->arr[i] = create_item(key, string);
    return true;
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
            print_item(ht->arr[i]);
            return true;
        }
        i = (i + 1) % ht->capacity;
        if (i == index)
            break;
    }

    printf("\033[1;31merror: Key not found\033[0m\n");
    return false;
}

void print_item(item *p) {
    printf("\033[1;32m%d: %s\033[0m\n", p->key, p->string);
}
