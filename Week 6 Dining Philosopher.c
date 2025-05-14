#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5
#define NUM_FORKS NUM_PHILOSOPHERS

sem_t forks[NUM_FORKS];

void *philosopher(void *arg);

void think(int philosopher_id);

void eat(int philosopher_id);

void pickup_forks(int philosopher_id);

void putdown_forks(int philosopher_id);

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];

    int i;

    for (i = 0; i < NUM_FORKS; i++) {
        if (sem_init(&forks[i], 0, 1) != 0) {
            perror("sem_init");
            exit(EXIT_FAILURE);
        }
    }

    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        int *philosopher_id = malloc(sizeof(int));
        if (philosopher_id == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
        *philosopher_id = i;
        if (pthread_create(&philosophers[i], NULL, philosopher, (void *)philosopher_id) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        if (pthread_join(philosophers[i], NULL) != 0) {
            perror("pthread_join");
            exit(EXIT_FAILURE);
        }
    }

    for (i = 0; i < NUM_FORKS; i++) {
        if (sem_destroy(&forks[i]) != 0) {
            perror("sem_destroy");
            exit(EXIT_FAILURE);
        }
    }

    printf("Simulation finished.\n");
    return 0;
}

void *philosopher(void *arg) {
    int philosopher_id = *(int *)arg;
    free(arg);
    printf("Philosopher %d started\n", philosopher_id);

    while (1) {
        think(philosopher_id);
        pickup_forks(philosopher_id);
        eat(philosopher_id);
        putdown_forks(philosopher_id);
    }
    return NULL;

void think(int philosopher_id) {
    printf("Philosopher %d is thinking\n", philosopher_id);
    sleep(1);
}

void eat(int philosopher_id) {
    printf("Philosopher %d is eating\n", philosopher_id);
    sleep(2);
}

void pickup_forks(int philosopher_id) {
    int left_fork = philosopher_id;
    int right_fork = (philosopher_id + 1) % NUM_FORKS;

    if (philosopher_id == NUM_PHILOSOPHERS - 1) {
        if (sem_wait(&forks[right_fork]) != 0) {
             perror("sem_wait");
             pthread_exit(NULL);
        }
        printf("Philosopher %d picked up right fork %d\n", philosopher_id, right_fork);
        if (sem_wait(&forks[left_fork]) != 0) {
            perror("sem_wait");
            sem_post(&forks[right_fork]);
            pthread_exit(NULL);
        }
        printf("Philosopher %d picked up left fork %d\n", philosopher_id, left_fork);
    } else {
         if (sem_wait(&forks[left_fork]) != 0) {
            perror("sem_wait");
            pthread_exit(NULL);
         }
        printf("Philosopher %d picked up left fork %d\n", philosopher_id, left_fork);
        if (sem_wait(&forks[right_fork]) != 0) {
            perror("sem_wait");
            sem_post(&forks[left_fork]);
            pthread_exit(NULL);
        }
        printf("Philosopher %d picked up right fork %d\n", philosopher_id, right_fork);
    }
}

void putdown_forks(int philosopher_id) {
    int left_fork = philosopher_id;
    int right_fork = (philosopher_id + 1) % NUM_FORKS;

    if (sem_post(&forks[left_fork]) != 0) {
        perror("sem_post");
        pthread_exit(NULL);
    }
    printf("Philosopher %d put down left fork %d\n", philosopher_id, left_fork);
    if (sem_post(&forks[right_fork]) != 0) {
        perror("sem_post");
        pthread_exit(NULL);
    }
    printf("Philosopher %d put down right fork %d\n", philosopher_id, right_fork);
}
