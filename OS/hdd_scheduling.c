#include <stdlib.h>
#include <stdio.h>

typedef struct io_requests {
    int *queue;
    int len;
    int max_cylinder_count;
} IORequests;

IORequests *get_data();
void fcfs(IORequests *);
void scan(IORequests *);
void cscan(IORequests *);

int main() {
    printf("\t\tHDD scheduling\n");
    IORequests *data = get_data();

    fcfs(data);
    scan(data);
    cscan(data);
}

IORequests *get_data() {
    IORequests *data = (IORequests *) malloc(sizeof(IORequests));

    printf("Enter the maximum number of cylinders: ");
    scanf("%d", &data->max_cylinder_count);

    printf("Enter the number of requests: ");
    scanf("%d", &data->len);
    data->len++;

    data->queue = (int *) malloc(data->len * sizeof(int));
    printf("Enter the position of the head: ");
    scanf("%d", &data->queue[0]);

    printf("Enter the elements of the queue: ");
    for (int i = 1; i < data->len; i++)
        scanf("%d", &data->queue[i]);

    return data;
}

void fcfs(IORequests *data) {
    int seek_time = 0;
    printf("\nFirst come first serve scheduling\n");

    printf("\tPath: ");
    for (int i = 0; i < data->len - 1; i++) {
        printf("%d->", data->queue[i]);
        seek_time += abs(data->queue[i] - data->queue[i + 1]);
    }
    printf("%d\n", data->queue[data->len - 1]);

    printf("\tTotal seek time: %d\n", seek_time);
    printf("\tAverage seek time: %0.2f\n", (float) seek_time / (float) (data->len - 1));
}

void scan(IORequests *data) {
    printf("\nSCAN scheduling\n");
    int head = data->queue[0], head_index = 0, seek_time, queue[data->len];

    for (int i = 0; i < data->len; i++)
        queue[i] = data->queue[i];

    for (int i = 0; i < data->len; i++) {
        for (int j = 0; j < data->len - i - 1; j++) {
            if (queue[j] > queue[j + 1]) {
                queue[j] += queue[j + 1];
                queue[j + 1] = queue[j] - queue[j + 1];
                queue[j] = queue[j] - queue[j + 1];
            }
        }
    }

    for (int i = 0; i < data->len; i++) {
        if (head == queue[i]) {
            head_index = i;
            break;
        }
    }

    printf("\tPath: ");
    if (head <= abs(head - data->max_cylinder_count)) {
        for (int i = head_index; i >= 0; i--)
            printf("%d->", queue[i]);
        for (int i = head_index + 1; i < data->len - 1; i++)
            printf("%d->", queue[i]);
        printf("%d\n", queue[data->len - 1]);
    } else {
        for (int i = head_index; i < data->len; i++)
            printf("%d->", queue[i]);
        for (int i = head_index - 1; i > 0; i--)
            printf("%d->", queue[i]);
        printf("%d\n", queue[0]);
    }

    seek_time = head + queue[data->len - 1];

    printf("\tTotal seek time: %d\n", seek_time);
    printf("\tAverage seek time: %0.2f\n", (float) seek_time / (float) (data->len - 1));
}

void cscan(IORequests *data) {
    printf("\nC-SCAN scheduling\n");
    int head = data->queue[0], head_index = 0, seek_time, queue[data->len];

    for (int i = 0; i < data->len; i++)
        queue[i] = data->queue[i];

    for (int i = 0; i < data->len; i++) {
        for (int j = 0; j < data->len - i - 1; j++) {
            if (queue[j] > queue[j + 1]) {
                queue[j] += queue[j + 1];
                queue[j + 1] = queue[j] - queue[j + 1];
                queue[j] = queue[j] - queue[j + 1];
            }
        }
    }
    for (int i = 0; i < data->len; i++) {
        if (head == queue[i]) {
            head_index = i;
            break;
        }
    }

    printf("\tPath: %d->", queue[head_index]);
    if (head >= abs(head - data->max_cylinder_count)) {
        for (int i = head_index + 1; i != head_index - 1; i = (i + 1) % data->len)
            printf("%d->", queue[i]);
        printf("%d\n", queue[head_index - 1]);
        seek_time = data->max_cylinder_count - queue[head_index] + queue[head_index - 1];
    } else {
        for (int i = head_index - 1; i != head_index + 1; i = (i - 1 + data->len) % data->len)
            printf("%d->", queue[i]);
        printf("%d\n", queue[head_index + 1]);
        seek_time = queue[head_index] + data->max_cylinder_count - queue[head_index + 1];
    }


    printf("\tTotal seek time: %d\n", seek_time);
    printf("\tAverage seek time: %0.2f\n", (float) seek_time / (float) (data->len - 1));
}
