// author: Ran Roni Cohen
// reviewer: Jenudi
// date: 09.09.22

#include <queue>
#include <thread>
#include <iostream>
#include <chrono> //chrono::seconds /milli
#include <vector>
#include "waitable_queue.hpp"

using namespace ilrd;
using namespace std;
int index_pop = 0;
int write(Waitable_Queue<int, std::queue<int>> &queue)
{
    static atomic_int count;

    queue.Push(count);
    std::mutex mu;
    mu.lock();
    count++;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    mu.unlock();

    return 0;
}

int read(Waitable_Queue<int, std::queue<int>> &queue, int *results)
{
    queue.Pop(results[index_pop]);

    std::mutex mu;
    mu.lock();
    ++index_pop;
    mu.unlock();

    return 0;
}

int read_with_timeout(Waitable_Queue<int, std::queue<int>> &queue, int *results)
{
    std::chrono::milliseconds millitime(100);
    queue.Pop(results[index_pop], millitime);

    std::mutex mu;
    mu.lock();
    ++index_pop;
    mu.unlock();

    return 0;
}

int main()
{
    std::thread threads[6];
    int results[3] = {0};
    Waitable_Queue<int, std::queue<int>> my_queue;
    cout << "is empty: " << my_queue.IsEmpty() << endl;

    for (size_t i = 0; i < 6; ++i)
    {
        if ((i % 2) == 0)
        {
            threads[i] = std::thread(write, std::ref(my_queue));
        }
        else
        {
            threads[i] = std::thread(read, std::ref(my_queue), std::ref(results));
        }
    }

    for (size_t i = 0; i < 6; i++)
    {
        threads[i].join();
    }

    for (size_t i = 0; i < 3; i++)
    {
        cout << results[i] << endl;
    }

    return 0;
}
