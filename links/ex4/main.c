#include <stdio.h>
#include <dirent.h>

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("Usage: %s <directory>\n", argv[0]);
        return 1;
    }

    DIR *dir;

    dir = opendir(argv[1]);
    if (dir == NULL)
    {
        perror("Error while opening directory");
        return 1;
    }

    struct dirent *file;

    while ((file = readdir(dir)) != NULL)
    {
        printf("Name: %15s | Inode: %10ld\n", file->d_name, file->d_ino);
    }

    closedir(dir);

    return 0;
}