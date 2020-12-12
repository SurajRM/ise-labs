#include <stdio.h>
#include <stdlib.h>

void input_allocation_vector(int *, const int *);

void input_max_vector(int *, const int *);

void input_available_vector(int *, const int *);

void input_data(int **, int **, int *, int *, int *);

int main() {
    int process_count, resource_count;
    int **allocation = NULL, **max = NULL, *available = NULL;
    printf("\t\tDeadlock avoidance using Banker's Algorithm.\n");
    input_data(allocation, max, available, &process_count, &resource_count);
    return 0;
}

void input_allocation_vector(int *allocation_vector, const int *resource_count) {
    for (int i = 0; i < *resource_count; i++) {
        printf("Allocation for resource: %d", i + 1);
        scanf("%d", &allocation_vector[i]);
    }
}

void input_max_vector(int *max_vector, const int *resource_count) {
    for (int i = 0; i < *resource_count; i++) {
        printf("Maximum demand for resource: %d", i + 1);
        scanf("%d", &max_vector[i]);
    }
}

void input_available_vector(int *available_vector, const int *resource_count) {
    for (int i = 0; i < *resource_count; i++) {
        printf("Enter the number of available instances for resource %d", i + 1);
        scanf("%d", &available_vector[i]);
    }
}

void input_data(int **allocation, int **max, int *available, int *process_count, int *resource_count) {
    printf("Enter the number of processes: ");
    scanf("%d", process_count);
    printf("Enter the number of resource: ");
    scanf("%d", resource_count);

    allocation = (int **) malloc(*process_count * sizeof(int *));
    max = (int **) malloc(*process_count * sizeof(int *));
    for (int i = 0; i < *process_count; i++) {
        allocation[i] = (int *) malloc(*resource_count * sizeof(int));
        printf("\nProcess %d:\n", i + 1);
        input_allocation_vector(allocation[i], resource_count);
        input_max_vector(max[i], resource_count);
    }
    input_available_vector(available, resource_count);
}
