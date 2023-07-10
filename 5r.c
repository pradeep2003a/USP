#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>

#define KEY 1234 // Shared semaphore key
#define SEM_COUNT 0 // Semaphore index

void error(const char *msg) {
    perror(msg);
    exit(1);
}

int main() {
    int semid;
    struct sembuf sem_op;

    // Create or get the shared semaphore
    semid = semget(KEY, 1, IPC_CREAT | 0666);
    if (semid < 0)
        error("Failed to create or get semaphore");

    printf("Receiver: Waiting for messages...\n");

    while (1) {
        // Wait for sender to write a new message
        sem_op.sem_num = SEM_COUNT;
        sem_op.sem_op = -1;
        sem_op.sem_flg = 0;
        if (semop(semid, &sem_op, 1) == -1)
            error("Failed to perform semop (wait)");

        // Read the message
        printf("Receiver: Message received: ");
        char ch;
        while ((ch = getchar()) != '\n' && ch != EOF)
            putchar(ch);
        printf("\n");

        // Signal sender that the message has been read
        sem_op.sem_num = SEM_COUNT;
        sem_op.sem_op = 1;
        sem_op.sem_flg = 0;
        if (semop(semid, &sem_op, 1) == -1)
            error("Failed to perform semop (signal)");
    }

    printf("Receiver: Exiting\n");

    return 0;
}

