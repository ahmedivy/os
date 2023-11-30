#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t semaphore;
int sharedResource = 0;

void *increment(void *arg)
{
    for (int i = 0; i < 5; ++i)
    {
        sem_wait(&semaphore);

        sharedResource++;
        printf("Incremented -> Shared Value: %d\n", sharedResource);

        sem_post(&semaphore);
    }

    pthread_exit(NULL);
}

void *decrement(void *arg)
{
    for (int i = 0; i < 5; ++i)
    {
        sem_wait(&semaphore);

        sharedResource--;
        printf("Decremented -> Shared Value: %d\n", sharedResource);

        sem_post(&semaphore);
    }

    pthread_exit(NULL);
}

int main()
{
    pthread_t tidA, tidB;

    sem_init(&semaphore, 0, 1);

    pthread_create(&tidA, NULL, increment, NULL);
    pthread_create(&tidB, NULL, decrement, NULL);

    pthread_join(tidA, NULL);
    pthread_join(tidB, NULL);

    sem_destroy(&semaphore);

    return 0;
}
