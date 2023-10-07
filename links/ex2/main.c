#include <stdio.h>

int main()
{
    FILE *fp;
    char ch;
    int blanks = 0, chars = 0, newlines = 0;

    fp = fopen("file.txt", "r");

    while (ch != EOF)
    {
        ch = fgetc(fp);
        switch (ch)
        {
        case ' ':
            blanks++;
            break;

        case '\n':
            newlines++;

        default:
            chars++;
            break;
        }
    }

    printf("Number of chars: %d\n", chars);
    printf("Number of blanks: %d\n", blanks);
    printf("Number of new lines: %d\n", newlines);

    return 0;
}