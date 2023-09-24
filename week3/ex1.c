#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("Original Process with PID = %d and PPID = %d\n", getpid(), getppid());
    int pid = fork();

    if (pid != 0)
    {
        printf("Parent Process with PID = %d and PPID = %d\n", getpid(), getppid());
    }
    else
    {
        // sleep(5);
        printf("Child Process with PID = %d and PPID = %d\n", getpid(), getppid());
    }

    printf("Process with PID = %d terminates\n", getpid());

    return 0;
}