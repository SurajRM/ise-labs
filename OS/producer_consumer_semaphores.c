#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MaxItems 5
#define BufferSize 5

sem_t empty;
sem_t full;
sem_t s;
int in = 0;
int out = 0;
int buffer[BufferSize];


void *producer(void *arg) {
    for (int i = 0; i < MaxItems; i++) {
        sleep(1);
        sem_wait(&empty);
        sem_wait(&s);
        buffer[in] = i;
        printf("Producer produced item %d\n", buffer[in]);
        in = (in + 1) % BufferSize;
        sem_post(&s);
        sem_post(&full);
    }
}
void *consumer(void *arg) {
    for (int i = 0; i < MaxItems; i++) {
        sleep(1);
        sem_wait(&full);
        sem_wait(&s);
        int item = buffer[out];
        printf("Consumer consumed item %d\n", item);
        out = (out + 1) % BufferSize;
        sem_post(&s);
        sem_post(&empty);
    }
}

int main() {
    printf("\t\tProducer Consumer problem using semaphores\n");
    pthread_t pro, con;
    sem_init(&empty, 0, BufferSize);
    sem_init(&full, 0, 0);
    sem_init(&s, 0, 1);

    pthread_create(&pro, NULL, producer, NULL);
    pthread_create(&con, NULL, consumer, NULL);

    pthread_join(pro, NULL);
    pthread_join(con, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&s);

    return 0;
}