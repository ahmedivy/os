#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // Redirect standard output to the file
    int fd = open(argv[1], O_WRONLY | O_CREAT | O_APPEND);
    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        perror("dup2");
        return 1;
    }

    // Close the file descriptor as it's no longer needed
    close(fd);

    // Now, anything written to stdout will be redirected to the file

    // Print a short message to the file
    printf("This message is appended to myfile after running ex3.\n");

    // Restore stdout to its original state (e.g., the terminal)
    dup2(STDOUT_FILENO, 1);

    // Close the original stdout redirection
    close(fd);

    return 0;
}
