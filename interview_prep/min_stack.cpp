// write a min stack – return min val in O(1)

#include <iostream>
#include <climits>
#include <exception>

using namespace std;

class stack
{
public:
    stack(int capacity) : m_the_stack(new int[capacity]), m_capacity(capacity), m_size(0)
    {
        // empty
    }
    void push(int val)
    {
        if (m_size == m_capacity)
        {
            throw std::runtime_error("error: stack is full\n");
        }
        if (m_size == 0)
        {
            m_the_stack[0] = val;
            m_size = 1;
        }
        else if (m_the_stack[m_size - 1] > val)
        {
            m_the_stack[m_size] = val;
            ++m_size;
        }
        else
        {

            RecInsertNewVal(val, m_size);
            ++m_size;
        }
    }
    void pop()
    {
        --m_size;
    }

    int peek() const
    {
        return m_the_stack[m_size - 1];
    }

    ~stack()
    {
        delete[] m_the_stack;
    }

private:
    int RecInsertNewVal(int val, int size);
    int *m_the_stack;
    int m_capacity;
    int m_size;
};

int stack::RecInsertNewVal(int val, int size)
{
    int temp = 0;

    if (size == 1)
    {
        if (m_the_stack[0] > val)
        {
            return val;
        }

        temp = m_the_stack[0];
        m_the_stack[0] = val;
        return temp;
    }

    int res = RecInsertNewVal(val, size - 1);
    if (size == m_size)
    {
        if (m_the_stack[size - 1] > res)
        {
            m_the_stack[size] = res;
            return INT_MIN;
        }
        else
        {
            m_the_stack[size] = m_the_stack[size - 1];
            m_the_stack[size - 1] = res;
            return INT_MIN;
        }
    }

    if (m_the_stack[size - 1] > res)
    {
        return res;
    }

    temp = m_the_stack[size - 1];
    m_the_stack[size - 1] = res;

    return temp;
}

int main()
{
    stack my_stack(10);
    my_stack.push(10);
    my_stack.push(3);
    my_stack.push(23);
    cout << my_stack.peek() << endl;
    my_stack.push(2);
    cout << my_stack.peek() << endl;

    my_stack.push(15);
    cout << my_stack.peek() << endl;

    my_stack.push(9);
    cout << my_stack.peek() << endl;

    my_stack.push(4);
    cout << my_stack.peek() << endl;

    return 0;
}