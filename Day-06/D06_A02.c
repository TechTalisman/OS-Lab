#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>  // Include this for wait()

int main() {
    pid_t pid1, pid2;
    
    pid1 = fork(); // Create P1 from P
    
    if (pid1 < 0) {
        perror("Fork failed");
        return 1;
    } else if (pid1 == 0) {
        // Child process P1
        printf("P1: PID = %d, PPID = %d\n", getpid(), getppid());
        
        pid2 = fork(); // Create P2 from P1
        
        if (pid2 < 0) {
            perror("Fork failed");
            return 1;
        } else if (pid2 == 0) {
            // Child process P2
            printf("P2: PID = %d, PPID = %d\n", getpid(), getppid());
        } else {
            wait(NULL); // P1 waits for P2
        }
    } else {
        // Parent process P
        printf("P: PID = %d\n", getpid());
        wait(NULL); // P waits for P1
    }
    
    return 0;
}
