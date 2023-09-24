// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <sys/wait.h>

// int main(int argc, const char *argv[])
// {
//     if (argc < 2)
//     {
//         printf("Usage: ./file.exe <n>\n");
//         exit(1);
//     }

//     int n = atoi(argv[1]);

//     int pid;
//     for (int i = 0; i < n; i++)
//     {
//         pid = fork();
//         if (pid == 0)
//         {
//             printf("Hello from process # %d\n", getpid());
//         }
//     }

//     return 0;
// }
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
            perror("fork");
            exit(1);
        }

        if (pid == 0)
        {
            // This is the child process
            printf("Child %d with PID %d\n", i + 1, getpid());
            sleep(1); // Sleep briefly to stagger the output
            exit(0);
        }
    }

    // This is the parent process
    printf("Parent process with PID %d created %d child processes.\n", getpid(), n);

    // Parent process waits for all child processes to complete
    for (int i = 0; i < n; i++)
    {
        wait(NULL);
    }

    return 0;
}
