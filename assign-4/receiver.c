#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <ctype.h>

struct Message
{
    char data[100];
    int type;
};

int main()
{
    key_t key;
    int msgQueueId;
    struct Message msg;

    key = ftok("keyfile", 'a');

    msgQueueId = msgget(key, 0666 | IPC_CREAT);
    if (msgQueueId == -1)
    {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        if (msgrcv(msgQueueId, &msg, sizeof(msg) - sizeof(long), 0, 0) == -1)
        {
            perror("msgrcv");
            exit(EXIT_FAILURE);
        }

        printf("Received Message: ");

        if (msg.type == 1)
        {
            for (int i = 0; msg.data[i] != '\0'; ++i)
                msg.data[i] = toupper(msg.data[i]);
            printf("%s\n", msg.data);
        }
        else if (msg.type == 2)
        {
            for (int i = 0; msg.data[i] != '\0'; ++i)
                msg.data[i] = tolower(msg.data[i]);
            printf("%s\n", msg.data);
        }
    }

    if (msgctl(msgQueueId, IPC_RMID, NULL) == -1)
    {
        perror("msgctl");
        exit(EXIT_FAILURE);
    }

    return 0;
}
