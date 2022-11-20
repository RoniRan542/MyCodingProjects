#include <stdio.h> /* for printf */
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <string.h> /* strcmp*/

void P1()
{
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    char *str = (char *)shmat(shmid, (void *)0, 0);
    printf("Write data: \n");
    scanf("%s", str);
    printf("Data written in memory: %s\n", str);
    shmdt(str);
}

void P2()
{
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    char *str = (char *)shmat(shmid, (void *)0, 0);
    printf("Data read from memory: %s\n", str);
    shmdt(str);
}

void P3()
{
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    char *str = (char *)shmat(shmid, (void *)0, 0);
    printf("Data read from memory: %s\n", str);
    shmdt(str);
}

void P4()
{
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    char *str = (char *)shmat(shmid, (void *)0, 0);
    printf("Data read from memory: %s\n", str);
    shmdt(str);
    shmctl(shmid, IPC_RMID, NULL);
}

int main(int argc, char **argv)
{

    if (0 == strcmp("1", argv[1]))
    {
        P1();
    }
    else if (0 == strcmp("2", argv[1]))
    {
        P2();
    }
    else if (0 == strcmp("3", argv[1]))
    {
        P3();
    }
    else if (0 == strcmp("4", argv[1]))
    {
        P4();
    }

    return 0;
}