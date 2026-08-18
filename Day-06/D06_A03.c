#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

int main() {
    pid_t pid1, pid2, pid3;

    srand(time(NULL));

    pid1 = fork();

    if (pid1 < 0) {
        perror("Fork failed");
        return 1;
    }
    else if (pid1 == 0) {
        // First child process
        int sleep_time = rand() % 5 + 1;

        printf("Child 1 (PID: %d, Parent PID: %d) - Sleeping for %d seconds.\n",
               getpid(), getppid(), sleep_time);

        sleep(sleep_time);

        printf("Child 1 finished after %d seconds.\n", sleep_time);
        exit(0);
    }
    else {
        pid2 = fork();

        if (pid2 < 0) {
            perror("Fork failed");
            return 1;
        }
        else if (pid2 == 0) {
            // Second child process
            int sleep_time = rand() % 5 + 1;

            printf("Child 2 (PID: %d, Parent PID: %d) - Sleeping for %d seconds.\n",
                   getpid(), getppid(), sleep_time);

            sleep(sleep_time);

            pid3 = fork();

            if (pid3 < 0) {
                perror("Fork failed");
                return 1;
            }
            else if (pid3 == 0) {
                // Third child process
                int child3_sleep = rand() % 5 + 1;

                printf("Child 3 (PID: %d, Parent PID: %d) - Sleeping for %d seconds.\n",
                       getpid(), getppid(), child3_sleep);

                sleep(child3_sleep);

                printf("Child 3 finished after %d seconds.\n", child3_sleep);
                exit(0);
            }
            else {
                // Child 2 waits for Child 3
                wait(NULL);

                printf("Child 2 finished after %d seconds.\n", sleep_time);
                exit(0);
            }
        }
        else {
            // Parent waits for Child 1 and Child 2
            printf("Parent (PID: %d) waiting for all children to complete.\n",
                   getpid());

            wait(NULL);
            wait(NULL);

            printf("Parent process exiting after all children completed.\n");
        }
    }

    return 0;
}
