#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *print_letter(void *arg)
{
    char letter = *(char *)arg;
    printf("%c\n", letter);
    return NULL;
}

int main()
{
    pthread_t thread1, thread2;
    char letter1 = 'A';
    char letter2 = 'B';
    pthread_create(&thread1, NULL, print_letter, &letter1);
    pthread_create(&thread2, NULL, print_letter, &letter2);
    sleep(1);
    return 0;
}
