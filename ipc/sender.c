#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>

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
        printf("Enter message data (up to 100 characters, 'exit' to quit): ");
        fgets(msg.data, sizeof(msg.data), stdin);
        if (strcmp(msg.data, "exit\n") == 0)
        {
            break;
        }
        printf("Enter type (1 for uppercase, 2 for lowercase): ");
        scanf("%d", &msg.type);
        getchar();

        if (msgsnd(msgQueueId, &msg, sizeof(msg) - sizeof(long), 0) == -1)
        {
            perror("msgsnd");
            exit(EXIT_FAILURE);
        }

        printf("Message sent. \n");
    }

    return 0;
}
