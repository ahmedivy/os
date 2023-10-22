#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    int fd1[2];
    int fd2[2];
    pid_t pid1, pid2;

    if (pipe(fd1) == -1 || pipe(fd2) == -1)
    {
        perror("pipe");
        exit(1);
    }

    if ((pid1 = fork()) == -1)
    {
        perror("fork");
        exit(1);
    }

    if (pid1 == 0) // First child: tail
    {
        close(fd1[0]);
        dup2(fd1[1], 1);
        close(fd1[1]);
        execlp("tail", "tail", "-5", "alpha.txt", NULL);
        perror("execlp tail");
        exit(1);
    }
    else // Parent
    {
        if ((pid2 = fork()) == -1)
        {
            perror("fork");
            exit(1);
        }

        if (pid2 == 0) // Second child: grep
        {
            close(fd1[1]);
            dup2(fd1[0], 0);
            close(fd1[0]);

            close(fd2[0]);
            dup2(fd2[1], 1);
            close(fd2[1]);

            execlp("grep", "grep", "a", NULL);
            perror("execlp grep");
            exit(1);
        }
        else // Parent
        {
            close(fd1[0]);
            close(fd1[1]);

            close(fd2[1]);
            dup2(fd2[0], 0);
            close(fd2[0]);

            execlp("sort", "sort", NULL);
            perror("execlp sort");
            exit(1);
        }
    }

    return 0;
}
