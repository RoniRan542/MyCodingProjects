/**********************************************************************
 *Name : Ran Aharon Cohen	 	    			                      *
 *Date: 14.07.22		            		                          *
 *Description : You have many readers and writers. You want to        *
 enable many readers in parallel but only one writer at the same time.*
 Imlement class SyncWriteRead to syncronize the threads               *
 **********************************************************************/
#include <iostream>
#include <mutex>
#include <thread>
#include <atomic>

std::string g_resource;
int g_counter;

class SyncWriteRead
{
public:
    SyncWriteRead(int max_readers = 10);
    void StartWrite();
    void StopWrite();
    void StartRead();
    void StopRead();

private:
    int m_max_readers;
    std::mutex m_mtx;
    std::atomic<int> m_count;
};

SyncWriteRead::SyncWriteRead(int max_readers) : m_max_readers(max_readers), m_count(0)
{
    // empty
}

void SyncWriteRead::StartWrite()
{
    m_mtx.lock();
    while (m_count > 0)
    {
    }
}

void SyncWriteRead::StopWrite()
{
    m_mtx.unlock();
}

void SyncWriteRead::StartRead()
{
    while (m_count > m_max_readers)
    {
    }
    m_mtx.lock();
    m_mtx.unlock();

    ++m_count;
}

void SyncWriteRead::StopRead()
{
    --m_count;
}

static void Write(SyncWriteRead *swr)
{
    swr->StartWrite();
    g_resource = std::to_string(g_counter);
    ++g_counter;
    swr->StopWrite();
}

static void Read(SyncWriteRead *swr)
{
    swr->StartRead();
    std::cout << g_resource << std::endl;
    swr->StopRead();
}

int main()
{
    size_t readers_size = 150;
    size_t writers_size = 10;
    g_counter = 0;
    size_t curr_thread = 0;
    SyncWriteRead *swr = new SyncWriteRead(5);
    std::thread writers[10];
    std::thread readers[150];

    std::cout << "Writing start\n";

    for (size_t i = 0; i < writers_size; i++)
    {

        writers[i] = std::thread(Write, swr);
        for (size_t i = curr_thread; i < (curr_thread + 15); i++)
        {
            readers[i] = std::thread(Read, swr);
        }

        curr_thread += 15;
    }

    for (size_t i = 0; i < writers_size; i++)
    {
        writers[i].join();
    }

    for (size_t i = 0; i < readers_size; i++)
    {
        readers[i].join();
    }
    std::cout << "The end\n";

    return 0;
}