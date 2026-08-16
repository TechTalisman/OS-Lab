#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid1, pid2;

    // First fork to create child process p1
    pid1 = fork();
    
    if (pid1 < 0) {
        perror("Fork failed");
        exit(1);
    }
    
    if (pid1 == 0) {
        // This is the first child process p1
        printf("Child p1: PID = %d, Parent PID = %d\n", getpid(), getppid());
    } else {
        // Parent process
        // Second fork to create child process p2
        pid2 = fork();
        
        if (pid2 < 0) {
            perror("Fork failed");
            exit(1);
        }
        
        if (pid2 == 0) {
            // This is the second child process p2
            printf("Child p2: PID = %d, Parent PID = %d\n", getpid(), getppid());
        } else {
            // Parent process
            printf("Parent p: PID = %d\n", getpid());
        }
    }
    
    return 0;
}
