#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MSG_SIZE 256

int main() {
    int pipe_fd[2];
    pid_t pid;

    // Create pipe
    if (pipe(pipe_fd) == -1) {
        perror("Pipe creation failed");
        exit(EXIT_FAILURE);
    }

    // Fork a child process
    pid = fork();

    if (pid == -1) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {  // Parent process
        close(pipe_fd[1]);  // Close the write end in the parent

        char message[MSG_SIZE];

        // Read messages from the pipe
        printf("Parent process reading messages:\n");

        for (int i = 0; i < 3; ++i) {
            ssize_t bytesRead = read(pipe_fd[0], message, MSG_SIZE);
            if (bytesRead == -1) {
                perror("Read failed");
                exit(EXIT_FAILURE);
            }

            message[bytesRead] = '\0';  // Null-terminate the string
            printf("%s\n", message);
        }

        close(pipe_fd[0]);  // Close the read end in the parent
    } else {  // Child process
        close(pipe_fd[0]);  // Close the read end in the child

        // Messages to be written
        char *messages[] = {"Hello World\n", "Hello SPPU\n", "Linux is Funny\n"};

        // Write messages to the pipe
        for (int i = 0; i < 3; ++i) {
            ssize_t bytesWritten = write(pipe_fd[1], messages[i], strlen(messages[i]));

            if (bytesWritten == -1) {
                perror("Write failed");
                exit(EXIT_FAILURE);
            }
        }

        close(pipe_fd[1]);  // Close the write end in the child
    }

    return 0;
}
