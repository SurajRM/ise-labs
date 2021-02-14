#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_SIZE 512

typedef struct queue {
    int queue_size;
    char **messages;
    int front, rear;
} Queue;

Queue *create_queue(int);
bool is_full(Queue *);
bool is_empty(Queue *);
void enqueue(Queue *, char *);
char *dequeue(Queue *);
void display_queue(Queue *);

int main() {
    int choice;
    int queue_size;
    float queue_size2;
    char msg[STRING_SIZE];

    printf("\t\tMessaging system\n");
    printf("Enter the size of the queue: ");
    scanf("%f", &queue_size2);
    queue_size = (int) queue_size2;
    if ((float) queue_size != queue_size2 || queue_size2 < 0) {
        printf("Invalid input\n");
        exit(1);
    }

    Queue *que = create_queue(queue_size);
    printf("Queue of size %d created\n\n", queue_size);

    while (true) {
        printf("1: Check if queue is full\n");
        printf("2: Check if queue is empty\n");
        printf("3: Display contents\n");
        if (!is_full(que)) {
            printf("4: Enqueue\n");
            if (!is_empty(que))
                printf("5: Dequeue\n");
        } else
            printf("4: Dequeue\n");
        printf("-1: Exit\n");
        printf("Select an operation: ");
        scanf("%d", &choice);

        if (is_full(que)) {
            if (choice == 4)
                choice++;
            else if (choice == 5) {
                printf("Invalid option\n\n");
                continue;
            }
        }

        switch (choice) {
            case 4:
                printf("Enter the message to be enqueued: ");
                getchar();
                scanf("%[^\n]s", msg);
                enqueue(que, msg);
                display_queue(que);
                break;
            case 5:
                if (is_empty(que)) {
                    printf("Invalid option\n");
                    break;
                }
                strcpy(msg, dequeue(que));
                if (strcmp(msg, "") != 0)
                    printf("The dequeued message is: %s\n", msg);
                display_queue(que);
                break;
            case 1:
                if (is_full(que))
                    printf("The queue is full\n");
                else
                    printf("The queue is not full\n");
                break;
            case 2:
                if (is_empty(que))
                    printf("The queue is empty\n");
                else
                    printf("The queue is not empty\n");
                break;
            case 3:
                display_queue(que);
                break;
            case -1:
                exit(0);
            default:
                printf("Invalid option\n");
                break;
        }
        printf("\n");
    }
}

Queue *create_queue(int size) {
    Queue *q = (Queue *) malloc(sizeof(Queue));
    q->messages = (char **) malloc(size * sizeof(char *));
    for (int i = 0; i < size; i++)
        q->messages[i] = (char *) malloc(STRING_SIZE * sizeof(char));

    q->queue_size = size;
    q->front = -1;
    q->rear = -1;

    return q;
}

bool is_full(Queue *q) {
    return (q->rear + 1) % q->queue_size == q->front;
}

bool is_empty(Queue *q) {
    return q->front == -1 && q->rear == -1;
}

void enqueue(Queue *q, char *message) {
    if (q->front == -1 && q->rear == -1) {
        q->front = 0;
        q->rear = 0;
    } else if (is_full(q)) {
        printf("QUEUE FULL\n");
        return;
    } else
        q->rear = (q->rear + 1) % q->queue_size;

    strcpy(q->messages[q->rear], message);
}

char *dequeue(Queue *q) {
    if (is_empty(q)) {
        printf("QUEUE EMPTY\n");
        return "";
    }
    char *message = q->messages[q->front];
    if (q->front == q->rear) {
        q->front = -1;
        q->rear = -1;
    } else
        q->front = (q->front + 1) % q->queue_size;

    return message;
}

void display_queue(Queue *q) {
    if (is_empty(q)) {
        printf("QUEUE EMPTY\n");
        return;
    }

    printf("\nQueue: [");
    for (int i = q->front; i != q->rear; i = (i + 1) % q->queue_size) {
        printf("\"%s\"", q->messages[i]);
        printf(", ");
    }
    printf("\"%s\"]\n", q->messages[q->rear]);
}