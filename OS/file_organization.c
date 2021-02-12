#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#define STRING_SIZE 512
#define MAX_FILE_COUNT 512

typedef struct File {
    char file_name[STRING_SIZE];
} File;

typedef struct SingleLevelTable {
    File *files[MAX_FILE_COUNT];
    int file_count;
} SingleLevelTable;

File *new_file(char *);
bool search_file(SingleLevelTable *, char *file);
void insert_file(SingleLevelTable *, char *file);
void display_files(SingleLevelTable *);
SingleLevelTable *create_slt();
void single_level();

int main() {
    printf("\t\tFile organization\n");
    printf("Maximum number of files supported is %d\n", MAX_FILE_COUNT);

    single_level();
    return 0;
}

File *new_file(char *file_name) {
    File *new_file = (File *) malloc(sizeof(File));
    strcpy(new_file->file_name, file_name);
    return new_file;
}

bool search_file(SingleLevelTable *slt, char *file) {
    for (int i = 0; i < slt->file_count; i++) {
        if (slt->files[i] != NULL && strcmp(slt->files[i]->file_name, file) == 0)
            return true;
    }
    return false;
}

void insert_file(SingleLevelTable *slt, char *file) {
    if (search_file(slt, file) == true) {
        printf("File %s already exists\n", file);
        return;
    }
    slt->files[slt->file_count] = new_file(file);
    slt->file_count++;
    printf("File created\n");
}

void display_files(SingleLevelTable *slt) {
    printf("Contents of root:\n");
    if (slt->file_count == 0) {
        printf("Empty!\n");
        return;
    }
    for (int i = 0; i < slt->file_count; i++) {
        if (slt->files[i] != NULL)
            printf("%s\t", slt->files[i]->file_name);
    }
    printf("\n");
}

SingleLevelTable *create_slt() {
    SingleLevelTable *slt = (SingleLevelTable *) malloc(sizeof(SingleLevelTable));
    slt->file_count = 0;
    for (int i = 0; i < MAX_FILE_COUNT; i++)
        slt->files[i] = NULL;
}

void single_level() {
    printf("Single-Level directory\n");
    int choice;
    char file[STRING_SIZE];
    SingleLevelTable *slt = create_slt();

    while (true) {
        printf("1: Create new file\n");
        printf("2: Display files\n");
        printf("-1: Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if (choice == 1) {
            printf("Enter file name: ");
            scanf("%s", file);
            insert_file(slt, file);
            display_files(slt);
        } else if (choice == 2)
            display_files(slt);
        else
            break;
        printf("\n");
    }
}

