// TODO: Dynamic options to be displayed depending upon queue
// TODO: Display contents of the queue after each enqueue
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct queue
{
    int queue_size, message_size;
    char **messages;
    int front, rear;
};
typedef struct queue Queue;

void create_queue(Queue *, int, int);
bool is_full(Queue *);
bool is_empty(Queue *);
void enqueue(Queue *, char *message);
char *dequeue(Queue *);
void display_queue(Queue *);

int main()
{
    Queue que;
    int choice;
    int queue_size, max_message_size;
    system("clear");
    printf("Enter the size of the queue: ");
    scanf("%d", &queue_size);
    printf("Enter the length of the maximum message: ");
    scanf("%d", &max_message_size);
    max_message_size++;
    char msg[max_message_size];
    create_queue(&que, queue_size, max_message_size);
    printf("\nQueue of size %d created\n", queue_size);
    while (true)
    {
        printf("\n--------------------------\n\
    1: Enqueue\n\
    2: Dequeue\n\
    3: IsFull\n\
    4: IsEmpty\n\
    5: Display contents\n\
    -1: Exit\n\
    Select an operation: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter the message to be enqueued: ");
            scanf("%s", msg); // FIXME: Input can be a sentence
            enqueue(&que, msg);
            break;
        case 2:
            strcpy(msg, dequeue(&que));
            if (strcmp(msg, ""))
            {
                printf("The dequeued message is: %s", msg);
            }
            break;
        case 3:
            if (is_full(&que))
                printf("The queue is full\n");
            else
                printf("The queue is not full\n");
            break;
        case 4:
            if (is_empty(&que))
                printf("The queue is empty\n");
            else
                printf("The queue is not empty\n");
            break;
        case 5:
            display_queue(&que);
            break;
        case -1:
            exit(0);
        default:
            printf("Invalid option\n");
            break;
        }
    }
}

void create_queue(Queue *q, int size, int msize)
{
    q->messages = malloc(size * sizeof(char *));
    for (int i = 0; i < size; i++)
    {
        q->messages[i] = malloc(msize * sizeof(char));
    }

    q->queue_size = size;
    q->message_size = msize;
    q->front = -1;
    q->rear = -1;
}

bool is_full(Queue *q)
{
    return (q->rear + 1) % q->queue_size == q->front;
}

bool is_empty(Queue *q)
{
    return q->front == -1 && q->rear == -1;
}

void enqueue(Queue *q, char *message)
{
    if (q->front == -1 && q->rear == -1)
    {
        q->front = 0;
        q->rear = 0;
    }
    else if (is_full(q))
    {
        printf("QUEUE FULL\n");
        return;
    }
    else
    {
        q->rear = (q->rear + 1) % q->queue_size;
    }
    strcpy(q->messages[q->rear], message);
}

char *dequeue(Queue *q)
{
    if (is_empty(q))
    {
        printf("QUEUE EMPTY\n");
        return "";
    }
    char *message = q->messages[q->front];
    if (q->front == q->rear)
    {
        q->front = -1;
        q->rear = -1;
    }
    else
    {
        q->front = (q->front + 1) % q->queue_size;
    }

    return message;
}

void display_queue(Queue *q)
{
    if (is_empty(q))
    {
        printf("QUEUE EMPTY\n");
        return "";
    }
    printf("\nQueue: [");
    for(int i = q->front; i <= q->rear; i = (i + 1) % q->queue_size)
    {
        printf("\"%s\"", q->messages[i]);
        if (i != q->rear)
            printf(", ");
    }
    printf("]\n");
}