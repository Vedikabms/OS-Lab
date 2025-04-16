#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int mutex = 1;
int full = 0;
int empty = 3;
int buffer[3];
int in = 0;
int out = 0;

int wait(int s) {
    return (--s);
}

int signal(int s) {
    return (++s);
}

void display_buffer() {
    printf("Buffer:");
    for (int i = 0; i < full; i++) {
        int index = (out + i) % 3;
        printf("%d ", buffer[index]);
    }
    printf("\n");
}

void producer(int id) {
    if ((mutex == 1) && (empty != 0)) {
        mutex = wait(mutex);
        full = signal(full);
        empty = wait(empty);

        int item = rand() % 40;
        buffer[in] = item;
        printf("Producer %d produced %d\n", id, item);
        in = (in + 1) % 3;

        display_buffer();
        mutex = signal(mutex);
    } else {
        printf("Buffer is full\n");
    }
}

void consumer(int id) {
    if ((mutex == 1) && (full != 0)) {
        mutex = wait(mutex);
        full = wait(full);
        empty = signal(empty);

        int item = buffer[out];
        printf("Consumer %d consumed %d\n", id, item);
        out = (out + 1) % 3;

        printf("Current buffer len: %d\n", full);
        mutex = signal(mutex);
    } else {
        printf("Buffer is empty\n");
    }
}

int main() {
    int p, c, capacity, choice;

    srand(time(NULL));

    printf("Enter the number of Producers:");
    scanf("%d", &p);
    printf("Enter the number of Consumers:");
    scanf("%d", &c);
    printf("Enter buffer capacity:");
    scanf("%d", &capacity);

    empty = capacity;

    for (int i = 1; i <= p; i++) {
        printf("Successfully created producer %d\n", i);
    }
    for (int i = 1; i <= c; i++) {
        printf("Successfully created consumer %d\n", i);
    }

    while (1) {
        printf("\n1. Produce\n2. Consume\n3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            producer(1);
            break;
        case 2:
            consumer(2);
            break;
        case 3:
            exit(0);
        default:
            printf("Invalid choice\n");
        }
    }

    return 0;
}
