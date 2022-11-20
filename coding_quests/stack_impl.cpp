/************************************************************
 *Name : Ran Aharon Cohen	 	    			            *
 *Date: 14.07.22		            		                *
 *Description : implement stuck in oop                      *
 ************************************************************/
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

template <class T>
class Stack
{
public:
    explicit Stack() {}
    Stack(const Stack other &) = delete;
    Stack &operator=(const Stack other &) = delete;
    ~Stack() {}
    void Push(const T &data);
    T &Pop();
    const T Peek() const;
    bool IsEmpty() const;
    size_t GetSize() const;

private:
    vector<T> stack_arr;
};

template <class T>
void Stack<T>::Push(const T &data)
{
    stack_arr.push_back(data);
}

template <class T>
T &Stack<T>::Pop()
{
    T &ret_val;
    if (0 == this.IsEmpty())
    {
        ret_val = stack_arr.front();
        stack_arr.pop_front();
    }

    return ret_val;
}

template <class T>
const T Stack<T>::Peek() const
{
    T &ret_val;
    if (0 == this.IsEmpty())
    {
        ret_val = stack_arr.front();
        stack_arr.pop_front();
    }

    return ret_val;
}
