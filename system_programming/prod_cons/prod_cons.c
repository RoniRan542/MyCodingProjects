/***************************
Author: Amir Topaz
Date: Jun 18, 2022
Reviewed by: none
***************************/

#include <pthread.h>   /* pthread API */
#include <stdatomic.h> /* atomic_int */
#include <stdio.h>     /* printf */
#include <assert.h>    /* assert.h */
#include <stdlib.h>    /* rand */
#include <semaphore.h> /* semaphore API */
#include <fcntl.h>     /* semaphore create flags */
#include <sys/stat.h>  /* semaphore permission modes */
#include <string.h>    /* strcpy */

#include "prod_cons.h" /* producer-consumer API */
#include "slinked.h"   /* singly linked list API */
#include "cbuffer.h"   /* circular buffer API */

enum status
{
    FAILURE = -1,
    SUCCESS
};

enum action
{
    READ = 1,
    WRITE = 2
};

#define LARGE_ARR (100)
#define MAGIC_NUMBER (10)

static void *ReadWrite(void *buffer);
static int InitListAndMutex(void);
static int ActivateThreadsMultAndMut(pthread_t *threadsies);
static int DestroyMultAndMut(pthread_t *threadsies);
static void *CreateNode(void *);
static void *RemoveNode(void *);
static int InitMultMutSem(void);
static int ActivateThreadsMultMutSem(pthread_t *threadsies);
static int DestroyMultMutSem(pthread_t *threadsies);
static void *RemoveNodeSem(void *index);
static void *CreateNodeSem(void *index);
static int InitFSQOneMutTwoSem(void);
static int ActivateFSQOneMutTwoSem(pthread_t *threadsies);
static int DestroyFSQOneMutTwoSem(pthread_t *threadsies);
static void *WriteToBuf(void *);
static void *ReadFromBuf(void *);
static int InitFSQTwoMutTwoSem(void);
static int ActivateFSQTwoMutTwoSem(pthread_t *threadsies);
static int DestroyFSQTwoMutTwoSem(pthread_t *threadsies);
static void *WriteToBufDoubleMut(void *write);
static void *ReadFromBufDoubleMut(void *read);
static int InitBarrier(void);
static int ActivateBarrier(pthread_t *threadsies);
static int DestroyBarrier(pthread_t *threadsies);
static void *WriteMessage(void *i);
static void *ReadMessage(void *i);

volatile atomic_int g_switch = WRITE;
pthread_mutex_t g_motex = {0};
pthread_mutex_t g_motex2 = {0};
pthread_cond_t g_cond_var = {0};

s_linked_list_t *g_list = NULL;
c_buffer_t *g_cbuffer = NULL;
sem_t g_semi1 = {0};
int g_shared1 = 0;
sem_t g_semi2 = {0};
int g_shared2 = 0;
char g_str[MAGIC_NUMBER] = "";
size_t g_counter = 0;

int main()
{
    size_t i = 0;

    /*  TwoThreadsNoMutex(); */
    /* MultipleAndMutex(); */
    /*MultipleMutSem(); */
    /*FSQOneMutTwoSem();*/
    /* FSQTwoMutTwoSem();*/

    UseBarrier();

    return 0;
}

/* Exercise 1 */
int TwoThreadsNoMutex(void)
{
    char buffer[LARGE_ARR] = "";
    pthread_t thready = 0;
    size_t i = 0;

    printf("write something and see it copied!\n");
    for (i = 0; i < MAGIC_NUMBER; ++i)
    {
        if (SUCCESS != pthread_create(&thready, NULL, &ReadWrite,
                                      (void *)buffer))
        {
            return FAILURE;
        }

        if (SUCCESS != pthread_join(thready, NULL))
        {
            return FAILURE;
        }
    }

    return SUCCESS;
}

static void *ReadWrite(void *buffer)
{
    char *buf = (char *)buffer;
    if (READ == g_switch)
    {
        printf("you wrote - %s\n", buf);
        g_switch = WRITE;
    }

    if (WRITE == g_switch)
    {
        scanf("%[^\n]%*c", buf);
        g_switch = READ;
    }

    return NULL;
}

/* Exercise 2 */
int MultipleAndMutex(void)
{
    pthread_t threadsies[MAGIC_NUMBER] = {0};

    if (SUCCESS != InitListAndMutex())
    {
        return FAILURE;
    }

    if (SUCCESS != ActivateThreadsMultAndMut(threadsies))
    {
        return FAILURE;
    }

    return DestroyMultAndMut(threadsies);
}

static int InitListAndMutex(void)
{
    g_list = SLinkedListCreate();

    if (NULL == g_list)
    {
        return FAILURE;
    }

    if (SUCCESS != pthread_mutex_init(&g_motex, NULL))
    {
        return FAILURE;
    }

    return SUCCESS;
}

static int ActivateThreadsMultAndMut(pthread_t *threadsies)
{
    size_t i = 0;

    assert(NULL != threadsies);

    for (i = 0; i < MAGIC_NUMBER / 2; ++i)
    {
        if (SUCCESS != pthread_create(threadsies + i, NULL, &CreateNode,
                                      (void *)i))
        {
            return FAILURE;
        }
    }

    for (i = MAGIC_NUMBER / 2; i < MAGIC_NUMBER; ++i)
    {
        if (SUCCESS != pthread_create(threadsies + i, NULL, &RemoveNode,
                                      (void *)i))
        {
            return FAILURE;
        }
    }

    return SUCCESS;
}

static int DestroyMultAndMut(pthread_t *threadsies)
{
    size_t i = 0;

    assert(NULL != threadsies);

    for (i = 0; i < MAGIC_NUMBER; ++i)
    {
        if (SUCCESS != pthread_join(threadsies[i], NULL))
        {
            return FAILURE;
        }
    }

    SLinkedListDestroy(g_list);
    g_list = NULL;

    return SUCCESS;
}

static void *CreateNode(void *index)
{
    (void)index;
    if (SUCCESS != pthread_mutex_lock(&g_motex))
    {
        return NULL;
    }

    SLinkedListInsertBefore(SLinkedListBegin(g_list), NULL);

    if (SUCCESS != pthread_mutex_unlock(&g_motex))
    {
        return NULL;
    }

    return NULL;
}

static void *RemoveNode(void *index)
{
    (void)index;
    if (SUCCESS != pthread_mutex_lock(&g_motex))
    {
        return NULL;
    }
    if ((!SLinkedListIsEmpty(g_list)))
    {
        SLinkedListRemove(SLinkedListBegin(g_list));
    }
    if (SUCCESS != pthread_mutex_unlock(&g_motex))
    {
        return NULL;
    }
    return NULL;
}

/*Exercise 3 */
int MultipleMutSem(void)
{
    pthread_t threadsies[MAGIC_NUMBER] = {0};

    if (SUCCESS != InitMultMutSem())
    {
        return FAILURE;
    }

    if (SUCCESS != ActivateThreadsMultMutSem(threadsies))
    {
        return FAILURE;
    }

    return DestroyMultMutSem(threadsies);
}

static int InitMultMutSem(void)
{
    if (SUCCESS != sem_init(&g_semi1, g_shared1, 0))
    {
        return FAILURE;
    }

    g_list = SLinkedListCreate();
    if (NULL == g_list)
    {
        return FAILURE;
    }

    if (SUCCESS != pthread_mutex_init(&g_motex, NULL))
    {
        return FAILURE;
    }

    return SUCCESS;
}

static int ActivateThreadsMultMutSem(pthread_t *threadsies)
{
    size_t i = 0;

    assert(NULL != threadsies);

    for (i = 0; i < MAGIC_NUMBER / 2; ++i)
    {
        if (SUCCESS != pthread_create(threadsies + i, NULL, &CreateNodeSem,
                                      (void *)i))
        {
            return FAILURE;
        }
    }

    for (i = MAGIC_NUMBER / 2; i < MAGIC_NUMBER; ++i)
    {
        if (SUCCESS != pthread_create(threadsies + i, NULL, &RemoveNodeSem,
                                      (void *)i))
        {
            return FAILURE;
        }
    }

    return SUCCESS;
}

static int DestroyMultMutSem(pthread_t *threadsies)
{
    size_t i = 0;

    assert(NULL != threadsies);

    for (i = 0; i < MAGIC_NUMBER; ++i)
    {
        if (SUCCESS != pthread_join(threadsies[i], NULL))
        {
            return FAILURE;
        }
    }

    SLinkedListDestroy(g_list);
    g_list = NULL;

    if (SUCCESS != sem_destroy(&g_semi1))
    {
        return FAILURE;
    }

    return SUCCESS;
}

static void *CreateNodeSem(void *index)
{
    (void)index;
    if (SUCCESS != sem_post(&g_semi1))
    {
        return NULL;
    }

    if (SUCCESS != pthread_mutex_lock(&g_motex))
    {
        return NULL;
    }

    SLinkedListInsertBefore(SLinkedListBegin(g_list), NULL);
    printf("insertion index %lu\n", (size_t)index);

    if (SUCCESS != pthread_mutex_unlock(&g_motex))
    {
        return NULL;
    }

    return NULL;
}

static void *RemoveNodeSem(void *index)
{
    (void)index;

    if (SUCCESS != sem_wait(&g_semi1))
    {
        return NULL;
    }

    if (SUCCESS != pthread_mutex_lock(&g_motex))
    {
        return NULL;
    }

    if (!SLinkedListIsEmpty(g_list))
    {
        SLinkedListRemove(SLinkedListBegin(g_list));
        printf("removal index %lu\n", (size_t)index);
    }

    if (SUCCESS != pthread_mutex_unlock(&g_motex))
    {
        return NULL;
    }

    return NULL;
}

/*Exercise 4 */
int FSQOneMutTwoSem(void)
{
    pthread_t threadsies[MAGIC_NUMBER] = {0};

    if (SUCCESS != InitFSQOneMutTwoSem())
    {
        return FAILURE;
    }

    if (SUCCESS != ActivateFSQOneMutTwoSem(threadsies))
    {
        return FAILURE;
    }

    return DestroyFSQOneMutTwoSem(threadsies);
}

static int InitFSQOneMutTwoSem(void)
{
    size_t capacity = MAGIC_NUMBER * 8;

    if (SUCCESS != sem_init(&g_semi1, g_shared1, 1))
    {
        return FAILURE;
    }

    if (SUCCESS != sem_init(&g_semi2, g_shared2, 0))
    {
        return FAILURE;
    }

    if (SUCCESS != pthread_mutex_init(&g_motex, NULL))
    {
        return FAILURE;
    }

    g_cbuffer = CBufferCreate(capacity);

    if (NULL == g_cbuffer)
    {
        return FAILURE;
    }

    return SUCCESS;
}

static int ActivateFSQOneMutTwoSem(pthread_t *threadsies)
{
    size_t read[MAGIC_NUMBER * 2] = {0};
    size_t i = 0;

    assert(NULL != threadsies);

    for (i = 0; i < MAGIC_NUMBER / 2; ++i)
    {
        if (SUCCESS != pthread_create(threadsies + i, NULL, &WriteToBuf,
                                      (void *)&i))
        {
            return FAILURE;
        }
    }
    for (i = MAGIC_NUMBER / 2; i < MAGIC_NUMBER; ++i)
    {
        if (SUCCESS != pthread_create(threadsies + i, NULL, &ReadFromBuf,
                                      (void *)(read + i - 5)))
        {
            return FAILURE;
        }
    }

    return SUCCESS;
}

static int DestroyFSQOneMutTwoSem(pthread_t *threadsies)
{
    size_t i = 0;

    assert(NULL != threadsies);

    for (i = 0; i < MAGIC_NUMBER; ++i)
    {
        if (SUCCESS != pthread_join(threadsies[i], NULL))
        {
            return FAILURE;
        }
    }

    CBufferDestroy(g_cbuffer);
    g_cbuffer = NULL;

    if (SUCCESS != sem_destroy(&g_semi1))
    {
        return FAILURE;
    }

    if (SUCCESS != sem_destroy(&g_semi2))
    {
        return FAILURE;
    }

    return SUCCESS;
}

static void *WriteToBuf(void *write)
{
    if (SUCCESS != sem_wait(&g_semi1))
    {
        return NULL;
    }
    if (SUCCESS != pthread_mutex_lock(&g_motex))
    {
        return NULL;
    }
    CBufferWrite(g_cbuffer, write, sizeof(int));/* הייתי מציע להכניס את הגודל של אינט למשתנה גלובלי */

    if (SUCCESS != pthread_mutex_unlock(&g_motex))
    {
        return NULL;
    }
    if (SUCCESS != sem_post(&g_semi2))
    {
        return NULL;
    }

    return NULL;
}

static void *ReadFromBuf(void *read)
{
    if (SUCCESS != sem_wait(&g_semi2))
    {
        return NULL;
    }

    CBufferRead(g_cbuffer, read, sizeof(int));

    if (SUCCESS != sem_post(&g_semi1))
    {
        return NULL;
    }

    return NULL;
}

/*Exercise 5 */
int FSQTwoMutTwoSem(void)
{
    pthread_t threadsies[MAGIC_NUMBER] = {0};

    if (SUCCESS != InitFSQTwoMutTwoSem())
    {
        return FAILURE;
    }

    if (SUCCESS != ActivateFSQTwoMutTwoSem(threadsies))
    {
        return FAILURE;
    }

    return DestroyFSQTwoMutTwoSem(threadsies);
}

static int InitFSQTwoMutTwoSem(void)
{
    size_t capacity = MAGIC_NUMBER * 8;
	/* put in array of sems and mutexes and then you can initialize them with a loop*/
    if (SUCCESS != sem_init(&g_semi1, g_shared1, 1))
    {
        return FAILURE;
    }

    if (SUCCESS != sem_init(&g_semi2, g_shared2, 1))
    {
        return FAILURE;
    }

    if (SUCCESS != pthread_mutex_init(&g_motex, NULL))
    {
        return FAILURE;
    }

    if (SUCCESS != pthread_mutex_init(&g_motex2, NULL))
    {
        return FAILURE;
    }

    g_cbuffer = CBufferCreate(capacity);
    if (NULL == g_cbuffer)
    {
        return FAILURE;
    }

    return SUCCESS;
}

static int ActivateFSQTwoMutTwoSem(pthread_t *threadsies)
{
    size_t i = 0;
    size_t read[MAGIC_NUMBER * 2] = {0};

    assert(NULL != threadsies);

    for (i = 0; i < MAGIC_NUMBER / 2; ++i)
    {
        if (SUCCESS != pthread_create(threadsies + i, NULL, &WriteToBufDoubleMut,
                                      (void *)&i))
        {
            return FAILURE;
        }
    }
    for (i = MAGIC_NUMBER / 2; i < MAGIC_NUMBER; ++i)
    {
        if (SUCCESS != pthread_create(threadsies + i, NULL, &ReadFromBufDoubleMut,
                                      (void *)(read + i - MAGIC_NUMBER / 2)))
        {
            return FAILURE;
        }
    }

    return SUCCESS;
}

static int DestroyFSQTwoMutTwoSem(pthread_t *threadsies)
{
    size_t i = 0;

    assert(NULL != threadsies);

    for (i = 0; i < MAGIC_NUMBER; ++i)
    {
        if (SUCCESS != pthread_join(threadsies[i], NULL))
        {
            return FAILURE;
        }
    }

    CBufferDestroy(g_cbuffer);
    g_cbuffer = NULL;

    if (SUCCESS != sem_destroy(&g_semi1))
    {
        return FAILURE;
    }

    if (SUCCESS != sem_destroy(&g_semi2))
    {
        return FAILURE;
    }

    return SUCCESS;
}

static void *WriteToBufDoubleMut(void *write)
{
    if (SUCCESS != sem_wait(&g_semi1))
    {
        return NULL;
    }
    if (SUCCESS != pthread_mutex_lock(&g_motex))
    {
        return NULL;
    }
    CBufferWrite(g_cbuffer, write, sizeof(int));

    if (SUCCESS != pthread_mutex_unlock(&g_motex))
    {
        return NULL;
    }
    if (SUCCESS != sem_post(&g_semi2))
    {
        return NULL;
    }

    return NULL;
}

static void *ReadFromBufDoubleMut(void *read)
{
    if (SUCCESS != sem_wait(&g_semi2))
    {
        return NULL;
    }

    if (SUCCESS != pthread_mutex_lock(&g_motex2))
    {
        return NULL;
    }

    CBufferRead(g_cbuffer, read, sizeof(int));

    if (SUCCESS != pthread_mutex_unlock(&g_motex2))
    {
        return NULL;
    }
    if (SUCCESS != sem_post(&g_semi1))
    {
        return NULL;
    }

    return NULL;
}

/*Exercise 6 */
int UseBarrier(void)
{
    pthread_t threadsies[10] = {0};

    if (SUCCESS != InitBarrier())
    {
        return FAILURE;
    }

    if (SUCCESS != ActivateBarrier(threadsies))
    {
        return FAILURE;
    }

    return DestroyBarrier(threadsies);
}

static int InitBarrier(void)
{
    if (SUCCESS != sem_init(&g_semi1, g_shared1, 0))
    {
        return FAILURE;
    }

    if (SUCCESS != pthread_mutex_init(&g_motex, NULL))
    {
        return FAILURE;
    }

    if (SUCCESS != pthread_cond_init(&g_cond_var, NULL))
    {
        return FAILURE;
    }

    return SUCCESS;
}

static int ActivateBarrier(pthread_t *threadsies)
{
    size_t i = 0;

    assert(NULL != threadsies);

    if (SUCCESS != pthread_create(threadsies, NULL, &WriteMessage, NULL))
    {
        return FAILURE;
    }

    for (i = 1; i < MAGIC_NUMBER + 1; ++i)
    {
        if (SUCCESS != pthread_create(threadsies + i, NULL, &ReadMessage, NULL))
        {
            return FAILURE;
        }
    }

    return SUCCESS;
}

static int DestroyBarrier(pthread_t *threadsies)
{
    size_t i = 0;

    assert(NULL != threadsies);

    for (i = 0; i < MAGIC_NUMBER + 1; ++i)
    {
        if (SUCCESS != pthread_join(threadsies[i], NULL))
        {
            return FAILURE;
        }
    }

    if (SUCCESS != pthread_cond_destroy(&g_cond_var))
    {
        return FAILURE;
    }

    if (SUCCESS != sem_destroy(&g_semi1))
    {
        return FAILURE;
    }

    return SUCCESS;
}

/*
producer:
sem_wait
lock
work()
broadcast
unlock

consumer:
lock
sem_post
cond_wait
unlock
work()
*/

static void *WriteMessage(void *index)
{
    size_t i = 0;

    char *beatles[10] = {"we", "all", "live", "in", "a", "yellow", "submarine",
                         "let", "it", "be"};
    (void)index;

    while (i < MAGIC_NUMBER)
    {
        if (SUCCESS != sem_wait(&g_semi1))
        {
            return NULL;
        }
        if (SUCCESS != pthread_mutex_lock(&g_motex))
        {
            return NULL;
        }

        strcpy(g_str, beatles[i]);
        ++i;

        if (SUCCESS != pthread_cond_broadcast(&g_cond_var))
        {
            return NULL;
        }

        if (SUCCESS != pthread_mutex_unlock(&g_motex))
        {
            return NULL;
        }
    }
    return NULL;
}

static void *ReadMessage(void *index)
{
    size_t i = 0;

    (void)index;

    while (i < MAGIC_NUMBER)
    {
        if (SUCCESS != pthread_mutex_lock(&g_motex))
        {
            return NULL;
        }
        ++g_counter;
        if (MAGIC_NUMBER == g_counter)
        {
            g_counter = 0;
            if (SUCCESS != sem_post(&g_semi1))
            {

                return NULL;
            }
        }

        if (SUCCESS != pthread_cond_wait(&g_cond_var, &g_motex))
        {
            return NULL;
        }

        printf("%s\n", g_str);
        ++i;

        if (SUCCESS != pthread_mutex_unlock(&g_motex))
        {
            return NULL;
        }
    }
    return NULL;
}
