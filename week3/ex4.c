#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <n>\n", argv[0]);
        exit(1);
    }

    int n = atoi(argv[1]);
    if (n < 1)
    {
        printf("Please provide a positive integer value for n.\n");
        exit(1);
    }

    for (int i = 0; i < n; i++)
    {
        pid_t pid = fork();

        if (pid == -1)
        {
            printf("fork failed");
            exit(1);
        }

        if (pid == 0)
        {
            // This is the child process
            printf("Child %d with PID %d\n", i + 1, getpid());
            exit(0);
        }
    }

    // This is the parent process
    printf("Parent process with PID %d created %d child processes.\n", getpid(), n);

    return 0;
}
