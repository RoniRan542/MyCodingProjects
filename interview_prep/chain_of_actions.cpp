#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <algorithm>
#include <unordered_map>

using namespace std;

class ChainHead
{
public:
    ChainHead() {}
    ChainHead(vector<float> vec) : m_vec(vec)
    {
        // empty
    }
    ChainHead(const ChainHead &) = delete;
    ChainHead(ChainHead &&) = delete;
    const ChainHead &operator=(const ChainHead &) = delete;
    const ChainHead &operator=(ChainHead &&) = delete;
    virtual void operator()() = 0;
    virtual vector<float> GetVector() const
    {
        return m_vec;
    }

    void SetVector(vector<float> vec)
    {
        m_vec = vec;
    }

    void Print(vector<float> vec)
    {
        for (size_t i = 0; i < vec.size(); ++i)
        {
            cout << vec[i] << " ";
        }
        cout << "\n";
    }

    virtual ~ChainHead(){};

private:
    vector<float> m_vec;
};

class A : public ChainHead
{
public:
    A() {}
    A(vector<float> vec) : m_self_vec(vec)
    {
        SetVector(m_self_vec);
    }
    virtual void operator()()
    {
        sort(m_self_vec.begin(), m_self_vec.end());
    }
    vector<float> GetVector() const
    {
        return m_self_vec;
    }

private:
    vector<float> m_self_vec;
};

class B : public ChainHead
{
public:
    B() {}
    B(vector<float> vec) : m_self_vec(vec)
    {
        SetVector(m_self_vec);
    }
    virtual void operator()()
    {
        for_each(m_self_vec.begin(), m_self_vec.end(), [](float &num)
                 { num = pow(num, 2); });
    }
    vector<float> GetVector() const
    {
        return m_self_vec;
    }

private:
    vector<float> m_self_vec;
};

class C : public ChainHead
{
public:
    C() {}
    C(vector<float> vec) : m_self_vec(vec)
    {
        SetVector(m_self_vec);
    }
    virtual void operator()()
    {
        for_each(m_self_vec.begin(), m_self_vec.end(), [](float &num)
                 { num = sqrt(num); });
    }
    vector<float> GetVector() const
    {
        return m_self_vec;
    }

private:
    vector<float> m_self_vec;
};

class D : public ChainHead
{
public:
    D() {}
    D(vector<float> vec) : m_self_vec(vec)
    {
        SetVector(m_self_vec);
    }
    virtual void operator()()
    {
        for_each(m_self_vec.begin(), m_self_vec.end(), [](float &num)
                 { num += 7; });
    }
    vector<float> GetVector() const
    {
        return m_self_vec;
    }

private:
    vector<float> m_self_vec;
};

class E : public ChainHead
{
public:
    E() {}
    E(vector<float> vec) : m_self_vec(vec)
    {
        SetVector(m_self_vec);
    }
    virtual void operator()()
    {
        float diff = 0;
        for (size_t i = 1; i < m_self_vec.size(); ++i)
        {
            diff = m_self_vec[i] - m_self_vec[i - 1];
            m_self_vec[i - 1] = diff;
        }
        m_self_vec.pop_back();
    }
    vector<float> GetVector() const
    {
        return m_self_vec;
    }

private:
    vector<float> m_self_vec;
};

class Factory
{
public:
    Factory();
    ChainHead *CreateNode(const std::string);
    void AddObjectCreate(const std::string, ChainHead *(*)(vector<float>));
    ~Factory();

private:
    unordered_map<string, ChainHead *(*)(vector<float>)> creation_map;
};

int main()
{

    vector<float> vec = {9, 2, 7, 4, 5, 6};
    A a(vec);
    a();
    a.Print(a.GetVector());
    B b(a.GetVector());
    b();
    b.Print(b.GetVector());
    C c(b.GetVector());
    c();
    c.Print(c.GetVector());
    D d(c.GetVector());
    d();
    d.Print(d.GetVector());
    E e(d.GetVector());
    e();
    e.Print(e.GetVector());

    return 0;
}