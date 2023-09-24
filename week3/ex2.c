#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
    int status, pid;
    pid = fork();

    if (pid == -1)
    {
        printf("Fork failed\n");
        exit(1);
    }

    if (pid == 0)
    {
        printf("Child here\n");
    }
    else
    {
        wait(&status);
        printf("Well done kid!\n");
    }
}