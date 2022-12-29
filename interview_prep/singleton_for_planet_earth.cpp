#include <iostream>
#include <mutex>
#include <boost/core/noncopyable.hpp>

using namespace std;

class planet_earth
{
public:
    void Print()
    {
        cout << "planet_earth" << endl;
    }

private:
    friend class Singleton;
    planet_earth()
    {
        // empty
    }
};

class Singleton : private boost::noncopyable
{
public:
    static planet_earth *GetInstance()
    {
        std::lock_guard<mutex> lock(m_mutex);
        if (true == m_is_destroyed)
        {
            abort();
        }
        if (m_instance == nullptr)
        {
            m_instance = new planet_earth;
            atexit(DestroyInstance);
        }

        return m_instance;
    }

    static void DestroyInstance()
    {
        std::lock_guard<mutex> lock(m_mutex);
        delete m_instance;
        m_instance = nullptr;
        m_is_destroyed = true;
    }

private:
    Singleton();
    static bool m_is_destroyed;
    static planet_earth *m_instance;
    static mutex m_mutex;
};

bool Singleton::m_is_destroyed = false;
planet_earth *Singleton::m_instance = nullptr;
mutex Singleton::m_mutex;

int main()
{
    Singleton::GetInstance()->Print();
    Singleton::DestroyInstance();
    // Singleton::GetInstance()->Print();

    return 0;
}
