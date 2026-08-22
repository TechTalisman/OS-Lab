#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void create_child_processes(int level) {
    // Stop creating processes after the grandchild level
    if (level == 2)
        return;

    for (int i = 0; i < 2; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0) {
            // Child process
            printf("Process %d (Child of %d)\n", getpid(), getppid());

            create_child_processes(level + 1);

            // Wait for own children before exiting
            for (int j = 0; j < 2; j++) {
                wait(NULL);
            }

            exit(EXIT_SUCCESS);
        }
    }

    // Parent waits for both child processes
    for (int i = 0; i < 2; i++) {
        wait(NULL);
    }
}

int main() {
    printf("Root Process (Parent) PID: %d\n", getpid());

    create_child_processes(0);

    printf("Parent Process %d terminating.\n", getpid());

    return 0;
}
