#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Function to check if a number is prime
int is_prime(int num) {
    if (num < 2)
        return 0;

    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0)
            return 0;
    }

    return 1;
}

int main() {
    int start, end;

    printf("Enter the range (start end): ");
    scanf("%d %d", &start, &end);

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {
        // Child process
        printf("Child process generating prime numbers in range %d to %d:\n",
               start, end);

        for (int i = start; i <= end; i++) {
            if (is_prime(i)) {
                printf("%d ", i);
            }
        }

        printf("\nChild process completed.\n");
        exit(EXIT_SUCCESS);
    }
    else {
        // Parent process
        wait(NULL);

        printf("Parent process: Child process finished execution.\n");
    }

    return 0;
}
