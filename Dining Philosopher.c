#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

#define N 5  // Number of philosophers
#define THINKING 2
#define HUNGRY 1
#define EATING 0
#define LEFT (phnum + 4) % N
#define RIGHT (phnum + 1) % N

int state[N];        // Array to store the state of each philosopher
int phil[N] = { 0, 1, 2, 3, 4 };  // Philosopher numbers

sem_t mutex;         // Mutex to protect the critical section
sem_t S[N];          // Semaphores for each philosopher

// Function to test if a philosopher can start eating
void test(int phnum)
{
    if (state[phnum] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) {
        // Philosopher can start eating
        state[phnum] = EATING;
        sleep(2); // Simulate time spent eating
        printf("Philosopher %d takes fork %d and %d\n", phnum + 1, LEFT + 1, phnum + 1);
        printf("Philosopher %d is Eating\n", phnum + 1);
        sem_post(&S[phnum]);  // Signal that the philosopher can start eating
    }
}

// Function for a philosopher to take forks (chopsticks)
void take_fork(int phnum)
{
    sem_wait(&mutex);  // Enter critical section
    state[phnum] = HUNGRY;  // Philosopher is hungry
    printf("Philosopher %d is Hungry\n", phnum + 1);

    test(phnum);  // Try to eat if possible
    sem_post(&mutex);  // Exit critical section

    sem_wait(&S[phnum]);  // Wait until the philosopher can start eating
    sleep(1);  // Simulate time spent eating
}

// Function for a philosopher to put down forks (chopsticks)
void put_fork(int phnum)
{
    sem_wait(&mutex);  // Enter critical section
    state[phnum] = THINKING;  // Philosopher is thinking

    printf("Philosopher %d putting fork %d and %d down\n", phnum + 1, LEFT + 1, phnum + 1);
    printf("Philosopher %d is thinking\n", phnum + 1);

    test(LEFT);  // Check if the left philosopher can start eating
    test(RIGHT);  // Check if the right philosopher can start eating

    sem_post(&mutex);  // Exit critical section
}

// Philosopher function representing each philosopher's behavior
void* philosopher(void* num)
{
    int* i = num;
    while (1) {
        sleep(1);  // Philosopher is thinking
        take_fork(*i);  // Philosopher takes forks to eat
        sleep(0);  // Simulate time spent eating
        put_fork(*i);  // Philosopher puts down forks after eating
    }
}

int main()
{
    int i;
    pthread_t thread_id[N];  // Thread IDs for each philosopher

    // Initialize semaphores
    sem_init(&mutex, 0, 1);  // Mutex initially 1
    for (i = 0; i < N; i++) {
        sem_init(&S[i], 0, 0);  // Each philosopher's semaphore initially 0
    }

    // Create philosopher threads
    for (i = 0; i < N; i++) {
        pthread_create(&thread_id[i], NULL, philosopher, &phil[i]);
        printf("Philosopher %d is thinking\n", i + 1);
    }

    // Wait for all philosopher threads to finish (they run infinitely)
    for (i = 0; i < N; i++) {
        pthread_join(thread_id[i], NULL);
    }

    return 0;
}
