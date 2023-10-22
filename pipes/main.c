#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int pipe_fd[2];
    char message[] = "Hello, Child Process!";

    if (pipe(pipe_fd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    int child_pid = fork();
    if (child_pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0)
    {
        // Child process
        close(pipe_fd[1]); // Close the writing end
        char buffer[256];
        ssize_t bytes_read = read(pipe_fd[0], buffer, sizeof(buffer));
        if (bytes_read > 0)
        {
            buffer[bytes_read] = '\0';
            printf("Child received: %s\n", buffer);
        }
        close(pipe_fd[0]); // Close the reading end
    }
    else
    {
        // Parent process
        close(pipe_fd[0]); // Close the reading end
        write(pipe_fd[1], message, strlen(message));
        close(pipe_fd[1]); // Close the writing end
    }

    return 0;
}
