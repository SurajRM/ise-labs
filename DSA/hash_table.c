#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define STRING_SIZE 512
#define BOLD_RED "\e[1;31m"
#define RESET "\e[0m"

typedef struct item {
    int key;
    char string[STRING_SIZE];
} item;

typedef struct hash_table {
    item **arr;
    int capacity;
} hash_table;

item dummy_item = {-1, "\0"};

hash_table *create_hash_table(int);
item *create_item(int, char *);
int hash(int, int);
bool insert(hash_table *, int, char *);
bool search(hash_table *, int);
item delete(hash_table *, int);
void display(hash_table *);
void print_item(item *);

int main() {
    int size, choice, key;
    char value[STRING_SIZE];

    printf("\t\tHash table with linear probing\n");
    printf("Enter the size of the hash table: ");
    scanf("%d", &size);
    if (size <= 0) {
        printf(BOLD_RED "error:" RESET " size can only be positive integers\n");
        exit(1);
    }
    hash_table *ht = create_hash_table(size);

    while (true) {
        printf("1: Insert\n");
        printf("2: Delete\n");
        printf("3: Search\n");
        printf("4: Display\n");
        printf("-1: Exit\n");
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
                printf(BOLD_RED "error:" RESET " invalid option\n");
        }
        printf("\n");
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
        printf(BOLD_RED "error:" RESET " key unhashable\n");
        exit(1);
    }
    return (key % size);
}

bool insert(hash_table *ht, int key, char *string) {
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
            printf(BOLD_RED "error:" RESET " hash table is full\n");
            return false;
        }
    }
    ht->arr[i] = create_item(key, string);
    return true;
}

item *create_item(int key, char *string) {
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

    printf(BOLD_RED "error:" RESET " Key not found\n");
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

    printf(BOLD_RED "error:" RESET " Key not found\n");
    return false;
}

void print_item(item *p) {
    printf("%d: %s\n", p->key, p->string);
}
