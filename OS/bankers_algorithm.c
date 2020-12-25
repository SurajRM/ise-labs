#include <stdio.h>
#include <stdlib.h>

int **input_allocation_matrix(int, int);

int **input_max_matrix(int, int);

int *input_available_vector(int);

bool is_safe(int **, int **, int *, int *, int *);

int main() {
    int process_count, resource_count;
    int **allocation, **max, *available;

    printf("\t\tDeadlock avoidance using Banker's Algorithm.\n");
    printf("Enter the number of processes: ");
    scanf("%d", &process_count);
    printf("Enter the number of resource: ");
    scanf("%d", &resource_count);
    available = input_available_vector(resource_count);
    max = input_max_matrix(process_count, resource_count);
    allocation = input_max_matrix(process_count, resource_count);

    return 0;
}

int *input_available_vector(int resource_count) {
    int *available_vector = (int *) malloc(resource_count * sizeof(int));
    for (int i = 0; i < resource_count; i++) {
        printf("Enter the number of available instances for resource %d", i + 1);
        scanf("%d", &available_vector[i]);
    }

    return available_vector;
}

int **input_allocation_matrix(int process_count, int resource_count) {
    int **allocation = (int **) malloc(process_count * sizeof(int *));
    for (int i = 0; i < process_count; i++) {
        printf("\nProcess %d:\n", i + 1);
        allocation[i] = (int *) malloc(resource_count * sizeof(int));
        for (int j = 0; j < resource_count; j++) {
            printf("Allocation for resource: %d", j + 1);
            scanf("%d", &allocation[i][j]);
        }
    }

    return allocation;
}

int **input_max_matrix(int process_count, int resource_count) {
    int **max = (int **) malloc(process_count * sizeof(int *));
    for (int i = 0; i < process_count; i++) {
        printf("\nProcess %d:\n", i + 1);
        max[i] = (int *) malloc(resource_count * sizeof(int *));
        for (int j = 0; j < resource_count; j++) {
            printf("Maximum demand for resource: %d", j + 1);
            scanf("%d", &max[i][j]);
        }
    }

    return max;
}
