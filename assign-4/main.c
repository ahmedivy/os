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

    printf("Enter message data (up to 100 characters): ");
    fgets(msg.data, sizeof(msg.data), stdin);
    printf("Enter type (1 for uppercase, 2 for lowercase): ");
    scanf("%d", &msg.type);

    if (msgsnd(msgQueueId, &msg, sizeof(msg.data), 0) == -1)
    {
        perror("msgsnd");
        exit(EXIT_FAILURE);
    }

    if (msgrcv(msgQueueId, &msg, sizeof(msg.data), 0, 0) == -1)
    {
        perror("msgrcv");
        exit(EXIT_FAILURE);
    }

    if (msg.type == 1)
    {
        for (int i = 0; msg.data[i] != '\0'; ++i)
        {
            msg.data[i] = toupper(msg.data[i]);
        }
        printf("Received and converted to Uppercase: %s\n", msg.data);
    }
    else if (msg.type == 2)
    {
        for (int i = 0; msg.data[i] != '\0'; ++i)
        {
            msg.data[i] = tolower(msg.data[i]);
        }
        printf("Received and converted to Lowercase: %s\n", msg.data);
    }

    if (msgctl(msgQueueId, IPC_RMID, NULL) == -1)
    {
        perror("msgctl");
        exit(EXIT_FAILURE);
    }

    return 0;
}
