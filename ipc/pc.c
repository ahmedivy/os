#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

// Define the message structure
struct my_message
{
    long mtype;      // Message type
    char mtext[256]; // Message content
};

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <message_type>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Convert command line argument to message type
    long message_type = atol(argv[1]);

    // Create or get the message queue with key 555
    key_t key = 555;
    int msgid = msgget(key, IPC_CREAT | 0666);
    if (msgid == -1)
    {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    if (message_type < 1)
    {
        fprintf(stderr, "Message type must be greater than 0\n");
        exit(EXIT_FAILURE);
    }

    // Producer
    if (fork() == 0)
    {
        // Generate message
        struct my_message msg;
        msg.mtype = message_type;
        snprintf(msg.mtext, sizeof(msg.mtext), "I am producer process and my proc id is %ld", (long)getpid());

        // Send message to the queue
        msgsnd(msgid, &msg, sizeof(struct my_message) - sizeof(long), 0);

        printf("Producer process (%ld) produced a message of type %ld\n", (long)getpid(), message_type);

        exit(EXIT_SUCCESS);
    }

    // Consumer
    if (fork() == 0)
    {
        sleep(1); // Wait for the producer to finish

        // Receive message from the queue with the specified type
        struct my_message msg;
        msgrcv(msgid, &msg, sizeof(struct my_message) - sizeof(long), message_type, 0);

        // Display message content
        printf("Message read from msg queue is\n%s\n", msg.mtext);

        exit(EXIT_SUCCESS);
    }

    // Wait for both processes to finish
    wait(NULL);
    wait(NULL);

    // Display the current state of the message queue
    struct msqid_ds buf;
    msgctl(msgid, IPC_STAT, &buf);

    printf("The current state of the message queue is as follows:\n");
    printf("PID of the last proc that wrote a message: %d\n", buf.msg_lspid);
    printf("PID of the last proc that read a message: %d\n", buf.msg_lrpid);
    printf("Current number of bytes on queue: %ld\n", (long)buf.__msg_cbytes);
    printf("Current number of messages on queue: %ld\n", (long)buf.msg_qnum);

    // Remove the message queue
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}
