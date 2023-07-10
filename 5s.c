#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

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

    printf("Sender: Enter text (type 'exit' to quit): \n");

    while (1) {
        char input[256];
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0'; // Remove trailing newline character

        // Check if user wants to exit
        if (strcmp(input, "exit") == 0)
            break;

        // Wait for receiver to read the previous message
        sem_op.sem_num = SEM_COUNT;
        sem_op.sem_op = -1;
        sem_op.sem_flg = 0;
        if (semop(semid, &sem_op, 1) == -1)
            error("Failed to perform semop (wait)");

        // Write the message
        printf("Sender: Sending message: %s\n", input);

        // Signal receiver that a new message is available
        sem_op.sem_num = SEM_COUNT;
        sem_op.sem_op = 1;
        sem_op.sem_flg = 0;
        if (semop(semid, &sem_op, 1) == -1)
            error("Failed to perform semop (signal)");
    }

    // Clean up and remove the semaphore
    if (semctl(semid, 0, IPC_RMID) == -1)
        error("Failed to remove semaphore");

    printf("Sender: Exiting\n");

    return 0;
}

