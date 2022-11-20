#include <iostream>

#include "shared_ptr.hpp"

using namespace std;
using namespace ilrd;

int main()
{
    int *num_ptr = new int(14);

    SharedPtr<int> st1(num_ptr);
    /* int temp = *st1; */
    cout << *st1 << endl;
    SharedPtr<int> st2(st1);
    cout << st1.GetPtr() << endl;
    cout << st2.GetPtr() << endl;
    SharedPtr<int> st3(new int(555));
    cout << *GetRefCount(st3) << endl;
    st2 = st3;
    cout << *st2.GetPtr() << endl;
    cout << st2.GetPtr() << endl;
    cout << st3.GetPtr() << endl;
    cout << *GetRefCount(st3) << endl;
    cout << *GetRefCount(st2) << endl;
    cout << *GetRefCount(st1) << endl;
    cout << (st1 == st2) << endl;
    cout << (st3 == st2) << endl;
    cout << (st1 != st2) << endl;

    return 0;
}