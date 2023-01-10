/*
how to implement – diff version – semphores / locks etc
 */

#include <iostream>
#include <mutex>
#include <chrono>
#include <semaphore>
#include <semaphore.h>
#include <thread>

using namespace std;

static char g_char_array[100] = {0};
static int g_int_array[100] = {0};
static mutex mu1;
static mutex mu2;
sem_t sem_full;
sem_t sem_empty;
sem_t sem_mutex;

void produce(int num, size_t index)
{
    sem_wait(&sem_empty);
    sem_wait(&sem_mutex);
    g_int_array[index] = num;
    sem_post(&sem_mutex);
    sem_post(&sem_full);
}

void consume(size_t index)
{
    sem_wait(&sem_full);
    sem_wait(&sem_mutex);
    cout << g_int_array[index] << " \n";
    sem_post(&sem_mutex);
    sem_post(&sem_empty);
}

int main()
{
    thread producers[100];
    thread consumers[100];

    sem_init(&sem_empty, 0, 100);
    sem_init(&sem_full, 0, 0);
    sem_init(&sem_mutex, 0, 1);

    for (size_t i = 0; i < 100; i++)
    {
        producers[i] = thread(produce, (int)i, i);
    }

    for (size_t i = 0; i < 100; i++)
    {
        consumers[i] = thread(consume, i);
    }

    for (size_t i = 0; i < 100; i++)
    {
        producers[i].join();
        consumers[i].join();
    }

    return 0;
}
