/*************************************************
 *Name : Ran Aharon Cohen	 	    			 *
 *Date: 	14.10.22		            		 *
 *Description :implement a thread-safe factory   *
 *************************************************/

#include <exception>
#include <unordered_map>
#include <mutex>
#include "/home/rani/git/cpp/src/singleton/singleton.hpp"

template <class T, class Key, class Args>
class SafeFactory
{
public:
    void Add(const Key &key, T *(*creator)(const Args &));
    T *Create(const Key &key, const Args &args) const;

private:
    SafeFactory();
    friend class Singleton;
    std::unordered_map<Key, T *(*)(const Args &)> m_creation_funcs;
    std::mutex m_mutex;
};

template <class T, class Key, class Args>
void SafeFactory<T, Key, Args>::Add(const Key &key, T *(*creator)(const Args &))
{
    m_mutex.lock();
    if (m_creation_funcs.find(key) != m_creation_funcs.end())
    {
        throw std::runtime_error("key alerady exist\n");
    }

    m_creation_funcs[key] = creator;
    m_mutex.unlock();
}

template <class T, class Key, class Args>
T *SafeFactory<T, Key, Args>::Create(const Key &key, const Args &args) const
{
    m_mutex.lock();
    if (m_creation_funcs.find(key) == m_creation_funcs.end())
    {
        throw std::runtime_error("key not found\n");
    }

    T *ptr_new = m_creation_funcs.at(key)(args);
    m_mutex.unlock();

    return ptr_new;
}
