#include <iostream>

using namespace std;
class A
{
public:
    int data[2];
    A(int x, int y)
    {
        data[0] = x;
        data[1] = y;
    };
    virtual void print() { cout << "A\n"; }
    int operator[](int index)
    {
        return data[index];
    }
    int *Getdata() { return data; }
    void Setdata(int x, int index)
    {
        data[index] = x;
    }
};

int main()
{

    A a(22, 55);
    A b(11, 99);
    a.print();
    cout << sizeof(A) << endl;
    cout << sizeof(a) << endl;
    cout << a[1] << endl;
    cout << a[2] << endl;
    cout << a[3] << endl;
    cout << a[4] << endl;
    cout << a[5] << endl;
    cout << a[6] << endl;
    int *data = a.Getdata();
    int *data2 = b.Getdata();
    // a.Setdata(100, 2);
    cout << &b << endl;
    cout << &a << endl;

    return 0;
}