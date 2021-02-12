#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <limits.h>

#define STRING_SIZE 255
#define MAX_FILE_COUNT 255
#define MAX_DIR_COUNT 255

#define BOLD_BLUE "\e[1;34m"
#define BOLD_PURPLE "\e[1;35m"
#define RESET "\033[0m"

typedef struct File {
    char file_name[STRING_SIZE];
} File;

typedef struct directory {
    char dir_name[STRING_SIZE];
    File *files[MAX_FILE_COUNT];
    struct directory *directories[MAX_DIR_COUNT];
    struct directory *parent;
    int file_count;
    int dir_count;
} Directory;

File *new_file(char *);
Directory *new_directory(char *, Directory *);
bool search_file(Directory *, char *);
bool search_directory(Directory *, char *);
Directory *get_directory(Directory *, char *);
void insert_file(Directory *, char *);
void insert_directory(Directory *, char *);
void display_contents(Directory *);
void display_all_contents(Directory *, int);
void n_level();

int main() {
    printf("\t\tFile organization\n");
    printf("Maximum number of files supported is %d\n", MAX_FILE_COUNT);

    n_level();
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
            printf(BOLD_BLUE "%s  " RESET, dir->directories[i]->dir_name);
    }

    for (int i = 0; i < dir->file_count; i++) {
        if (dir->files[i] != NULL)
            printf(BOLD_PURPLE "%s  " RESET, dir->files[i]->file_name);
    }
    printf("\n");
}

void display_all_contents(Directory *dir, int level) {
    printf(BOLD_BLUE "%s/\n" RESET, dir->dir_name);
    level++;
    for (int i = 0; i < dir->dir_count; i++) {
        if (dir->directories[i] != NULL) {
            for (int j = 0; j < level; j++)
                printf("  ");
            display_all_contents(dir->directories[i], level);
        }
    }
    for (int i = 0; i < dir->file_count; i++) {
        if (dir->files[i] != NULL) {
            for (int j = 0; j < level; j++)
                printf("  ");
            printf(BOLD_PURPLE "%s\n" RESET, dir->files[i]->file_name);
        }
    }
}

Directory *new_directory(char *dir_name, Directory *parent) {
    Directory *new_dir = (Directory *) malloc(sizeof(Directory));
    strcpy(new_dir->dir_name, dir_name);
    new_dir->parent = parent;
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
    dir->directories[dir->dir_count++] = new_directory(dir_name, dir);
    printf("Directory created\n");
}

Directory *get_directory(Directory *dir, char *dir_name) {
    for (int i = 0; i < dir->dir_count; i++) {
        if (dir->directories[i] != NULL && strcmp(dir->directories[i]->dir_name, dir_name) == 0)
            return dir->directories[i];
    }
    return NULL;
}

void n_level() {
    printf("N-level directory\n");
    int level = INT_MAX, current_level = 1, choice, temp;
    char file_name[STRING_SIZE];
    char dir_name[STRING_SIZE];
    printf("Enter the value of level (-1 for limitless level): ");
    scanf("%d", &temp);
    if (temp != -1)
        level = temp;

    if (level <= 0) {
        printf("Invalid input\n");
        return;
    }

    Directory *root = new_directory("root", NULL);
    Directory *current_dir = root;
    printf(BOLD_BLUE "root" RESET " directory created\n");

    while (true) {
        printf("1: Create new file\n");
        printf("2: Display contents in the directory\n");
        printf("3: Display all the contents\n");
        printf("4: Display current working directory\n");
        if (current_level < level) {
            printf("5: Create new directory\n");
            printf("6: Enter a directory\n");
        }
        printf("-1: Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter file name: ");
                scanf("%s", file_name);
                insert_file(current_dir, file_name);
                break;

            case 2:
                display_contents(current_dir);
                break;

            case 3:
                display_all_contents(root, 0);
                break;

            case 4:
                printf(BOLD_BLUE "%s\n" RESET, current_dir->dir_name);
                break;

            case 5:
                if (current_level < level) {
                    printf("Enter directory name: ");
                    scanf("%s", dir_name);
                    insert_directory(current_dir, dir_name);
                } else
                    printf("Invalid choice\n");
                break;

            case 6:
                if (current_level < level) {
                    printf("Enter " BOLD_BLUE "\"..\"" RESET " to go to the parent directory");
                    printf("and " BOLD_BLUE "\"root\"" RESET " for the root directory\n");
                    printf("Enter the name of the directory: ");
                    scanf("%s", dir_name);

                    if (strcmp("root", dir_name) == 0) {
                        current_dir = root;
                        current_level = 0;
                    } else if (strcmp("..", dir_name) == 0 && current_dir != root) {
                        current_dir = current_dir->parent;
                        current_level--;
                    } else if (search_directory(current_dir, dir_name)) {
                        current_dir = get_directory(current_dir, dir_name);
                        current_level++;
                    } else {
                        printf("Directory not found\n");
                        break;
                    }
                    printf("Entered " BOLD_BLUE "%s\n" RESET, current_dir->dir_name);
                } else
                    printf("Invalid choice\n");
                break;

            case -1:
                return;

            default:
                printf("Invalid choice\n");
        }
        printf("\n");
    }
}