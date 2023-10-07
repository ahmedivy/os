#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <source_file> <destination_file>\n", argv[0]);
        return 1;
    }

    int old, new;
    char buffer[4096];

    // Open source file for reading
    old = open(argv[1], O_RDONLY);
    if (old == -1)
    {
        perror("Error while opening source file");
        return 1;
    }

    // Create or open destination file for writing
    new = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (new == -1)
    {
        perror("Error while opening or creating destination file");
        close(old); // Close the source file before exiting
        return 1;
    }

    ssize_t bytes;

    while ((bytes = read(old, buffer, sizeof(buffer))) > 0)
    {
        ssize_t bytes_written = write(new, buffer, bytes);
        if (bytes_written == -1)
        {
            perror("Error while writing to destination file");
            close(old);
            close(new);
            return 1;
        }
    }

    if (bytes == -1)
    {
        perror("Error while reading source file");
        close(old);
        close(new);
        return 1;
    }

    // Close both files
    close(old);
    close(new);

    // Remove source file
    unlink(argv[1]);

    return 0;
}
