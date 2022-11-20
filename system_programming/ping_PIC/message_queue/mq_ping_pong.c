#include <stdio.h> /* for printf */
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#define MAX 10

enum status
{
    FAIL = -1,
    SUCCESS = 0,
    EQUAL = 0,
    FAILURE
};

struct mesg_buffer
{
    long mesg_type;
    char mesg_text[100];
} message;

void P1(int msgid)
{

    printf("Write Data : ");
    fgets(message.mesg_text, MAX, stdin);
    msgsnd(msgid, &message, sizeof(message), 0);
    msgsnd(msgid, &message, sizeof(message), 0);
    msgsnd(msgid, &message, sizeof(message), 0);
}

void P2(int msgid)
{

    msgrcv(msgid, &message, sizeof(message), 1, 0);
    printf("P2 Data Received is : %s \n",
           message.mesg_text);
}

void P3(int msgid)
{
    msgrcv(msgid, &message, sizeof(message), 1, 0);
    printf("P3 Data Received is : %s \n",
           message.mesg_text);
}

void P4(int msgid)
{
    msgrcv(msgid, &message, sizeof(message), 1, 0);
    printf("P4 Data Received is : %s \n",
           message.mesg_text);
}

int main(int argc, char *argv[])
{
    key_t key = ftok("key.txt", 65);
    int msgid = msgget(key, 0666 | IPC_CREAT);
    message.mesg_type = 1;

    if (0 == strcmp("P1", argv[1]))
    {
        P1(msgid);
    }
    else if (0 == strcmp("P2", argv[1]))
    {
        P2(msgid);
    }
    else if (0 == strcmp("P3", argv[1]))
    {
        P3(msgid);
    }
    else if (0 == strcmp("P4", argv[1]))
    {
        P4(msgid);
        msgctl(msgid, IPC_RMID, NULL);
    }

    return SUCCESS;
}