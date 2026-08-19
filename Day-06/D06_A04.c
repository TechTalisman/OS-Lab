#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int pipefd[2]; 
    pid_t pid;
    int data;

    if (pipe(pipefd) == -1) {
        perror("Pipe failed");
        exit(EXIT_FAILURE);
    }

    printf("Enter an integer to send to the child process: ");
    scanf("%d", &data);

    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } 
    else if (pid == 0) { // Child process
        close(pipefd[1]); // Close unused write end
        int received_data;
        read(pipefd[0], &received_data, sizeof(received_data));
        printf("Child received: %d\n", received_data);
        close(pipefd[0]);
        exit(0);
    } 
    else { // Parent process
        close(pipefd[0]); // Close unused read end
        printf("Parent sending: %d\n", data);
        write(pipefd[1], &data, sizeof(data));
        close(pipefd[1]);

        wait(NULL); // Wait for child to finish
        printf("Parent process exiting.\n");
    }

    return 0;
}
