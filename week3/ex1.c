#include <stdio.h>
#include <unistd.h>

int main()
{
    int pid = fork();

    if (pid != 0)
    {
        printf("Parent Process with PID = %d and PPID = %d\n", getpid(), getppid());
    }
    else
    {
        printf("Child Process with PID = %d and PPID = %d\n", getpid(), getppid());
    }

    return 0;
}