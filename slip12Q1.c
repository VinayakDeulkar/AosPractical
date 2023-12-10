
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t child_pid;

    // Create a child process
    child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {
        // Child process
        printf("Child process executing...\n");

        // Simulate some work in the child process
        sleep(2);

        // Exit with a specific status
        exit(42);
    } else {
        // Parent process
        printf("Waiting for the child process to complete...\n");

        // Wait for the child process to complete and get its exit status
        int status;
        waitpid(child_pid, &status, 0);

        if (WIFEXITED(status)) {
            printf("Child process exited with status: %d\n", WEXITSTATUS(status));
        } else {
            printf("Child process did not exit normally.\n");
        }

        printf("Parent process exiting...\n");
    }

    return 0;
}