#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void createProcess(int n, int count)
{
    if (n == count)
    {
        return;
    }

    int pid = fork();
    if (pid == -1)
    {
        printf("Fork Failed!\n");
        exit(1);
    }

    if (pid == 0)
    {
        printf("Processs %d created %d\n", getppid(), getpid());
        createProcess(n, count + 1);
        exit(0);
    }
    else
    {
        wait(NULL);
    }
}

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
        printf("Please enter a positive integer value for n.\n");
        exit(1);
    }

    createProcess(n, 0);

    return 0;
}
