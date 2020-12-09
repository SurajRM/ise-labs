#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

sem_t seat;
sem_t chopstick[5];

void *philosopher(void *);

int main() {
    int i, name[5];
    pthread_t tid[5];
    printf("\t\tDining Philosophers problem using semaphores\n");

    sem_init(&seat, 0, 4);
    for (i = 0; i < 5; i++)
        sem_init(&chopstick[i], 0, 1);

    for (i = 0; i < 5; i++) {
        name[i] = i;
        pthread_create(&tid[i], NULL, philosopher, (void *) &name[i]);
    }
    for (i = 0; i < 5; i++)
        pthread_join(tid[i], NULL);

    sem_destroy(&seat);
    for (i = 0; i < 5; i++)
        sem_destroy(&chopstick[i]);
}

void *philosopher(void *num) {
    int phil = *(int *) num;

    sem_wait(&seat);
    printf("Philosopher %d has taken seat\n", phil);
    sem_wait(&chopstick[phil]);
    sem_wait(&chopstick[(phil + 1) % 5]);

    printf("Philosopher %d is eating\n", phil);
    sleep(1);
    printf("Philosopher %d has finished eating\n", phil);

    sem_post(&chopstick[(phil + 1) % 5]);
    sem_post(&chopstick[phil]);
    sem_post(&seat);

    return NULL;
}