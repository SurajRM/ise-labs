#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#define STRING_SIZE 255
#define MAX_FILE_COUNT 255
#define MAX_DIR_COUNT 255

typedef struct File {
    char file_name[STRING_SIZE];
} File;

typedef struct directory {
    char dir_name[STRING_SIZE];
    File *files[MAX_FILE_COUNT];
    struct Directory *directories[MAX_DIR_COUNT];
    int file_count;
    int dir_count;
} Directory;

File *new_file(char *);
Directory *new_directory(char *);
bool search_file(Directory *, char *file);
void insert_file(Directory *, char *file);
void display_files(Directory *);
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

bool search_file(Directory *dir, char *file) {
    for (int i = 0; i < dir->file_count; i++) {
        if (dir->files[i] != NULL && strcmp(dir->files[i]->file_name, file) == 0)
            return true;
    }
    return false;
}

void insert_file(Directory *dir, char *file) {
    if (search_file(dir, file) == true) {
        printf("File \"%s\" already exists\n", file);
        return;
    }
    dir->files[dir->file_count] = new_file(file);
    dir->file_count++;
    printf("File created\n");
}

void display_files(Directory *dir) {
    printf("Contents of root:\n");
    if (dir->file_count == 0) {
        printf("Empty!\n");
        return;
    }
    for (int i = 0; i < dir->file_count; i++) {
        if (dir->files[i] != NULL)
            printf("%s\t", dir->files[i]->file_name);
    }
    printf("\n");
}

void single_level() {
    printf("Single-Level directory\n");
    int choice;
    char file[STRING_SIZE];
    Directory *root = new_directory("root");

    while (true) {
        printf("1: Create new file\n");
        printf("2: Display files\n");
        printf("-1: Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if (choice == 1) {
            printf("Enter file name: ");
            scanf("%s", file);
            insert_file(root, file);
            display_files(root);
        } else if (choice == 2)
            display_files(root);
        else
            break;
        printf("\n");
    }
}

Directory *new_directory(char *dir_name) {
    Directory *new_dir = (Directory *) malloc(sizeof(Directory));
    strcpy(new_dir->dir_name, dir_name);
    new_dir->dir_count = 0;
    new_dir->file_count = 0;
    for (int i = 0; i < MAX_FILE_COUNT; i++)
        new_dir->files[i] = NULL;
    for (int i = 0; i < MAX_DIR_COUNT; i++)
        new_dir->directories[i] = NULL;

    return new_dir;
}

