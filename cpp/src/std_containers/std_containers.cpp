
#include <iostream> // cin, cout, get_line, string
#include <queue>    // queue
#include <map>      // map

#include "std_containers.hpp"

using namespace std;

namespace ilrd
{
    static void Print(queue<string> &queue, map<string, size_t> &map);

    void StdHisto()
    {
        string input;
        queue<string> str_queue;
        map<string, size_t> map;

        getline(cin, input);
        while (0 != input.compare("."))
        {
            if (map.find(input) == map.end())
            {
                str_queue.push(input);
                map.insert(pair<string, size_t>(input, 1));
            }
            else
            {
                ++map.at(input);
            }
            getline(cin, input);
        }

        Print(str_queue, map);
    }

    static void Print(queue<string> &queue, const map<string, size_t> &map)
    {
        while (1 != queue.empty())
        {
            if (map.at(queue.front()) > 1)
            {
                cout << map.at(queue.front()) << " x ";
            }

            cout << queue.front() << "\n";
            queue.pop();
        }
    }
}
