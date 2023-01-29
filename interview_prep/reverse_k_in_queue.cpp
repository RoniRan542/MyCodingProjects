#include <iostream>
#include <queue>
#include <stack>

using namespace std;

queue<int> reverseKInQueue(queue<int> q, size_t k)
{

    vector<int> temp(q.size());
    queue<int> retval;
    size_t i = 1;

    while (i <= k)
    {
        temp[k - i] = q.front();
        q.pop();
        ++i;
    }

    while (!q.empty())
    {
        temp[i - 1] = q.front();
        ++i;
        q.pop();
    }

    for (i = 0; i < temp.size(); ++i)
    {
        retval.push(temp[i]);
    }

    return retval;
}

queue<int> reverseKInQueue2(queue<int> q, size_t k)
{

    stack<int> temp;
    queue<int> retval;
    size_t i = 0;

    while (i < k)
    {
        temp.push(q.front());
        q.pop();
        ++i;
    }

    while (!temp.empty())
    {
        int data = temp.top();
        q.push(data);
        temp.pop();
    }

    for (i = 0; i < (q.size() - k); ++i)
    {
        q.push(q.front());
        q.pop();
    }

    return q;
}

int main()
{
    queue<int> myq;
    myq.push(0);
    myq.push(1);
    myq.push(2);
    myq.push(3);
    myq.push(4);
    myq.push(5);

    /* while (!myq.empty())
    {
        cout << myq.front() << endl;
        myq.pop();
    }
 */
    queue<int> retval = reverseKInQueue2(myq, 2);

    while (!retval.empty())
    {
        cout << retval.front() << endl;
        retval.pop();
    }

    return 0;
}
