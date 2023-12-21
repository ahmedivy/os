#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

int n_semaphore = 0; // keep track of no of item in the buffer
int s_semaphore = 1; // to enforce mutual exclusion
char s;

void producer()
{
    s_semaphore = 0; // set semaphore to avoid access to consumer
    if (!s_semaphore)
        printf("Now producer can add data to buffer\n");
    else
        printf("Critical Region \n");
    s_semaphore = 1; // release semaphore
    signal_c();      // call to consumer
}
void consumer()
{
    buffer_check();  // check buffer is empty or not
    s_semaphore = 0; // set semaphore to avoid access to producer
    if (!s_semaphore)
        printf("Consumer takes from the buffer\n");
    else
        printf("Critical Region \n");
    s_semaphore = 1; // release semaphore
    signal_p();      // call to producer
}
signal_c()
{
    n_semaphore = n_semaphore + 1;
    consumer();
    return 0;
}
signal_p()
{
    n_semaphore = n_semaphore - 1;
    printf("Enter n to stop\n");
    scanf("%c", &s);
    if (s == 'n')
        exit(0);
    return 0;
}
buffer_check()
{
    if (n_semaphore <= 0)
    {
        printf("Buffer is empty\n");
        exit(0);
    }
    return 0;
}
void main()
{
    clrscr();
    n_semaphore = 0;
    while (1)
    {
        producer();
    }
}