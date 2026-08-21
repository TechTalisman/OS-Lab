#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void fibonacci(int n) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process: prints even-indexed Fibonacci numbers
        int a = 0, b = 1, next;

        for (int i = 0; i < n; i++) {
            if (i % 2 == 0) {
                printf("Child (Even %d): %d\n", i, a);
            }

            next = a + b;
            a = b;
            b = next;
        }

        exit(0);
    } else {
        // Parent process: prints odd-indexed Fibonacci numbers
        int a = 0, b = 1, next;

        for (int i = 0; i < n; i++) {
            if (i % 2 != 0) {
                printf("Parent (Odd %d): %d\n", i, a);
            }

            next = a + b;
            a = b;
            b = next;
        }

        // Parent waits for child to finish
        wait(NULL);
    }
}

int main() {
    int n;

    printf("Enter the number of terms: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Please enter a positive integer.\n");
        return 1;
    }

    fibonacci(n);

    return 0;
}
