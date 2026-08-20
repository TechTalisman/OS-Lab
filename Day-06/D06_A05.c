#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

int main() {
    pid_t pid1, pid2;
    int status;

    pid1 = fork();

    if (pid1 < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) {
        // First child process
        srand(time(NULL) ^ getpid());

        int sleep_time = rand() % 5 + 1;

        printf("Child 1 (PID: %d, Parent PID: %d) - Sleeping for %d seconds.\n",
               getpid(), getppid(), sleep_time);

        sleep(sleep_time);

        printf("Child 1 finished after %d seconds.\n", sleep_time);
        exit(0);
    }

    pid2 = fork();

    if (pid2 < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0) {
        // Second child process
        srand(time(NULL) ^ getpid());

        int sleep_time = rand() % 5 + 1;

        printf("Child 2 (PID: %d, Parent PID: %d) - Sleeping for %d seconds.\n",
               getpid(), getppid(), sleep_time);

        sleep(sleep_time);

        printf("Child 2 finished after %d seconds.\n", sleep_time);
        exit(0);
    }

    // Parent process
    printf("Parent (PID: %d) waiting for both children to complete.\n",
           getpid());

    waitpid(pid1, &status, 0);
    waitpid(pid2, &status, 0);

    printf("Parent process exiting after both children completed.\n");

    return 0;
}
