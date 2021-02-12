#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#define STRING_SIZE 255
#define MAX_FILE_COUNT 255
#define MAX_DIR_COUNT 255

#define BOLD_BLUE "\033[1m\033[34m"
#define BOLD_CYAN "\033[1m\033[36m"
#define RESET "\033[0m"

typedef struct File {
    char file_name[STRING_SIZE];
} File;

typedef struct directory {
    char dir_name[STRING_SIZE];
    File *files[MAX_FILE_COUNT];
    struct directory *directories[MAX_DIR_COUNT];
    int file_count;
    int dir_count;
} Directory;

File *new_file(char *);
Directory *new_directory(char *);
bool search_file(Directory *, char *);
bool search_directory(Directory *, char *);
Directory *get_directory(Directory *, char *);
void insert_file(Directory *, char *);
void insert_directory(Directory *, char *);
void display_contents(Directory *);
void single_level();
void two_level();

int main() {
    printf("\t\tFile organization\n");
    printf("Maximum number of files supported is %d\n", MAX_FILE_COUNT);

//    single_level();
    two_level();
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
    dir->files[dir->file_count++] = new_file(file);
    printf("File created\n");
}

void display_contents(Directory *dir) {
    printf("Contents of " BOLD_BLUE "%s:\n" RESET, dir->dir_name);
    if (dir->dir_count == 0 && dir->file_count == 0) {
        printf("Directory empty\n");
        return;
    }

    for (int i = 0; i < dir->dir_count; i++) {
        if (dir->directories[i] != NULL)
            printf(BOLD_BLUE "%s\t" RESET, dir->directories[i]->dir_name);
    }

    for (int i = 0; i < dir->file_count; i++) {
        if (dir->files[i] != NULL)
            printf(BOLD_CYAN "%s\t" RESET, dir->files[i]->file_name);
    }
    printf("\n");
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

bool search_directory(Directory *dir, char *dir_name) {
    for (int i = 0; i < dir->dir_count; i++) {
        if (dir->directories[i] != NULL && strcmp(dir->directories[i]->dir_name, dir_name) == 0)
            return true;
    }
    return false;
}

void insert_directory(Directory *dir, char *dir_name) {
    if (search_directory(dir, dir_name) == true) {
        printf("Directory " BOLD_BLUE "\"%s\"" RESET "already exists\n", dir_name);
        return;
    }
    dir->directories[dir->dir_count++] = new_directory(dir_name);
    printf("Directory created\n");
}

Directory *get_directory(Directory *dir, char *dir_name) {
    for (int i = 0; i < dir->dir_count; i++) {
        if (dir->directories[i] != NULL && strcmp(dir->directories[i]->dir_name, dir_name) == 0)
            return dir->directories[i];
    }
    return NULL;
}

void single_level() {
    printf("Single-Level directory\n");
    int choice;
    char file_name[STRING_SIZE];
    Directory *root = new_directory("root");
    printf("root directory created\n");

    while (true) {
        printf("1: Create new file\n");
        printf("2: Display files\n");
        printf("-1: Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter file name: ");
                scanf("%s", file_name);
                insert_file(root, file_name);
                break;
            case 2:
                display_contents(root);
                break;
            case -1:
                return;
            default:
                printf("Invalid choice\n");
        }
        printf("\n");
    }
}

void two_level() {
    printf("Two-level directory\n");
    int choice, level = 1;
    char file_name[STRING_SIZE];
    char dir_name[STRING_SIZE];
    Directory *root = new_directory("root");
    Directory *current_dir = root;
    printf("root directory created\n");

    while (true) {
        printf("1: Enter a directory\n");
        printf("2: Create new file\n");
        printf("3: Create new directory\n");
        printf("4: Display contents\n");
        printf("-1: Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the name of the directory: ");
                scanf("%s", dir_name);

                if (strcmp("root", dir_name) == 0) {
                    current_dir = root;
                    level = 1;
                } else if (search_directory(root, dir_name)) {
                    current_dir = get_directory(root, dir_name);
                    level = 2;
                } else {
                    printf("Directory not found\n");
                    break;
                }

                printf("Entered " BOLD_BLUE "%s\n" RESET, dir_name);
                break;

            case 2:
                printf("Enter file name: ");
                scanf("%s", file_name);
                insert_file(current_dir, file_name);
                break;

            case 3:
                if (level < 2) {
                    printf("Enter directory name: ");
                    scanf("%s", dir_name);
                    insert_directory(current_dir, dir_name);
                } else
                    printf("Unable to create directory\n");
                break;

            case 4:
                display_contents(current_dir);
                break;

            case -1:
                return;

            default:
                printf("Invalid choice\n");
        }
        printf("\n");
    }
}

